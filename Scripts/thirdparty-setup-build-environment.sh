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


set -e

export GOD_ARCHITECTURE_TRIPLE="x86_64-unknown-linux-gnu"
export GOD_TOOLCHAIN_NAME="clang"
export GOD_TOOLCHAIN_TARGET_PLATFORM="centos7"
export GOD_TOOLCHAIN_VERSION_PREFIX="v13"
export GOD_TOOLCHAIN_VERSION_MAJOR="7"
export GOD_TOOLCHAIN_VERSION_MINOR="0"
export GOD_TOOLCHAIN_VERSION_PATCH="1"
export GOD_TOOLCHAIN_VERSION="${GOD_TOOLCHAIN_VERSION_MAJOR}.${GOD_TOOLCHAIN_VERSION_MINOR}.${GOD_TOOLCHAIN_VERSION_PATCH}"
export GOD_TOOLCHAIN="${GOD_TOOLCHAIN_VERSION_PREFIX}_${GOD_TOOLCHAIN_NAME}-${GOD_TOOLCHAIN_VERSION}-${GOD_TOOLCHAIN_TARGET_PLATFORM}"
export GOD_TOOLCHAIN_ROOT_DIRECTORY="/opt/UnrealEngine/Engine/Extras/ThirdPartyNotUE/SDKs/HostLinux/Linux_x64/${GOD_TOOLCHAIN}/${GOD_ARCHITECTURE_TRIPLE}"
export GOD_TOOLCHAIN_BIN_DIRECTORY="${GOD_TOOLCHAIN_ROOT_DIRECTORY}/bin"
export GOD_TOOLCHAIN_COMPILER_INCLUDE_DIRECTORY="${GOD_TOOLCHAIN_ROOT_DIRECTORY}/lib/${GOD_TOOLCHAIN_NAME}/${GOD_TOOLCHAIN_VERSION}/include"
export GOD_TOOLCHAIN_SYSTEM_INCLUDE_DIRECTORY="${GOD_TOOLCHAIN_ROOT_DIRECTORY}/usr/include"
export GOD_SYSTEM_LIBCPP_INCLUDE_DIRECTORY="/usr/include/c++/v1"

export GOD_TEMP_DIRECTORY="/tmp"
export GOD_PROJECT_DIRECTORY=`dirname $(dirname $(realpath "$0"))`
export GOD_THIRDPARTY_DIRECTORY="${GOD_PROJECT_DIRECTORY}/ThirdParty"
export GOD_THIRDPARTY_INCLUDE_DIRECTORY="${GOD_THIRDPARTY_DIRECTORY}/include"
export GOD_THIRDPARTY_LIB_BASE_DIRECTORY="${GOD_THIRDPARTY_DIRECTORY}/lib/linux"
export GOD_THIRDPARTY_LIB_DEBUG_DIRECTORY="${GOD_THIRDPARTY_LIB_BASE_DIRECTORY}/debug"
export GOD_THIRDPARTY_LIB_RELEASE_DIRECTORY="${GOD_THIRDPARTY_LIB_BASE_DIRECTORY}/release"
export GOD_THIRDPARTY_TOOLCHAIN_DIRECTORY="${GOD_THIRDPARTY_DIRECTORY}/toolchain"
export GOD_THIRDPARTY_TOOLCHAIN_FILE="${GOD_THIRDPARTY_TOOLCHAIN_DIRECTORY}/ue4-bundled-toolchain.cmake"
export GOD_THIRDPARTY_BUILD_DIRECTORY_PREFIX="god-thirdparty"

# WORKAROUND
# Linker refuses to find ${GOD_TOOLCHAIN_ROOT_DIRECTORY}/usr/lib64 if
# ${GOD_TOOLCHAIN_ROOT_DIRECTORY}/usr/lib does not exists and stops with the
# following errors:
# cannot find crt1.o: No such file or directory
# cannot find crti.o: No such file or directory
mkdir -p "${GOD_TOOLCHAIN_ROOT_DIRECTORY}/usr/lib"

# WORKAROUND
# For asserts in ${GOD_TOOLCHAIN_ROOT_DIRECTORY}/bin/x86_64-unknown-linux-gnu-* binaries
export LANG=C
export LC_CTYPE="C"
export LC_NUMERIC="C"
export LC_TIME="C"
export LC_COLLATE="C"
export LC_MONETARY="C"
export LC_MESSAGES="C"
export LC_PAPER="C"
export LC_NAME="C"
export LC_ADDRESS="C"
export LC_TELEPHONE="C"
export LC_MEASUREMENT="C"
export LC_IDENTIFICATION="C"
locale

export PS1="[UE4 Bundled Toolchain] $PS1"
