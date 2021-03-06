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
 * Target file for GodsOfDeceitEditor.
 */


using System.Collections.Generic;
using UnrealBuildTool;

public class GodsOfDeceitEditorTarget : TargetRules
{
    public GodsOfDeceitEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;

        ExtraModuleNames.AddRange(
            new string[] {
                "GodsOfDeceit",
                "GodsOfDeceitCompression",
                "GodsOfDeceitCompressionImpl",
                "GodsOfDeceitCrypto",
                "GodsOfDeceitCryptoImpl",
                "GodsOfDeceitEditor",
                "GodsOfDeceitHacks",
                "GodsOfDeceitInterop",
                "GodsOfDeceitLoadingScreen",
                "GodsOfDeceitLog",
                "GodsOfDeceitMath",
                "GodsOfDeceitPersistentData",
                "GodsOfDeceitPersistentDataImpl",
                "GodsOfDeceitPlatform",
                "GodsOfDeceitPlatformImpl",
                "GodsOfDeceitRandom",
                "GodsOfDeceitRandomImpl",
                "GodsOfDeceitTypes",
                "GodsOfDeceitUtils",
                "GodsOfDeceitUtilsImpl",
                "GodsOfDeceitVersion",
                "GodsOfDeceitVersionImpl"
            });

        BuildEnvironment = TargetBuildEnvironment.Shared;

        bEnforceIWYU = true;
        bBuildDeveloperTools = true;
        bForceEnableRTTI = false;
        bForceEnableExceptions = false;
        bUseUnityBuild = true;
        bForceUnityBuild = true;
    }
}
