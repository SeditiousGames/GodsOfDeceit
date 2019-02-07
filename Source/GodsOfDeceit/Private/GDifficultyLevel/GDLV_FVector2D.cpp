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
 * A game difficulty level variable which represents FVector2D type
 */


#include "GDifficultyLevel/GDLV_FVector2D.h"
#include "GodsOfDeceit.h"

#include <Engine/World.h>
#include <Kismet/GameplayStatics.h>
#include <Templates/Casts.h>

#include <GEngine/GGameInstance.h>
#include <GTypes/GDifficultyLevelTypes.h>

FGDLV_FVector2D::FGDLV_FVector2D()
{
    Outer = nullptr;

    Dummy = FVector2D();

    Recruit = Dummy;
    Regular = Dummy;
    Hardened = Dummy;
    Veteran = Dummy;
}

const FVector2D& FGDLV_FVector2D::Get() const
{
    checkf(Outer, TEXT("FATAL: has not been initialized! Call"
                       " Initialize(UObject* InOuter) first!"));

    UWorld* World = Outer ? Outer->GetWorld() : nullptr;

    if (World && (World->WorldType == EWorldType::EditorPreview))
    {
        return Dummy;
    }

    UGGameInstance* GameInstance = World
            ? Cast<UGGameInstance>(UGameplayStatics::GetGameInstance(World))
            : nullptr;

    if (World && GameInstance)
    {
        const EGDifficultyLevel& DifficultyLevel =
                GameInstance->GetDifficultyLevel();

        switch (DifficultyLevel)
        {

        case EGDifficultyLevel::Recruit:
            return Recruit;

        case EGDifficultyLevel::Regular:
            return Regular;

        case EGDifficultyLevel::Hardened:
            return Hardened;

        case EGDifficultyLevel::Veteran:
            return Veteran;

        }
    }

    checkf(false, TEXT("FATAL: the execution flow should never reach here!"));

    return this->Dummy;
}
