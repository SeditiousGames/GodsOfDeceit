#!/usr/bin/env bash

PROJECT_NAME="GodsOfDeceit"
MAKEOPTS="-j17"
ANDROID_CLI="/opt/bin/android-cli.sh"
PROJECT_DIRECTORY=`dirname $(dirname $(realpath "$0"))`
BUILD_DIRECTORY="${PROJECT_DIRECTORY}/build"
MAKE_ARGUMENTS="${PROJECT_NAME}Editor ${MAKEOPTS}"

cd "${BUILD_DIRECTORY}" \
    && source "${ANDROID_CLI}" \
    && make ${MAKE_ARGUMENTS} 
