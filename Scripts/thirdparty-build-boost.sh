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


BOOST_GIT_CLONE_URL="https://github.com/boostorg/boost.git"
BOOST_VERSION_MAJOR=1
BOOST_VERSION_MINOR=70
BOOST_VERSION_PATCH=0
BOOST_GIT_TAG_TO_BUILD="boost-${BOOST_VERSION_MAJOR}.${BOOST_VERSION_MINOR}.${BOOST_VERSION_PATCH}"
BOOST_SOURCE_DIRECTORY_NAME="boost"
BOOST_STAGE_DIRECTORY_NAME="boost-stage"
ZLIB_GIT_CLONE_URL="https://github.com/madler/zlib.git"
ZLIB_GIT_TAG_TO_BUILD="v1.2.11"
ZLIB_SOURCE_DIRECTORY_NAME="zlib"
TEMP_DIRECTORY="/tmp"
GIT_CLONE_NUMBER_OF_JOBS=16
BOOST_BUILD_NUMBER_OF_JOBS=17

TARGET_INCLUDE_DIRECTORY_NAME="boost"

BOOST_SOURCE_DIRECTORY="${TEMP_DIRECTORY}/${BOOST_SOURCE_DIRECTORY_NAME}"
BOOST_BUILD_PATH="${BOOST_SOURCE_DIRECTORY}/tools/build/src"
BOOST_STAGE_DIRECTORY="${TEMP_DIRECTORY}/${BOOST_STAGE_DIRECTORY_NAME}"
BOOST_STAGE_INCLUDE_DIRECTORY="${BOOST_STAGE_DIRECTORY}/include"
BOOST_STAGE_LIB_DIRECTORY="${BOOST_STAGE_DIRECTORY}/lib"
ZLIB_SOURCE_DIRECTORY="${TEMP_DIRECTORY}/${ZLIB_SOURCE_DIRECTORY_NAME}"

PROJECT_DIRECTORY=`dirname $(dirname $(realpath "$0"))`
THIRDPARTY_DIRECTORY="${PROJECT_DIRECTORY}/ThirdParty"
BUILD_TOOLCHAIN_SETUP="${PROJECT_DIRECTORY}/Scripts/thirdparty-build-toochain-setup.sh"
BUILD_USER_CONFIG_JAM_FILE="${THIRDPARTY_DIRECTORY}/toolchains/boost-user-config.jam"
THIRDPARTY_INCLUDE_DIRECTORY="${THIRDPARTY_DIRECTORY}/include"
THIRDPARTY_INCLUDE_TARGET_DIRECTORY="${THIRDPARTY_INCLUDE_DIRECTORY}/${TARGET_INCLUDE_DIRECTORY_NAME}"
THIRDPARTY_LIB_DEBUG_DIRECTORY="${THIRDPARTY_DIRECTORY}/lib/linux/debug"
THIRDPARTY_LIB_RELEASE_DIRECTORY="${THIRDPARTY_DIRECTORY}/lib/linux/release"

source "${BUILD_TOOLCHAIN_SETUP}" \
    && rm -rf "${BOOST_SOURCE_DIRECTORY}" \
    && rm -rf "${BOOST_STAGE_DIRECTORY}" \
    && rm -rf "${ZLIB_SOURCE_DIRECTORY}" \
    && git clone -b ${ZLIB_GIT_TAG_TO_BUILD} --single-branch --depth 1 \
        ${ZLIB_GIT_CLONE_URL} "${ZLIB_SOURCE_DIRECTORY}" \
    && git clone -b ${BOOST_GIT_TAG_TO_BUILD} --single-branch --depth 1 \
        ${BOOST_GIT_CLONE_URL} "${BOOST_SOURCE_DIRECTORY}" \
        --recursive --shallow-submodules --jobs ${GIT_CLONE_NUMBER_OF_JOBS} \
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
    && rm -rf "${THIRDPARTY_INCLUDE_DIRECTORY}/boost" \
        "${THIRDPARTY_LIB_DEBUG_DIRECTORY}/"libboost_*mt-d-x64*.* \
        "${THIRDPARTY_LIB_RELEASE_DIRECTORY}/"libboost_*mt-x64*.* \
    && cp -vr \
        "${BOOST_STAGE_INCLUDE_DIRECTORY}/boost-${BOOST_VERSION_MAJOR}_${BOOST_VERSION_MINOR}/boost" \
        "${THIRDPARTY_INCLUDE_TARGET_DIRECTORY}" \
    && cp -vr "${BOOST_STAGE_LIB_DIRECTORY}/"libboost_*mt-d-x64*.* \
        "${THIRDPARTY_LIB_DEBUG_DIRECTORY}" \
    && cp -vr "${BOOST_STAGE_LIB_DIRECTORY}/"libboost_*mt-x64*.* \
        "${THIRDPARTY_LIB_RELEASE_DIRECTORY}" \
    && rm -rf "${BOOST_STAGE_DIRECTORY}"\
        "${BOOST_SOURCE_DIRECTORY}" \
        "${ZLIB_SOURCE_DIRECTORY}"
