@echo off

REM  (The MIT License)
REM
REM  Copyright (c) 2018 Mohammad S. Babaei
REM  Copyright (c) 2018 Khavaran67
REM
REM  Permission is hereby granted, free of charge, to any person obtaining a copy
REM  of this software and associated documentation files (the "Software"), to deal
REM  in the Software without restriction, including without limitation the rights
REM  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
REM  copies of the Software, and to permit persons to whom the Software is
REM  furnished to do so, subject to the following conditions:
REM
REM  The above copyright notice and this permission notice shall be included in all
REM  copies or substantial portions of the Software.
REM
REM  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
REM  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
REM  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
REM  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
REM  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
REM  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
REM  SOFTWARE.

title "Gods of Deceit's Unreal Engine 4 CLI"

cd %~dp0

set LANG=en_US.UTF-8
set MM_CHARSET=UTF-8
set LC_ALL=en_US.UTF-8
chcp 65001

SET OPT=OPT
SET OPT_PATH=C:\%OPT%

set NVPACK_NDK_VERSION=android-ndk-r12b
set ANDROID_HOME=%OPT_PATH%\NVPACK\android-sdk-windows
set ANDROID_NDK_ROOT=%OPT_PATH%\NVPACK\%NVPACK_NDK_VERSION%
set ANT_HOME=%OPT_PATH%\NVPACK\apache-ant-1.8.2
set GRADLE_HOME=%OPT_PATH%\NVPACK\gradle-2.9
set JAVA_HOME=%OPT_PATH%\NVPACK\jdk1.8.0_77
set NDK_ROOT=%OPT_PATH%\NVPACK\%NVPACK_NDK_VERSION%
set NDKROOT=%OPT_PATH%\NVPACK\%NVPACK_NDK_VERSION%
set NVPACK_NDK_TOOL_VERSION=4.9
set NVPACK_ROOT=C:\\%OPT%\\NVPACK

REM Do it in reverse order:
set PATH=%OPT_PATH%\Git\bin;%PATH%
set PATH=%OPT_PATH%\Git\cmd;%PATH%
set PATH=%OPT_PATH%\Git\usr\bin;%PATH%
set PATH=%OPT_PATH%\NVPACK\gradle-2.9\bin;%PATH%
set PATH=%OPT_PATH%\NVPACK\apache-ant-1.8.2\bin;%PATH%
set PATH=%OPT_PATH%\NVPACK\jdk1.8.0_77\bin;%PATH%
set PATH=%OPT_PATH%\NVPACK\%NVPACK_NDK_VERSION%;%PATH%
set PATH=%OPT_PATH%\NVPACK\android-sdk-windows\extras\android\support;%PATH%
set PATH=%OPT_PATH%\NVPACK\android-sdk-windows\build-tools;%PATH%
set PATH=%OPT_PATH%\NVPACK\android-sdk-windows\platform-tools;%PATH%
set PATH=%OPT_PATH%\NVPACK\android-sdk-windows\tools;%PATH%

set UE4_PATH=%OPT_PATH%\UnrealEngine

echo.
echo %LANG% & echo %MM_CHARSET% & echo %LC_ALL%
echo.
echo %PATH%
echo.
echo %ANDROID_HOME%
echo %ANDROID_NDK_ROOT%
echo %ANT_HOME%
echo %GRADLE_HOME%
echo %JAVA_HOME%
echo %NDK_ROOT%
echo %NDKROOT%
echo %NVPACK_NDK_TOOL_VERSION%
echo %NVPACK_NDK_VERSION%
echo.
echo %UE4_PATH%
echo.

%comspec% /k