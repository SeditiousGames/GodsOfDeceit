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

New-Variable -Name "GitCloneUrl" `
    -Value "https://github.com/weidai11/cryptopp.git"
New-Variable -Name "GitTagToBuild" -Value "CRYPTOPP_8_1_0"

New-Variable -Name "TAG" -Value "cryptlib"

New-Variable -Name "ScriptsDirectory" -Value "$PSScriptRoot"
New-Variable -Name "BuildEnvironmentSetupScript" `
    -Value "$ScriptsDirectory\thirdparty-setup-build-environment.ps1"

. "$BuildEnvironmentSetupScript"

New-Variable -Name "SourceDirectoryName" `
    -Value "$GOD_ThidPartyBuildDirectoryPrefix-$TAG"
New-Variable -Name "SourceDirectory" `
    -Value "$GOD_TempDirectory\$SourceDirectoryName"

New-Variable -Name "VcxprojName" -Value "$TAG.vcxproj"
New-Variable -Name "Win32DebugTargetName" -Value "$($TAG)d"
New-Variable -Name "Win32ReleaseTargetName" -Value "$TAG"
New-Variable -Name "Win64DebugTargetName" -Value "$Win32DebugTargetName"
New-Variable -Name "Win64ReleaseTargetName" -Value "$Win32ReleaseTargetName"

New-Variable -Name "TargetIncludeDirectoryName" -Value "cryptopp"
New-Variable -Name "TargetIncludeDirectory" `
    -Value "$GOD_ThirdPartyIncludeDirectory\$TargetIncludeDirectoryName"

$Win32DebugLibraries = ( `
    "$Win32DebugTargetName.lib", `
    "$Win32DebugTargetName.pdb"
)

$Win32ReleaseLibraries = ( `
    "$Win32ReleaseTargetName.lib"
)

$Win64DebugLibraries = ( `
    "$Win64DebugTargetName.lib", `
    "$Win64DebugTargetName.pdb"
)

$Win64ReleaseLibraries = ( `
    "$Win64ReleaseTargetName.lib"
)

# Remove the temporary build directory if it does exists already
Remove-Item -LiteralPath "$SourceDirectory" -ErrorAction Ignore -Force -Recurse

# Fetch the source code
[Bool]$ReturnCode = GOD-ExecuteExternalCommand `
    -Executable "$GOD_GitExecutable" `
    -Arguments "clone -b $GitTagToBuild --single-branch --depth 1 $GitCloneUrl `"$SourceDirectory`""
GOD-DieOnError -Succeeded $ReturnCode `
    -Error "failed to clone '$GitCloneUrl'!"

# Win32 Debug Build
GOD-RunMsBuild `
    -Configuration "Debug" `
    -Platform "Win32" `
    -TargetName "$Win32DebugTargetName" `
    -SourceDirectory "$SourceDirectory" `
    -VcxprojName "$VcxprojName" `

# Win32 Release Build
GOD-RunMsBuild `
    -Configuration "Release" `
    -Platform "Win32" `
    -TargetName "$Win32ReleaseTargetName" `
    -SourceDirectory "$SourceDirectory" `
    -VcxprojName "$VcxprojName" `

# Win64 Debug Build
GOD-RunMsBuild `
    -Configuration "Debug" `
    -Platform "X64" `
    -TargetName "$Win64DebugTargetName" `
    -SourceDirectory "$SourceDirectory" `
    -VcxprojName "$VcxprojName" `

# Win64 Release Build
GOD-RunMsBuild `
    -Configuration "Release" `
    -Platform "X64" `
    -TargetName "$Win64ReleaseTargetName" `
    -SourceDirectory "$SourceDirectory" `
    -VcxprojName "$VcxprojName" `

# First, clean up the old headers
# Then, copy the new headers to destination
Remove-Item -LiteralPath "$TargetIncludeDirectory" `
    -ErrorAction Ignore -Force -Recurse
New-Item -Path "$GOD_ThirdPartyIncludeDirectory" `
    -Name "$TargetIncludeDirectoryName" `
    -ItemType "directory"
Copy-Item "$SourceDirectory\*.h" -Destination "$TargetIncludeDirectory" `

# First, clean up the old win32 debug libraries
# Then, copy the new win32 debug libraries to destination
$Win32DebugLibraries | Foreach {
    Remove-Item -LiteralPath "$GOD_ThirdPartyLibWin32DebugDirectory\$_" `
        -ErrorAction Ignore -Force -Recurse
    Copy-Item "$SourceDirectory\Win32\Output\Debug\$_" `
        -Destination "$GOD_ThirdPartyLibWin32DebugDirectory" -Recurse
}

# First, clean up the old win32 release libraries
# Then, copy the new win32 release libraries to destination
$Win32ReleaseLibraries | Foreach {
    Remove-Item -LiteralPath "$GOD_ThirdPartyLibWin32ReleaseDirectory\$_" `
        -ErrorAction Ignore -Force -Recurse
    Copy-Item "$SourceDirectory\Win32\Output\Release\$_" `
        -Destination "$GOD_ThirdPartyLibWin32ReleaseDirectory" -Recurse
}

# First, clean up the old win64 debug libraries
# Then, copy the new win64 debug libraries to destination
$Win64DebugLibraries | Foreach {
    Remove-Item -LiteralPath "$GOD_ThirdPartyLibWin64DebugDirectory\$_" `
        -ErrorAction Ignore -Force -Recurse
    Copy-Item "$SourceDirectory\X64\Output\Debug\$_" `
        -Destination "$GOD_ThirdPartyLibWin64DebugDirectory" -Recurse
}

# First, clean up the old win64 release libraries
# Then, copy the new win64 release libraries to destination
$Win64ReleaseLibraries | Foreach {
    Remove-Item -LiteralPath "$GOD_ThirdPartyLibWin64ReleaseDirectory\$_" `
        -ErrorAction Ignore -Force -Recurse
    Copy-Item "$SourceDirectory\X64\Output\Release\$_" `
        -Destination "$GOD_ThirdPartyLibWin64ReleaseDirectory" -Recurse
}

# Clean up the temporary build directory
Remove-Item -LiteralPath "$SourceDirectory" -ErrorAction Ignore -Force -Recurse
