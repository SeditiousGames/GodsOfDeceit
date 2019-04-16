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


GIT_CLONE_URL="https://github.com/USCiLab/cereal.git"
GIT_TAG_TO_BUILD="v1.2.2"
SOURCE_DIRECTORY_NAME="cereal"
TEMP_DIRECTORY="/tmp"

declare -a INCLUDES=( "cereal" )

SOURCE_DIRECTORY="${TEMP_DIRECTORY}/${SOURCE_DIRECTORY_NAME}"

PROJECT_DIRECTORY=`dirname $(dirname $(realpath "$0"))`
THIRDPARTY_DIRECTORY="${PROJECT_DIRECTORY}/ThirdParty"
THIRDPARTY_INCLUDE_DIRECTORY="${THIRDPARTY_DIRECTORY}/include"

rm -rf "${SOURCE_DIRECTORY}" \
    && git clone -b ${GIT_TAG_TO_BUILD} --single-branch --depth 1 \
        ${GIT_CLONE_URL} "${SOURCE_DIRECTORY}" \
    && mkdir -p "${THIRDPARTY_INCLUDE_DIRECTORY}" \
    && mkdir -p "${THIRDPARTY_LIB_DEBUG_DIRECTORY}" \
    && mkdir -p "${THIRDPARTY_LIB_RELEASE_DIRECTORY}" \
    && for ITEM in "${INCLUDES[@]}"; \
        do \
            rm -rf "${THIRDPARTY_INCLUDE_DIRECTORY}/${ITEM}";\
        done \
    && for ITEM in "${INCLUDES[@]}"; \
        do \
            cp -vr "${SOURCE_DIRECTORY}/include/${ITEM}" \
                "${THIRDPARTY_INCLUDE_DIRECTORY}/${ITEM}"; \
        done \
    && rm -rf "${SOURCE_DIRECTORY}"
