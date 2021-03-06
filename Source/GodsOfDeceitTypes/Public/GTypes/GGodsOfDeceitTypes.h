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
 * A place to define the main game module's types and enumerations.
 */


#pragma once

#include <CoreTypes.h>
#include <UObject/ObjectMacros.h>

/** Enum that defines all player's aim states. */
UENUM(BlueprintType)
enum class EGPlayerAimState : uint8
{
    /**
     * Uninitialized aim state.
     *
     * Note: This has to be defined as the first enum element since the enum
     * count calculations relies on it.
     */
    None            UMETA(DisplayName="None"),

    /** Player's aim state machine has been disabled. */
    Inactive        UMETA(DisplayName="Inactive"),

    /** Player's aim has been blocked by an obstacle. */
    Blocked         UMETA(DisplayName="Blocked"),

    /** Hip aim mode. */
    Hip             UMETA(DisplayName="Hip"),

    /** Iron-sight aim mode. */
    IronSight       UMETA(DisplayName="IronSight"),

    /**
     * Telescopi-sight aim mode.
     *
     * Note: This has to be defined as the last enum element since the enum
     * count calculations relies on it.
     */
    TelescopicSight UMETA(DisplayName="TelescopicSight")
};

/**
 * Calculates the number of elements defined by the player's aim state enum at
 * compile time.
 */
constexpr uint8 G_PLAYER_AIM_STATE_ENUM_COUNT =
        static_cast<uint8>(EGPlayerAimState::TelescopicSight)
        - static_cast<uint8>(EGPlayerAimState::None)
        + 1;

/** Enum that defines all player's combat states. */
UENUM(BlueprintType)
enum class EGPlayerCombatState : uint8
{
    /**
     * Uninitialized combat state.
     *
     * Note: This has to be defined as the first enum element since the enum
     * count calculations relies on it.
     */
    None            UMETA(DisplayName="None"),

    /** Player's combat state machine has been disabled. */
    Inactive        UMETA(DisplayName="Inactive"),

    /** Player is equiping a weapon. */
    Equipping       UMETA(DisplayName="Equipping"),

    /** Player is firing a weapon. */
    Firing          UMETA(DisplayName="Firing"),

    /** Player is not fighting or doing nothing with the current weapon. */
    Idle            UMETA(DisplayName="Idle"),

    /** Player is performing a melee attack. */
    Melee           UMETA(DisplayName="Melee"),

    /** Player is reloading a weapon. */
    Reloading       UMETA(DisplayName="Reloading"),

    /** Player is throwing a grenade. */
    Throwing        UMETA(DisplayName="Throwing"),

    /**
    * Player is switching a weapon.
    *
    * Note: This has to be defined as the last enum element since the enum
    * count calculations relies on it.
    */
    WeaponSwitching UMETA(DisplayName="WeaponSwitching")
};

/**
 * Calculates the number of elements defined by the player's combat state enum
 * at compile time.
 */
constexpr uint8 G_PLAYER_COMBAT_STATE_ENUM_COUNT =
        static_cast<uint8>(EGPlayerCombatState::WeaponSwitching)
        - static_cast<uint8>(EGPlayerCombatState::None)
        + 1;

/** Enum that defines all player's movement states. */
UENUM(BlueprintType)
enum class EGPlayerMovementState : uint8
{
    /**
     * Uninitialized movement state.
     *
     * Note: This has to be defined as the first enum element since the enum
     * count calculations relies on it.
     */
    None                UMETA(DisplayName="None"),

    /** Player is idle while in crouching pose. */
    Crouching_Idle      UMETA(DisplayName="Crouching_Idle"),

    /** Player is walking in crouching pose. */
    Crouching_Walking   UMETA(DisplayName="Crouching_Walking"),

    /** Player is dead. */
    Dead                UMETA(DisplayName="Dead"),

    /** Player is falling down. */
    Falling             UMETA(DisplayName="Falling"),

    /** Player is not performing a movement action. */
    Idle                UMETA(DisplayName="Idle"),

    /** Player's movement state machine has been disabled. */
    Inactive            UMETA(DisplayName="Inactive"),

    /** Player is performing a jump. */
    Jumping             UMETA(DisplayName="Jumping"),

    /** Player is landing on a ground. */
    Landing             UMETA(DisplayName="Landing"),

    /** Player is leaping forward. */
    Leaping             UMETA(DisplayName="Leaping"),

    /** Player is ascending a platform. */
    PlatformAscending   UMETA(DisplayName="PlatformAscending"),

    /** Player is in free fall. */
    Plummeting          UMETA(DisplayName="Plummeting"),

    /** Player is crawling. */
    Prone_Crawling      UMETA(DisplayName="Prone_Crawling"),

    /** Player is idle while in crawling pose. */
    Prone_Idle          UMETA(DisplayName="Prone_Idle"),

    /** Player is spawning. */
    Spawning            UMETA(DisplayName="Spawning"),

    /** Player is sprinting. */
    Sprinting           UMETA(DisplayName="Sprinting"),

    /** Player is performing a vault. */
    Vaulting            UMETA(DisplayName="Vaulting"),

    /**
    * Player is walking.
    *
    * Note: This has to be defined as the last enum element since the enum
    * count calculations relies on it.
    */
    Walking             UMETA(DisplayName="Walking")
};

/**
 * Calculates the number of elements defined by the player's movement state
 * enum at compile time.
 */
constexpr uint8 G_PLAYER_MOVEMENT_STATE_ENUM_COUNT =
        static_cast<uint8>(EGPlayerMovementState::Walking)
        - static_cast<uint8>(EGPlayerMovementState::None)
        + 1;
