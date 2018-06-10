#!/usr/bin/env bash

PROJECT_NAME="GodsOfDeceit"
ENGINE_DIRECTORY="/opt/UnrealEngine"
PROJECT_DIRECTORY=`dirname $(dirname $(realpath "$0"))`
PROJECT_FILE="${PROJECT_DIRECTORY}/${PROJECT_NAME}.uproject"
BUILD_TARGET="${PROJECT_NAME}Editor"

echo

echo "Projects > Build & Run > Build > Build Steps > Make > Make arguments ==> ${BUILD_TARGET}"
echo "Projects > Build & Run > Build > Build Steps > Clean Steps > Make arguments ==> ${BUILD_TARGET} ARGS=\"-clean\""

echo

echo "Projects > Build & Run > Build > Build Environment > Variable ==> LD_LIBRARY_PATH"
echo "Projects > Build & Run > Build > Build Environment > Value ==> /opt/UnrealEngine/Engine/Binaries/Linux/"

echo

echo "Projects > Build & Run > Run > Run > Executable ==> ${ENGINE_DIRECTORY}/Engine/Binaries/Linux/UE4Editor"
echo "Projects > Build & Run > Run > Run > Command line arguments ==> \"${PROJECT_FILE}\" -opengl4"
echo "Projects > Build & Run > Run > Run > Working directory ==> ${ENGINE_DIRECTORY}/Engine/Binaries/Linux/"

echo

echo "Projects > Build & Run > Run > Run Environment > Variable ==> LD_LIBRARY_PATH"
echo "Projects > Build & Run > Run > Run Environment > Value ==> /opt/UnrealEngine/Engine/Binaries/Linux/:/opt/UnrealEngine/Engine/Plugins/Experimental/AlembicImporter/Binaries/Linux/:/opt/UnrealEngine/Engine/Plugins/Editor/CryptoKeys/Binaries/Linux/:/opt/UnrealEngine/Engine/Plugins/Media/ImgMedia/Binaries/Linux"

echo
