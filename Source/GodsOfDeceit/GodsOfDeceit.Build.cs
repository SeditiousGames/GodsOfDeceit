/**
 * @file
 * @author  Mohammad S. Babaei <info@babaei.net>
 * @version 0.1.0
 *
 * @section LICENSE
 *
 * (The MIT License)
 *
 * Copyright (c) 2018 Mohammad S. Babaei
 * Copyright (c) 2018 Khavaran67
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @section DESCRIPTION
 *
 * Build script for GodsOfDeceit target.
 */


using System;
using System.Collections.Generic;
using System.IO;
using System.Text.RegularExpressions;
using UnrealBuildTool;

public class GodsOfDeceit : ModuleRules
{
    public GUtils Utils;

    public GodsOfDeceit(ReadOnlyTargetRules Target) : base(Target)
    {
        InitializeUtils();

        Utils.Log.Start();

        SetupBuildConfiguration();
        AddEngineModules();
        AddGameModules();
        AddPlugins();
        AddDefinitions();

        Utils.BuildInfo.Print();

        Utils.Log.Stop();
    }

    private void InitializeUtils()
    {
        Utils = new GUtils(this, "GodsOfDeceit");

        /// Order matters, these modules must get initialized before the rest
        Utils.BuildPlatform = new GBuildPlatform(Utils);
        Utils.Path = new GPath(Utils);
        Utils.Log = new GLog(Utils);

        Utils.BuildConfiguration = new GBuildConfiguration(Utils);
        Utils.BuildInfo = new GBuildInfo(Utils);
        Utils.Definitions = new GDefinitions(Utils);
        Utils.EngineModules = new GEngineModules(Utils);
        Utils.GameModules = new GGameModules(Utils);
        Utils.Plugins = new GPlugins(Utils);
        Utils.ThirdParty = new GThirdParty(Utils);
    }

    private void AddDefinitions()
    {
        bool bShippingBuild = Utils.BuildPlatform.IsShippingBuild();
        bool bWindowsBuild = Utils.BuildPlatform.IsWindowsBuild();

        if (bWindowsBuild)
        {
            Utils.Definitions.DefinePublicly("_UNICODE");
            Utils.Definitions.DefinePublicly("UNICODE");
            Utils.Definitions.DefinePublicly("WIN32_LEAN_AND_MEAN");
        }

        if (!bShippingBuild)
        {
            Utils.Definitions.DefinePublicly("GOD_LOGGING");
        }

        Utils.Log.EmptyLine();
    }

    private void AddEngineModules()
    {
        Utils.Log.Info("Adding required engine modules for '{0}'...", Utils.ModuleName);

        Utils.EngineModules.AddCore(true);
        Utils.EngineModules.AddCoreUObject(true);
        Utils.EngineModules.AddEngine(true);
        Utils.EngineModules.AddInputCore(false);

        Utils.Log.EmptyLine();
    }

    private void AddGameModules()
    {
        Utils.Log.Info("Setting up required game modules for '{0}'...", Utils.ModuleName);

        Utils.GameModules.AddCompression(false);
        Utils.GameModules.AddCrypto(false);
        Utils.GameModules.AddLoadingScreen(false);
        Utils.GameModules.AddLog(false);
        Utils.GameModules.AddPersistentData(false);
        Utils.GameModules.AddPlatform(false);
        Utils.GameModules.AddVersion(false);

        Utils.Log.EmptyLine();
    }

    private void AddPlugins()
    {
        Utils.Log.Info("Setting up required plugins for '{0}'...", Utils.ModuleName);

        Utils.Plugins.AddUFSM();
        Utils.Plugins.AddVlcMedia();

        Utils.Log.EmptyLine();
    }

    private void SetupBuildConfiguration()
    {
        Utils.Log.Info("Setting up build configuration for '{0}'...", Utils.ModuleName);

        bool bX64 = Utils.BuildPlatform.IsX64();
        bool bDebugBuild = Utils.BuildPlatform.IsDebugBuild();
        bool bShippingBuild = Utils.BuildPlatform.IsShippingBuild();

        Utils.BuildConfiguration.SetPCHUsage(PCHUsageMode.UseExplicitOrSharedPCHs);
        Utils.BuildConfiguration.SetUseRTTI(false);
        Utils.BuildConfiguration.SetEnableExceptions(false);
        Utils.BuildConfiguration.SetUseAVX(bX64 && !bShippingBuild);
        Utils.BuildConfiguration.SetEnableShadowVariableWarnings(true);
        Utils.BuildConfiguration.SetEnableUndefinedIdentifierWarnings(true);
        Utils.BuildConfiguration.SetFasterWithoutUnity(bDebugBuild);
        Utils.BuildConfiguration.SetOptimizeCode(bDebugBuild ? CodeOptimization.Never : CodeOptimization.Always);

        Utils.Log.EmptyLine();
    }
}

public class GBuildConfiguration
{
    private GUtils Utils;

    public GBuildConfiguration(GUtils Utils)
    {
        this.Utils = Utils;
    }

    public void SetEnableExceptions(bool bEnableExceptions)
    {
        Utils.Module.bEnableExceptions = bEnableExceptions;

        if (bEnableExceptions)
        {
            Utils.Log.Info("Enabling exception handling...");
        }
        else
        {
            Utils.Log.Info("Disabling exception handling...");
        }
    }

    public void SetEnableShadowVariableWarnings(bool bEnableShadowVariableWarnings)
    {
        Utils.Module.bEnableShadowVariableWarnings = bEnableShadowVariableWarnings;

        if (bEnableShadowVariableWarnings)
        {
            Utils.Log.Info("Enabling warnings for shadowed variables...");
        }
        else
        {
            Utils.Log.Info("Disabling warnings for shadowed variables...");
        }
    }

    public void SetEnableUndefinedIdentifierWarnings(bool bEnableUndefinedIdentifierWarnings)
    {
        Utils.Module.bEnableUndefinedIdentifierWarnings = bEnableUndefinedIdentifierWarnings;

        if (bEnableUndefinedIdentifierWarnings)
        {
            Utils.Log.Info("Enabling warnings for using undefined identifiers in #if expressions...");
        }
        else
        {
            Utils.Log.Info("Disabling warnings for using undefined identifiers in #if expressions...");
        }
    }

    public void SetFasterWithoutUnity(bool bFasterWithoutUnity)
    {
        Utils.Module.bFasterWithoutUnity = bFasterWithoutUnity;

        if (bFasterWithoutUnity)
        {
            Utils.Log.Info("Enabling non-unity builds.....");
        }
        else
        {
            Utils.Log.Info("Enabling unity builds...");
        }
    }

    public void SetOptimizeCode(ModuleRules.CodeOptimization OptimizeCode)
    {
        bool bDebugBuild = Utils.BuildPlatform.IsDebugBuild();
        bool bShippingBuild = Utils.BuildPlatform.IsShippingBuild();

        Utils.Module.OptimizeCode = OptimizeCode;

        switch (OptimizeCode)
        {
            case ModuleRules.CodeOptimization.Never:
                Utils.Log.Info("Disabling code optimization...");
                break;

            case ModuleRules.CodeOptimization.InNonDebugBuilds:
                if (bDebugBuild)
                {
                    Utils.Log.Info("Debug build detected; disabling code optimization...");
                }
                else
                {
                    Utils.Log.Info("Non-debug build detected; enabling code optimization...");
                }
                break;

            case ModuleRules.CodeOptimization.InShippingBuildsOnly:
                if (bShippingBuild)
                {
                    Utils.Log.Info("Shipping build detected; enabling code optimization...");
                }
                else
                {
                    Utils.Log.Info("Non-shipping build detected; disabling code optimization...");
                }
                break;

            case ModuleRules.CodeOptimization.Always:
                Utils.Log.Info("Enabling code optimization...");
                break;

            case ModuleRules.CodeOptimization.Default:
                if (bDebugBuild)
                {
                    Utils.Log.Info("Debug build detected; disabling code optimization for game modules...");
                }
                else
                {
                    Utils.Log.Info("Non-debug build detected; enabling code optimization for game modules...");
                }
                break;

            default:
                Utils.Log.Warning("Unknown code optimization settings: '{0}'!", OptimizeCode.ToString());
                break;
        }
    }

    public void SetPCHUsage(ModuleRules.PCHUsageMode PCHUsage)
    {
        Utils.Module.PCHUsage = PCHUsage;

        switch (PCHUsage)
        {
            case ModuleRules.PCHUsageMode.Default:
                Utils.Log.Info("Enabling shared PCH usage for engine modules only...");
                Utils.Log.Info("Disabling shared PCH usage for game modules...");
                break;

            case ModuleRules.PCHUsageMode.NoSharedPCHs:
                Utils.Log.Info("Disabling shared PCH usage...");
                break;

            case ModuleRules.PCHUsageMode.UseSharedPCHs:
                Utils.Log.Info("Enabling shared PCH usage...");
                break;

            case ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs:
                Utils.Log.Info("Enabling explicit or shared PCH usage...");
                break;

            default:
                Utils.Log.Warning("Unknown PCH usage mode: '{0}'!", PCHUsage.ToString());
                break;
        }
    }

    public void SetUseAVX(bool bUseAVX)
    {
        Utils.Module.bUseAVX = bUseAVX;

        if (bUseAVX)
        {
            Utils.Log.Info("Enabling AVX instructions...");
        }
        else
        {
            Utils.Log.Info("Disabling AVX instructions...");
        }
    }

    public void SetUseRTTI(bool bUseRTTI)
    {
        Utils.Module.bUseRTTI = bUseRTTI;

        if (bUseRTTI)
        {
            Utils.Log.Info("Enabling run-time type identification...");
        }
        else
        {
            Utils.Log.Info("Disabling run-time type identification...");
        }
    }
}

public class GBuildPlatform
{
    private GUtils Utils;

    public GBuildPlatform(GUtils Utils)
    {
        this.Utils = Utils;
    }

    public bool IsX64()
    {
        return (Utils.Module.Target.Platform == UnrealTargetPlatform.Linux || Utils.Module.Target.Platform == UnrealTargetPlatform.Win64);
    }

    public bool IsX86()
    {
        return (Utils.Module.Target.Platform == UnrealTargetPlatform.Win32);
    }

    public bool IsDevelopmentBuild()
    {
        return (Utils.Module.Target.Configuration == UnrealTargetConfiguration.Development);
    }

    public bool IsDebugBuild()
    {
        return (Utils.Module.Target.Configuration == UnrealTargetConfiguration.Debug || Utils.Module.Target.Configuration == UnrealTargetConfiguration.DebugGame);
    }

    public bool IsLinuxBuild()
    {
        return (Utils.Module.Target.Platform == UnrealTargetPlatform.Linux);
    }

    public bool IsShippingBuild()
    {
        return (Utils.Module.Target.Configuration == UnrealTargetConfiguration.Shipping);
    }

    public bool IsTestBuild()
    {
        return (Utils.Module.Target.Configuration == UnrealTargetConfiguration.Test);
    }

    public bool IsWindowsBuild()
    {
        return (Utils.Module.Target.Platform == UnrealTargetPlatform.Win32 || Utils.Module.Target.Platform == UnrealTargetPlatform.Win64);
    }
}

public class GDefinitions
{
    private GUtils Utils;

    public GDefinitions(GUtils Utils)
    {
        this.Utils = Utils;
    }

    public void DefinePublicly(string Definition)
    {
        AddPublicDefinition(Definition);
    }

    public void DefinePrivately(string Definition)
    {
        AddPrivateDefinition(Definition);
    }

    private void AddPublicDefinition(string Definition)
    {
        Utils.Log.Info("Defining public definition '{0}'...", Definition);

        Utils.Module.PublicDefinitions.Add(Definition);
    }

    private void AddPrivateDefinition(string Definition)
    {
        Utils.Log.Info("Defining private definition '{0}'...", Definition);

        Utils.Module.PrivateDefinitions.Add(Definition);
    }
}

public class GEngineModules
{
    private GUtils Utils;

    public GEngineModules(GUtils Utils)
    {
        this.Utils = Utils;
    }

    public void AddAssetTools(bool bPublic)
    {
        if (bPublic)
        {
            AddPublicDependencyModuleName("AssetTools");
            AddPublicIncludePathModuleName("AssetTools");
        }
        else
        {
            AddPrivateDependencyModuleName("AssetTools");
            AddPrivateIncludePathModuleName("AssetTools");
        }
    }

    public void AddCore(bool bPublic)
    {
        if (bPublic)
        {
            AddPublicDependencyModuleName("Core");
        }
        else
        {
            AddPublicDependencyModuleName("Core");
        }
    }

    public void AddCoreUObject(bool bPublic)
    {
        if (bPublic)
        {
            AddPublicDependencyModuleName("CoreUObject");
        }
        else
        {
            AddPublicDependencyModuleName("CoreUObject");
        }
    }

    public void AddEngine(bool bPublic)
    {
        if (bPublic)
        {
            AddPublicDependencyModuleName("Engine");
        }
        else
        {
            AddPublicDependencyModuleName("Engine");
        }
    }

    public void AddInputCore(bool bPublic)
    {
        if (bPublic)
        {
            AddPublicDependencyModuleName("InputCore");
        }
        else
        {
            AddPublicDependencyModuleName("InputCore");
        }
    }

    public void AddSlate(bool bPublic)
    {
        if (bPublic)
        {
            AddPublicDependencyModuleName("Slate");
        }
        else
        {
            AddPrivateDependencyModuleName("Slate");
        }
        }

    public void AddSlateCore(bool bPublic)
    {
        if (bPublic)
        {
            AddPublicDependencyModuleName("SlateCore");
        }
        else
        {
            AddPrivateDependencyModuleName("SlateCore");
        }
    }

    public void AddUnrealEd(bool bPublic)
    {
        if (bPublic)
        {
            AddPublicDependencyModuleName("UnrealEd");
            AddPublicIncludePathModuleName("UnrealEd");
        }
        else
        {
            AddPrivateDependencyModuleName("UnrealEd");
            AddPrivateIncludePathModuleName("UnrealEd");
        }
    }

    private void AddPublicIncludePathModuleName(string Plugin)
    {
        Utils.Log.Info("Adding public include path module '{0}'...", Plugin);

        Utils.Module.PublicIncludePathModuleNames.Add(Plugin);
    }

    private void AddPublicDependencyModuleName(string Plugin)
    {
        Utils.Log.Info("Adding public dependency module '{0}'...", Plugin);

        Utils.Module.PublicDependencyModuleNames.Add(Plugin);
    }

    private void AddPrivateIncludePathModuleName(string Plugin)
    {
        Utils.Log.Info("Adding private include path module '{0}'...", Plugin);

        Utils.Module.PrivateIncludePathModuleNames.Add(Plugin);
    }

    private void AddPrivateDependencyModuleName(string Plugin)
    {
        Utils.Log.Info("Adding private dependency module '{0}'...", Plugin);

        Utils.Module.PrivateDependencyModuleNames.Add(Plugin);
    }
}

public class GGameModules
{
    private GUtils Utils;

    public GGameModules(GUtils Utils)
    {
        this.Utils = Utils;
    }

    public void AddCompression(bool bPublic)
    {
        if (bPublic)
        {
            AddPublicDependencyModuleName("GodsOfDeceitCompression");
        }
        else
        {
            AddPrivateDependencyModuleName("GodsOfDeceitCompression");
        }
    }

    public void AddCompressionImpl(bool bPublic)
    {
        if (bPublic)
        {
            AddPublicDependencyModuleName("GodsOfDeceitCompressionImpl");
        }
        else
        {
            AddPrivateDependencyModuleName("GodsOfDeceitCompressionImpl");
        }
    }

    public void AddCrypto(bool bPublic)
    {
        if (bPublic)
        {
            AddPublicDependencyModuleName("GodsOfDeceitCrypto");
        }
        else
        {
            AddPrivateDependencyModuleName("GodsOfDeceitCrypto");
        }
    }

    public void AddCryptoImpl(bool bPublic)
    {
        if (bPublic)
        {
            AddPublicDependencyModuleName("GodsOfDeceitCryptoImpl");
        }
        else
        {
            AddPrivateDependencyModuleName("GodsOfDeceitCryptoImpl");
        }
    }

    public void AddGodsOfDeceit(bool bPublic)
    {
        if (bPublic)
        {
            AddPublicDependencyModuleName("GodsOfDeceit");
        }
        else
        {
            AddPrivateDependencyModuleName("GodsOfDeceit");
        }
    }

    public void AddEditor(bool bPublic)
    {
        if (bPublic)
        {
            AddPublicDependencyModuleName("GodsOfDeceitEditor");
        }
        else
        {
            AddPrivateDependencyModuleName("GodsOfDeceitEditor");
        }
    }

    public void AddHacks(bool bPublic)
    {
        if (bPublic)
        {
            AddPublicDependencyModuleName("GodsOfDeceitHacks");
        }
        else
        {
            AddPrivateDependencyModuleName("GodsOfDeceitHacks");
        }
    }

    public void AddInterop(bool bPublic)
    {
        if (bPublic)
        {
            AddPublicDependencyModuleName("GodsOfDeceitInterop");
        }
        else
        {
            AddPrivateDependencyModuleName("GodsOfDeceitInterop");
        }
    }

    public void AddLoadingScreen(bool bPublic)
    {
        if (bPublic)
        {
            AddPublicDependencyModuleName("GodsOfDeceitLoadingScreen");
        }
        else
        {
            AddPrivateDependencyModuleName("GodsOfDeceitLoadingScreen");
        }
    }

    public void AddLog(bool bPublic)
    {
        if (bPublic)
        {
            AddPublicDependencyModuleName("GodsOfDeceitLog");
        }
        else
        {
            AddPrivateDependencyModuleName("GodsOfDeceitLog");
        }
    }

    public void AddPersistentData(bool bPublic)
    {
        if (bPublic)
        {
            AddPublicDependencyModuleName("GodsOfDeceitPersistentData");
        }
        else
        {
            AddPrivateDependencyModuleName("GodsOfDeceitPersistentData");
        }
    }

    public void AddPersistentDataImpl(bool bPublic)
    {
        if (bPublic)
        {
            AddPublicDependencyModuleName("GodsOfDeceitPersistentDataImpl");
        }
        else
        {
            AddPrivateDependencyModuleName("GodsOfDeceitPersistentDataImpl");
        }
    }

    public void AddPlatform(bool bPublic)
    {
        if (bPublic)
        {
            AddPublicDependencyModuleName("GodsOfDeceitPlatform");
        }
        else
        {
            AddPrivateDependencyModuleName("GodsOfDeceitPlatform");
        }
    }

    public void AddPlatformImpl(bool bPublic)
    {
        if (bPublic)
        {
            AddPublicDependencyModuleName("GodsOfDeceitPlatformImpl");
        }
        else
        {
            AddPrivateDependencyModuleName("GodsOfDeceitPlatformImpl");
        }
    }

    public void AddTypes(bool bPublic)
    {
        if (bPublic)
        {
            AddPublicDependencyModuleName("GodsOfDeceitTypes");
        }
        else
        {
            AddPrivateDependencyModuleName("GodsOfDeceitTypes");
        }
    }

    public void AddVersion(bool bPublic)
    {
        if (bPublic)
        {
            AddPublicDependencyModuleName("GodsOfDeceitVersion");
        }
        else
        {
            AddPrivateDependencyModuleName("GodsOfDeceitVersion");
        }
    }

    public void AddVersionImpl(bool bPublic)
    {
        if (bPublic)
        {
            AddPublicDependencyModuleName("GodsOfDeceitVersionImpl");
        }
        else
        {
            AddPrivateDependencyModuleName("GodsOfDeceitVersionImpl");
        }
    }

    private void AddPublicIncludePathModuleName(string Plugin)
    {
        Utils.Log.Info("Adding public include path module '{0}'...", Plugin);

        Utils.Module.PublicIncludePathModuleNames.Add(Plugin);
    }

    private void AddPublicDependencyModuleName(string Plugin)
    {
        Utils.Log.Info("Adding public dependency module '{0}'...", Plugin);

        Utils.Module.PublicDependencyModuleNames.Add(Plugin);
    }

    private void AddPrivateIncludePathModuleName(string Plugin)
    {
        Utils.Log.Info("Adding private include path module '{0}'...", Plugin);

        Utils.Module.PrivateIncludePathModuleNames.Add(Plugin);
    }

    private void AddPrivateDependencyModuleName(string Plugin)
    {
        Utils.Log.Info("Adding private dependency module '{0}'...", Plugin);

        Utils.Module.PrivateDependencyModuleNames.Add(Plugin);
    }
}

public class GLog
{
    private GUtils Utils;

    public GLog(GUtils Utils)
    {
        this.Utils = Utils;
    }

    public void EmptyLine()
    {
        Console.WriteLine();
    }

    public void Debug(string Format, params object[] Args)
    {
        Log("DEBUG", Format, Args);
    }

    public void Error(string Format, params object[] Args)
    {
        Log("ERROR", Format, Args);
    }

    public void Fatal(string Format, params object[] Args)
    {
        Log("FATAL", Format, Args);
    }

    public void Info(string Format, params object[] Args)
    {
        Log("INFO", Format, Args);
    }

    public void Trace(string Format, params object[] Args)
    {
        Log("TRACE", Format, Args);
    }

    public void Warning(string Format, params object[] Args)
    {
        Log("WARNING", Format, Args);
    }

    public void Start()
    {
        if (Utils.ModuleName == "GodsOfDeceit") {
            EmptyLine();
            EmptyLine();
        }

        Info("Setting up module '{0}'...", Utils.ModuleName);
        EmptyLine();

        Info("Target build configuration is '{0}'.", Utils.Module.Target.Configuration);
        EmptyLine();
    }

    public void Stop()
    {
        Info("Finished setting up module '{0}'.", Utils.ModuleName);
        EmptyLine();
    }

    private void Log(string Type, string Format, params object[] Args)
    {
        DateTime LocalDate = DateTime.Now;

        Console.WriteLine(string.Format("[ {0} {1} ] {2}", LocalDate.ToString(), Type, string.Format(Format, Args)));
    }
}

public class GPath
{
    public string ModulePath { get; private set; }
    public string ProjectPath { get; private set; }
    public string GitDirectoryPath { get; private set; }
    public string PluginsPath { get; private set; }
    public string ThirdPartyPath { get; private set; }
    public string ThirdPartyIncludePath { get; private set; }
    public string LinuxThirdPartyDebugLibraryPath { get; private set; }
    public string LinuxThirdPartyReleaseLibraryPath { get; private set; }
    public string Win32ThirdPartyDebugLibraryPath { get; private set; }
    public string Win32ThirdPartyReleaseLibraryPath { get; private set; }
    public string Win64ThirdPartyDebugLibraryPath { get; private set; }
    public string Win64ThirdPartyReleaseLibraryPath { get; private set; }
    public string ThirdPartyLibraryLinkPath { get; private set; }

    public GPath(GUtils Utils)
    {
        bool bX64 = Utils.BuildPlatform.IsX64();
        bool bX86 = Utils.BuildPlatform.IsX86();
        bool bDebugBuild = Utils.BuildPlatform.IsDebugBuild();
        bool bLinuxBuild = Utils.BuildPlatform.IsLinuxBuild();
        bool bWindowsBuild = Utils.BuildPlatform.IsWindowsBuild();

        ModulePath = Utils.Module.ModuleDirectory;
        ProjectPath = Directory.GetParent(ModulePath).ToString();
        GitDirectoryPath = Path.GetFullPath(Path.Combine(ProjectPath, "..", ".git"));
        PluginsPath = Path.GetFullPath(Path.Combine(ModulePath, "..", "..", "Plugins"));
        ThirdPartyPath = Path.GetFullPath(Path.Combine(ModulePath, "..", "..", "ThirdParty"));
        ThirdPartyIncludePath = Path.GetFullPath(Path.Combine(ThirdPartyPath, "include"));
        LinuxThirdPartyDebugLibraryPath = Path.GetFullPath(Path.Combine(ThirdPartyPath, "lib", "linux", "debug"));
        LinuxThirdPartyReleaseLibraryPath = Path.GetFullPath(Path.Combine(ThirdPartyPath, "lib", "linux", "release"));
        Win32ThirdPartyDebugLibraryPath = Path.GetFullPath(Path.Combine(ThirdPartyPath, "lib", "win32", "debug"));
        Win32ThirdPartyReleaseLibraryPath = Path.GetFullPath(Path.Combine(ThirdPartyPath, "lib", "win32", "release"));
        Win64ThirdPartyDebugLibraryPath = Path.GetFullPath(Path.Combine(ThirdPartyPath, "lib", "win64", "debug"));
        Win64ThirdPartyReleaseLibraryPath = Path.GetFullPath(Path.Combine(ThirdPartyPath, "lib", "win64", "release"));
        
        if (bLinuxBuild)
        {
            if (bDebugBuild)
            {
                ThirdPartyLibraryLinkPath = LinuxThirdPartyDebugLibraryPath;
            }
            else
            {
                ThirdPartyLibraryLinkPath = LinuxThirdPartyReleaseLibraryPath;
            }
        }
        else if (bWindowsBuild)
        {
            if (bX64)
            {
                if (bDebugBuild)
                {
                    ThirdPartyLibraryLinkPath = Win64ThirdPartyDebugLibraryPath;
                }
                else
                {
                    ThirdPartyLibraryLinkPath = Win64ThirdPartyReleaseLibraryPath;
                }
            }
            else if (bX86)
            {
                if (bDebugBuild)
                {
                    ThirdPartyLibraryLinkPath = Win32ThirdPartyDebugLibraryPath;
                }
                else
                {
                    ThirdPartyLibraryLinkPath = Win32ThirdPartyReleaseLibraryPath;
                }
            }
            else
            {
                ThirdPartyLibraryLinkPath = string.Empty;
            }
        }
        else
        {
            ThirdPartyLibraryLinkPath = string.Empty;
        }
    }
}

public class GPlugins
{
    private GUtils Utils;

    public GPlugins(GUtils Utils)
    {
        this.Utils = Utils;
    }

    public void AddUFSM()
    {
        AddPrivateDependencyModuleName("UFSM");
    }

    public void AddVlcMedia()
    {
        AddPrivateDependencyModuleName("VlcMedia");
    }

    private void AddPublicDependencyModuleName(string Plugin)
    {
        Utils.Log.Info("Adding public dependency module '{0}'...", Plugin);

        Utils.Module.PublicDependencyModuleNames.Add(Plugin);
    }

    private void AddPrivateDependencyModuleName(string Plugin)
    {
        Utils.Log.Info("Adding private dependency module '{0}'...", Plugin);

        Utils.Module.PrivateDependencyModuleNames.Add(Plugin);
    }
}

public class GThirdParty
{
    private GUtils Utils;

    public GThirdParty(GUtils Utils)
    {
        this.Utils = Utils;
    }

    public void AddBoost()
    {
        bool bLinuxBuild = Utils.BuildPlatform.IsLinuxBuild();
        bool bWindowsBuild = Utils.BuildPlatform.IsWindowsBuild();

        if (bWindowsBuild)
        {
            Utils.Definitions.DefinePublicly("BOOST_DISABLE_ABI_HEADERS");

            /// NOTE
            /// Make Boost.WinAPI target Windows 7, where possible
            /// https://msdn.microsoft.com/en-us/library/6sehtctf.aspx
            Utils.Definitions.DefinePublicly("BOOST_USE_WINAPI_VERSION=0x0601");
        }

        Utils.Definitions.DefinePublicly("BOOST_UUID_USE_SSE41");

        AddPublicSystemIncludePath(Utils.Path.ThirdPartyIncludePath);
        AddPublicLibraryPath(Utils.Path.ThirdPartyLibraryLinkPath);

        DirectoryInfo LibrariesDirectoryInfo = new DirectoryInfo(Utils.Path.ThirdPartyLibraryLinkPath);

        if (bLinuxBuild)
        {
            FileInfo[] LibrariesFileInfo = LibrariesDirectoryInfo.GetFiles("libboost_*.a", SearchOption.TopDirectoryOnly);

            foreach (FileInfo LibraryFileInfo in LibrariesFileInfo)
            {
                Regex LibraryRegex = new Regex("(^lib)(.*)(\\.a$)");
                Match LibraryMatch = LibraryRegex.Match(LibraryFileInfo.Name);

                if (LibraryMatch.Success) {
                    string LibraryName = LibraryMatch.Groups[2].Value;

                    AddPublicAdditionalLibrary(LibraryName);
                }
            }
        }
        else if (bWindowsBuild)
        {
            FileInfo[] LibrariesFileInfo = LibrariesDirectoryInfo.GetFiles("libboost_*.lib", SearchOption.TopDirectoryOnly);

            foreach (FileInfo LibraryFileInfo in LibrariesFileInfo)
            {
                AddPublicAdditionalLibrary(LibraryFileInfo.Name);
            }
        }
    }

    public void AddCereal()
    {
        bool bWindowsBuild = Utils.BuildPlatform.IsWindowsBuild();

        /// NOTE
        /// Workaround for Windows/MSVC conflicting macros 'min/max'
        /// used by cereal
        if (bWindowsBuild)
        {
            Utils.Definitions.DefinePublicly("NOMINMAX");
        }

        AddPublicSystemIncludePath(Utils.Path.ThirdPartyIncludePath);
    }

    public void AddCppDB()
    {
        bool bDebugBuild = Utils.BuildPlatform.IsDebugBuild();
        bool bLinuxBuild = Utils.BuildPlatform.IsLinuxBuild();
        bool bWindowsBuild = Utils.BuildPlatform.IsWindowsBuild();

        AddPublicSystemIncludePath(Utils.Path.ThirdPartyIncludePath);
        AddPublicLibraryPath(Utils.Path.ThirdPartyLibraryLinkPath);

        if (bLinuxBuild)
        {
            AddPublicAdditionalLibrary("cppdb");
            AddPublicAdditionalLibrary("cppdb_sqlite3");
        }
        else if (bWindowsBuild)
        {
            if (bDebugBuild)
            {
                AddPublicAdditionalLibrary("libcppdbd.lib");
                AddPublicAdditionalLibrary("libcppdb_sqlite3d.lib");
            }
            else
            {
                AddPublicAdditionalLibrary("libcppdb.lib");
                AddPublicAdditionalLibrary("libcppdb_sqlite3.lib");
            }
        }
    }

    public void AddCryptoPP()
    {
        bool bDebugBuild = Utils.BuildPlatform.IsDebugBuild();
        bool bLinuxBuild = Utils.BuildPlatform.IsLinuxBuild();
        bool bWindowsBuild = Utils.BuildPlatform.IsWindowsBuild();

        /// NOTE
        /// Prior to v5.0.0 LLVM/Clang won't be able to handle SSE2
        /// v6.0.0 still does not support ssse3
        if (bLinuxBuild)
        {
            Utils.Definitions.DefinePublicly("CRYPTOPP_DISABLE_ASM");
        }

        AddPublicSystemIncludePath(Utils.Path.ThirdPartyIncludePath);
        AddPublicLibraryPath(Utils.Path.ThirdPartyLibraryLinkPath);

        if (bLinuxBuild)
        {
            AddPublicAdditionalLibrary("cryptopp");
        }
        else if (bWindowsBuild)
        {
            if (bDebugBuild)
            {
                AddPublicAdditionalLibrary("cryptlibd.lib");
            }
            else
            {
                AddPublicAdditionalLibrary("cryptlib.lib");
            }
        }
    }

    public void AddFMT()
    {
        bool bDebugBuild = Utils.BuildPlatform.IsDebugBuild();
        bool bLinuxBuild = Utils.BuildPlatform.IsLinuxBuild();
        bool bWindowsBuild = Utils.BuildPlatform.IsWindowsBuild();

        AddPublicSystemIncludePath(Utils.Path.ThirdPartyIncludePath);
        AddPublicLibraryPath(Utils.Path.ThirdPartyLibraryLinkPath);

        if (bLinuxBuild)
        {
            if (bDebugBuild)
            {
                AddPublicAdditionalLibrary("fmtd");
            }
            else
            {
                AddPublicAdditionalLibrary("fmt");
            }
        }
        else if (bWindowsBuild)
        {
            if (bDebugBuild)
            {
                AddPublicAdditionalLibrary("fmtd.lib");
            }
            else
            {
                AddPublicAdditionalLibrary("fmt.lib");
            }
        }
    }

    public void AddSQLite3()
    {
        bool bDebugBuild = Utils.BuildPlatform.IsDebugBuild();
        bool bLinuxBuild = Utils.BuildPlatform.IsLinuxBuild();
        bool bWindowsBuild = Utils.BuildPlatform.IsWindowsBuild();

        AddPublicSystemIncludePath(Utils.Path.ThirdPartyIncludePath);
        AddPublicLibraryPath(Utils.Path.ThirdPartyLibraryLinkPath);

        if (bLinuxBuild)
        {
            AddPublicAdditionalLibrary("sqlite3");
        }
        else if (bWindowsBuild)
        {
            if (bDebugBuild)
            {
                AddPublicAdditionalLibrary("sqlite3d.lib");
            }
            else
            {
                AddPublicAdditionalLibrary("sqlite3.lib");
            }
        }
    }

    private void AddPublicAdditionalLibrary(string Library)
    {
        Utils.Log.Info("Adding public additional library '{0}'...", Library);

        Utils.Module.PublicAdditionalLibraries.Add(Library);
    }

    private void AddPublicLibraryPath(string Path)
    {
        Utils.Log.Info("Adding public library Path '{0}'...", Path);

        Utils.Module.PublicLibraryPaths.Add(Path);
    }

    private void AddPublicSystemIncludePath(string Path)
    {
        Utils.Log.Info("Adding public system include path '{0}'...", Path);

        Utils.Module.PublicSystemIncludePaths.Add(Path);
    }
}

public class GBuildInfo
{
    public string Company { get; private set; }
    public string Name { get; private set; }
    public string InternalName { get; private set; }
    public string Description { get; private set; }
    public string Copyright { get; private set; }
    public int VersionMajor { get; private set; }
    public int VersionMinor { get; private set; }
    public int VersionPatch { get; private set; }
    public string Branch { get; private set; }
    public string ShortRevisionHash { get; private set; }
    public string Version { get; private set; }
    public string Revision { get; private set; }
    public string BuildHost { get; private set; }

    private GUtils Utils;
    
    public GBuildInfo(GUtils Utils)
    {
        this.Utils = Utils;

        Company = "Khavaran67 and Mohammad S. Babaei";
        Name = "Gods of Deceit";
        InternalName = "GOD";
        Description = "A first-person shooter game written and developed in C++ and Unreal Engine 4.";
        Copyright = String.Format("(C) {0} {1}. All Rights Reserved.", DateTime.Now.Year.ToString(), Company);
        VersionMajor = 0;
        VersionMinor = 0;
        VersionPatch = 1;
        Branch = GetBranch();
        ShortRevisionHash = GetShortRevisionHash();
        this.Version = String.Format("{0}.{1}.{2}", VersionMajor, VersionMinor, VersionPatch);

        if (!string.IsNullOrEmpty(Branch) && !string.IsNullOrEmpty(ShortRevisionHash))
        {
            Revision = String.Format("{0}-{1}", Branch, ShortRevisionHash);
        }
        else if (!string.IsNullOrEmpty(Branch))
        {
            Revision = Branch;
        }
        else if (!string.IsNullOrEmpty(ShortRevisionHash))
        {
            Revision = ShortRevisionHash;
        }
        else
        {
            Revision = String.Empty;
        }

        BuildHost = System.Net.Dns.GetHostName();
    }

    public void Print()
    {
        Utils.Log.Info("Build information for module: '{0}'", Utils.ModuleName);

        Utils.Log.Info("Company Name: {0}", Company);
        Utils.Log.Info("Product Name: {0}", Name);
        Utils.Log.Info("Product Internal Name: {0}", InternalName);
        Utils.Log.Info("Product Description: {0}", Description);
        Utils.Log.Info("Copyright Notice: {0}", Copyright);
        Utils.Log.Info("Product Major Version: {0}", VersionMajor);
        Utils.Log.Info("Product Minor Version: {0}", VersionMinor);
        Utils.Log.Info("Product Patch Version: {0}", VersionPatch);
        Utils.Log.Info("Branch Name: {0}", Branch);
        Utils.Log.Info("Short Revision Hash: {0}", ShortRevisionHash);
        Utils.Log.Info("Version: {0}", this.Version);
        Utils.Log.Info("Revision: {0}", Revision);
        Utils.Log.Info("Build Host: {0}", BuildHost);

        Utils.Log.EmptyLine();
    }

    private string GetBranch()
    {
        bool bWindowsBuild = Utils.BuildPlatform.IsWindowsBuild();

        try
        {
            System.Diagnostics.Process Process = new System.Diagnostics.Process();
            Process.StartInfo.FileName = bWindowsBuild ? "git.exe" : "git";
            Process.StartInfo.Arguments = "rev-parse --abbrev-ref HEAD";
            Process.StartInfo.UseShellExecute = false;
            Process.StartInfo.RedirectStandardOutput = true;
            Process.StartInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;
            Process.StartInfo.CreateNoWindow = true;
            Process.StartInfo.WorkingDirectory = Utils.Path.ProjectPath;
            Process.Start();

            string Branch = Process.StandardOutput.ReadToEnd().Trim();
            Process.WaitForExit();

            return Branch;
        }

        catch (System.ObjectDisposedException ex)
        {
            Utils.Log.Error(ex.Message);
        }

        catch (System.InvalidOperationException ex)
        {
            Utils.Log.Error(ex.Message);
        }

        catch (System.ComponentModel.Win32Exception ex)
        {
            Utils.Log.Error(ex.Message);
        }

        catch (System.Exception ex)
        {
            Utils.Log.Error(ex.Message);
        }

        Utils.Log.Warning("Warning: cannot get branch name through git executable; setting branch name to an empty string!");

        return string.Empty;
    }

    private string GetShortRevisionHash()
    {
        bool bWindowsBuild = Utils.BuildPlatform.IsWindowsBuild();

        try {
            System.Diagnostics.Process Process = new System.Diagnostics.Process();
            Process.StartInfo.FileName = bWindowsBuild ? "git.exe" : "git";
            Process.StartInfo.Arguments = String.Format(
                        "--git-dir=\"{0}\" --work-tree=\"{1}\" describe --always",
                        Utils.Path.GitDirectoryPath, Utils.Path.ProjectPath);
            Process.StartInfo.UseShellExecute = false;
            Process.StartInfo.RedirectStandardOutput = true;
            Process.StartInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;
            Process.StartInfo.CreateNoWindow = true;
            Process.StartInfo.WorkingDirectory = Utils.Path.ProjectPath;
            Process.Start();

            string RevisionHash = Process.StandardOutput.ReadToEnd().Trim();
            Process.WaitForExit();

            return RevisionHash;
        }

        catch (System.ObjectDisposedException ex)
        {
            Utils.Log.Error(ex.Message);
        }

        catch (System.InvalidOperationException ex)
        {
            Utils.Log.Error(ex.Message);
        }

        catch (System.ComponentModel.Win32Exception ex)
        {
            Utils.Log.Error(ex.Message);
        }

        catch (System.Exception ex)
        {
            Utils.Log.Error(ex.Message);
        }

        Utils.Log.Warning("Warning: cannot get revision number name through git executable; setting revision number to an empty string!");

        return string.Empty;
    }
}

public class GUtils : Object
{
    public GBuildConfiguration BuildConfiguration;
    public GBuildInfo BuildInfo;
    public GBuildPlatform BuildPlatform;
    public GDefinitions Definitions;
    public GEngineModules EngineModules;
    public GGameModules GameModules;
    public GLog Log;
    public GPath Path;
    public GPlugins Plugins;
    public GThirdParty ThirdParty;

    public ModuleRules Module;
    public string ModuleName;

    public GUtils(ModuleRules Module, string ModuleName)
    {
        this.Module = Module;
        this.ModuleName = ModuleName;
    }
}
