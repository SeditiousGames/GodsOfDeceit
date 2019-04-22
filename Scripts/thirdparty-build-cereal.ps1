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

New-Variable -Name "GitCloneUrl" -Value "https://github.com/USCiLab/cereal.git"
New-Variable -Name "GitTagToBuild" -Value "v1.2.2"

New-Variable -Name "TAG" -Value "cereal"

New-Variable -Name "ScriptsDirectory" -Value "$PSScriptRoot"
New-Variable -Name "BuildEnvironmentSetupScript" -Value "$ScriptsDirectory\thirdparty-setup-build-environment.ps1"

. "$BuildEnvironmentSetupScript"

New-Variable -Name "SourceDirectoryName" -Value "$GOD_ThidPartyBuildDirectoryPrefix-$TAG"
New-Variable -Name "SourceDirectory" -Value "$GOD_TempDirectory\$SourceDirectoryName"

$Includes = ( `
    "$TAG"
)

# Remove the temporary build directory if it does exists already
Remove-Item -LiteralPath "$SourceDirectory" -ErrorAction Ignore -Force -Recurse

# Fetch the source code
[Bool]$ReturnCode = GOD-ExecuteExternalCommand `
    -Executable "$GOD_GitExecutable" `
    -Arguments "clone -b $GitTagToBuild --single-branch --depth 1 $GitCloneUrl `"$SourceDirectory`""
GOD-DieOnError -Succeeded $ReturnCode `
    -Error "failed to clone '$GitCloneUrl'!"

# First, clean up the old headers
# Then, copy the new headers to destination
$Includes | ForEach {
    Remove-Item -LiteralPath "$GOD_ThirdPartyIncludeDirectory\$_" `
        -ErrorAction Ignore -Force -Recurse
    Copy-Item "$SourceDirectory\include\$_" `
        -Destination "$GOD_ThirdPartyIncludeDirectory" -Recurse
}

# Clean up the temporary build directory
Remove-Item -LiteralPath "$SourceDirectory" -ErrorAction Ignore -Force -Recurse
