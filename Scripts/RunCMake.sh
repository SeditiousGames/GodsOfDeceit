#!/usr/bin/env bash

ANDROID_CLI="/opt/bin/android-cli.sh"
PROJECT_DIRECTORY=`dirname $(dirname $(realpath "$0"))`
BUILD_DIRECTORY="${PROJECT_DIRECTORY}/build"
CMAKE_ARGS="-DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_BUILD_TYPE=Debug ../"

mkdir -p "${BUILD_DIRECTORY}" \
    && cd "${BUILD_DIRECTORY}" \
    && source "${ANDROID_CLI}" \
    && cmake ${CMAKE_ARGS}
