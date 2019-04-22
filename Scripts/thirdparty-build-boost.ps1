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


Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"
$PSDefaultParameterValues['*:ErrorAction']='Stop'

New-Variable -Name "TAG" -Value "boost"
New-Variable -Name "TAG_ZLIB" -Value "zlib"

New-Variable -Name "BoostGitCloneUrl" `
    -Value "https://github.com/boostorg/$TAG.git"
New-Variable -Name "BoostVersionMajor" -Value "1"
New-Variable -Name "BoostVersionMinor" -Value "70"
New-Variable -Name "BoostVersionPatch" -Value "0"
New-Variable -Name "BoostGitTagToBuild" `
    -Value "$TAG-$BoostVersionMajor.$BoostVersionMinor.$BoostVersionPatch"

New-Variable -Name "ZlibGitCloneUrl" `
    -Value "https://github.com/madler/$TAG_ZLIB.git"
New-Variable -Name "ZlibGitTagToBuild" -Value "v1.2.11"

New-Variable -Name "GitCloneNumberOfJobs" -Value "16"
New-Variable -Name "BoostBuildNumberOfJobs" -Value "17"

New-Variable -Name "ScriptsDirectory" -Value "$PSScriptRoot"
New-Variable -Name "BuildEnvironmentSetupScript" `
    -Value "$ScriptsDirectory\thirdparty-setup-build-environment.ps1"

. "$BuildEnvironmentSetupScript"

New-Variable -Name "SourceDirectoryName" `
    -Value "$GOD_ThidPartyBuildDirectoryPrefix-$TAG"
New-Variable -Name "SourceDirectory" `
    -Value "$GOD_TempDirectory\$SourceDirectoryName"
New-Variable -Name "BoostSourceDirectory" `
    -Value "$SourceDirectory\$TAG"
New-Variable -Name "BoostStageDirectory" `
    -Value "$SourceDirectory\stage"
New-Variable -Name "ZlibSourceDirectory" `
    -Value "$SourceDirectory\$TAG_ZLIB"

New-Variable -Name "TargetIncludeDirectoryName" -Value "$TAG"
New-Variable -Name "TargetIncludeDirectory" `
    -Value "$GOD_ThirdPartyIncludeDirectory\$TargetIncludeDirectoryName"

# Remove the temporary build directory if it does exists already
Remove-Item -LiteralPath "$SourceDirectory" -ErrorAction Ignore -Force -Recurse

# Fetch the source code
[Bool]$ReturnCode = GOD-ExecuteExternalCommand `
    -Executable "$GOD_GitExecutable" `
    -Arguments "clone -b $ZlibGitTagToBuild --single-branch --depth 1 $ZlibGitCloneUrl `"$ZlibSourceDirectory`""
GOD-DieOnError -Succeeded $ReturnCode `
    -Error "failed to clone '$ZlibGitCloneUrl'!"
[Bool]$ReturnCode = GOD-ExecuteExternalCommand `
    -Executable "$GOD_GitExecutable" `
    -Arguments "clone -b $BoostGitTagToBuild --single-branch --depth 1 --recursive --shallow-submodules --jobs $GitCloneNumberOfJobs $BoostGitCloneUrl `"$BoostSourceDirectory`""
GOD-DieOnError -Succeeded $ReturnCode `
    -Error "failed to clone '$BoostGitCloneUrl'!"

# Note 1: turning on debug-symbols causes failed to write output file on
# windows due to ntfs path length limit, so either use --abbreviate-paths or
# --hash in order to limit the path lengths
# Note 2: adding -j parameter while debug-symbols is on causes too many build
# failures
# Note 3: by turning on debug-symbols b2 fails to build and install
# libboost_math_c99*.lib files (all six of them) despite the fact that it
# produces the corresponding .pdb files.
# Note 4: adding /FS to cflags, cxxflags, and linkflags should resolve all the
# above issues.
# Note 5: run b2 command multiple times if boost fails to build some targets.

# Setup msvc build environment for both Win32 and X64 platforms
# Both x64-native tools and x86 cross tools
GOD-InvokeCmdScript -Script "$GOD_VcVarsAmd64X86Script"

# Bootstrap Boost C++ Libraries
[Bool]$ReturnCode = GOD-ExecuteExternalCommand `
    -Executable "$BoostSourceDirectory\bootstrap.bat" `
    -Arguments "--with-toolset=msvc --prefix=`"$BoostStageDirectory`"" `
    -WorkingDirectory "$BoostSourceDirectory"
GOD-DieOnError -Succeeded $ReturnCode `
    -Error "failed to bootstrap Boost C++ Libraries inside '$BoostStageDirectory'!"

# Build Boost C++ Libraries
[Bool]$ReturnCode = GOD-ExecuteExternalCommand `
    -Executable "$BoostSourceDirectory\b2.exe" `
    -Arguments "--hash toolset=msvc debug-symbols=on debug-store=database optimization=space address-model=32,64 architecture=x86 threading=multi link=static runtime-link=shared cflags=`"/FS`" cxxflags=`"/std:c++17 /FS`" linkflags=`"/std:c++17 /FS`" pch=off define=BOOST_USE_WINAPI_VERSION=0x0601 --layout=versioned --build-type=minimal --build-dir=`"build`" --prefix=`"$BoostStageDirectory`" --without-mpi --without-python -sZLIB_SOURCE=`"$ZlibSourceDirectory`" -j $BoostBuildNumberOfJobs install" `
    -WorkingDirectory "$BoostSourceDirectory"
GOD-DieOnError -Succeeded $ReturnCode `
    -Error "failed to build Boost C++ Libraries inside '$BoostSourceDirectory'!"
