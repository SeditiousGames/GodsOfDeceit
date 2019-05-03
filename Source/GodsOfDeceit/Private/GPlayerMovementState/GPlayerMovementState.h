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
 * A base struct to be implemented by all the player's movement states.
 */


#pragma once

#include <Containers/Array.h>
#include <CoreTypes.h>
#include <UObject/NameTypes.h>
#include <UObject/ObjectMacros.h>

#include <GTypes/GGodsOfDeceitTypes.h>

#include "GAnimation/GStateAnimation.h"
#include "GPlayerMovementState/GPlayerMovementStateCombatActions.h"
#include "GPlayerMovementState/GPlayerMovementStateTransition.h"

#include "GPlayerMovementState.generated.h"

class AGPlayerCharacter;

USTRUCT(BlueprintInternalUseOnly)
struct GODSOFDECEIT_API FGPlayerMovementState
{
    GENERATED_USTRUCT_BODY()

public:
    typedef void (AGPlayerCharacter::*EventHandlerPtr)(void);

protected:
    /** The player's combat state */
    EGPlayerMovementState State;

    /** The integer representation of the player's aim state */
    uint8 Id;

    /** The string representation of the player's aim state */
    FName Name;

    FGPlayerMovementStateCombatActions CombatActions;

    TArray<FGPlayerMovementStateTransition> OutTransitions;

    FGStateAnimation Animation;

    /** The begin event handler */
    EventHandlerPtr BeginEventHandler;

    /** The begin event handler's name */
    FName BeginEventHandlerName;

    /** The update event handler */
    EventHandlerPtr UpdateEventHandler;

    /** The update event handler's name */
    FName UpdateEventHandlerName;

    /** The exit event handler */
    EventHandlerPtr ExitEventHandler;

    /** The exit event handler's name */
    FName ExitEventHandlerName;

public:
    FGPlayerMovementState();

protected:
    /** Registers event handlers */
    void RegisterHandler(const EventHandlerPtr HandlerPointer,
                         const FName& HandlerName,
                         EventHandlerPtr& Out_HandlerPointer,
                         FName& Out_HandlerName);
};
