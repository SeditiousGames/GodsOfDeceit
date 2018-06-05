#!/usr/bin/env bash

PROJECT_NAME="GodsOfDeceit"
ENGINE_DIRECTORY="/opt/UnrealEngine"
ANDROID_CLI="/opt/bin/android-cli.sh"
PROJECT_DIRECTORY=`dirname $(dirname $(realpath "$0"))`
PROJECT_FILE="${PROJECT_DIRECTORY}/${PROJECT_NAME}.uproject"
GENERATE_PROJECT_FILES_ARGS="-project=\"${PROJECT_FILE}\" -qmakefile -game -engine"

cd "${ENGINE_DIRECTORY}" \
    && source "${ANDROID_CLI}" \
    && ./GenerateProjectFiles.sh ${GENERATE_PROJECT_FILES_ARGS}
