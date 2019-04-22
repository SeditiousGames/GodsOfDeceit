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

New-Variable -Name "VersionToBuild" -Value "0.3.1"
New-Variable -Name "7Zip4PowershellModuleVersion" -Value "1.9.0"

New-Variable -Name "TAG" -Value "cppdb"

New-Variable -Name "ArchiveName" -Value "$TAG-$VersionToBuild"
New-Variable -Name "TarFileName" -Value "$ArchiveName.tar"
New-Variable -Name "ArchiveFileName" -Value "$TarFileName.bz2"
New-Variable -Name "SourceArchiveUrl" `
    -Value "https://newcontinuum.dl.sourceforge.net/project/cppcms/$TAG/$VersionToBuild/$ArchiveFileName"

New-Variable -Name "TAG_SQLITE3" -Value "sqlite3"
New-Variable -Name "TAG_SQLITE3_BACKEND" -Value "$($TAG)_$($TAG_SQLITE3)"

New-Variable -Name "ScriptsDirectory" -Value "$PSScriptRoot"
New-Variable -Name "BuildEnvironmentSetupScript" `
    -Value "$ScriptsDirectory\thirdparty-setup-build-environment.ps1"

. "$BuildEnvironmentSetupScript"

New-Variable -Name "SourceDirectoryName" `
    -Value "$GOD_ThidPartyBuildDirectoryPrefix-$TAG"
New-Variable -Name "SourceDirectory" `
    -Value "$GOD_TempDirectory\$SourceDirectoryName"
New-Variable -Name "InnerSourceDirectoryName" -Value "$ArchiveName"
New-Variable -Name "InnerSourceDirectory" `
    -Value "$SourceDirectory\$InnerSourceDirectoryName"

New-Variable -Name "TarFile" -Value "$SourceDirectory\$TarFileName"
New-Variable -Name "ArchiveFile" -Value "$SourceDirectory\$ArchiveFileName"

#New-Variable -Name "7Zip4PowershellModulePrefix"  -Value "$SourceDirectory"
#New-Variable -Name "7Zip4PowershellModuleDirectory" `
#    -Value "$SourceDirectory\7Zip4Powershell\$7Zip4PowershellModuleVersion"
#New-Variable -Name "7Zip4PowershellModulePath" `
#    -Value "$7Zip4PowershellModuleDirectory\7Zip4PowerShell.psd1"

New-Variable -Name "VcxprojName" -Value "$TAG-static.vcxproj"
New-Variable -Name "Win32DebugTargetName" -Value "$($TAG)d"
New-Variable -Name "Win32ReleaseTargetName" -Value "$TAG"
New-Variable -Name "Win64DebugTargetName" -Value "$Win32DebugTargetName"
New-Variable -Name "Win64ReleaseTargetName" -Value "$Win32ReleaseTargetName"

New-Variable -Name "SQLite3BackendVcxprojName" -Value "$TAG_SQLITE3_BACKEND-static.vcxproj"
New-Variable -Name "SQLite3BackendWin32DebugTargetName" -Value "$($TAG_SQLITE3_BACKEND)d"
New-Variable -Name "SQLite3BackendWin32ReleaseTargetName" -Value "$TAG_SQLITE3_BACKEND"
New-Variable -Name "SQLite3BackendWin64DebugTargetName" -Value "$SQLite3BackendWin32DebugTargetName"
New-Variable -Name "SQLite3BackendWin64ReleaseTargetName" -Value "$SQLite3BackendWin32ReleaseTargetName"

New-Variable -Name "Win32DebugBuildDirectoryName" -Value "build-win32-debug"
New-Variable -Name "Win32ReleaseBuildDirectoryName" -Value "build-win32-release"
New-Variable -Name "Win64DebugBuildDirectoryName" -Value "build-win64-debug"
New-Variable -Name "Win64ReleaseBuildDirectoryName" -Value "build-win64-release"

New-Variable -Name "Win32DebugBuildDirectory" `
    -Value "$InnerSourceDirectory\$Win32DebugBuildDirectoryName"
New-Variable -Name "Win32ReleaseBuildDirectory" `
    -Value "$InnerSourceDirectory\$Win32ReleaseBuildDirectoryName"
New-Variable -Name "Win64DebugBuildDirectory" `
    -Value "$InnerSourceDirectory\$Win64DebugBuildDirectoryName"
New-Variable -Name "Win64ReleaseBuildDirectory" `
    -Value "$InnerSourceDirectory\$Win64ReleaseBuildDirectoryName"

New-Variable -Name "SQLite3DebugLibName" -Value "$($TAG_SQLITE3)d.lib"
New-Variable -Name "SQLite3ReleaseLibName" -Value "$TAG_SQLITE3.lib"
New-Variable -Name "IntermediateSQLite3Win32DebugLibDirectoryName" `
    -Value "$($TAG_SQLITE3)d_win32"
New-Variable -Name "IntermediateSQLite3Win64DebugLibDirectoryName" `
    -Value "$($TAG_SQLITE3)d_win64"
New-Variable -Name "IntermediateSQLite3Win32DebugLibDirectory" `
    -Value "$SourceDirectory\$IntermediateSQLite3Win32DebugLibDirectoryName"
New-Variable -Name "IntermediateSQLite3Win64DebugLibDirectory" `
    -Value "$SourceDirectory\$IntermediateSQLite3Win64DebugLibDirectoryName"

New-Variable -Name "CommonCMakeBuildOptions" `
    -Value "-DCMAKE_INCLUDE_PATH=`"$GOD_ThirdPartyIncludeDirectory`" -DSQLITE_BACKEND_INTERNAL=OFF -DDISABLE_MYSQL=ON -DDISABLE_PQ=ON -DDISABLE_ODBC=ON"
New-Variable -Name "Win32DebugCMakeBuildOptions"  `
    -Value "-DCMAKE_LIBRARY_PATH=`"$IntermediateSQLite3Win32DebugLibDirectory`" $CommonCMakeBuildOptions"
New-Variable -Name "Win32ReleaseCMakeBuildOptions"  `
    -Value "-DCMAKE_LIBRARY_PATH=`"$GOD_ThirdPartyLibWin32ReleaseDirectory`" $CommonCMakeBuildOptions"
New-Variable -Name "Win64DebugCMakeBuildOptions"  `
    -Value "-DCMAKE_LIBRARY_PATH=`"$IntermediateSQLite3Win64DebugLibDirectory`" $CommonCMakeBuildOptions"
New-Variable -Name "Win64ReleaseCMakeBuildOptions"  `
    -Value "-DCMAKE_LIBRARY_PATH=`"$GOD_ThirdPartyLibWin64ReleaseDirectory`" $CommonCMakeBuildOptions"

New-Variable -Name "SharedObjectSourceFile" `
    -Value "$InnerSourceDirectory\src\shared_object.cpp"

New-Variable -Name "LibNamePrefix" -Value "lib"

$Includes = ( `
    "$TAG"
)

$Win32DebugLibraries = ( `
    "$LibNamePrefix$Win32DebugTargetName.lib", `
    "$LibNamePrefix$Win32DebugTargetName.pdb", `
    "$LibNamePrefix$SQLite3BackendWin32DebugTargetName.lib", `
    "$LibNamePrefix$SQLite3BackendWin32DebugTargetName.pdb"
)

$Win32ReleaseLibraries = ( `
    "$LibNamePrefix$Win32ReleaseTargetName.lib", `
    "$LibNamePrefix$SQLite3BackendWin32ReleaseTargetName.lib"
)

$Win64DebugLibraries = ( `
    "$LibNamePrefix$Win64DebugTargetName.lib", `
    "$LibNamePrefix$Win64DebugTargetName.pdb", `
    "$LibNamePrefix$SQLite3BackendWin64DebugTargetName.lib", `
    "$LibNamePrefix$SQLite3BackendWin64DebugTargetName.pdb"
)

$Win64ReleaseLibraries = ( `
    "$LibNamePrefix$Win64ReleaseTargetName.lib", `
    "$LibNamePrefix$SQLite3BackendWin64ReleaseTargetName.lib"
)

# Remove the temporary build directory if it does exists already
Remove-Item -LiteralPath "$SourceDirectory" -ErrorAction Ignore -Force -Recurse

# Create the temporary build directory
New-Item -Path "$GOD_TempDirectory" -Name "$SourceDirectoryName" `
    -ItemType "directory"

# Download the distfile
Invoke-WebRequest -Uri $SourceArchiveUrl -OutFile "$ArchiveFile"

# Fetch, install, and import an instance of 7Zip4Powershell powershell module
# in order to be able to extract .tar.bz2 archives
# https://www.powershellgallery.com/packages/7Zip4PowerShell
#Save-Module -Name 7Zip4Powershell -Path "$7Zip4PowershellModulePrefix" `
#    -RequiredVersion 1.9.0
#if (-not (Get-Command Expand-7Zip -ErrorAction Ignore)) {
#    Import-Module "$7Zip4PowershellModulePath"
#}

# Extract the source archive
#Expand-7Zip -ArchiveFileName "$ArchiveFile" -TargetPath "$SourceDirectory"
& "$GOD_7zExecutable" e "$ArchiveFile" -o"$SourceDirectory"
GOD-DieOnError -Succeeded $? `
    -Error "failed to extract the source archive '$ArchiveFile' into '$SourceDirectory'!"
& "$GOD_7zExecutable" x "$TarFile" -o"$SourceDirectory"
GOD-DieOnError -Succeeded $? `
    -Error "failed to extract the source archive '$TarFile' into '$SourceDirectory'!"

# WORKAROUND
# Allow CppDB's CMake build script to find SQLite3 Backend dependencies in
# debug builds
New-Item -Path "$SourceDirectory" `
    -Name "$IntermediateSQLite3Win32DebugLibDirectoryName" `
    -ItemType "directory"
New-Item -Path "$SourceDirectory" `
    -Name "$IntermediateSQLite3Win64DebugLibDirectoryName" `
    -ItemType "directory"
Copy-Item "$GOD_ThirdPartyLibWin32DebugDirectory\$SQLite3DebugLibName" `
    -Destination "$IntermediateSQLite3Win32DebugLibDirectory\$SQLite3ReleaseLibName"
Copy-Item "$GOD_ThirdPartyLibWin64DebugDirectory\$SQLite3DebugLibName" `
    -Destination "$IntermediateSQLite3Win64DebugLibDirectory\$SQLite3ReleaseLibName"

# WORKAROUND
# Fix windows build errors when CharacterSet's value is Unicode
# replace
# return LoadLibrary(name);
# with either
# return LoadLibraryA(name);
# or
# return LoadLibrary(LPCWSTR(name));
$SharedObjectSource = Get-Content "$SharedObjectSourceFile" -Raw
$SharedObjectSource = $SharedObjectSource.Replace( `
    "return LoadLibrary(name);", `
    "return LoadLibraryA(name);")
$SharedObjectSource | Out-File "$SharedObjectSourceFile"

# Win32 Debug Build
GOD-RunCmakeBuild `
    -Configuration "Debug" `
    -Platform "Win32" `
    -TargetName "$Win32DebugTargetName" `
    -SourceDirectory "$InnerSourceDirectory" `
    -VcxprojName "$VcxprojName" `
    -BuildDirectoryName "$Win32DebugBuildDirectoryName" `
    -CMakeBuildOptions "$Win32DebugCMakeBuildOptions" `
    -LibNamePrefix "$LibNamePrefix"
GOD-RunMsBuild `
    -Configuration "Debug" `
    -Platform "Win32" `
    -TargetName "$SQLite3BackendWin32DebugTargetName" `
    -SourceDirectory "$Win32DebugBuildDirectory" `
    -VcxprojName "$SQLite3BackendVcxprojName" `
    -LibNamePrefix "$LibNamePrefix"

# Win32 Release Build
GOD-RunCmakeBuild `
    -Configuration "Release" `
    -Platform "Win32" `
    -TargetName "$Win32ReleaseTargetName" `
    -SourceDirectory "$InnerSourceDirectory" `
    -VcxprojName "$VcxprojName" `
    -BuildDirectoryName "$Win32ReleaseBuildDirectoryName" `
    -CMakeBuildOptions "$Win32ReleaseCMakeBuildOptions" `
    -LibNamePrefix "$LibNamePrefix"
GOD-RunMsBuild `
    -Configuration "Release" `
    -Platform "Win32" `
    -TargetName "$SQLite3BackendWin32ReleaseTargetName" `
    -SourceDirectory "$Win32ReleaseBuildDirectory" `
    -VcxprojName "$SQLite3BackendVcxprojName" `
    -LibNamePrefix "$LibNamePrefix"

# Win64 Debug Build
GOD-RunCmakeBuild `
    -Configuration "Debug" `
    -Platform "X64" `
    -TargetName "$Win64DebugTargetName" `
    -SourceDirectory "$InnerSourceDirectory" `
    -VcxprojName "$VcxprojName" `
    -BuildDirectoryName "$Win64DebugBuildDirectoryName" `
    -CMakeBuildOptions "$Win64DebugCMakeBuildOptions" `
    -LibNamePrefix "$LibNamePrefix"
GOD-RunMsBuild `
    -Configuration "Debug" `
    -Platform "X64" `
    -TargetName "$SQLite3BackendWin64DebugTargetName" `
    -SourceDirectory "$Win64DebugBuildDirectory" `
    -VcxprojName "$SQLite3BackendVcxprojName" `
    -LibNamePrefix "$LibNamePrefix"

# Win64 Release Build
GOD-RunCmakeBuild `
    -Configuration "Release" `
    -Platform "X64" `
    -TargetName "$Win64ReleaseTargetName" `
    -SourceDirectory "$InnerSourceDirectory" `
    -VcxprojName "$VcxprojName" `
    -BuildDirectoryName "$Win64ReleaseBuildDirectoryName" `
    -CMakeBuildOptions "$Win64ReleaseCMakeBuildOptions" `
    -LibNamePrefix "$LibNamePrefix"
GOD-RunMsBuild `
    -Configuration "Release" `
    -Platform "X64" `
    -TargetName "$SQLite3BackendWin64ReleaseTargetName" `
    -SourceDirectory "$Win64ReleaseBuildDirectory" `
    -VcxprojName "$SQLite3BackendVcxprojName" `
    -LibNamePrefix "$LibNamePrefix"

# First, clean up the old headers
# Then, copy the new headers to destination
$Includes | Foreach {
    Remove-Item -LiteralPath "$GOD_ThirdPartyIncludeDirectory\$_" `
        -ErrorAction Ignore -Force -Recurse
    Copy-Item "$InnerSourceDirectory\$_" `
        -Destination "$GOD_ThirdPartyIncludeDirectory" -Recurse
}

# First, clean up the old win32 debug libraries
# Then, copy the new win32 debug libraries to destination
$Win32DebugLibraries | Foreach {
    Remove-Item -LiteralPath "$GOD_ThirdPartyLibWin32DebugDirectory\$_" `
        -ErrorAction Ignore -Force -Recurse
    Copy-Item "$Win32DebugBuildDirectory\Debug\$_" `
        -Destination "$GOD_ThirdPartyLibWin32DebugDirectory" -Recurse
}

# First, clean up the old win32 release libraries
# Then, copy the new win32 release libraries to destination
$Win32ReleaseLibraries | Foreach {
    Remove-Item -LiteralPath "$GOD_ThirdPartyLibWin32ReleaseDirectory\$_" `
        -ErrorAction Ignore -Force -Recurse
    Copy-Item "$Win32ReleaseBuildDirectory\Release\$_" `
        -Destination "$GOD_ThirdPartyLibWin32ReleaseDirectory" -Recurse
}

# First, clean up the old win64 debug libraries
# Then, copy the new win64 debug libraries to destination
$Win64DebugLibraries | Foreach {
    Remove-Item -LiteralPath "$GOD_ThirdPartyLibWin64DebugDirectory\$_" `
        -ErrorAction Ignore -Force -Recurse
    Copy-Item "$Win64DebugBuildDirectory\Debug\$_" `
        -Destination "$GOD_ThirdPartyLibWin64DebugDirectory" -Recurse
}

# First, clean up the old win64 release libraries
# Then, copy the new win64 release libraries to destination
$Win64ReleaseLibraries | Foreach {
    Remove-Item -LiteralPath "$GOD_ThirdPartyLibWin64ReleaseDirectory\$_" `
        -ErrorAction Ignore -Force -Recurse
    Copy-Item "$Win64ReleaseBuildDirectory\Release\$_" `
        -Destination "$GOD_ThirdPartyLibWin64ReleaseDirectory" -Recurse
}

# Clean up the temporary build directory
Remove-Item -LiteralPath "$SourceDirectory" -ErrorAction Ignore -Force -Recurse

