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
    public GodsOfDeceit(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        GBuildPlatform.Initialize(Target);
        GDefinitions.Initialize(PublicDefinitions, PrivateDefinitions);
        GEngineModules.Initialize(PublicDependencyModuleNames, PrivateDependencyModuleNames);
        GLog.Initialize(Target);
        GPath.Initialize(ModuleDirectory);
        GPlugins.Initialize(PublicDependencyModuleNames, PrivateDependencyModuleNames);
        GThirdParty.Initialize(PublicSystemIncludePaths, PublicLibraryPaths, PublicAdditionalLibraries);

        GLog.Start();

        SetBuildConfiguration();
        AddEngineModules();
        AddPlugins();
        AddDefinitions();
        AddThirdPartyLibraries();

        GLog.Stop();
    }

    private void AddDefinitions()
    {
        bool bWindowsBuild = GBuildPlatform.IsWindowsBuild();

        if (bWindowsBuild)
        {
            GDefinitions.DefinePublicly("_UNICODE");
            GDefinitions.DefinePublicly("UNICODE");
            GDefinitions.DefinePublicly("WIN32_LEAN_AND_MEAN");
        }

        GLog.EmptyLine();
    }

    private void AddEngineModules()
    {
        GEngineModules.AddCore();
        GEngineModules.AddCoreUObject();
        GEngineModules.AddEngine();
        GEngineModules.AddInputCore();

        GLog.EmptyLine();
    }

    private void AddPlugins()
    {
        GPlugins.AddUFSM();
        GPlugins.AddVlcMedia();

        GLog.EmptyLine();
    }

    private void AddThirdPartyLibraries()
    {
        GThirdParty.AddBoost();
        GLog.EmptyLine();

        GThirdParty.AddCereal();
        GLog.EmptyLine();

        GThirdParty.AddCppDB();
        GLog.EmptyLine();

        GThirdParty.AddCryptoPP();
        GLog.EmptyLine();

        GThirdParty.AddFMT();
        GLog.EmptyLine();

        GThirdParty.AddSQLite3();
        GLog.EmptyLine();
    }

    private void SetBuildConfiguration()
    {
        bool bX64 = GBuildPlatform.IsX64();
        bool bDebugBuild = GBuildPlatform.IsDebugBuild();
        bool bShippingBuild = GBuildPlatform.IsShippingBuild();

        if (bX64 && !bShippingBuild)
        {
            GLog.Info("Enabling AVX instructions...");
            this.bUseAVX = true;
        }

        GLog.Info("Enabling run-time type identification...");
        this.bUseRTTI = true;

        GLog.Info("Enabling exception handling...");
        this.bEnableExceptions = true;

        GLog.Info("Enabling warnings for shadowed variables...");
        this.bEnableShadowVariableWarnings = true;

        GLog.Info("Enabling warnings for using undefined identifiers in #if expressions...");
        this.bEnableUndefinedIdentifierWarnings = true;

        if (bDebugBuild)
        {
            GLog.Info("Enabling non-unity builds...");
            this.bFasterWithoutUnity = true;

            GLog.Info("Turning code optimization off for debugging purpose...");
            this.OptimizeCode = CodeOptimization.Never;
        }
        else
        {
            GLog.Info("Enabling unity builds...");
            this.bFasterWithoutUnity = false;
        }

        GLog.EmptyLine();
    }
}

static public class GBuildPlatform
{
    static private ReadOnlyTargetRules Target;

    static public void Initialize(ReadOnlyTargetRules Target)
    {
        GBuildPlatform.Target = Target;
    }

    static public bool IsX64()
    {
        return (Target.Platform == UnrealTargetPlatform.Linux
            || Target.Platform == UnrealTargetPlatform.Win64);
    }

    static public bool IsX86()
    {
        return (Target.Platform == UnrealTargetPlatform.Win32);
    }

    static public bool IsDevelopmentBuild()
    {
        return (Target.Configuration == UnrealTargetConfiguration.Development);
    }

    static public bool IsDebugBuild()
    {
        return (Target.Configuration == UnrealTargetConfiguration.Debug
            || Target.Configuration == UnrealTargetConfiguration.DebugGame);
    }

    static public bool IsLinuxBuild()
    {
        return (Target.Platform == UnrealTargetPlatform.Linux);
    }

    static public bool IsShippingBuild()
    {
        return (Target.Configuration == UnrealTargetConfiguration.Shipping);
    }

    static public bool IsTestBuild()
    {
        return (Target.Configuration == UnrealTargetConfiguration.Test);
    }

    static public bool IsWindowsBuild()
    {
        return (Target.Platform == UnrealTargetPlatform.Win32
            || Target.Platform == UnrealTargetPlatform.Win64);
    }
}

static public class GDefinitions
{
    static private List<string> PublicDefinitions;
    static private List<string> PrivateDefinitions;

    static public void Initialize(List<string> PublicDefinitions, List<string> PrivateDefinitions)
    {
        GDefinitions.PublicDefinitions = PublicDefinitions;
        GDefinitions.PrivateDefinitions = PrivateDefinitions;
    }

    static public void DefinePublicly(string Definition)
    {
        AddPublicDefinition(Definition);
    }

    static public void DefinePrivately(string Definition)
    {
        AddPrivateDefinition(Definition);
    }

    static private void AddPublicDefinition(string Definition)
    {
        GLog.Info("Defining '{0}' as a public definition...", Definition);

        PublicDefinitions.Add(Definition);
    }

    static private void AddPrivateDefinition(string Definition)
    {
        GLog.Info("Defining '{0}' as a private definition...", Definition);

        PrivateDefinitions.Add(Definition);
    }
}

static public class GLog
{
    static private ReadOnlyTargetRules Target;

    static public void Initialize(ReadOnlyTargetRules Target)
    {
        GLog.Target = Target;
    }

    static public void EmptyLine()
    {
        Console.WriteLine();
    }

    static public void Debug(string Format, params object[] Args)
    {
        Log("DEBUG", Format, Args);
    }

    static public void Error(string Format, params object[] Args)
    {
        Log("ERROR", Format, Args);
    }

    static public void Fatal(string Format, params object[] Args)
    {
        Log("FATAL", Format, Args);
    }

    static public void Info(string Format, params object[] Args)
    {
        Log("INFO", Format, Args);
    }

    static public void Trace(string Format, params object[] Args)
    {
        Log("TRACE", Format, Args);
    }

    static public void Warning(string Format, params object[] Args)
    {
        Log("WARNING", Format, Args);
    }

    static public void Start()
    {
        EmptyLine();
        EmptyLine();
        Info("Setting up '{0}' target...", Target.Name);
        EmptyLine();

        Info("Target build configuration is '{0}'.", Target.Configuration);
        EmptyLine();
    }

    static public void Stop()
    {
        Info("Finished setting up '{0}' target.", Target.Name);
        EmptyLine();
    }

    static private void Log(string Type, string Format, params object[] Args)
    {
        DateTime LocalDate = DateTime.Now;

        Console.WriteLine(string.Format("[ {0} {1} ] {2}", LocalDate.ToString(), Type, string.Format(Format, Args)));
    }
}

static public class GEngineModules
{
    private static List<string> PublicDependencyModuleNames;
    private static List<string> PrivateDependencyModuleNames;

    static public void Initialize(List<string> PublicDependencyModuleNames, List<string> PrivateDependencyModuleNames)
    {
        GEngineModules.PublicDependencyModuleNames = PublicDependencyModuleNames;
        GEngineModules.PrivateDependencyModuleNames = PrivateDependencyModuleNames;
    }

    static public void AddCore()
    {
        AddPublicDependencyModuleName("Core");
    }

    static public void AddCoreUObject()
    {
        AddPublicDependencyModuleName("CoreUObject");
    }

    static public void AddEngine()
    {
        AddPublicDependencyModuleName("Engine");
    }

    static public void AddInputCore()
    {
        AddPublicDependencyModuleName("InputCore");
    }

    static private void AddPublicDependencyModuleName(string Plugin)
    {
        GLog.Info("Adding '{0}' as a public dependency module...", Plugin);

        PublicDependencyModuleNames.Add(Plugin);
    }

    static private void AddPrivateDependencyModuleName(string Plugin)
    {
        GLog.Info("Adding '{0}' as a private dependency module...", Plugin);

        PrivateDependencyModuleNames.Add(Plugin);
    }
}

static public class GPath
{
    static public string ModulePath
    {
        get
        {
            return ModuleDirectory;
        }
    }

    static public string ProjectPath
    {
        get
        {
            return Directory.GetParent(ModulePath).ToString();
        }
    }

    static public string GitDirectoryPath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ProjectPath, "..", ".git"));
        }
    }

    static public string PluginsPath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ModulePath, "..", "..", "Plugins"));
        }
    }

    static public string ThirdPartyPath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ModuleDirectory, "..", "..", "ThirdParty"));
        }
    }

    static public string ThirdPartyIncludePath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ThirdPartyPath, "include"));
        }
    }

    static public string LinuxThirdPartyDebugLibraryPath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ThirdPartyPath, "lib", "linux", "debug"));
        }
    }

    static public string LinuxThirdPartyReleaseLibraryPath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ThirdPartyPath, "lib", "linux", "release"));
        }
    }

    static public string Win32ThirdPartyDebugLibraryPath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ThirdPartyPath, "lib", "win32", "debug"));
        }
    }

    static public string Win32ThirdPartyReleaseLibraryPath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ThirdPartyPath, "lib", "win32", "release"));
        }
    }

    static public string Win64ThirdPartyDebugLibraryPath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ThirdPartyPath, "lib", "win64", "debug"));
        }
    }

    static public string Win64ThirdPartyReleaseLibraryPath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ThirdPartyPath, "lib", "win64", "release"));
        }
    }

    static public string ThirdPartyLibraryLinkPath
    {
        get
        {
            bool bX64 = GBuildPlatform.IsX64();
            bool bX86 = GBuildPlatform.IsX86();
            bool bDebugBuild = GBuildPlatform.IsDebugBuild();
            bool bLinuxBuild = GBuildPlatform.IsLinuxBuild();
            bool bWindowsBuild = GBuildPlatform.IsWindowsBuild();

            if (bLinuxBuild)
            {
                if (bDebugBuild)
                {
                    return GPath.LinuxThirdPartyDebugLibraryPath;
                }
                else
                {
                    return GPath.LinuxThirdPartyReleaseLibraryPath;
                }
            }

            if (bWindowsBuild)
            {
                if (bX64)
                {
                    if (bDebugBuild)
                    {
                        return GPath.Win32ThirdPartyDebugLibraryPath;
                    }
                    else
                    {
                        return GPath.Win32ThirdPartyReleaseLibraryPath;
                    }
                }

                if (bX86)
                {
                    if (bDebugBuild)
                    {
                        return GPath.Win64ThirdPartyDebugLibraryPath;
                    }
                    else
                    {
                        return GPath.Win64ThirdPartyReleaseLibraryPath;
                    }
                }
            }

            return string.Empty;
        }
    }

    static private string ModuleDirectory;

    static public void Initialize(string ModuleDirectory)
    {
        GPath.ModuleDirectory = ModuleDirectory;
    }
}

static public class GPlugins
{
    private static List<string> PublicDependencyModuleNames;
    private static List<string> PrivateDependencyModuleNames;

    static public void Initialize(List<string> PublicDependencyModuleNames, List<string> PrivateDependencyModuleNames)
    {
        GPlugins.PublicDependencyModuleNames = PublicDependencyModuleNames;
        GPlugins.PrivateDependencyModuleNames = PrivateDependencyModuleNames;
    }

    static public void AddUFSM()
    {
        AddPrivateDependencyModuleName("UFSM");
    }

    static public void AddVlcMedia()
    {
        AddPrivateDependencyModuleName("VlcMedia");
    }

    static private void AddPublicDependencyModuleName(string Plugin)
    {
        GLog.Info("Adding '{0}' third-party plugin as a public dependency module...", Plugin);

        PublicDependencyModuleNames.Add(Plugin);
    }

    static private void AddPrivateDependencyModuleName(string Plugin)
    {
        GLog.Info("Adding '{0}' third-party plugin as a private dependency module...", Plugin);

        PrivateDependencyModuleNames.Add(Plugin);
    }
}

static public class GThirdParty
{
    static private List<string> PublicAdditionalLibraries;
    static private List<string> PublicLibraryPaths;
    static private List<string> PublicSystemIncludePaths;

    static public void Initialize(List<string> PublicSystemIncludePaths, List<string> PublicLibraryPaths, List<string> PublicAdditionalLibraries)
    {
        GThirdParty.PublicSystemIncludePaths = PublicSystemIncludePaths;
        GThirdParty.PublicLibraryPaths = PublicLibraryPaths;
        GThirdParty.PublicAdditionalLibraries = PublicAdditionalLibraries;
    }

    static public void AddBoost()
    {
        GLog.Info("Adding third-party library: 'Boost C++ Libraries'");

        bool bLinuxBuild = GBuildPlatform.IsLinuxBuild();
        bool bWindowsBuild = GBuildPlatform.IsWindowsBuild();

        if (bWindowsBuild)
        {
            GDefinitions.DefinePublicly("BOOST_DISABLE_ABI_HEADERS");
        }

        GDefinitions.DefinePublicly("BOOST_UUID_USE_SSE41");

        AddPublicSystemIncludePath(GPath.ThirdPartyIncludePath);
        AddPublicLibraryPath(GPath.ThirdPartyLibraryLinkPath);

        string librarySearchPattern = string.Empty;

        if (bLinuxBuild)
        {
            librarySearchPattern = "libboost_*.a";
        }
        else if (bWindowsBuild)
        {
            librarySearchPattern = "libboost_*.lib";
        }

        DirectoryInfo di = new DirectoryInfo(GPath.ThirdPartyLibraryLinkPath);
        FileInfo[] libraries = di.GetFiles(librarySearchPattern, SearchOption.TopDirectoryOnly);

        foreach (FileInfo library in libraries)
        {
            AddPublicAdditionalLibrary(library.Name);
        }
    }

    static public void AddCereal()
    {
        GLog.Info("Adding third-party library: 'cereal: A C++11 library for serialization...'");

        bool bWindowsBuild = GBuildPlatform.IsWindowsBuild();

        /// NOTE
        /// Workaround for Windows/MSVC conflicting macros 'min/max'
        /// used by cereal
        if (bWindowsBuild)
        {
            GDefinitions.DefinePublicly("NOMINMAX");
        }

        AddPublicSystemIncludePath(GPath.ThirdPartyIncludePath);
    }

    static public void AddCppDB()
    {
        GLog.Info("Adding third-party library: 'CppDB: SQL Connectivity Library...'");

        bool bDebugBuild = GBuildPlatform.IsDebugBuild();
        bool bLinuxBuild = GBuildPlatform.IsLinuxBuild();
        bool bWindowsBuild = GBuildPlatform.IsWindowsBuild();

        AddPublicSystemIncludePath(GPath.ThirdPartyIncludePath);
        AddPublicLibraryPath(GPath.ThirdPartyLibraryLinkPath);

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

    static public void AddCryptoPP()
    {
        GLog.Info("Adding third-party library: 'Crypto++: A free C++ class library of cryptographic schemes'...");

        bool bDebugBuild = GBuildPlatform.IsDebugBuild();
        bool bLinuxBuild = GBuildPlatform.IsLinuxBuild();
        bool bWindowsBuild = GBuildPlatform.IsWindowsBuild();

        /// NOTE
        /// Prior to v5.0.0 LLVM/Clang won't be able to handle SSE2
        if (bLinuxBuild)
        {
            GDefinitions.DefinePublicly("CRYPTOPP_DISABLE_ASM");
        }

        AddPublicSystemIncludePath(GPath.ThirdPartyIncludePath);
        AddPublicLibraryPath(GPath.ThirdPartyLibraryLinkPath);

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

    static public void AddFMT()
    {
        GLog.Info("Adding third-party library: 'fmt: A modern formatting library'...");

        bool bDebugBuild = GBuildPlatform.IsDebugBuild();
        bool bLinuxBuild = GBuildPlatform.IsLinuxBuild();
        bool bWindowsBuild = GBuildPlatform.IsWindowsBuild();

        AddPublicSystemIncludePath(GPath.ThirdPartyIncludePath);
        AddPublicLibraryPath(GPath.ThirdPartyLibraryLinkPath);

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

    static public void AddSQLite3()
    {
        GLog.Info("Adding third-party library: 'SQLite 3: A self-contained, high-reliability, embedded, full-featured, public-domain, SQL database engine'...");

        bool bDebugBuild = GBuildPlatform.IsDebugBuild();
        bool bLinuxBuild = GBuildPlatform.IsLinuxBuild();
        bool bWindowsBuild = GBuildPlatform.IsWindowsBuild();

        AddPublicSystemIncludePath(GPath.ThirdPartyIncludePath);
        AddPublicLibraryPath(GPath.ThirdPartyLibraryLinkPath);

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

    static private void AddPublicAdditionalLibrary(string Library)
    {
        GLog.Info("Adding '{0}' third-party static library as a public additional library for linking...", Library);

        PublicAdditionalLibraries.Add(Library);
    }

    static private void AddPublicLibraryPath(string Path)
    {
        GLog.Info("Adding '{0}' as a public library search path for linking...", Path);

        PublicLibraryPaths.Add(Path);
    }

    static private void AddPublicSystemIncludePath(string Path)
    {
        GLog.Info("Adding '{0}' as a public system include search path...", Path);

        PublicSystemIncludePaths.Add(Path);
    }
}