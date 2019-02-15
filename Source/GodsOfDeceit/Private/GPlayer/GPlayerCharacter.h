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


#pragma once

#include <CoreTypes.h>
#include <GGameFramework/GCharacter.h>
#include <UObject/ObjectMacros.h>

#include "GPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

enum class FSM_Transition : uint8;

UCLASS(BlueprintType, config=Game)
class GODSOFDECEIT_API AGPlayerCharacter : public ACharacter
{
    GENERATED_UCLASS_BODY()

protected:
    /** Camera boom which positions the third-person camera behind the character */
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* ThirdPersonCameraBoom;

    /** Third-person camera */
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    UCameraComponent* ThirdPersonCamera;

    /** First-person camera */
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    UCameraComponent* FirstPersonCamera;

public:
    /**
     * Handles Begin event for any Aim state
     *
     * @param    StateId         The state id
     * @param    PreviousStateId The previous state id
     * @param    StateName       The state name
     * @param    Transition      The finite state machine transition
     *
     * @see  OnAim_*_Begin()
     */
    UFUNCTION()
    void OnBeginAimState(uint8 StateId, uint8 PreviousStateId,
                         FName StateName, FSM_Transition Transition);

    /**
     * Handles Update event for any Aim state
     *
     * @param    StateId         The state id
     * @param    StateName       The state name
     * @param    StateTime       The state time
     *
     * @see  OnAim_*_Update()
     */
    UFUNCTION()
    void OnUpdateAimState(uint8 StateId, FName StateName,
                          float StateTime);

    /**
     * Handles Exit event for any Aim state
     *
     * @param    StateId         The state id
     * @param    StateName       The state name
     * @param    Transition      The finite state machine transition
     *
     * @see  OnAim_*_Exit()
     */
    UFUNCTION()
    void OnExitAimState(uint8 StateId, FName StateName,
                        FSM_Transition Transition);

    /**
     * Handles Begin event for any Combat state
     *
     * @param    StateId         The state id
     * @param    PreviousStateId The previous state id
     * @param    StateName       The state name
     * @param    Transition      The finite state machine transition
     *
     * @see  OnCombat_*_Begin()
     */
    UFUNCTION()
    void OnBeginCombatState(uint8 StateId, uint8 PreviousStateId,
                            FName StateName, FSM_Transition Transition);

    /**
     * Handles Update event for any Combat state
     *
     * @param    StateId         The state id
     * @param    StateName       The state name
     * @param    StateTime       The state time
     *
     * @see  OnCombat_*_Update()
     */
    UFUNCTION()
    void OnUpdateCombatState(uint8 StateId, FName StateName,
                             float StateTime);

    /**
     * Handles Exit event for any Combat state
     *
     * @param    StateId         The state id
     * @param    StateName       The state name
     * @param    Transition      The finite state machine transition
     *
     * @see  OnCombat_*_Exit()
     */
    UFUNCTION()
    void OnExitCombatState(uint8 StateId, FName StateName,
                           FSM_Transition Transition);

    /**
     * Handles Begin event for any Movement state
     *
     * @param    StateId         The state id
     * @param    PreviousStateId The previous state id
     * @param    StateName       The state name
     * @param    Transition      The finite state machine transition
     *
     * @see  OnMovement_*_Begin()
     */
    UFUNCTION()
    void OnBeginMovementState(uint8 StateId, uint8 PreviousStateId,
                              FName StateName, FSM_Transition Transition);

    /**
    * Handles Update event for any Movement state
    *
    * @param    StateId         The state id
    * @param    StateName       The state name
    * @param    StateTime       The state time
    *
    * @see  OnMovement_*_Update()
    */
    UFUNCTION()
    void OnUpdateMovementState(uint8 StateId, FName StateName,
                               float StateTime);

    /**
    * Handles Exit event for any Movement state
    *
    * @param    StateId         The state id
    * @param    StateName       The state name
    * @param    Transition      The finite state machine transition
    *
    * @see  OnMovement_*_Exit()
    */
    UFUNCTION()
    void OnExitMovementState(uint8 StateId, FName StateName,
                             FSM_Transition Transition);

    /** Handles Blocked state Begin event for Aim state machine */
    UFUNCTION()
    void OnAim_Blocked_Begin();

    /** Handles Blocked state Update event for Aim state machine */
    UFUNCTION()
    void OnAim_Blocked_Update();

    /** Handles Blocked state Exit event for Aim state machine */
    UFUNCTION()
    void OnAim_Blocked_Exit();

    /** Handles Hip state Begin event for Aim state machine */
    UFUNCTION()
    void OnAim_Hip_Begin();

    /** Handles Hip state Update event for Aim state machine */
    UFUNCTION()
    void OnAim_Hip_Update();

    /** Handles Hip state Exit event for Aim state machine */
    UFUNCTION()
    void OnAim_Hip_Exit();

    /** Handles Inactive state Begin event for Aim state machine */
    UFUNCTION()
    void OnAim_Inactive_Begin();

    /** Handles Inactive state Update event for Aim state machine */
    UFUNCTION()
    void OnAim_Inactive_Update();

    /** Handles Inactive state Exit event for Aim state machine */
    UFUNCTION()
    void OnAim_Inactive_Exit();

    /** Handles Iron Sight state Begin event for Aim state machine */
    UFUNCTION()
    void OnAim_IronSight_Begin();

    /** Handles Iron Sight state Update event for Aim state machine */
    UFUNCTION()
    void OnAim_IronSight_Update();

    /** Handles Iron Sight state Exit event for Aim state machine */
    UFUNCTION()
    void OnAim_IronSight_Exit();

    /** Handles None state Begin event for Aim state machine */
    UFUNCTION()
    void OnAim_None_Begin();

    /** Handles None state Update event for Aim state machine */
    UFUNCTION()
    void OnAim_None_Update();

    /** Handles None state Exit event for Aim state machine */
    UFUNCTION()
    void OnAim_None_Exit();

    /** Handles Telescopic Sight state Begin event for Aim state machine */
    UFUNCTION()
    void OnAim_TelescopicSight_Begin();

    /** Handles Telescopic Sight state Update event for Aim state machine */
    UFUNCTION()
    void OnAim_TelescopicSight_Update();

    /** Handles Telescopic Sight state Exit event for Aim state machine */
    UFUNCTION()
    void OnAim_TelescopicSight_Exit();

    /** Handles Equipping state Begin event for Combat state machine */
    UFUNCTION()
    void OnCombat_Equipping_Begin();

    /** Handles Equipping state Update event for Combat state machine */
    UFUNCTION()
    void OnCombat_Equipping_Update();

    /** Handles Equipping state Exit event for Combat state machine */
    UFUNCTION()
    void OnCombat_Equipping_Exit();

    /** Handles Firing state Begin event for Combat state machine */
    UFUNCTION()
    void OnCombat_Firing_Begin();

    /** Handles Firing state Update event for Combat state machine */
    UFUNCTION()
    void OnCombat_Firing_Update();

    /** Handles Firing state Exit event for Combat state machine */
    UFUNCTION()
    void OnCombat_Firing_Exit();

    /** Handles Idle state Begin event for Combat state machine */
    UFUNCTION()
    void OnCombat_Idle_Begin();

    /** Handles Idle state Update event for Combat state machine */
    UFUNCTION()
    void OnCombat_Idle_Update();

    /** Handles Idle state Exit event for Combat state machine */
    UFUNCTION()
    void OnCombat_Idle_Exit();

    /** Handles Inactive state Begin event for Combat state machine */
    UFUNCTION()
    void OnCombat_Inactive_Begin();

    /** Handles Inactive state Update event for Combat state machine */
    UFUNCTION()
    void OnCombat_Inactive_Update();

    /** Handles Inactive state Exit event for Combat state machine */
    UFUNCTION()
    void OnCombat_Inactive_Exit();

    /** Handles None state Begin event for Combat state machine */
    UFUNCTION()
    void OnCombat_None_Begin();

    /** Handles None state Update event for Combat state machine */
    UFUNCTION()
    void OnCombat_None_Update();

    /** Handles None state Exit event for Combat state machine */
    UFUNCTION()
    void OnCombat_None_Exit();

    /** Handles Melee state Begin event for Combat state machine */
    UFUNCTION()
    void OnCombat_Melee_Begin();

    /** Handles Melee state Update event for Combat state machine */
    UFUNCTION()
    void OnCombat_Melee_Update();

    /** Handles Melee state Exit event for Combat state machine */
    UFUNCTION()
    void OnCombat_Melee_Exit();

    /** Handles Reloading state Begin event for Combat state machine */
    UFUNCTION()
    void OnCombat_Reloading_Begin();

    /** Handles Reloading state Update event for Combat state machine */
    UFUNCTION()
    void OnCombat_Reloading_Update();

    /** Handles Reloading state Exit event for Combat state machine */
    UFUNCTION()
    void OnCombat_Reloading_Exit();

    /** Handles Throwing state Begin event for Combat state machine */
    UFUNCTION()
    void OnCombat_Throwing_Begin();

    /** Handles Throwing state Update event for Combat state machine */
    UFUNCTION()
    void OnCombat_Throwing_Update();

    /** Handles Throwing state Exit event for Combat state machine */
    UFUNCTION()
    void OnCombat_Throwing_Exit();

    /** Handles Weapon Switching state Begin event for Combat state machine */
    UFUNCTION()
    void OnCombat_WeaponSwitching_Begin();

    /** Handles Weapon Switching state Update event for Combat state machine */
    UFUNCTION()
    void OnCombat_WeaponSwitching_Update();

    /** Handles Weapon Switching state Exit event for Combat state machine */
    UFUNCTION()
    void OnCombat_WeaponSwitching_Exit();

    /** Handles Crouching Idle state Begin event for Movement state machine */
    UFUNCTION()
    void OnMovement_CrouchingIdle_Begin();

    /** Handles Crouching Idle state Update event for Movement state machine */
    UFUNCTION()
    void OnMovement_CrouchingIdle_Update();

    /** Handles Crouching Idle state Exit event for Movement state machine */
    UFUNCTION()
    void OnMovement_CrouchingIdle_Exit();

    /**
     * Handles Crouching Walking state Begin event for Movement state machine
     */
    UFUNCTION()
    void OnMovement_CrouchingWalking_Begin();

    /**
     * Handles Crouching Walking state Update event for Movement state machine
     */
    UFUNCTION()
    void OnMovement_CrouchingWalking_Update();

    /**
     * Handles Crouching Walking state Exit event for Movement state machine
     */
    UFUNCTION()
    void OnMovement_CrouchingWalking_Exit();

    /** Handles Dead state Begin event for Movement state machine */
    UFUNCTION()
    void OnMovement_Dead_Begin();

    /** Handles Dead state Update event for Movement state machine */
    UFUNCTION()
    void OnMovement_Dead_Update();

    /** Handles Dead state Exit event for Movement state machine */
    UFUNCTION()
    void OnMovement_Dead_Exit();

    /** Handles Falling state Begin event for Movement state machine */
    UFUNCTION()
    void OnMovement_Falling_Begin();

    /** Handles Falling state Update event for Movement state machine */
    UFUNCTION()
    void OnMovement_Falling_Update();

    /** Handles Falling state Exit event for Movement state machine */
    UFUNCTION()
    void OnMovement_Falling_Exit();

    /** Handles Idle state Begin event for Movement state machine */
    UFUNCTION()
    void OnMovement_Idle_Begin();

    /** Handles Idle state Update event for Movement state machine */
    UFUNCTION()
    void OnMovement_Idle_Update();

    /** Handles Idle state Exit event for Movement state machine */
    UFUNCTION()
    void OnMovement_Idle_Exit();

    /** Handles Inactive state Begin event for Movement state machine */
    UFUNCTION()
    void OnMovement_Inactive_Begin();

    /** Handles Inactive state Update event for Movement state machine */
    UFUNCTION()
    void OnMovement_Inactive_Update();

    /** Handles Inactive state Exit event for Movement state machine */
    UFUNCTION()
    void OnMovement_Inactive_Exit();

    /** Handles Jumping state Begin event for Movement state machine */
    UFUNCTION()
    void OnMovement_Jumping_Begin();

    /** Handles Jumping state Update event for Movement state machine */
    UFUNCTION()
    void OnMovement_Jumping_Update();

    /** Handles Jumping state Exit event for Movement state machine */
    UFUNCTION()
    void OnMovement_Jumping_Exit();

    /** Handles Landing state Begin event for Movement state machine */
    UFUNCTION()
    void OnMovement_Landing_Begin();

    /** Handles Landing state Update event for Movement state machine */
    UFUNCTION()
    void OnMovement_Landing_Update();

    /** Handles Landing state Exit event for Movement state machine */
    UFUNCTION()
    void OnMovement_Landing_Exit();

    /** Handles Leaping state Begin event for Movement state machine */
    UFUNCTION()
    void OnMovement_Leaping_Begin();

    /** Handles Leaping state Update event for Aim state machine */
    UFUNCTION()
    void OnMovement_Leaping_Update();

    /** Handles Leaping state Exit event for Movement state machine */
    UFUNCTION()
    void OnMovement_Leaping_Exit();

    /** Handles None state Begin event for Movement state machine */
    UFUNCTION()
    void OnMovement_None_Begin();

    /** Handles None state Update event for Movement state machine */
    UFUNCTION()
    void OnMovement_None_Update();

    /** Handles None state Exit event for Movement state machine */
    UFUNCTION()
    void OnMovement_None_Exit();

    /**
     * Handles Platform Ascending state Begin event for Movement state machine
     */
    UFUNCTION()
    void OnMovement_PlatformAscending_Begin();

    /**
     * Handles Platform Ascending state Update event for Movement state machine
     */
    UFUNCTION()
    void OnMovement_PlatformAscending_Update();

    /**
     * Handles Platform Ascending state Exit event for Movement state machine
     */
    UFUNCTION()
    void OnMovement_PlatformAscending_Exit();

    /** Handles Plummeting state Begin event for Movement state machine */
    UFUNCTION()
    void OnMovement_Plummeting_Begin();

    /** Handles Plummeting state Update event for Movement state machine */
    UFUNCTION()
    void OnMovement_Plummeting_Update();

    /** Handles Plummeting state Exit event for Movement state machine */
    UFUNCTION()
    void OnMovement_Plummeting_Exit();

    /** Handles Prone Crawling state Begin event for Movement state machine */
    UFUNCTION()
    void OnMovement_ProneCrawling_Begin();

    /** Handles Prone Crawling state Update event for Movement state machine */
    UFUNCTION()
    void OnMovement_ProneCrawling_Update();

    /** Handles Prone Crawling state Exit event for Movement state machine */
    UFUNCTION()
    void OnMovement_ProneCrawling_Exit();

    /** Handles Prone Idle state Begin event for Movement state machine */
    UFUNCTION()
    void OnMovement_ProneIdle_Begin();

    /** Handles Prone Idle state Update event for Movement state machine */
    UFUNCTION()
    void OnMovement_ProneIdle_Update();

    /** Handles Prone Idle state Exit event for Movement state machine */
    UFUNCTION()
    void OnMovement_ProneIdle_Exit();

    /** Handles Spawning state Begin event for Movement state machine */
    UFUNCTION()
    void OnMovement_Spawning_Begin();

    /** Handles Spawning state Update event for Movement state machine */
    UFUNCTION()
    void OnMovement_Spawning_Update();

    /** Handles Spawning state Exit event for Movement state machine */
    UFUNCTION()
    void OnMovement_Spawning_Exit();

    /** Handles Sprinting state Begin event for Movement state machine */
    UFUNCTION()
    void OnMovement_Sprinting_Begin();

    /** Handles Sprinting state Update event for Movement state machine */
    UFUNCTION()
    void OnMovement_Sprinting_Update();

    /** Handles Sprinting state Exit event for Movement state machine */
    UFUNCTION()
    void OnMovement_Sprinting_Exit();

    /** Handles Vaulting state Begin event for Movement state machine */
    UFUNCTION()
    void OnMovement_Vaulting_Begin();

    /** Handles Vaulting state Update event for Movement state machine */
    UFUNCTION()
    void OnMovement_Vaulting_Update();

    /** Handles Vaulting state Exit event for Movement state machine */
    UFUNCTION()
    void OnMovement_Vaulting_Exit();

    /** Handles Walking state Begin event for Movement state machine */
    UFUNCTION()
    void OnMovement_Walking_Begin();

    /** Handles Walking state Update event for Movement state machine */
    UFUNCTION()
    void OnMovement_Walking_Update();

    /** Handles Walking state Exit event for Movement state machine */
    UFUNCTION()
    void OnMovement_Walking_Exit();

public:
    /** Returns ThirdPersonCameraBoom component */
    FORCEINLINE const USpringArmComponent* GetThirdPersonCameraBoom() const
    {
        return ThirdPersonCameraBoom;
    }

    /** Returns ThirdPersonCamera component */
    FORCEINLINE const UCameraComponent* GetThirdPersonCamera() const
    {
        return ThirdPersonCamera;
    }

    /** Returns FirstPersonCamera component */
    FORCEINLINE const UCameraComponent* GetFirstPersonCamera() const
    {
        return FirstPersonCamera;
    }
};
