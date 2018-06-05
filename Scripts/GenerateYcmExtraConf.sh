#!/usr/bin/env bash

PROJECT_NAME="GodsOfDeceit"
MAKEOPTS="-j17"
ANDROID_CLI="/opt/bin/android-cli.sh"
PROJECT_DIRECTORY=`dirname $(dirname $(realpath "$0"))`
HOME_DIRECTORY="~"
eval HOME_DIRECTORY="${HOME_DIRECTORY}"
YCM_GENERATOR_DIRECTORY="${HOME_DIRECTORY}/.local/share/nvim/plugged/ycm-generator"
YCM_GENERATOR_EXECUTABLE="${YCM_GENERATOR_DIRECTORY}/config_gen.py"
YCM_GENERATOR_ARGS="--verbose \"${PROJECT_DIRECTORY}\" --build-system cmake --make-flags=\"${PROJECT_NAME}Editor -i ${MAKEOPTS}\""

cd "${YCM_GENERATOR_DIRECTORY}" \
    && source "${ANDROID_CLI}" \
    && ${YCM_GENERATOR_EXECUTABLE} --verbose "${PROJECT_DIRECTORY}" --build-system cmake --make-flags="GodsOfDeceitEditor -i ${MAKEOPTS}"
    # && ${YCM_GENERATOR_EXECUTABLE} ${YCM_GENERATOR_ARGS} 
