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


GIT_CLONE_URL="https://github.com/weidai11/cryptopp.git"
GIT_TAG_TO_BUILD="CRYPTOPP_8_2_0"

TARGET_INCLUDE_DIRECTORY_NAME="cryptopp"
declare -a DEBUG_LIBRARIES=( "libcryptopp.a" )
declare -a RELEASE_LIBRARIES=( "libcryptopp.a" )

SCRIPTS_DIRECTORY=$(dirname $(realpath "$0"))
BUILD_TOOLCHAIN_SETUP="${SCRIPTS_DIRECTORY}/thirdparty-setup-build-environment.sh"
source "${BUILD_TOOLCHAIN_SETUP}"

BUILD_CMAKE_LISTS="${GOD_THIRDPARTY_TOOLCHAIN_DIRECTORY}/cryptopp-CMakeLists.txt"
SOURCE_DIRECTORY_NAME="${GOD_THIRDPARTY_BUILD_DIRECTORY_PREFIX}-cryptopp"
SOURCE_DIRECTORY="${GOD_TEMP_DIRECTORY}/${SOURCE_DIRECTORY_NAME}"
DEBUG_BUILD_DIRECTORY_NAME="build-debug"
DEBUG_BUILD_DIRECTORY="${SOURCE_DIRECTORY}/${DEBUG_BUILD_DIRECTORY_NAME}"
RELEASE_BUILD_DIRECTORY_NAME="build-release"
RELEASE_BUILD_DIRECTORY="${SOURCE_DIRECTORY}/${RELEASE_BUILD_DIRECTORY_NAME}"
THIRDPARTY_INCLUDE_TARGET_DIRECTORY="${GOD_THIRDPARTY_INCLUDE_DIRECTORY}/${TARGET_INCLUDE_DIRECTORY_NAME}"

source "${BUILD_TOOLCHAIN_SETUP}" \
    && rm -rf "${SOURCE_DIRECTORY}" \
    && git clone -b ${GIT_TAG_TO_BUILD} --single-branch --depth 1 \
        ${GIT_CLONE_URL} "${SOURCE_DIRECTORY}" \
    && cp -vr "${BUILD_CMAKE_LISTS}" "${SOURCE_DIRECTORY}/CMakeLists.txt" \
    && cd "${SOURCE_DIRECTORY}" \
    && mkdir -p "${DEBUG_BUILD_DIRECTORY}" \
    && cd "${DEBUG_BUILD_DIRECTORY}" \
    && cmake -GNinja \
        -DCMAKE_TOOLCHAIN_FILE="${GOD_THIRDPARTY_TOOLCHAIN_FILE}" \
        -DCMAKE_BUILD_TYPE=Debug .. \
    && ninja \
    && cd .. \
    && mkdir -p "${RELEASE_BUILD_DIRECTORY}" \
    && cd "${RELEASE_BUILD_DIRECTORY}" \
    && cmake -GNinja \
        -DCMAKE_TOOLCHAIN_FILE="${GOD_THIRDPARTY_TOOLCHAIN_FILE}" \
        -DCMAKE_BUILD_TYPE=Release .. \
    && ninja \
    && cd .. \
    && mkdir -p "${GOD_THIRDPARTY_INCLUDE_DIRECTORY}" \
    && mkdir -p "${GOD_THIRDPARTY_LIB_DEBUG_DIRECTORY}" \
    && mkdir -p "${GOD_THIRDPARTY_LIB_RELEASE_DIRECTORY}" \
    && rm -rf "${THIRDPARTY_INCLUDE_TARGET_DIRECTORY}" \
    && mkdir -p "${THIRDPARTY_INCLUDE_TARGET_DIRECTORY}" \
    && cp -vr "${SOURCE_DIRECTORY}/"*.h \
        "${THIRDPARTY_INCLUDE_TARGET_DIRECTORY}/" \
    && for ITEM in "${DEBUG_LIBRARIES[@]}"; \
        do \
            rm -rf "${GOD_THIRDPARTY_LIB_DEBUG_DIRECTORY}/${ITEM}"; \
            cp -vr "${DEBUG_BUILD_DIRECTORY}/${ITEM}" \
                "${GOD_THIRDPARTY_LIB_DEBUG_DIRECTORY}/${ITEM}"; \
        done \
    && for ITEM in "${RELEASE_LIBRARIES[@]}"; \
        do \
            rm -rf "${GOD_THIRDPARTY_LIB_RELEASE_DIRECTORY}/${ITEM}"; \
            cp -vr "${RELEASE_BUILD_DIRECTORY}/${ITEM}" \
                "${GOD_THIRDPARTY_LIB_RELEASE_DIRECTORY}/${ITEM}"; \
        done \
    && rm -rf "${SOURCE_DIRECTORY}"
