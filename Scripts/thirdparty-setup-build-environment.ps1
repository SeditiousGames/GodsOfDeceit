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

New-Variable -Name "GOD_CMakeExecutable" -Value "C:\CMake\bin\cmake.exe"
New-Variable -Name "GOD_GitExecutable" -Value "C:\Program Files\Git\bin\git.exe"
New-Variable -Name "GOD_VisualStudioBasePath" `
    -Value "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community"
New-Variable -Name "GOD_CmakeGenerator" -Value "Visual Studio 16 2019"
New-Variable -Name "GOD_WindowsTargetPlatformVersion" -Value "10.0"

New-Variable -Name "GOD_VcVarsScriptsBasePath" `
    -Value "$GOD_VisualStudioBasePath\VC\Auxiliary\Build"
New-Variable -Name "GOD_VcVarsAllScript" `
    -Value "$GOD_VcVarsScriptsBasePath\vcvarsall.bat"
New-Variable -Name "GOD_VcVars32Script" `
    -Value "$GOD_VcVarsScriptsBasePath\vcvars32.bat"
New-Variable -Name "GOD_VcVars64Script" `
    -Value "$GOD_VcVarsScriptsBasePath\vcvars64.bat"

New-Variable -Name "GOD_ProjectDirectory" -Value "$PSScriptRoot\.."
New-Variable -Name "GOD_ThirdPartyDirectory" `
    -Value "$GOD_ProjectDirectory\ThirdParty"
New-Variable -Name "GOD_ThirdPartyIncludeDirectory" `
    -Value "$GOD_ThirdPartyDirectory\include"
New-Variable -Name "GOD_ThirdPartyLibBaseDirectory" `
    -Value "$GOD_ThirdPartyDirectory\lib"
New-Variable -Name "GOD_ThirdPartyLibWin32BaseDirectory" `
    -Value "$GOD_ThirdPartyLibBaseDirectory\win32"
New-Variable -Name "GOD_ThirdPartyLibWin32DebugDirectory" `
    -Value "$GOD_ThirdPartyLibWin32BaseDirectory\debug"
New-Variable -Name "GOD_ThirdPartyLibWin32ReleaseDirectory" `
    -Value "$GOD_ThirdPartyLibWin32BaseDirectory\release"
New-Variable -Name "GOD_ThirdPartyLibWin64BaseDirectory" `
    -Value "$GOD_ThirdPartyLibBaseDirectory\win64"
New-Variable -Name "GOD_ThirdPartyLibWin64DebugDirectory" `
    -Value "$GOD_ThirdPartyLibWin64BaseDirectory\debug"
New-Variable -Name "GOD_ThirdPartyLibWin64ReleaseDirectory" `
    -Value "$GOD_ThirdPartyLibWin64BaseDirectory\release"
New-Variable -Name "GOD_ThidPartyToolchainDirectory" `
    -Value "$GOD_ThirdPartyDirectory\toolchain"
New-Variable -Name "GOD_ThidPartyBuildDirectoryPrefix" -Value "god-thirdparty"

New-Variable -Name "GOD_TempDirectory" `
    -Value "$($(Get-ChildItem Env:\TEMP).Value)"

function GOD-Fatal() {
    Param(
        [Parameter(Mandatory=$True)]
        [String]$Error
    )

    Write-Host "[GOD] FATAL: $Error" -ForegroundColor Red

    Exit
}

function GOD-DieOnError() {
    Param([
        Parameter(Mandatory=$True)]
        [Bool]$Succeeded,
        [Parameter(Mandatory=$True)]
        [String]$Error
    )

    if (-not $Succeeded) {
        GOD-Fatal -Error "$Error"
    }
}

function GOD-InvokeCmdScript {
    Param(
        [Parameter(Mandatory=$True)]
        [String]$Script
    )
    $CmdLine = """$Script"" $args & set"
        & $Env:SystemRoot\system32\cmd.exe /c $CmdLine |
        Select-String '^([^=]*)=(.*)$' | Foreach-Object {
        $VarName = $_.Matches[0].Groups[1].Value
        $VarValue = $_.Matches[0].Groups[2].Value
        Set-Item Env:$VarName $VarValue
    }
}

function GOD-GetEnvironment {
  Get-ChildItem Env:
}

function GOD-RestoreEnvironment {
    Param(
        [Parameter(Mandatory=$True)]
        [System.Collections.DictionaryEntry[]]$OldEnvironment
    )

    Compare-Object $OldEnvironment $(GOD-GetEnvironment) `
        -Property Key -PassThru |
    Where-Object { $_.SideIndicator -eq "=>" } |
    Foreach-Object { Remove-item Env:$($_.Name) }
    Compare-Object $OldEnvironment $(GOD-GetEnvironment) `
        -Property Value -PassThru |
    Where-Object { $_.SideIndicator -eq "<=" } |
    Foreach-Object { Set-Item Env:$($_.Name) $_.Value }
}

function GOD-ApplyBuildSettings {
    Param(
        [Parameter(Mandatory=$True)]
        [String]$Configuration,
        [Parameter(Mandatory=$True)]
        [String]$Platform,
        [Parameter(Mandatory=$True)]
        [String]$Vcxproj,
        [Parameter(Mandatory=$True)]
        [String]$TargetName
    )

    if ("$Configuration" -ne "Debug" -And "$Configuration" -ne "Release") {
        GOD-Fatal -Error "invalid configuration '$Configuration'!"
    }

    if ("$Platform" -ne "Win32" -And "$Platform" -ne "X64") {
        GOD-Fatal -Error "invalid platform '$Configuration'!"
    }

    $BuildType = "$Configuration`|$Platform";

    $Xmlns = "http://schemas.microsoft.com/developer/msbuild/2003"

    $XPathProject = "//ns:Project"
    $XPathPropertyGroup = "$XPathProject/ns:PropertyGroup"
    $XPathGlobals = "$XPathPropertyGroup[@Label = `"Globals`"]"
    $XPathWindowsTargetPlatformVersion = `
        "$XPathGlobals/ns:WindowsTargetPlatformVersion"
    $XPathPropertyGroupNoAttribute = "$XPathPropertyGroup[not(@*)]"
    $XPathTargetName = `
        "$XPathPropertyGroupNoAttribute/ns:TargetName[contains(@Condition, `"$BuildType`")]"
    $XPathConfiguration = `
        "$XPathPropertyGroup[contains(@Condition, `"$BuildType`") and @Label = `"Configuration`"]"
    $XPathCharacterSet = "$XPathConfiguration/ns:CharacterSet"
    $XPathItemDefinitionGroup = `
        "$XPathProject/ns:ItemDefinitionGroup[contains(@Condition, `"$BuildType`")]"
    $XPathClCompile = "$XPathItemDefinitionGroup/ns:ClCompile"
    $XPathRuntimeLibrary = "$XPathClCompile/ns:RuntimeLibrary"
    $XPathProgramDataBaseFileName = "$XPathClCompile/ns:ProgramDataBaseFileName"

    [Xml]$BuildConfig = Get-Content -Path "$Vcxproj"
    $Namespace = New-Object System.Xml.XmlNamespaceManager `
        -ArgumentList $BuildConfig.NameTable
    $Namespace.AddNamespace("ns", "$Xmlns")

    $Project = $BuildConfig.SelectSingleNode("$XPathProject", $Namespace)
    if (-not $Project) {
        GOD-Fatal -Error "'$Vcxproj' is not a valid .vcxproj file!"
    }

    $Globals = $BuildConfig.SelectSingleNode("$XPathGlobals", $Namespace)
    if (-not $Globals) {
        $PropertyGroupElement = $BuildConfig.CreateElement("PropertyGroup", `
            $Project.NamespaceURI);
        $LabelAttribute = $BuildConfig.CreateAttribute("Label")
        $LabelAttribute.Value = "Globals"
        $PropertyGroupElement.Attributes.Append($LabelAttribute)
        $Project.AppendChild($PropertyGroupElement)

        $Globals = $BuildConfig.SelectSingleNode("$XPathGlobals", $Namespace)
    }

    $WindowsTargetPlatformVersion = `
        $BuildConfig.SelectSingleNode("$XPathWindowsTargetPlatformVersion",`
             $Namespace)
    if (-not $WindowsTargetPlatformVersion) {
        $WindowsTargetPlatformVersionElement = `
            $BuildConfig.CreateElement("WindowsTargetPlatformVersion", `
                $Globals.NamespaceURI);
        $TextNode = `
            $BuildConfig.CreateTextNode("$GOD_WindowsTargetPlatformVersion")
        $WindowsTargetPlatformVersionElement.AppendChild($TextNode)
        $Globals.AppendChild($WindowsTargetPlatformVersionElement)

        $WindowsTargetPlatformVersion = `
            $BuildConfig.SelectSingleNode("$XPathWindowsTargetPlatformVersion", `
                $Namespace)
    } else {
        $WindowsTargetPlatformVersion."#text" = `
            "$GOD_WindowsTargetPlatformVersion"
    }

    $PropertyGroupNoAttribute = `
        $BuildConfig.SelectSingleNode("$XPathPropertyGroupNoAttribute",`
             $Namespace)
    if (-not $PropertyGroupNoAttribute) {
        $PropertyGroupElement = $BuildConfig.CreateElement("PropertyGroup", `
            $Project.NamespaceURI);
        $Project.AppendChild($PropertyGroupElement)

        $PropertyGroupNoAttribute = `
            $BuildConfig.SelectSingleNode("$XPathPropertyGroupNoAttribute", `
                $Namespace)
    }

    $TargetNameNode = $BuildConfig.SelectSingleNode("$XPathTargetName", `
        $Namespace)
    if (-not $TargetNameNode) {
        $TargetNameElement = $BuildConfig.CreateElement("TargetName", `
            $PropertyGroupNoAttribute.NamespaceURI);
        $ConditionAttribute = $BuildConfig.CreateAttribute("Condition")
        $ConditionAttribute.Value = `
            "'`$(Configuration)`|`$(Platform)'=='$Configuration`|$Platform'"
        $TargetNameElement.Attributes.Append($ConditionAttribute)
        $TextNode = $BuildConfig.CreateTextNode("$TargetName")
        $TargetNameElement.AppendChild($TextNode)
        $PropertyGroupNoAttribute.AppendChild($TargetNameElement)

        $TargetNameNode = $BuildConfig.SelectSingleNode("$XPathTargetName",`
             $Namespace)
    } else {
        $TargetNameNode."#text" = "$TargetName"
    }

    $ConfigurationNode = $BuildConfig.SelectSingleNode("$XPathConfiguration", `
        $Namespace)
    if (-not $ConfigurationNode) {
        $PropertyGroupElement = $BuildConfig.CreateElement("PropertyGroup", `
            $Project.NamespaceURI);
        $ConditionAttribute = $BuildConfig.CreateAttribute("Condition")
        $ConditionAttribute.Value = `
            "'`$(Configuration)`|`$(Platform)'=='$Configuration`|$Platform'"
        $PropertyGroupElement.Attributes.Append($ConditionAttribute)
        $LabelAttribute = $BuildConfig.CreateAttribute("Label")
        $LabelAttribute.Value = "Configuration"
        $PropertyGroupElement.Attributes.Append($LabelAttribute)
        $Project.AppendChild($PropertyGroupElement)

        $ConfigurationNode = `
            $BuildConfig.SelectSingleNode("$XPathConfiguration", $Namespace)
    }

    $CharacterSet = $BuildConfig.SelectSingleNode("$XPathCharacterSet", `
        $Namespace)
    if (-not $CharacterSet) {
        $CharacterSetElement = $BuildConfig.CreateElement("CharacterSet", `
            $ConfigurationNode.NamespaceURI);
        $TextNode = $BuildConfig.CreateTextNode("Unicode")
        $CharacterSetElement.AppendChild($TextNode)
        $ConfigurationNode.AppendChild($CharacterSetElement)

        $CharacterSet = `
            $BuildConfig.SelectSingleNode("$XPathCharacterSet", $Namespace)
    } else {
        $CharacterSet."#text" = "Unicode"
    }

    $ItemDefinitionGroup = `
        $BuildConfig.SelectSingleNode("$XPathItemDefinitionGroup", $Namespace)
    if (-not $ItemDefinitionGroup) {
        $ItemDefinitionGroupElement = `
            $BuildConfig.CreateElement("ItemDefinitionGroup", `
                $Project.NamespaceURI);
        $ConditionAttribute = $BuildConfig.CreateAttribute("Condition")
        $ConditionAttribute.Value = `
            "'`$(Configuration)`|`$(Platform)'=='$Configuration`|$Platform'"
        $ItemDefinitionGroupElement.Attributes.Append($ConditionAttribute)
        $Project.AppendChild($ItemDefinitionGroupElement)

        $ItemDefinitionGroup = `
            $BuildConfig.SelectSingleNode("$XPathItemDefinitionGroup", `
            $Namespace)
    }

    $ClCompile = $BuildConfig.SelectSingleNode("$XPathClCompile", $Namespace)
    if (-not $ClCompile) {
        $ClCompileElement = $BuildConfig.CreateElement("ClCompile", `
            $ItemDefinitionGroup.NamespaceURI);
        $ItemDefinitionGroup.AppendChild($ClCompileElement)

        $ClCompile = $BuildConfig.SelectSingleNode("$XPathClCompile", `
            $Namespace)
    }

    if ("$Configuration" -eq "Debug") {
        $RuntimeLibraryValue = "MultiThreadedDebugDLL"
    } else {
        $RuntimeLibraryValue = "MultiThreadedDLL"
    }

    $RuntimeLibrary = `
        $BuildConfig.SelectSingleNode("$XPathRuntimeLibrary", $Namespace)
    if (-not $RuntimeLibrary) {
        $RuntimeLibraryElement = $BuildConfig.CreateElement("RuntimeLibrary", `
            $ClCompile.NamespaceURI);
        $TextNode = $BuildConfig.CreateTextNode("$RuntimeLibraryValue")
        $RuntimeLibraryElement.AppendChild($TextNode)
        $ClCompile.AppendChild($RuntimeLibraryElement)

        $RuntimeLibrary = `
            $BuildConfig.SelectSingleNode("$XPathRuntimeLibrary", $Namespace)
    } else {
        $RuntimeLibrary."#text" = "$RuntimeLibraryValue"
    }

    if ("$Configuration" -eq "Debug") {
        $PdbFile = "`$(OutDir)`$(TargetName).pdb"

        $ProgramDataBaseFileName = `
            $BuildConfig.SelectSingleNode("$XPathProgramDataBaseFileName", `
                $Namespace)
        if (-not $ProgramDataBaseFileName) {
            $ProgramDataBaseFileNameElement = `
                $BuildConfig.CreateElement("ProgramDataBaseFileName", `
                    $ClCompile.NamespaceURI);
            $TextNode = $BuildConfig.CreateTextNode("$PdbFile")
            $ProgramDataBaseFileNameElement.AppendChild($TextNode)
            $ClCompile.AppendChild($ProgramDataBaseFileNameElement)

            $ProgramDataBaseFileName = `
                $BuildConfig.SelectSingleNode("$XPathProgramDataBaseFileName", `
                    $Namespace)
        } else {
            $ProgramDataBaseFileName."#text" = "$PdbFile"
        }
    }

    $BuildConfig.Save($Vcxproj)
}

function GOD-RunCmakeBuild {
    Param(
        [Parameter(Mandatory=$True)]
        [String]$Configuration,
        [Parameter(Mandatory=$True)]
        [String]$Platform,
        [Parameter(Mandatory=$True)]
        [String]$TargetName,
        [Parameter(Mandatory=$True)]
        [String]$SourceDirectory,
        [Parameter(Mandatory=$True)]
        [String]$VcxprojName,
        [Parameter(Mandatory=$True)]
        [String]$BuildDirectoryName
    )

    if ("$Configuration" -ne "Debug" -And "$Configuration" -ne "Release") {
        GOD-Fatal -Error "invalid configuration '$Configuration'!"
    }

    if ("$Platform" -ne "Win32" -And "$Platform" -ne "X64") {
        GOD-Fatal -Error "invalid platform '$Configuration'!"
    }

    $BuildDirectory = "$SourceDirectory\$BuildDirectoryName"
    $Vcxproj = "$BuildDirectory\$VcxprojName"

    New-Item -Path "$SourceDirectory" -Name "$BuildDirectoryName" `
        -ItemType "directory"

    $EnvironmentCache = GOD-GetEnvironment

    if ("$Platform" -eq "Win32") {
        GOD-InvokeCmdScript -Script "$GOD_VcVars32Script"
    } else {
        GOD-InvokeCmdScript -Script "$GOD_VcVars64Script"
    }

    & "$GOD_CMakeExecutable" -G "$GOD_CmakeGenerator" `
        -A $Platform `
        -DCMAKE_BUILD_TYPE=$Configuration `
        "$SourceDirectory"
    GOD-DieOnError -Succeeded $? `
        -Error "failed to invoke $GOD_CMakeExecutable!"

    GOD-ApplyBuildSettings `
        -Configuration "$Configuration" `
        -Platform "$Platform" `
        -Vcxproj "$Vcxproj" `
        -TargetName "$TargetName"

    & msbuild /t:clean /t:build "$VcxprojName" `
        /property:Configuration=$Configuration `
        /property:Platform=$Platform
    GOD-DieOnError -Succeeded $? `
        -Error "failed to invoke msbuild!"

    GOD-RestoreEnvironment -OldEnvironment $EnvironmentCache
}

function GOD-RunMsBuild {
    Param(
        [Parameter(Mandatory=$True)]
        [String]$Configuration,
        [Parameter(Mandatory=$True)]
        [String]$Platform,
        [Parameter(Mandatory=$True)]
        [String]$TargetName,
        [Parameter(Mandatory=$True)]
        [String]$SourceDirectory,
        [Parameter(Mandatory=$True)]
        [String]$VcxprojName
    )

    if ("$Configuration" -ne "Debug" -And "$Configuration" -ne "Release") {
        GOD-Fatal -Error "invalid configuration '$Configuration'!"
    }

    if ("$Platform" -ne "Win32" -And "$Platform" -ne "X64") {
        GOD-Fatal -Error "invalid platform '$Configuration'!"
    }

    $Vcxproj = "$SourceDirectory\$VcxprojName"

    $EnvironmentCache = GOD-GetEnvironment

    if ("$Platform" -eq "Win32") {
        GOD-InvokeCmdScript -Script "$GOD_VcVars32Script"
    } else {
        GOD-InvokeCmdScript -Script "$GOD_VcVars64Script"
    }

    GOD-ApplyBuildSettings `
        -Configuration "$Configuration" `
        -Platform "$Platform" `
        -Vcxproj "$Vcxproj" `
        -TargetName "$TargetName"

    & msbuild /t:clean /t:build "$VcxprojName" `
        /property:Configuration=$Configuration `
        /property:Platform=$Platform
    GOD-DieOnError -Succeeded $? `
        -Error "failed to invoke msbuild!"

    GOD-RestoreEnvironment -OldEnvironment $EnvironmentCache
}
