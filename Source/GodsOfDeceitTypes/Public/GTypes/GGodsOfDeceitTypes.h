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

UENUM(BlueprintType)
enum class EGPlayerAimState : uint8
{
    None            UMETA(DisplayName="None"),
    Blocked         UMETA(DisplayName="Blocked"),
    Hip             UMETA(DisplayName="Hip"),
    Inactive        UMETA(DisplayName="Inactive"),
    IronSight       UMETA(DisplayName="IronSight"),
    TelescopicSight UMETA(DisplayName="TelescopicSight")
};

UENUM(BlueprintType)
enum class EGPlayerCombatState : uint8 {
    None            UMETA(DisplayName="None"),
    Equipping       UMETA(DisplayName="Equipping"),
    Firing          UMETA(DisplayName="Firing"),
    Idle            UMETA(DisplayName="Idle"),
    Inactive        UMETA(DisplayName="Inactive"),
    Melee           UMETA(DisplayName="Melee"),
    Reloading       UMETA(DisplayName="Reloading"),
    Throwing        UMETA(DisplayName="Throwing"),
    WeaponSwitching UMETA(DisplayName="WeaponSwitching")
};