#!/usr/bin/env bash

#  (The MIT License)
#
#  Copyright (c) 2018 - 2019 Mohammad S. Babaei
#  Copyright (c) 2018 - 2019 Seditious Games Studio
#
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included in all
#  copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#  SOFTWARE.


set -e

BOOST_GIT_CLONE_URL="https://github.com/boostorg/boost.git"
BOOST_VERSION_MAJOR=1
BOOST_VERSION_MINOR=70
BOOST_VERSION_PATCH=0

ZLIB_GIT_CLONE_URL="https://github.com/madler/zlib.git"
ZLIB_GIT_TAG_TO_BUILD="v1.2.11"

GIT_CLONE_NUMBER_OF_JOBS=16
BOOST_BUILD_NUMBER_OF_JOBS=17

BOOST_GIT_TAG_TO_BUILD="boost-${BOOST_VERSION_MAJOR}.${BOOST_VERSION_MINOR}.${BOOST_VERSION_PATCH}"
BOOST_SOURCE_DIRECTORY_NAME="god-thirdparty-boost"
BOOST_STAGE_DIRECTORY_NAME="god-thirdparty-boost-stage"
ZLIB_SOURCE_DIRECTORY_NAME="zlib"

TARGET_INCLUDE_DIRECTORY_NAME="boost"

SCRIPTS_DIRECTORY=$(dirname $(realpath "$0"))
BUILD_TOOLCHAIN_SETUP="${SCRIPTS_DIRECTORY}/thirdparty-setup-build-environment.sh"
source "${BUILD_TOOLCHAIN_SETUP}"

BUILD_USER_CONFIG_JAM_FILE="${GOD_THIRDPARTY_DIRECTORY}/toolchains/boost-user-config.jam"

BOOST_SOURCE_DIRECTORY="${GOD_TEMP_DIRECTORY}/${BOOST_SOURCE_DIRECTORY_NAME}"
BOOST_BUILD_PATH="${BOOST_SOURCE_DIRECTORY}/tools/build/src"
BOOST_STAGE_DIRECTORY="${GOD_TEMP_DIRECTORY}/${BOOST_STAGE_DIRECTORY_NAME}"
BOOST_STAGE_INCLUDE_DIRECTORY="${BOOST_STAGE_DIRECTORY}/include"
BOOST_STAGE_LIB_DIRECTORY="${BOOST_STAGE_DIRECTORY}/lib"
ZLIB_SOURCE_DIRECTORY="${GOD_TEMP_DIRECTORY}/${ZLIB_SOURCE_DIRECTORY_NAME}"

rm -rf "${BOOST_SOURCE_DIRECTORY}" \
    && rm -rf "${BOOST_STAGE_DIRECTORY}" \
    && rm -rf "${ZLIB_SOURCE_DIRECTORY}" \
    && git clone -b ${ZLIB_GIT_TAG_TO_BUILD} --single-branch --depth 1 \
        ${ZLIB_GIT_CLONE_URL} "${ZLIB_SOURCE_DIRECTORY}" \
    && git clone -b ${BOOST_GIT_TAG_TO_BUILD} --single-branch --depth 1 \
        --recursive --shallow-submodules --jobs ${GIT_CLONE_NUMBER_OF_JOBS} \
        ${BOOST_GIT_CLONE_URL} "${BOOST_SOURCE_DIRECTORY}" \
    && mkdir -p "${BOOST_BUILD_PATH}" \
    && cp -vr "${BUILD_USER_CONFIG_JAM_FILE}" \
        "${BOOST_BUILD_PATH}/user-config.jam" \
    && cd "${BOOST_SOURCE_DIRECTORY}" \
    && ./bootstrap.sh --with-toolset=clang \
        --prefix="${BOOST_STAGE_DIRECTORY}" \
    && ./b2 --ignore-site-config \
        toolset=clang \
        optimization=space \
        address-model=64 \
        architecture=x86 \
        threading=multi \
        link=static \
        runtime-link=shared \
        --layout=versioned \
        --build-type=complete \
        --build-dir="./build" \
        --prefix="${BOOST_STAGE_DIRECTORY}" \
        --includedir="${BOOST_STAGE_INCLUDE_DIRECTORY}" \
        --without-mpi \
        --without-python \
        -sZLIB_SOURCE="${ZLIB_SOURCE_DIRECTORY}" \
        -j 17 \
        install \
    && mkdir -p "${GOD_THIRDPARTY_INCLUDE_DIRECTORY}" \
    && mkdir -p "${GOD_THIRDPARTY_LIB_DEBUG_DIRECTORY}" \
    && mkdir -p "${GOD_THIRDPARTY_LIB_RELEASE_DIRECTORY}" \
    && rm -rf "${GOD_THIRDPARTY_INCLUDE_DIRECTORY}/boost" \
        "${GOD_THIRDPARTY_LIB_DEBUG_DIRECTORY}/"libboost_*mt-d-x64*.* \
        "${GOD_THIRDPARTY_LIB_RELEASE_DIRECTORY}/"libboost_*mt-x64*.* \
    && cp -vr \
        "${BOOST_STAGE_INCLUDE_DIRECTORY}/boost-${BOOST_VERSION_MAJOR}_${BOOST_VERSION_MINOR}/boost" \
        "${GOD_THIRDPARTY_INCLUDE_TARGET_DIRECTORY}" \
    && cp -vr "${BOOST_STAGE_LIB_DIRECTORY}/"libboost_*mt-d-x64*.* \
        "${GOD_THIRDPARTY_LIB_DEBUG_DIRECTORY}" \
    && cp -vr "${BOOST_STAGE_LIB_DIRECTORY}/"libboost_*mt-x64*.* \
        "${GOD_THIRDPARTY_LIB_RELEASE_DIRECTORY}" \
    && rm -rf "${BOOST_STAGE_DIRECTORY}"\
        "${BOOST_SOURCE_DIRECTORY}" \
        "${ZLIB_SOURCE_DIRECTORY}"