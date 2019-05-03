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
 * An interface to be implemented by all the player's aim states.
 */


#pragma once

#include <CoreTypes.h>
#include <UObject/Interface.h>
#include <UObject/NameTypes.h>
#include <UObject/ObjectMacros.h>

#include <GTypes/GGodsOfDeceitTypes.h>

#include "IGPlayerCombatState.generated.h"

class AGPlayerCharacter;

UINTERFACE(Category = "FSM", BlueprintType, meta = (DisplayName = "Combat State Interface"))
class GODSOFDECEIT_API UGPlayerCombatState : public UInterface
{
    GENERATED_UINTERFACE_BODY()
};

class GODSOFDECEIT_API IGPlayerCombatState
{
    GENERATED_IINTERFACE_BODY()

public:
    typedef void (AGPlayerCharacter::*EventHandlerPtr)(void);
    typedef IGPlayerCombatState* Ptr;

protected:
    /** The player's combat state */
    EGPlayerCombatState State;

    /** The integer representation of the player's aim state */
    uint8 Id;

    /** The string representation of the player's aim state */
    FName Name;

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
    /** Returns State */
    FORCEINLINE const EGPlayerCombatState& GetState() const
    {
        return State;
    }

    /** Returns Id */
    FORCEINLINE uint8 GetId() const
    {
        return Id;
    }

    /** Returns Name */
    FORCEINLINE const FName& GetName() const
    {
        return Name;
    }

    /** Returns BeginEventHandler */
    FORCEINLINE EventHandlerPtr GetBeginEventHandler() const
    {
        checkf(BeginEventHandler, TEXT("FATAL: null event handler detected!"));

        return BeginEventHandler;
    }

    /** Returns BeginEventHandlerName */
    FORCEINLINE const FName& GetBeginEventHandlerName() const
    {
        return BeginEventHandlerName;
    }

    /** Returns UpdateEventHandler */
    FORCEINLINE EventHandlerPtr GetUpdateEventHandler() const
    {
        checkf(UpdateEventHandler, TEXT("FATAL: null event handler detected!"));

        return UpdateEventHandler;
    }

    /** Returns UpdateEventHandlerName */
    FORCEINLINE const FName& GetUpdateEventHandlerName() const
    {
        return UpdateEventHandlerName;
    }

    /** Returns ExitEventHandler */
    FORCEINLINE EventHandlerPtr GetExitEventHandler() const
    {
        checkf(ExitEventHandler, TEXT("FATAL: null event handler detected!"));

        return ExitEventHandler;
    }

    /** Returns ExitEventHandlerName */
    FORCEINLINE const FName& GetExitEventHandlerName() const
    {
        return ExitEventHandlerName;
    }

protected:
    /** Registers event handlers */
    void RegisterHandler(const EventHandlerPtr HandlerPointer,
                         const FName& HandlerName,
                         EventHandlerPtr& Out_HandlerPointer,
                         FName& Out_HandlerName);

#define RegisterBeginHandler( Pointer ) \
    RegisterHandler( Pointer, STATIC_FUNCTION_FNAME( TEXT( #Pointer ) ), \
    BeginEventHandler, BeginEventHandlerName );

#define RegisterUpdateHandler( Pointer ) \
    RegisterHandler( Pointer, STATIC_FUNCTION_FNAME( TEXT( #Pointer ) ), \
    UpdateEventHandler, UpdateEventHandlerName );

#define RegisterExitHandler( Pointer ) \
    RegisterHandler( Pointer, STATIC_FUNCTION_FNAME( TEXT( #Pointer ) ), \
    ExitEventHandler, ExitEventHandlerName );
};
