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

New-Variable -Name "VersionToBuild" -Value "3280000"

New-Variable -Name "ArchiveName" -Value "sqlite-amalgamation-${VersionToBuild}"
New-Variable -Name "ArchiveFileName" -Value "$ArchiveName.zip"
New-Variable -Name "SourceArchiveUrl" -Value "https://sqlite.org/2019/${ArchiveFileName}"

New-Variable -Name "TAG" -Value "sqlite3"

New-Variable -Name "ScriptsDirectory" -Value "$PSScriptRoot"
New-Variable -Name "BuildEnvironmentSetupScript" -Value "$ScriptsDirectory\thirdparty-setup-build-environment.ps1"

. "$BuildEnvironmentSetupScript"

New-Variable -Name "BuildCMakeLists" -Value "$GOD_ThidPartyToolchainDirectory\sqlite3-CMakeLists.txt"

New-Variable -Name "SourceDirectoryName" -Value "$GOD_ThidPartyBuildDirectoryPrefix-$TAG"
New-Variable -Name "SourceDirectory" -Value "$GOD_TempDirectory\$SourceDirectoryName"
New-Variable -Name "InnerSourceDirectoryName" -Value "$ArchiveName"
New-Variable -Name "InnerSourceDirectory" -Value "$SourceDirectory\$InnerSourceDirectoryName"

New-Variable -Name "ArchiveFile" -Value "$SourceDirectory\$ArchiveFileName"

New-Variable -Name "VcxprojName" -Value "$TAG.vcxproj"
New-Variable -Name "Win32DebugTargetName" -Value "$($TAG)d"
New-Variable -Name "Win32ReleaseTargetName" -Value "$TAG"
New-Variable -Name "Win64DebugTargetName" -Value "$Win32DebugTargetName"
New-Variable -Name "Win64ReleaseTargetName" -Value "$Win32ReleaseTargetName"

New-Variable -Name "Win32DebugBuildDirectoryName" -Value "build-win32-debug"
New-Variable -Name "Win32ReleaseBuildDirectoryName" -Value "build-win32-release"
New-Variable -Name "Win64DebugBuildDirectoryName" -Value "build-win64-debug"
New-Variable -Name "Win64ReleaseBuildDirectoryName" -Value "build-win64-release"

New-Variable -Name "Win32DebugBuildDirectory" -Value "$InnerSourceDirectory\$Win32DebugBuildDirectoryName"
New-Variable -Name "Win32ReleaseBuildDirectory" -Value "$InnerSourceDirectory\$Win32ReleaseBuildDirectoryName"
New-Variable -Name "Win64DebugBuildDirectory" -Value "$InnerSourceDirectory\$Win64DebugBuildDirectoryName"
New-Variable -Name "Win64ReleaseBuildDirectory" -Value "$InnerSourceDirectory\$Win64ReleaseBuildDirectoryName"

# Remove the temporary build directory if it does exists already
Remove-Item -LiteralPath "$SourceDirectory" -ErrorAction Ignore -Force -Recurse

# Create the temporary build directory
New-Item -Path "$GOD_TempDirectory" -Name "$SourceDirectoryName" -ItemType "directory"

# Download the distfile
Invoke-WebRequest -Uri $SourceArchiveUrl -OutFile "$ArchiveFile"

# Extract the source archive
Expand-Archive "$ArchiveFile" -DestinationPath "$SourceDirectory"

# Copy our own cmake file in order to perform a cmake build
Copy-Item "$BuildCMakeLists" -Destination "$InnerSourceDirectory\CMakeLists.txt"

# Win32 Debug Build
GOD-RunCmakeBuild `
    -Configuration "Debug" `
    -Platform "Win32" `
    -TargetName "$Win32DebugTargetName" `
    -SourceDirectory "$InnerSourceDirectory" `
    -VcxprojName "$VcxprojName" `
    -BuildDirectoryName "$Win32DebugBuildDirectoryName"

# Win32 Release Build
GOD-RunCmakeBuild `
    -Configuration "Release" `
    -Platform "Win32" `
    -TargetName "$Win32ReleaseTargetName" `
    -SourceDirectory "$InnerSourceDirectory" `
    -VcxprojName "$VcxprojName" `
    -BuildDirectoryName "$Win32ReleaseBuildDirectoryName"

# Win64 Debug Build
GOD-RunCmakeBuild `
    -Configuration "Debug" `
    -Platform "X64" `
    -TargetName "$Win64DebugTargetName" `
    -SourceDirectory "$InnerSourceDirectory" `
    -VcxprojName "$VcxprojName" `
    -BuildDirectoryName "$Win64DebugBuildDirectoryName"

# Win64 Release Build
GOD-RunCmakeBuild `
    -Configuration "Release" `
    -Platform "X64" `
    -TargetName "$Win64ReleaseTargetName" `
    -SourceDirectory "$InnerSourceDirectory" `
    -VcxprojName "$VcxprojName" `
    -BuildDirectoryName "$Win64ReleaseBuildDirectoryName"

# Copy the headers to ThirdParty/include
Copy-Item "$InnerSourceDirectory\sqlite3.h" -Destination "$GOD_ThirdPartyIncludeDirectory"
Copy-Item "$InnerSourceDirectory\sqlite3ext.h" -Destination "$GOD_ThirdPartyIncludeDirectory"

# Copy the win32 debug libraries to ThirdParty/lib/win32/debug
Copy-Item "$Win32DebugBuildDirectory\Debug\$Win32DebugTargetName.lib" -Destination "$GOD_ThirdPartyLibWin32DebugDirectory"
Copy-Item "$Win32DebugBuildDirectory\Debug\$Win32DebugTargetName.pdb" -Destination "$GOD_ThirdPartyLibWin32DebugDirectory"

# Copy win32 release libraries to ThirdParty/lib/win32/release
Copy-Item "$Win32ReleaseBuildDirectory\Release\$Win32ReleaseTargetName.lib" -Destination "$GOD_ThirdPartyLibWin32ReleaseDirectory"

# Copy the win64 debug libraries to ThirdParty/lib/win64/debug
Copy-Item "$Win64DebugBuildDirectory\Debug\$Win64DebugTargetName.lib" -Destination "$GOD_ThirdPartyLibWin64DebugDirectory"
Copy-Item "$Win64DebugBuildDirectory\Debug\$Win64DebugTargetName.pdb" -Destination "$GOD_ThirdPartyLibWin64DebugDirectory"

# Copy win64 release libraries to ThirdParty/lib/win64/release
Copy-Item "$Win64ReleaseBuildDirectory\Release\$Win64ReleaseTargetName.lib" -Destination "$GOD_ThirdPartyLibWin64ReleaseDirectory"

# Clean up the temporary build directory
Remove-Item -LiteralPath "$SourceDirectory" -ErrorAction Ignore -Force -Recurse

Set-Location "$GOD_ProjectDirectory"
