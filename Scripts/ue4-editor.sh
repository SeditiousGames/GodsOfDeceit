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


PROJECT_NAME="GodsOfDeceit"
ENGINE_DIRECTORY="/opt/UnrealEngine"
PROJECT_DIRECTORY=`dirname $(dirname $(realpath "$0"))`
PROJECT_FILE="${PROJECT_DIRECTORY}/${PROJECT_NAME}.uproject"
UE4_EDITOR_WORKING_DIRECTORY="${ENGINE_DIRECTORY}/Engine/Binaries/Linux/"
UE4_EDITOR_EXECUTABLE="${UE4_EDITOR_WORKING_DIRECTORY}/UE4Editor"
UE4_EDITOR_COMMAND_LINE_ARGUMENTS="\"${PROJECT_FILE}\" -opengl4"
LD_LIBRARY_PATH="${ENGINE_DIRECTORY}/Engine/Binaries/Linux/:${ENGINE_DIRECTORY}/Engine/Plugins/Experimental/AlembicImporter/Binaries/Linux/:${ENGINE_DIRECTORY}/Engine/Plugins/Editor/CryptoKeys/Binaries/Linux/:${ENGINE_DIRECTORY}/Engine/Plugins/Media/ImgMedia/Binaries/Linux"
ANDROID_CLI="${PROJECT_DIRECTORY}/Scripts/android-cli.sh"

cd "${UE4_EDITOR_WORKING_DIRECTORY}" \
    && source "${ANDROID_CLI}" \
    && ${UE4_EDITOR_EXECUTABLE} ${UE4_EDITOR_COMMAND_LINE_ARGUMENTS}
