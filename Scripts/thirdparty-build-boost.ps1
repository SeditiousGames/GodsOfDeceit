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
New-Variable -Name "BoostVersionMinor" -Value "71"
New-Variable -Name "BoostVersionPatch" -Value "0"
New-Variable -Name "BoostGitTagToBuild" `
    -Value "$TAG-$BoostVersionMajor.$BoostVersionMinor.$BoostVersionPatch"

New-Variable -Name "ICU4CWin32ArchiveFileName" -Value "icu4c-65_1-Win32-MSVC2017.zip"
New-Variable -Name "ICU4CWin64ArchiveFileName" -Value "icu4c-65_1-Win64-MSVC2017.zip"

New-Variable -Name "ICU4CWin32SourceArchiveUrl" `
    -Value "https://github.com/unicode-org/icu/releases/download/release-65-1/icu4c-65_1-Win32-MSVC2017.zip"
New-Variable -Name "ICU4CWin64SourceArchiveUrl" `
    -Value "https://github.com/unicode-org/icu/releases/download/release-65-1/icu4c-65_1-Win64-MSVC2017.zip"

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
New-Variable -Name "BoostStageIncludeDirectory" `
    -Value "$BoostStageDirectory\include"
New-Variable -Name "BoostStageLibDirectory" `
    -Value "$BoostStageDirectory\lib"
New-Variable -Name "ICU4CWin32ArchiveFile" `
    -Value "$SourceDirectory\$ICU4CWin32ArchiveFileName"
New-Variable -Name "ICU4CWin64ArchiveFile" `
    -Value "$SourceDirectory\$ICU4CWin64ArchiveFileName"
New-Variable -Name "ICU4CWin32SourceDirectory" `
    -Value "$SourceDirectory\icu4c-win32"
New-Variable -Name "ICU4CWin64SourceDirectory" `
    -Value "$SourceDirectory\icu4c-win64"
New-Variable -Name "ZlibSourceDirectory" `
    -Value "$SourceDirectory\$TAG_ZLIB"

New-Variable -Name "TargetIncludeDirectoryName" -Value "$TAG"
New-Variable -Name "TargetIncludeDirectory" `
    -Value "$GOD_ThirdPartyIncludeDirectory\$TargetIncludeDirectoryName"

# Remove the temporary build directory if it does exists already
Remove-Item -LiteralPath "$SourceDirectory" -ErrorAction Ignore -Force -Recurse

# Fetch the source code
New-Item -ItemType Directory -Force -Path $SourceDirectory
[Net.ServicePointManager]::SecurityProtocol =
  [Net.SecurityProtocolType]::Tls12 -bor `
  [Net.SecurityProtocolType]::Tls11 -bor `
  [Net.SecurityProtocolType]::Tls
Invoke-WebRequest -Uri $ICU4CWin32SourceArchiveUrl -OutFile "$ICU4CWin32ArchiveFile"
Expand-Archive -LiteralPath "$ICU4CWin32ArchiveFile" -DestinationPath "$ICU4CWin32SourceDirectory"
$ICU4CWin32Libs = get-childitem $ICU4CWin32SourceDirectory\lib -File -Recurse
foreach ($file in $ICU4CWin32Libs) {
    Copy-Item -Path $file.FullName `
        -Destination ("$ICU4CWin32SourceDirectory\lib" + "\" + $file.BaseName + "d" + $file.Extension) `
        -Force
}
Invoke-WebRequest -Uri $ICU4CWin64SourceArchiveUrl -OutFile "$ICU4CWin64ArchiveFile"
Expand-Archive -LiteralPath "$ICU4CWin64ArchiveFile" -DestinationPath "$ICU4CWin64SourceDirectory" -Force
$ICU4CWin64Libs = get-childitem $ICU4CWin64SourceDirectory\lib64 -File -Recurse
foreach ($file in $ICU4CWin64Libs) {
    Copy-Item -Path $file.FullName `
        -Destination ("$ICU4CWin64SourceDirectory\lib64" + "\" + $file.BaseName + "d" + $file.Extension) `
        -Force
}
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
# Note 4: adding /FS to cflags and cxxflags should resolve all the
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

# Build Boost C++ Libraries for Win32
[Bool]$ReturnCode = GOD-ExecuteExternalCommand `
    -Executable "$BoostSourceDirectory\b2.exe" `
    -Arguments "--hash toolset=msvc debug-store=database address-model=32 architecture=x86 threading=multi link=static runtime-link=shared cflags=`"/FS`" cxxflags=`"/std:c++17 /FS`" archiveflags=`"/LIBPATH:$ICU4CWin32SourceDirectory\lib icudt.lib icuin.lib icuio.lib icutest.lib icutu.lib icuuc.lib`" pch=off define=BOOST_USE_WINAPI_VERSION=0x0601 --layout=versioned --build-type=minimal --build-dir=`"build`" --prefix=`"$BoostStageDirectory`" --without-mpi --without-python -sICU_PATH=`"$ICU4CWin32SourceDirectory`" -sZLIB_SOURCE=`"$ZlibSourceDirectory`" -j $BoostBuildNumberOfJobs install" `
    -WorkingDirectory "$BoostSourceDirectory"
GOD-DieOnError -Succeeded $ReturnCode `
    -Error "failed to build Boost C++ Libraries for Win32 inside '$BoostSourceDirectory'!"

# First, clean up the old headers
# Then, copy the new headers to destination
Remove-Item -LiteralPath "$TargetIncludeDirectory" `
    -ErrorAction Ignore -Force -Recurse
Copy-Item "$BoostStageIncludeDirectory\$TAG-$($BoostVersionMajor)_$($BoostVersionMinor)\$TargetIncludeDirectoryName" `
    -Destination "$GOD_ThirdPartyIncludeDirectory" `
    -Recurse

# First, clean up the old Win32 debug libraries
# Then, copy the new Win32 debug libraries to destination
$CopyPattern = "libboost_*-mt-gd-x32-*"
$CopyDestination = "$GOD_ThirdPartyLibWin32DebugDirectory"
Remove-Item `
    -Path "$CopyDestination\$CopyPattern.lib" `
    -ErrorAction Ignore -Force
Remove-Item `
    -Path "$CopyDestination\$CopyPattern.pdb" `
    -ErrorAction Ignore -Force
Copy-Item "$BoostStageLibDirectory\$CopyPattern.lib" `
    -Destination "$CopyDestination"
Get-ChildItem "$BoostSourceDirectory" `
    -Recurse -Filter "$CopyPattern.pdb" | `
    Copy -Destination "$CopyDestination"

# First, clean up the old Win32 release libraries
# Then, copy the new Win32 release libraries to destination
$CopyPattern = "libboost_*-mt-x32-*"
$CopyDestination = "$GOD_ThirdPartyLibWin32ReleaseDirectory"
Remove-Item `
    -Path "$CopyDestination\$CopyPattern.lib" `
    -ErrorAction Ignore -Force
Copy-Item "$BoostStageLibDirectory\$CopyPattern.lib" `
    -Destination "$CopyDestination"

# Clean up the previous build in order to prepare for the next build
[Bool]$ReturnCode = GOD-ExecuteExternalCommand `
    -Executable "$BoostSourceDirectory\b2.exe" `
    -Arguments "--clean" `
    -WorkingDirectory "$BoostSourceDirectory"
GOD-DieOnError -Succeeded $ReturnCode `
    -Error "failed to clean up the previous build of Boost C++ Libraries inside '$BoostSourceDirectory'!"

# Build Boost C++ Libraries for Win64
[Bool]$ReturnCode = GOD-ExecuteExternalCommand `
    -Executable "$BoostSourceDirectory\b2.exe" `
    -Arguments "--hash toolset=msvc debug-store=database address-model=64 architecture=x86 threading=multi link=static runtime-link=shared cflags=`"/FS`" cxxflags=`"/std:c++17 /FS`" archiveflags=`"/LIBPATH:$ICU4CWin64SourceDirectory\lib64 icudt.lib icuin.lib icuio.lib icutest.lib icutu.lib icuuc.lib`" pch=off define=BOOST_USE_WINAPI_VERSION=0x0601 --layout=versioned --build-type=minimal --build-dir=`"build`" --prefix=`"$BoostStageDirectory`" --without-mpi --without-python -sICU_PATH=`"$ICU4CWin64SourceDirectory`" -sZLIB_SOURCE=`"$ZlibSourceDirectory`" -j $BoostBuildNumberOfJobs install" `
    -WorkingDirectory "$BoostSourceDirectory"
GOD-DieOnError -Succeeded $ReturnCode `
    -Error "failed to build Boost C++ Libraries for Win64 inside '$BoostSourceDirectory'!"

# First, clean up the old Win64 debug libraries
# Then, copy the new Win64 debug libraries to destination
$CopyPattern = "libboost_*-mt-gd-x64-*"
$CopyDestination = "$GOD_ThirdPartyLibWin64DebugDirectory"
Remove-Item `
    -Path "$CopyDestination\$CopyPattern.lib" `
    -ErrorAction Ignore -Force
Remove-Item `
    -Path "$CopyDestination\$CopyPattern.pdb" `
    -ErrorAction Ignore -Force
Copy-Item "$BoostStageLibDirectory\$CopyPattern.lib" `
    -Destination "$CopyDestination"
Get-ChildItem "$BoostSourceDirectory" `
    -Recurse -Filter "$CopyPattern.pdb" | `
    Copy -Destination "$CopyDestination"

# First, clean up the old Win64 release libraries
# Then, copy the new Win64 release libraries to destination
$CopyPattern = "libboost_*-mt-x64-*"
$CopyDestination = "$GOD_ThirdPartyLibWin64ReleaseDirectory"
Remove-Item `
    -Path "$CopyDestination\$CopyPattern.lib" `
    -ErrorAction Ignore -Force
Copy-Item "$BoostStageLibDirectory\$CopyPattern.lib" `
    -Destination "$CopyDestination"

# Clean up the temporary build directory
Remove-Item -LiteralPath "$SourceDirectory" -ErrorAction Ignore -Force -Recurse