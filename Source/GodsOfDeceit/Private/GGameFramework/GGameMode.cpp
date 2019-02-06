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
 * The main game mode class for Gods of Deceit
 */


#include "GGameFramework/GGameMode.h"
#include "GodsOfDeceit.h"

#include <Templates/Casts.h>
#include <UObject/Class.h>
#include <UObject/ConstructorHelpers.h>

#include <GLog/GLog.h>
#include <GPlatform/GSystem.h>
#include <GRandom/GRandom.h>
#include <GTypes/GPlatformTypes.h>
#include <GTypes/GVersionTypes.h>
#include <GUtils/GUtils.h>
#include <GVersion/GBuildInfo.h>

AGGameMode::AGGameMode(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    static ConstructorHelpers::FObjectFinder<UClass> GameStateBlueprints(
                TEXT("Class'/Game/GodsOfDeceit/Core/"
                     "BP_GameState.BP_GameState_C'"));
    if (GameStateBlueprints.Object)
    {
       GameStateClass = GameStateBlueprints.Object;
    }

    static ConstructorHelpers::FObjectFinder<UClass> PlayerControllerBlueprints(
                TEXT("Class'/Game/GodsOfDeceit/Core/Characters/Player/"
                     "BP_PlayerController.BP_PlayerController_C'"));
    if (PlayerControllerBlueprints.Object)
    {
        PlayerControllerClass = PlayerControllerBlueprints.Object;
    }

    static ConstructorHelpers::FObjectFinder<UClass> HUDBlueprints(
                TEXT("Class'/Game/GodsOfDeceit/Core/HUDs/"
                     "BP_GameHUD.BP_GameHUD_C'"));
    if (HUDBlueprints.Object)
    {
        HUDClass = HUDBlueprints.Object;
    }

    static ConstructorHelpers::FObjectFinder<UClass> DefaultPawnBlueprints(
                TEXT("Class'/Game/GodsOfDeceit/Core/Characters/Player/"
                     "BP_PlayerCharacter.BP_PlayerCharacter_C'"));
    if (DefaultPawnBlueprints.Object)
    {
        DefaultPawnClass = DefaultPawnBlueprints.Object;
    }
}

void AGGameMode::BeginPlay()
{
    Super::BeginPlay();

    GLOG_WARNING(GLOG_KEY_INFINITE,
                 TEXT("GetProductBranchName"),
                 GBuildInfo::GetProductBranchName());
    GLOG_WARNING(GLOG_KEY_INFINITE,
                 TEXT("GetProductBuildDate"),
                 GBuildInfo::GetProductBuildDate());
    GLOG_WARNING(GLOG_KEY_INFINITE,
                 TEXT("GetProductBuildHost"),
                 GBuildInfo::GetProductBuildHost());
    GLOG_WARNING(GLOG_KEY_INFINITE,
                 TEXT("GetProductBuildTime"),
                 GBuildInfo::GetProductBuildTime());
    GLOG_WARNING(GLOG_KEY_INFINITE,
                 TEXT("GetProductCompanyName"),
                 GBuildInfo::GetProductCompanyName());
    GLOG_WARNING(GLOG_KEY_INFINITE,
                 TEXT("GetProductCopyrightHolder"),
                 GBuildInfo::GetProductCopyrightHolder());
    GLOG_WARNING(GLOG_KEY_INFINITE,
                 TEXT("GetProductCopyrightNotice"),
                 GBuildInfo::GetProductCopyrightNotice());
    GLOG_WARNING(GLOG_KEY_INFINITE,
                 TEXT("GetProductDescription"),
                 GBuildInfo::GetProductDescription());
    GLOG_WARNING(GLOG_KEY_INFINITE,
                 TEXT("GetProductInternalName"),
                 GBuildInfo::GetProductInternalName());
    GLOG_WARNING(GLOG_KEY_INFINITE,
                 TEXT("GetProductName"),
                 GBuildInfo::GetProductName());
    GLOG_WARNING(GLOG_KEY_INFINITE,
                 TEXT("GetProductRevision"),
                 GBuildInfo::GetProductRevision());
    GLOG_WARNING(GLOG_KEY_INFINITE,
                 TEXT("GetProductShortRevisionHash"),
                 GBuildInfo::GetProductShortRevisionHash());
    GLOG_WARNING(GLOG_KEY_INFINITE,
                 TEXT("GetProductVersion"),
                 GBuildInfo::GetProductVersion());

    GLOG_WARNING(GLOG_KEY_GENERIC, GBuildInfo::ToJson(true));

    FGProductVersionNumbers ProductVersionNumbers(
                GBuildInfo::GetProductVersionNumbers());
    GLOG_WARNING(GLOG_KEY_EDITOR,
                 ProductVersionNumbers.Major,
                 ProductVersionNumbers.Minor,
                 ProductVersionNumbers.Patch);

    GLOG_WARNING(GLOG_KEY_SQL, GSystem::GetDirectorySeparatorChar());
    GLOG_WARNING(GLOG_KEY_INPUT, GSystem::GetExecutablePath());
    GLOG_WARNING(GLOG_KEY_ANIMATION, GSystem::GetCurrentPath());
    GLOG_WARNING(GLOG_KEY_BLUEPRINTS,
                 GSystem::GetSystemDirectoryPath(
                     EGSystemDirectory::UserDesktop),
                 GSystem::GetSystemDirectoryPath(
                     EGSystemDirectory::UserDocuments),
                 GSystem::GetSystemDirectoryPath(
                     EGSystemDirectory::UserGameData),
                 GSystem::GetSystemDirectoryPath(
                     EGSystemDirectory::UserHome));

    GLOG_WARNING(GLOG_KEY_GENERIC, GUtils::CalculateBytes(8193));

    GLOG_WARNING(GLOG_KEY_GENERIC, GRandom::Characters(
                     EGRandomCharacterSet::Alphanumeric, 10));
    GLOG_WARNING(GLOG_KEY_GENERIC, GRandom::Number(10, 90));
    GLOG_WARNING(GLOG_KEY_GENERIC, GRandom::Uuid());
}

void AGGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
}
