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

export ANDROID_HOME="/opt/NVPACK/android-sdk-linux"
export ANT_HOME="/opt/NVPACK/apache-ant-1.8.2"
export GRADLE_HOME="/opt/NVPACK/gradle-2.9"
export JAVA_HOME="/opt/oracle-jdk-bin-1.8.0.162"
export NDK_ROOT="/opt/NVPACK/android-ndk-r12b"
export NDK_STANDALONE_46_ANDROID9_32="/opt/NVPACK/android-ndk-r12b/standalone-toolchain-32"
export NDK_STANDALONE_46_ANDROID9_64="/opt/NVPACK/android-ndk-r12b/standalone-toolchain-64"
export NDKROOT="/opt/NVPACK/android-ndk-r12b"
export NVPACK_NDK_TOOL_VERSION="4.9"
export NVPACK_NDK_VERSION="android-ndk-r12b"
export NVPACK_ROOT="/opt/NVPACK"

export PATH=${ANDROID_HOME}/tools:${PATH}
export PATH=${ANDROID_HOME}/platform-tools:${PATH}
export PATH=${ANDROID_HOME}/build-tools:${PATH}
export PATH=${ANDROID_HOME}/extras/android/support:${PATH}
export PATH=${NDK_ROOT}:${PATH}
export PATH=${JAVA_HOME}/bin:${PATH}
export PATH=${ANT_HOME}/bin:${PATH}
export PATH=${GRADLE_HOME}/bin:${PATH}

export PS1="[UE4] $PS1"

echo
echo "ANDROID_HOME                  :  ${ANDROID_HOME}"
echo "ANT_HOME                      :  ${ANT_HOME}"
echo "GRADLE_HOME                   :  ${GRADLE_HOME}"
echo "JAVA_HOME                     :  ${JAVA_HOME}"
echo "NDK_ROOT                      :  ${NDK_ROOT}"
echo "NDK_STANDALONE_46_ANDROID9_32 :  ${NDK_STANDALONE_46_ANDROID9_32}"
echo "NDK_STANDALONE_46_ANDROID9_64 :  ${NDK_STANDALONE_46_ANDROID9_64}"
echo "NDKROOT                       :  ${NDKROOT}"
echo "NVPACK_NDK_TOOL_VERSION       :  ${NVPACK_NDK_TOOL_VERSION}"
echo "NVPACK_NDK_VERSION            :  ${NVPACK_NDK_VERSION}"
echo "NVPACK_ROOT                   :  ${NVPACK_ROOT}"
echo
echo "PATH                          :  ${PATH}"
echo