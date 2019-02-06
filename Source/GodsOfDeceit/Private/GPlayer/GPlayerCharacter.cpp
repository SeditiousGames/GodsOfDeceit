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
 * A player character implementation for Gods of Deceit
 */


#include "GPlayer/GPlayerCharacter.h"
#include "GodsOfDeceit.h"

#include <Animation/AnimBlueprintGeneratedClass.h>
#include <Components/CapsuleComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Engine/SkeletalMesh.h>
#include <Templates/Casts.h>
#include <UObject/Class.h>
#include <UObject/ConstructorHelpers.h>

#include "GPlayer/GPlayerAnimInstance.h"

AGPlayerCharacter::AGPlayerCharacter(
        const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    UCapsuleComponent* CapsuleComponent = GetCapsuleComponent();
    if (CapsuleComponent)
    {
        CapsuleComponent->InitCapsuleSize(88.f, 150.0f);
        RootComponent = CapsuleComponent;
    }

    USkeletalMeshComponent* Mesh = GetMesh();
    if (Mesh)
    {
        static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(
                    TEXT("SkeletalMesh'/Game/ThirdParty/SimpleMilitary/Meshes/"
                         "Characters/SK_Soldier_01.SK_Soldier_01'"));
        if (SkeletalMesh.Succeeded() && SkeletalMesh.Object)
        {
            Mesh->SetSkeletalMesh(SkeletalMesh.Object, true);
        }

        static ConstructorHelpers::FObjectFinder<UAnimBlueprintGeneratedClass>
                AnimBlueprint(
                    TEXT("AnimBlueprint'/Game/GodsOfDeceit/Core/"
                         "Characters/Player/"
                         "ABP_PlayerCharacter.ABP_PlayerCharacter_C'"));
        if (AnimBlueprint.Succeeded() && AnimBlueprint.Object)
        {
            Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
            Mesh->AnimClass = AnimBlueprint.Object;
        }

        Mesh->SetupAttachment(this->RootComponent);
        Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -150.0f),
                                             FRotator(0.0f, -90.0f, 0.0f));
        Mesh->SetOnlyOwnerSee(false);
        Mesh->bCastDynamicShadow = true;
        Mesh->CastShadow = true;
        Mesh->SetCollisionObjectType(ECC_Pawn);
        Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
        Mesh->SetCanEverAffectNavigation(false);
    }
}
