#!/usr/bin/env bash

#  (The MIT License)
#
#  Copyright (c) 2018 Mohammad S. Babaei
#  Copyright (c) 2018 Khavaran67
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


PROJECT_NAME="GodsOfDeceit"
MAKEOPTS="-j17 -l16"
PROJECT_DIRECTORY=`dirname $(dirname $(realpath "$0"))`
HOME_DIRECTORY="~"
eval HOME_DIRECTORY="${HOME_DIRECTORY}"
YCM_GENERATOR_DIRECTORY="${HOME_DIRECTORY}/.local/share/nvim/plugged/ycm-generator"
YCM_GENERATOR_EXECUTABLE="${YCM_GENERATOR_DIRECTORY}/config_gen.py"
YCM_GENERATOR_ARGS="--verbose \"${PROJECT_DIRECTORY}\" --build-system cmake --make-flags=\"${PROJECT_NAME}Editor -i ${MAKEOPTS}\""
ANDROID_CLI="${PROJECT_DIRECTORY}/Scripts/android-cli.sh"

cd "${YCM_GENERATOR_DIRECTORY}" \
    && source "${ANDROID_CLI}" \
    && ${YCM_GENERATOR_EXECUTABLE} --verbose "${PROJECT_DIRECTORY}" --build-system cmake --make-flags="GodsOfDeceitEditor -i ${MAKEOPTS}"
    # && ${YCM_GENERATOR_EXECUTABLE} ${YCM_GENERATOR_ARGS} 
