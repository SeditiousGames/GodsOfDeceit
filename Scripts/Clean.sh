#!/usr/bin/env bash

PROJECT_NAME="GodsOfDeceit"
ANDROID_CLI="/opt/bin/android-cli.sh"
PROJECT_DIRECTORY=`dirname $(dirname $(realpath "$0"))`
BUILD_DIRECTORY="${PROJECT_DIRECTORY}/build"
MAKE_ARGUMENTS="${PROJECT_NAME}Editor ARGS=\"-clean\""

cd "${BUILD_DIRECTORY}" \
    && source "${ANDROID_CLI}" \
    && make ${MAKE_ARGUMENTS}
