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


FOSSIL_CLONE_URL="https://www.sqlite.org/src"
FOSSIL_TAG_TO_BUILD="release"
FOSSIL_FILE_NAME="sqlite.fossil"
FOSSIL_SOURCE_DIRECTORY_NAME="sqlite"
AMALGAMATION_SOURCE_DIRECTORY_NAME="sqlite-amalgamation"
SOURCE_DIRECTORY_NAME="sqlite3"
DEBUG_BUILD_DIRECTORY_NAME="build-debug"
RELEASE_BUILD_DIRECTORY_NAME="build-release"
TEMP_DIRECTORY="/tmp"

declare -a INCLUDES=( "sqlite3.h" "sqlite3ext.h" )
declare -a DEBUG_LIBRARIES=( "libsqlite3.a" )
declare -a RELEASE_LIBRARIES=( "libsqlite3.a" )

FOSSIL_FILE="${TEMP_DIRECTORY}/${FOSSIL_FILE_NAME}"
FOSSIL_SOURCE_DIRECTORY="${TEMP_DIRECTORY}/${FOSSIL_SOURCE_DIRECTORY_NAME}"
AMALGAMATION_SOURCE_DIRECTORY="${TEMP_DIRECTORY}/${AMALGAMATION_SOURCE_DIRECTORY_NAME}"
SOURCE_DIRECTORY="${TEMP_DIRECTORY}/${SOURCE_DIRECTORY_NAME}"
DEBUG_BUILD_DIRECTORY="${SOURCE_DIRECTORY}/${DEBUG_BUILD_DIRECTORY_NAME}"
RELEASE_BUILD_DIRECTORY="${SOURCE_DIRECTORY}/${RELEASE_BUILD_DIRECTORY_NAME}"

PROJECT_DIRECTORY=`dirname $(dirname $(realpath "$0"))`
THIRDPARTY_DIRECTORY="${PROJECT_DIRECTORY}/ThirdParty"
BUILD_TOOLCHAIN_SETUP="${PROJECT_DIRECTORY}/Scripts/thirdparty-build-toochain-setup.sh"
BUILD_TOOLCHAIN_FILE="${THIRDPARTY_DIRECTORY}/toolchains/ue4-bundled-toolchain.cmake"
BUILD_CMAKE_LISTS="${THIRDPARTY_DIRECTORY}/toolchains/sqlite3-CMakeLists.txt"
THIRDPARTY_INCLUDE_DIRECTORY="${THIRDPARTY_DIRECTORY}/include"
THIRDPARTY_LIB_DEBUG_DIRECTORY="${THIRDPARTY_DIRECTORY}/lib/linux/debug"
THIRDPARTY_LIB_RELEASE_DIRECTORY="${THIRDPARTY_DIRECTORY}/lib/linux/release"

source "${BUILD_TOOLCHAIN_SETUP}" \
    && rm -rf "${FOSSIL_FILE}" \
    && rm -rf "${FOSSIL_SOURCE_DIRECTORY}" \
    && rm -rf "${AMALGAMATION_SOURCE_DIRECTORY}" \
    && rm -rf "${SOURCE_DIRECTORY}" \
    && fossil clone ${FOSSIL_CLONE_URL} "${FOSSIL_FILE}" \
    && mkdir -p "${FOSSIL_SOURCE_DIRECTORY}" \
    && cd "${FOSSIL_SOURCE_DIRECTORY}" \
    && fossil open ${FOSSIL_FILE} \
    && fossil update ${FOSSIL_TAG_TO_BUILD} \
    && mkdir -p "${AMALGAMATION_SOURCE_DIRECTORY}" \
    && cd "${AMALGAMATION_SOURCE_DIRECTORY}" \
    && "${FOSSIL_SOURCE_DIRECTORY}/configure" \
    && make .target_source \
    && tclsh "${FOSSIL_SOURCE_DIRECTORY}/tool/mksqlite3h.tcl" \
        "${FOSSIL_SOURCE_DIRECTORY}" > sqlite3.h \
    && tclsh "${FOSSIL_SOURCE_DIRECTORY}/tool/mksqlite3c.tcl" \
    && mkdir -p "${SOURCE_DIRECTORY}" \
    && cp -vr "${AMALGAMATION_SOURCE_DIRECTORY}/sqlite3.c" \
        "${AMALGAMATION_SOURCE_DIRECTORY}/sqlite3.h" \
        "${FOSSIL_SOURCE_DIRECTORY}/src/sqlite3ext.h" \
        "${SOURCE_DIRECTORY}/" \
    && cp -vr "${BUILD_CMAKE_LISTS}" "${SOURCE_DIRECTORY}/CMakeLists.txt" \
    && cd "${SOURCE_DIRECTORY}" \
    && mkdir -p "${DEBUG_BUILD_DIRECTORY}" \
    && cd "${DEBUG_BUILD_DIRECTORY}" \
    && cmake -GNinja \
        -DCMAKE_TOOLCHAIN_FILE="${BUILD_TOOLCHAIN_FILE}" \
        -DCMAKE_BUILD_TYPE=Debug .. \
    && ninja \
    && cd .. \
    && mkdir -p "${RELEASE_BUILD_DIRECTORY}" \
    && cd "${RELEASE_BUILD_DIRECTORY}" \
    && cmake -GNinja \
        -DCMAKE_TOOLCHAIN_FILE=${BUILD_TOOLCHAIN_FILE} \
        -DCMAKE_BUILD_TYPE=Release .. \
    && ninja \
    && cd .. \
    && for ITEM in "${INCLUDES[@]}"; \
        do \
            rm -rf "${THIRDPARTY_INCLUDE_DIRECTORY}/${ITEM}";\
        done \
    && for ITEM in "${DEBUG_LIBRARIES[@]}"; \
        do \
            rm -rf "${THIRDPARTY_LIB_DEBUG_DIRECTORY}/${ITEM}"; \
        done \
    && for ITEM in "${RELEASE_LIBRARIES[@]}"; \
        do \
            rm -rf "${THIRDPARTY_LIB_RELEASE_DIRECTORY}/${ITEM}"; \
        done \
    && for ITEM in "${INCLUDES[@]}"; \
        do \
            cp -vr "${SOURCE_DIRECTORY}/${ITEM}" \
                "${THIRDPARTY_INCLUDE_DIRECTORY}/${ITEM}"; \
        done \
    && for ITEM in "${DEBUG_LIBRARIES[@]}"; \
        do \
            cp -vr "${DEBUG_BUILD_DIRECTORY}/${ITEM}" \
                "${THIRDPARTY_LIB_DEBUG_DIRECTORY}/${ITEM}"; \
        done \
    && for ITEM in "${RELEASE_LIBRARIES[@]}"; \
        do \
            cp -vr "${RELEASE_BUILD_DIRECTORY}/${ITEM}" \
                "${THIRDPARTY_LIB_RELEASE_DIRECTORY}/${ITEM}"; \
        done \
    && rm -rf "${SOURCE_DIRECTORY}" \
        "${AMALGAMATION_SOURCE_DIRECTORY}" \
        "${FOSSIL_SOURCE_DIRECTORY}" \
        "${FOSSIL_FILE}"
