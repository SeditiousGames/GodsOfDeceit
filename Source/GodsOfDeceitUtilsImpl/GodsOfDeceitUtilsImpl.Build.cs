/**
 * @file
 * @author  Mohammad S. Babaei <info@babaei.net>
 * @version 0.1.0
 *
 * @section LICENSE
 *
 * (The MIT License)
 *
 * Copyright (c) 2018 - 2019 Mohammad S. Babaei
 * Copyright (c) 2018 - 2019 Seditious Games Studio
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
 * Build script for GodsOfDeceitUtilsImpl target.
 */


using UnrealBuildTool;

public class GodsOfDeceitUtilsImpl : ModuleRules
{
    public GUtils Utils;

    public GodsOfDeceitUtilsImpl(ReadOnlyTargetRules Target) : base(Target)
    {
        InitializeUtils();

        Utils.Log.Start();

        SetupBuildConfiguration();
        AddEngineModules();
        AddGameModules();
        AddDefinitions();
        AddThirdPartyLibraries();

        Utils.BuildInfo.Print();

        Utils.Log.Stop();
    }

    private void InitializeUtils()
    {
        Utils = new GUtils(this, "GodsOfDeceitUtilsImpl");

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
        bool bWindowsBuild = Utils.BuildPlatform.IsWindowsBuild();

        if (bWindowsBuild)
        {
            Utils.Definitions.DefinePublicly("_UNICODE");
            Utils.Definitions.DefinePublicly("UNICODE");
            Utils.Definitions.DefinePublicly("WIN32_LEAN_AND_MEAN");
        }

        Utils.Definitions.DefinePublicly("GOD_BUILDING_UTILS_IMPL_MODULE");

        Utils.Log.EmptyLine();
    }

    private void AddEngineModules()
    {
        Utils.Log.Info("Setting up required engine modules for '{0}'...", Utils.ModuleName);

        Utils.EngineModules.AddCore(true);

        Utils.Log.EmptyLine();
    }

    private void AddGameModules()
    {
        Utils.Log.Info("Setting up required game modules for '{0}'...", Utils.ModuleName);

        Utils.GameModules.AddHacks(false);
        Utils.GameModules.AddInterop(false);

        Utils.Log.EmptyLine();
    }

    private void AddThirdPartyLibraries()
    {
        Utils.Log.Info("Setting up required third-party libraries for '{0}'...", Utils.ModuleName);
        Utils.Log.EmptyLine();

        Utils.ThirdParty.AddBoost();
        Utils.Log.EmptyLine();
    }

    private void SetupBuildConfiguration()
    {
        Utils.Log.Info("Setting up build configuration for '{0}'...", Utils.ModuleName);

        bool bX64 = Utils.BuildPlatform.IsX64();
        bool bDebugBuild = Utils.BuildPlatform.IsDebugBuild();
        bool bShippingBuild = Utils.BuildPlatform.IsShippingBuild();

        Utils.BuildConfiguration.SetPCHUsage(PCHUsageMode.UseExplicitOrSharedPCHs);
        Utils.BuildConfiguration.SetUseRTTI(true);
        Utils.BuildConfiguration.SetEnableExceptions(true);
        Utils.BuildConfiguration.SetUseAVX(bX64 && !bShippingBuild);
        Utils.BuildConfiguration.SetEnableShadowVariableWarnings(true);
        Utils.BuildConfiguration.SetEnableUndefinedIdentifierWarnings(true);
        Utils.BuildConfiguration.SetFasterWithoutUnity(bDebugBuild);
        Utils.BuildConfiguration.SetOptimizeCode(bDebugBuild ? CodeOptimization.Never : CodeOptimization.Always);

        Utils.Log.EmptyLine();
    }
}
