/**
 * @file
 * @author  Mamadou Babaei <info@babaei.net>
 * @version 0.1.0
 *
 * @section LICENSE
 *
 * (The MIT License)
 *
 * Copyright (c) 2018 - 2019 Mamadou Babaei
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
 * Build script for GodsOfDeceitTypes target.
 */


using UnrealBuildTool;

public class GodsOfDeceitTypes : ModuleRules
{
    public GUtils Utils;

    public GodsOfDeceitTypes(ReadOnlyTargetRules Target) : base(Target)
    {
        InitializeUtils();

        Utils.Log.Start();

        SetupBuildConfiguration();
        AddEngineModules();
        AddDefinitions();
        AddThirdPartyLibraries();

        Utils.BuildInfo.Print();

        Utils.Log.Stop();
    }

    private void InitializeUtils()
    {
        Utils = new GUtils(this, "GodsOfDeceitTypes");

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
        Utils.Log.Info("Setting up required engine modules for '{0}'...", Utils.ModuleName);

        Utils.EngineModules.AddCore(true);
        Utils.EngineModules.AddCoreUObject(true);

        Utils.Log.EmptyLine();
    }

    private void AddThirdPartyLibraries()
    {
        Utils.Log.Info("Setting up required third-party libraries for '{0}'...", Utils.ModuleName);
        Utils.Log.EmptyLine();

        Utils.ThirdParty.AddBoost();
        Utils.Log.EmptyLine();

        Utils.ThirdParty.AddCereal();
        Utils.Log.EmptyLine();

        Utils.ThirdParty.AddFMT();
        Utils.Log.EmptyLine();
    }

    private void SetupBuildConfiguration()
    {
        Utils.Log.Info("Setting up build configuration for '{0}'...", Utils.ModuleName);

        bool bDebugBuild = Utils.BuildPlatform.IsDebugBuild();

        Utils.BuildConfiguration.SetPCHUsage(PCHUsageMode.UseExplicitOrSharedPCHs);
        Utils.BuildConfiguration.SetUseRTTI(false);
        Utils.BuildConfiguration.SetEnableExceptions(false);
        Utils.BuildConfiguration.SetUseAVX(true);
        Utils.BuildConfiguration.SetEnableShadowVariableWarnings(true);
        Utils.BuildConfiguration.SetEnableUndefinedIdentifierWarnings(true);
        Utils.BuildConfiguration.SetFasterWithoutUnity(bDebugBuild);
        Utils.BuildConfiguration.SetOptimizeCode(bDebugBuild ? CodeOptimization.Never : CodeOptimization.Always);

        Utils.Log.EmptyLine();
    }
}
