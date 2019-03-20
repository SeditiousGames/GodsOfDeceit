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

#include <utility>

#include <Animation/AnimBlueprintGeneratedClass.h>
#include <Components/CapsuleComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Engine/SkeletalMesh.h>
#include <Templates/Casts.h>
#include <UObject/Class.h>
#include <UObject/ConstructorHelpers.h>

#include <UFSM_StateMachineComponent.h>

#include "GPlayer/GPlayerAnimInstance.h"
#include "GPlayer/GPlayerCharacterMovementComponent.h"
#include "GPlayerStates/GPlayerStates.h"

struct AGPlayerCharacter::Impl
{
public:

private:
    AGPlayerCharacter* Owner;

public:
    explicit Impl(AGPlayerCharacter* InOwner);
    ~Impl();

public:
};

AGPlayerCharacter::AGPlayerCharacter(
        const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass
            <UGPlayerCharacterMovementComponent>
            (ACharacter::CharacterMovementComponentName))
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

    AimStateMachine = ObjectInitializer.CreateDefaultSubobject<
            UStateMachineComponent>(this, TEXT("AimStateMachine"));
    if (AimStateMachine->IsValidLowLevel())
    {
        AimStates.Emplace(NewObject<UGPlayerAimState_None>(
                              AimStateMachine,
                              TEXT("PlayerAimState_None")));
        AimStates.Emplace(NewObject<UGPlayerAimState_Blocked>(
                              AimStateMachine,
                              TEXT("PlayerAimState_Blocked")));
        AimStates.Emplace(NewObject<UGPlayerAimState_Hip>(
                              AimStateMachine,
                              TEXT("PlayerAimState_Hip")));
        AimStates.Emplace(NewObject<UGPlayerAimState_Inactive>(
                              AimStateMachine,
                              TEXT("PlayerAimState_Inactive")));
        AimStates.Emplace(NewObject<UGPlayerAimState_IronSight>(
                              AimStateMachine,
                              TEXT("PlayerAimState_IronSight")));
        AimStates.Emplace(NewObject<UGPlayerAimState_TelescopicSight>(
                              AimStateMachine,
                              TEXT("PlayerAimState_TelescopicSight")));
    }

    CombatStateMachine = ObjectInitializer.CreateDefaultSubobject<
            UStateMachineComponent>(this, TEXT("CombatStateMachine"));

    MovementStateMachine = ObjectInitializer.CreateDefaultSubobject<
            UStateMachineComponent>(this, TEXT("MovementStateMachine"));
}

void AGPlayerCharacter::OnBeginAimState(
        uint8 StateId, uint8 PreviousStateId,
        FName StateName, FSM_Transition Transition)
{
    (void)StateId;
    (void)PreviousStateId;
    (void)StateName;
    (void)Transition;
}

void AGPlayerCharacter::OnUpdateAimState(
        uint8 StateId, FName StateName,
        float StateTime)
{
    (void)StateId;
    (void)StateName;
    (void)StateTime;
}

void AGPlayerCharacter::OnExitAimState(
        uint8 StateId, FName StateName,
        FSM_Transition Transition)
{
    (void)StateId;
    (void)StateName;
    (void)Transition;
}

void AGPlayerCharacter::OnBeginCombatState(
        uint8 StateId, uint8 PreviousStateId,
        FName StateName, FSM_Transition Transition)
{
    (void)StateId;
    (void)PreviousStateId;
    (void)StateName;
    (void)Transition;
}

void AGPlayerCharacter::OnUpdateCombatState(
        uint8 StateId, FName StateName,
        float StateTime)
{
    (void)StateId;
    (void)StateName;
    (void)StateTime;
}

void AGPlayerCharacter::OnExitCombatState(
        uint8 StateId, FName StateName,
        FSM_Transition Transition)
{
    (void)StateId;
    (void)StateName;
    (void)Transition;
}

void AGPlayerCharacter::OnBeginMovementState(
        uint8 StateId, uint8 PreviousStateId,
        FName StateName, FSM_Transition Transition)
{
    (void)StateId;
    (void)PreviousStateId;
    (void)StateName;
    (void)Transition;
}

void AGPlayerCharacter::OnUpdateMovementState(
        uint8 StateId, FName StateName,
        float StateTime)
{
    (void)StateId;
    (void)StateName;
    (void)StateTime;
}

void AGPlayerCharacter::OnExitMovementState(
        uint8 StateId, FName StateName,
        FSM_Transition Transition)
{
    (void)StateId;
    (void)StateName;
    (void)Transition;
}

void AGPlayerCharacter::OnAim_Blocked_Begin()
{

}

void AGPlayerCharacter::OnAim_Blocked_Update()
{

}

void AGPlayerCharacter::OnAim_Blocked_Exit()
{

}

void AGPlayerCharacter::OnAim_Hip_Begin()
{

}

void AGPlayerCharacter::OnAim_Hip_Update()
{

}

void AGPlayerCharacter::OnAim_Hip_Exit()
{

}

void AGPlayerCharacter::OnAim_Inactive_Begin()
{

}

void AGPlayerCharacter::OnAim_Inactive_Update()
{

}

void AGPlayerCharacter::OnAim_Inactive_Exit()
{

}

void AGPlayerCharacter::OnAim_IronSight_Begin()
{

}

void AGPlayerCharacter::OnAim_IronSight_Update()
{

}

void AGPlayerCharacter::OnAim_IronSight_Exit()
{

}

void AGPlayerCharacter::OnAim_None_Begin()
{

}

void AGPlayerCharacter::OnAim_None_Update()
{

}

void AGPlayerCharacter::OnAim_None_Exit()
{

}

void AGPlayerCharacter::OnAim_TelescopicSight_Begin()
{

}

void AGPlayerCharacter::OnAim_TelescopicSight_Update()
{

}

void AGPlayerCharacter::OnAim_TelescopicSight_Exit()
{

}

void AGPlayerCharacter::OnCombat_Equipping_Begin()
{

}

void AGPlayerCharacter::OnCombat_Equipping_Update()
{

}

void AGPlayerCharacter::OnCombat_Equipping_Exit()
{

}

void AGPlayerCharacter::OnCombat_Firing_Begin()
{

}

void AGPlayerCharacter::OnCombat_Firing_Update()
{

}

void AGPlayerCharacter::OnCombat_Firing_Exit()
{

}

void AGPlayerCharacter::OnCombat_Idle_Begin()
{

}

void AGPlayerCharacter::OnCombat_Idle_Update()
{

}

void AGPlayerCharacter::OnCombat_Idle_Exit()
{

}

void AGPlayerCharacter::OnCombat_Inactive_Begin()
{

}

void AGPlayerCharacter::OnCombat_Inactive_Update()
{

}

void AGPlayerCharacter::OnCombat_Inactive_Exit()
{

}

void AGPlayerCharacter::OnCombat_None_Begin()
{

}

void AGPlayerCharacter::OnCombat_None_Update()
{

}

void AGPlayerCharacter::OnCombat_None_Exit()
{

}

void AGPlayerCharacter::OnCombat_Melee_Begin()
{

}

void AGPlayerCharacter::OnCombat_Melee_Update()
{

}

void AGPlayerCharacter::OnCombat_Melee_Exit()
{

}

void AGPlayerCharacter::OnCombat_Reloading_Begin()
{

}

void AGPlayerCharacter::OnCombat_Reloading_Update()
{

}

void AGPlayerCharacter::OnCombat_Reloading_Exit()
{

}

void AGPlayerCharacter::OnCombat_Throwing_Begin()
{

}

void AGPlayerCharacter::OnCombat_Throwing_Update()
{

}

void AGPlayerCharacter::OnCombat_Throwing_Exit()
{

}

void AGPlayerCharacter::OnCombat_WeaponSwitching_Begin()
{

}

void AGPlayerCharacter::OnCombat_WeaponSwitching_Update()
{

}

void AGPlayerCharacter::OnCombat_WeaponSwitching_Exit()
{

}

void AGPlayerCharacter::OnMovement_CrouchingIdle_Begin()
{

}

void AGPlayerCharacter::OnMovement_CrouchingIdle_Update()
{

}

void AGPlayerCharacter::OnMovement_CrouchingIdle_Exit()
{

}

void AGPlayerCharacter::OnMovement_CrouchingWalking_Begin()
{

}

void AGPlayerCharacter::OnMovement_CrouchingWalking_Update()
{

}

void AGPlayerCharacter::OnMovement_CrouchingWalking_Exit()
{

}

void AGPlayerCharacter::OnMovement_Dead_Begin()
{

}

void AGPlayerCharacter::OnMovement_Dead_Update()
{

}

void AGPlayerCharacter::OnMovement_Dead_Exit()
{

}

void AGPlayerCharacter::OnMovement_Falling_Begin()
{

}

void AGPlayerCharacter::OnMovement_Falling_Update()
{

}

void AGPlayerCharacter::OnMovement_Falling_Exit()
{

}

void AGPlayerCharacter::OnMovement_Idle_Begin()
{

}

void AGPlayerCharacter::OnMovement_Idle_Update()
{

}

void AGPlayerCharacter::OnMovement_Idle_Exit()
{

}

void AGPlayerCharacter::OnMovement_Inactive_Begin()
{

}

void AGPlayerCharacter::OnMovement_Inactive_Update()
{

}

void AGPlayerCharacter::OnMovement_Inactive_Exit()
{

}

void AGPlayerCharacter::OnMovement_Jumping_Begin()
{

}

void AGPlayerCharacter::OnMovement_Jumping_Update()
{

}

void AGPlayerCharacter::OnMovement_Jumping_Exit()
{

}

void AGPlayerCharacter::OnMovement_Landing_Begin()
{

}

void AGPlayerCharacter::OnMovement_Landing_Update()
{

}

void AGPlayerCharacter::OnMovement_Landing_Exit()
{

}

void AGPlayerCharacter::OnMovement_Leaping_Begin()
{

}

void AGPlayerCharacter::OnMovement_Leaping_Update()
{

}

void AGPlayerCharacter::OnMovement_Leaping_Exit()
{

}

void AGPlayerCharacter::OnMovement_None_Begin()
{

}

void AGPlayerCharacter::OnMovement_None_Update()
{

}

void AGPlayerCharacter::OnMovement_None_Exit()
{

}

void AGPlayerCharacter::OnMovement_PlatformAscending_Begin()
{

}

void AGPlayerCharacter::OnMovement_PlatformAscending_Update()
{

}

void AGPlayerCharacter::OnMovement_PlatformAscending_Exit()
{

}

void AGPlayerCharacter::OnMovement_Plummeting_Begin()
{

}

void AGPlayerCharacter::OnMovement_Plummeting_Update()
{

}

void AGPlayerCharacter::OnMovement_Plummeting_Exit()
{

}

void AGPlayerCharacter::OnMovement_ProneCrawling_Begin()
{

}

void AGPlayerCharacter::OnMovement_ProneCrawling_Update()
{

}

void AGPlayerCharacter::OnMovement_ProneCrawling_Exit()
{

}

void AGPlayerCharacter::OnMovement_ProneIdle_Begin()
{

}

void AGPlayerCharacter::OnMovement_ProneIdle_Update()
{

}

void AGPlayerCharacter::OnMovement_ProneIdle_Exit()
{

}

void AGPlayerCharacter::OnMovement_Spawning_Begin()
{

}

void AGPlayerCharacter::OnMovement_Spawning_Update()
{

}

void AGPlayerCharacter::OnMovement_Spawning_Exit()
{

}

void AGPlayerCharacter::OnMovement_Sprinting_Begin()
{

}

void AGPlayerCharacter::OnMovement_Sprinting_Update()
{

}

void AGPlayerCharacter::OnMovement_Sprinting_Exit()
{

}

void AGPlayerCharacter::OnMovement_Vaulting_Begin()
{

}

void AGPlayerCharacter::OnMovement_Vaulting_Update()
{

}

void AGPlayerCharacter::OnMovement_Vaulting_Exit()
{

}

void AGPlayerCharacter::OnMovement_Walking_Begin()
{

}

void AGPlayerCharacter::OnMovement_Walking_Update()
{

}

void AGPlayerCharacter::OnMovement_Walking_Exit()
{

}

AGPlayerCharacter::Impl::Impl(AGPlayerCharacter* InOwner)
    : Owner(InOwner)
{

}

AGPlayerCharacter::Impl::~Impl() = default;

void AGPlayerCharacter::ImplDeleter::operator()(
        AGPlayerCharacter::Impl* Pointer)
{
    delete Pointer;
}
