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
using UnrealBuildTool;

public class GodsOfDeceit : ModuleRules
{
    public GUtils Utils;

    public GodsOfDeceit(ReadOnlyTargetRules Target) : base(Target)
    {
        Utils = new GUtils(this);
        Utils.BuildPlatform = new GBuildPlatform(Utils);
        Utils.Definitions = new GDefinitions(Utils);
        Utils.EngineModules = new GEngineModules(Utils);
        Utils.Log = new GLog(Utils);
        Utils.Path = new GPath(Utils);
        Utils.Plugins = new GPlugins(Utils);
        Utils.ThirdParty = new GThirdParty(Utils);

        Utils.Log.Start();

        SetBuildConfiguration();
        AddEngineModules();
        AddPlugins();
        AddDefinitions();
        AddThirdPartyLibraries();

        Utils.Log.Stop();
    }

    private void AddDefinitions()
    {
        bool bWindowsBuild = Utils.BuildPlatform.IsWindowsBuild();

        if (bWindowsBuild)
        {
            Utils.Definitions.DefinePublicly("_UNICODE");
            Utils.Definitions.DefinePublicly("UNICODE");
            Utils.Definitions.DefinePublicly("WIN32_LEAN_AND_MEAN");
        }

        Utils.Log.EmptyLine();
    }

    private void AddEngineModules()
    {
        Utils.EngineModules.AddCore();
        Utils.EngineModules.AddCoreUObject();
        Utils.EngineModules.AddEngine();
        Utils.EngineModules.AddInputCore();

        Utils.Log.EmptyLine();
    }

    private void AddPlugins()
    {
        Utils.Plugins.AddUFSM();
        Utils.Plugins.AddVlcMedia();

        Utils.Log.EmptyLine();
    }

    private void AddThirdPartyLibraries()
    {
        Utils.ThirdParty.AddBoost();
        Utils.Log.EmptyLine();

        Utils.ThirdParty.AddCereal();
        Utils.Log.EmptyLine();

        Utils.ThirdParty.AddCppDB();
        Utils.Log.EmptyLine();

        Utils.ThirdParty.AddCryptoPP();
        Utils.Log.EmptyLine();

        Utils.ThirdParty.AddFMT();
        Utils.Log.EmptyLine();

        Utils.ThirdParty.AddSQLite3();
        Utils.Log.EmptyLine();
    }

    private void SetBuildConfiguration()
    {
        bool bX64 = Utils.BuildPlatform.IsX64();
        bool bDebugBuild = Utils.BuildPlatform.IsDebugBuild();
        bool bShippingBuild = Utils.BuildPlatform.IsShippingBuild();

        Utils.Log.Info("Enabling explicit or shared PCH usage mode...");
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        Utils.Log.Info("Enabling run-time type identification...");
        this.bUseRTTI = true;

        Utils.Log.Info("Enabling exception handling...");
        this.bEnableExceptions = true;

        if (bX64 && !bShippingBuild)
        {
            Utils.Log.Info("Enabling AVX instructions...");
            this.bUseAVX = true;
        }

        Utils.Log.Info("Enabling warnings for shadowed variables...");
        this.bEnableShadowVariableWarnings = true;

        Utils.Log.Info("Enabling warnings for using undefined identifiers in #if expressions...");
        this.bEnableUndefinedIdentifierWarnings = true;

        if (bDebugBuild)
        {
            Utils.Log.Info("Enabling non-unity builds...");
            this.bFasterWithoutUnity = true;

            Utils.Log.Info("Turning code optimization off for debugging purpose...");
            this.OptimizeCode = CodeOptimization.Never;
        }
        else
        {
            Utils.Log.Info("Enabling unity builds...");
            this.bFasterWithoutUnity = false;
        }

        Utils.Log.EmptyLine();
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
        Utils.Log.Info("Defining '{0}' as a public definition...", Definition);

        Utils.Module.PublicDefinitions.Add(Definition);
    }

    private void AddPrivateDefinition(string Definition)
    {
        Utils.Log.Info("Defining '{0}' as a private definition...", Definition);

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

    public void AddAssetTools()
    {
        AddPrivateDependencyModuleName("AssetTools");
        AddPrivateIncludePathModuleName("AssetTools");
    }

    public void AddCore()
    {
        AddPublicDependencyModuleName("Core");
    }

    public void AddCoreUObject()
    {
        AddPublicDependencyModuleName("CoreUObject");
    }

    public void AddEngine()
    {
        AddPublicDependencyModuleName("Engine");
    }

    public void AddGodsOfDeceit()
    {
        AddPublicDependencyModuleName("GodsOfDeceit");
    }

    public void AddInputCore()
    {
        AddPublicDependencyModuleName("InputCore");
    }

    public void AddUnrealEd()
    {
        AddPrivateDependencyModuleName("UnrealEd");
        AddPrivateIncludePathModuleName("UnrealEd");
    }

    private void AddPublicIncludePathModuleName(string Plugin)
    {
        Utils.Log.Info("Adding '{0}' as a public include path module...", Plugin);

        Utils.Module.PublicIncludePathModuleNames.Add(Plugin);
    }

    private void AddPublicDependencyModuleName(string Plugin)
    {
        Utils.Log.Info("Adding '{0}' as a public dependency module...", Plugin);

        Utils.Module.PublicDependencyModuleNames.Add(Plugin);
    }

    private void AddPrivateIncludePathModuleName(string Plugin)
    {
        Utils.Log.Info("Adding '{0}' as a private include path module...", Plugin);

        Utils.Module.PrivateIncludePathModuleNames.Add(Plugin);
    }

    private void AddPrivateDependencyModuleName(string Plugin)
    {
        Utils.Log.Info("Adding '{0}' as a private dependency module...", Plugin);

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
        EmptyLine();
        EmptyLine();
        Info("Setting up '{0}' target...", Utils.Module.Target.Name);
        EmptyLine();

        Info("Target build configuration is '{0}'.", Utils.Module.Target.Configuration);
        EmptyLine();
    }

    public void Stop()
    {
        Info("Finished setting up '{0}' target.", Utils.Module.Target.Name);
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
    private GUtils Utils;

    public GPath(GUtils Utils)
    {
        this.Utils = Utils;
    }

    public string ModulePath
    {
        get
        {
            return Utils.Module.ModuleDirectory;
        }
    }

    public string ProjectPath
    {
        get
        {
            return Directory.GetParent(ModulePath).ToString();
        }
    }

    public string GitDirectoryPath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ProjectPath, "..", ".git"));
        }
    }

    public string PluginsPath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ModulePath, "..", "..", "Plugins"));
        }
    }

    public string ThirdPartyPath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ModulePath, "..", "..", "ThirdParty"));
        }
    }

    public string ThirdPartyIncludePath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ThirdPartyPath, "include"));
        }
    }

    public string LinuxThirdPartyDebugLibraryPath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ThirdPartyPath, "lib", "linux", "debug"));
        }
    }

    public string LinuxThirdPartyReleaseLibraryPath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ThirdPartyPath, "lib", "linux", "release"));
        }
    }

    public string Win32ThirdPartyDebugLibraryPath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ThirdPartyPath, "lib", "win32", "debug"));
        }
    }

    public string Win32ThirdPartyReleaseLibraryPath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ThirdPartyPath, "lib", "win32", "release"));
        }
    }

    public string Win64ThirdPartyDebugLibraryPath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ThirdPartyPath, "lib", "win64", "debug"));
        }
    }

    public string Win64ThirdPartyReleaseLibraryPath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ThirdPartyPath, "lib", "win64", "release"));
        }
    }

    public string ThirdPartyLibraryLinkPath
    {
        get
        {
            bool bX64 = Utils.BuildPlatform.IsX64();
            bool bX86 = Utils.BuildPlatform.IsX86();
            bool bDebugBuild = Utils.BuildPlatform.IsDebugBuild();
            bool bLinuxBuild = Utils.BuildPlatform.IsLinuxBuild();
            bool bWindowsBuild = Utils.BuildPlatform.IsWindowsBuild();

            if (bLinuxBuild)
            {
                if (bDebugBuild)
                {
                    return Utils.Path.LinuxThirdPartyDebugLibraryPath;
                }
                else
                {
                    return Utils.Path.LinuxThirdPartyReleaseLibraryPath;
                }
            }

            if (bWindowsBuild)
            {
                if (bX64)
                {
                    if (bDebugBuild)
                    {
                        return Utils.Path.Win32ThirdPartyDebugLibraryPath;
                    }
                    else
                    {
                        return Utils.Path.Win32ThirdPartyReleaseLibraryPath;
                    }
                }

                if (bX86)
                {
                    if (bDebugBuild)
                    {
                        return Utils.Path.Win64ThirdPartyDebugLibraryPath;
                    }
                    else
                    {
                        return Utils.Path.Win64ThirdPartyReleaseLibraryPath;
                    }
                }
            }

            return string.Empty;
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
        Utils.Log.Info("Adding '{0}' third-party plugin as a public dependency module...", Plugin);

        Utils.Module.PublicDependencyModuleNames.Add(Plugin);
    }

    private void AddPrivateDependencyModuleName(string Plugin)
    {
        Utils.Log.Info("Adding '{0}' third-party plugin as a private dependency module...", Plugin);

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
        Utils.Log.Info("Adding third-party library: 'Boost C++ Libraries'");

        bool bLinuxBuild = Utils.BuildPlatform.IsLinuxBuild();
        bool bWindowsBuild = Utils.BuildPlatform.IsWindowsBuild();

        if (bWindowsBuild)
        {
            Utils.Definitions.DefinePublicly("BOOST_DISABLE_ABI_HEADERS");
        }

        Utils.Definitions.DefinePublicly("BOOST_UUID_USE_SSE41");

        AddPublicSystemIncludePath(Utils.Path.ThirdPartyIncludePath);
        AddPublicLibraryPath(Utils.Path.ThirdPartyLibraryLinkPath);

        string librarySearchPattern = string.Empty;

        if (bLinuxBuild)
        {
            librarySearchPattern = "libboost_*.a";
        }
        else if (bWindowsBuild)
        {
            librarySearchPattern = "libboost_*.lib";
        }

        DirectoryInfo di = new DirectoryInfo(Utils.Path.ThirdPartyLibraryLinkPath);
        FileInfo[] libraries = di.GetFiles(librarySearchPattern, SearchOption.TopDirectoryOnly);

        foreach (FileInfo library in libraries)
        {
            AddPublicAdditionalLibrary(library.Name);
        }
    }

    public void AddCereal()
    {
        Utils.Log.Info("Adding third-party library: 'cereal: A C++11 library for serialization...'");

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
        Utils.Log.Info("Adding third-party library: 'CppDB: SQL Connectivity Library...'");

        bool bDebugBuild = Utils.BuildPlatform.IsDebugBuild();
        bool bLinuxBuild = Utils.BuildPlatform.IsLinuxBuild();
        bool bWindowsBuild = Utils.BuildPlatform.IsWindowsBuild();

        AddPublicSystemIncludePath(Utils.Path.ThirdPartyIncludePath);
        AddPublicLibraryPath(Utils.Path.ThirdPartyLibraryLinkPath);

        if (bLinuxBuild)
        {
            AddPublicAdditionalLibrary("libcppdb.a");
            AddPublicAdditionalLibrary("libcppdb_sqlite3.a");
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
        Utils.Log.Info("Adding third-party library: 'Crypto++: A free C++ class library of cryptographic schemes'...");

        bool bDebugBuild = Utils.BuildPlatform.IsDebugBuild();
        bool bLinuxBuild = Utils.BuildPlatform.IsLinuxBuild();
        bool bWindowsBuild = Utils.BuildPlatform.IsWindowsBuild();

        /// NOTE
        /// Prior to v5.0.0 LLVM/Clang won't be able to handle SSE2
        if (bLinuxBuild)
        {
            Utils.Definitions.DefinePublicly("CRYPTOPP_DISABLE_ASM");
        }

        AddPublicSystemIncludePath(Utils.Path.ThirdPartyIncludePath);
        AddPublicLibraryPath(Utils.Path.ThirdPartyLibraryLinkPath);

        if (bLinuxBuild)
        {
            AddPublicAdditionalLibrary("libcryptopp.a");
        }
        else if (bWindowsBuild)
        {
            if (bDebugBuild)
            {
                AddPublicAdditionalLibrary("libcryptoppd.lib");
            }
            else
            {
                AddPublicAdditionalLibrary("libcryptopp.lib");
            }
        }
    }

    public void AddFMT()
    {
        Utils.Log.Info("Adding third-party library: 'fmt: A modern formatting library'...");

        bool bDebugBuild = Utils.BuildPlatform.IsDebugBuild();
        bool bLinuxBuild = Utils.BuildPlatform.IsLinuxBuild();
        bool bWindowsBuild = Utils.BuildPlatform.IsWindowsBuild();

        AddPublicSystemIncludePath(Utils.Path.ThirdPartyIncludePath);
        AddPublicLibraryPath(Utils.Path.ThirdPartyLibraryLinkPath);

        if (bLinuxBuild)
        {
            if (bDebugBuild)
            {
                AddPublicAdditionalLibrary("libfmtd.a");
            }
            else
            {
                AddPublicAdditionalLibrary("libfmt.a");
            }
        }
        else if (bWindowsBuild)
        {
            if (bDebugBuild)
            {
                AddPublicAdditionalLibrary("libfmtd.lib");
            }
            else
            {
                AddPublicAdditionalLibrary("libfmt.lib");
            }
        }
    }

    public void AddSQLite3()
    {
        Utils.Log.Info("Adding third-party library: 'SQLite 3: A self-contained, high-reliability, embedded, full-featured, public-domain, SQL database engine'...");

        bool bDebugBuild = Utils.BuildPlatform.IsDebugBuild();
        bool bLinuxBuild = Utils.BuildPlatform.IsLinuxBuild();
        bool bWindowsBuild = Utils.BuildPlatform.IsWindowsBuild();

        AddPublicSystemIncludePath(Utils.Path.ThirdPartyIncludePath);
        AddPublicLibraryPath(Utils.Path.ThirdPartyLibraryLinkPath);

        if (bLinuxBuild)
        {
            AddPublicAdditionalLibrary("libsqlite3.a");
        }
        else if (bWindowsBuild)
        {
            if (bDebugBuild)
            {
                AddPublicAdditionalLibrary("libsqlite3d.lib");
            }
            else
            {
                AddPublicAdditionalLibrary("libsqlite3.lib");
            }
        }
    }

    private void AddPublicAdditionalLibrary(string Library)
    {
        Utils.Log.Info("Adding '{0}' third-party library as a public additional library for linking...", Library);

        Utils.Module.PublicAdditionalLibraries.Add(Library);
    }

    private void AddPublicLibraryPath(string Path)
    {
        Utils.Log.Info("Adding '{0}' as a public library search path for linking...", Path);

        Utils.Module.PublicLibraryPaths.Add(Path);
    }

    private void AddPublicSystemIncludePath(string Path)
    {
        Utils.Log.Info("Adding '{0}' as a public system include search path...", Path);

        Utils.Module.PublicSystemIncludePaths.Add(Path);
    }
}

public class GUtils : Object
{
    public GBuildPlatform BuildPlatform;
    public GDefinitions Definitions;
    public GEngineModules EngineModules;
    public GLog Log;
    public GPath Path;
    public GPlugins Plugins;
    public GThirdParty ThirdParty;

    public ModuleRules Module;

    public GUtils(ModuleRules Module)
    {
        this.Module = Module;
    }
}