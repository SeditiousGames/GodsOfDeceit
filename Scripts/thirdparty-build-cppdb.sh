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


VERSION_TO_BUILD="0.3.1"
ARCHIVE_FILE_NAME="cppdb-${VERSION_TO_BUILD}.tar.bz2"
SOURCE_ARCHIVE_URL="https://sourceforge.net/projects/cppcms/files/cppdb/${VERSION_TO_BUILD}/${ARCHIVE_FILE_NAME}"
SOURCE_DIRECTORY_NAME="cppdb-${VERSION_TO_BUILD}"
DEBUG_BUILD_DIRECTORY_NAME="build-debug"
RELEASE_BUILD_DIRECTORY_NAME="build-release"
TEMP_DIRECTORY="/tmp"

declare -a INCLUDES=( "cppdb" )
declare -a DEBUG_LIBRARIES=( "libcppdb.a" "libcppdb_sqlite3.a" )
declare -a RELEASE_LIBRARIES=( "libcppdb.a" "libcppdb_sqlite3.a" )

ARCHIVE_FILE="${TEMP_DIRECTORY}/${ARCHIVE_FILE_NAME}"
SOURCE_DIRECTORY="${TEMP_DIRECTORY}/${SOURCE_DIRECTORY_NAME}"
DEBUG_BUILD_DIRECTORY="${SOURCE_DIRECTORY}/${DEBUG_BUILD_DIRECTORY_NAME}"
RELEASE_BUILD_DIRECTORY="${SOURCE_DIRECTORY}/${RELEASE_BUILD_DIRECTORY_NAME}"

PROJECT_DIRECTORY=`dirname $(dirname $(realpath "$0"))`
THIRDPARTY_DIRECTORY="${PROJECT_DIRECTORY}/ThirdParty"
BUILD_TOOLCHAIN_SETUP="${PROJECT_DIRECTORY}/Scripts/thirdparty-build-toochain-setup.sh"
BUILD_TOOLCHAIN_FILE="${THIRDPARTY_DIRECTORY}/toolchains/ue4-bundled-toolchain.cmake"
THIRDPARTY_INCLUDE_DIRECTORY="${THIRDPARTY_DIRECTORY}/include"
THIRDPARTY_LIB_DEBUG_DIRECTORY="${THIRDPARTY_DIRECTORY}/lib/linux/debug"
THIRDPARTY_LIB_RELEASE_DIRECTORY="${THIRDPARTY_DIRECTORY}/lib/linux/release"

source "${BUILD_TOOLCHAIN_SETUP}" \
    && export FAKE_SQLITE3_PREFIX="${GOD_TOOLCHAIN_ROOT_DIRECTORY}/usr/local" \
    && export FAKE_SQLITE3_INCLUDE_DIRECTORY="${FAKE_SQLITE3_PREFIX}/include" \
    && export FAKE_SQLITE3_LIB_DIRECTORY="${FAKE_SQLITE3_PREFIX}/usr/local/lib" \
    && export FAKE_SQLITE3_LIB64_DIRECTORY="${FAKE_SQLITE3_PREFIX}/usr/local/lib64" \
    && rm -rf "${ARCHIVE_FILE}" \
    && rm -rf "${SOURCE_DIRECTORY}" \
    && cd "${TEMP_DIRECTORY}" \
    && wget ${SOURCE_ARCHIVE_URL} -O "${ARCHIVE_FILE}" \
    && tar xvjf "${ARCHIVE_FILE}" -C "${TEMP_DIRECTORY}" \
    && cd "${SOURCE_DIRECTORY}" \
    && mkdir -p "${FAKE_SQLITE3_PREFIX}" \
        "${FAKE_SQLITE3_LIB_DIRECTORY}" \
    && ln -sfn "${THIRDPARTY_INCLUDE_DIRECTORY}" \
        "${FAKE_SQLITE3_INCLUDE_DIRECTORY}" \
    && ln -sfn "${THIRDPARTY_LIB_DEBUG_DIRECTORY}" \
        "${FAKE_SQLITE3_LIB64_DIRECTORY}" \
    && mkdir -p "${DEBUG_BUILD_DIRECTORY}" \
    && cd "${DEBUG_BUILD_DIRECTORY}" \
    && cmake -GNinja \
        -DCMAKE_TOOLCHAIN_FILE="${BUILD_TOOLCHAIN_FILE}" \
        -DCMAKE_BUILD_TYPE=Debug \
        -DCMAKE_INCLUDE_PATH="${FAKE_SQLITE3_INCLUDE_DIRECTORY}" \
        -DCMAKE_LIBRARY_PATH="${FAKE_SQLITE3_LIB64_DIRECTORY}" \
        -DDISABLE_MYSQL=ON \
        -DDISABLE_ODBC=ON \
        -DDISABLE_PQ=ON \
        -DSQLITE_BACKEND_INTERNAL=OFF \
        .. \
    && ninja \
    && cd .. \
    && unlink "${FAKE_SQLITE3_LIB64_DIRECTORY}" \
    && ln -sfn "${THIRDPARTY_LIB_RELEASE_DIRECTORY}" \
        "${FAKE_SQLITE3_LIB64_DIRECTORY}" \
    && mkdir -p "${RELEASE_BUILD_DIRECTORY}" \
    && cd "${RELEASE_BUILD_DIRECTORY}" \
    && cmake -GNinja \
        -DCMAKE_TOOLCHAIN_FILE="${BUILD_TOOLCHAIN_FILE}" \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INCLUDE_PATH="${FAKE_SQLITE3_INCLUDE_DIRECTORY}" \
        -DCMAKE_LIBRARY_PATH="${FAKE_SQLITE3_LIB64_DIRECTORY}" \
        -DDISABLE_MYSQL=ON \
        -DDISABLE_ODBC=ON \
        -DDISABLE_PQ=ON \
        -DSQLITE_BACKEND_INTERNAL=OFF \
        .. \
    && ninja \
    && cd .. \
    && unlink "${FAKE_SQLITE3_LIB64_DIRECTORY}" \
    && unlink "${FAKE_SQLITE3_INCLUDE_DIRECTORY}" \
    && rm -rf "${FAKE_SQLITE3_PREFIX}" \
    && mkdir -p "${THIRDPARTY_INCLUDE_DIRECTORY}" \
    && mkdir -p "${THIRDPARTY_LIB_DEBUG_DIRECTORY}" \
    && mkdir -p "${THIRDPARTY_LIB_RELEASE_DIRECTORY}" \
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
        "${ARCHIVE_FILE}"
