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
 * Build script for GodsOfDeceitEditor target.
 */


using UnrealBuildTool;

public class GodsOfDeceitEditor : ModuleRules
{
    public GUtils Utils;

    public GodsOfDeceitEditor(ReadOnlyTargetRules Target) : base(Target)
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

        Utils.Log.Stop();
    }

    private void AddEngineModules()
    {
        Utils.EngineModules.AddAssetTools();
        Utils.EngineModules.AddCore();
        Utils.EngineModules.AddCoreUObject();
        Utils.EngineModules.AddEngine();
        Utils.EngineModules.AddGodsOfDeceit();
        Utils.EngineModules.AddUnrealEd();

        Utils.Log.EmptyLine();
    }

    private void SetBuildConfiguration()
    {
        bool bDebugBuild = Utils.BuildPlatform.IsDebugBuild();

        Utils.Log.Info("Enabling explicit or shared PCH usage mode...");
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        Utils.Log.Info("Disabling run-time type identification...");
        this.bUseRTTI = false;

        Utils.Log.Info("Disabling exception handling...");
        this.bEnableExceptions = false;

        Utils.Log.Info("Enabling AVX instructions...");
        this.bUseAVX = true;

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
