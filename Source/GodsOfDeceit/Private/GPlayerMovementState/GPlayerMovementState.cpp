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


#include "GPlayerMovementState/GPlayerMovementState.h"
#include "GodsOfDeceit.h"

#include <Misc/AssertionMacros.h>

FGPlayerMovementState::FGPlayerMovementState()
    : State(EGPlayerMovementState::None),
      Id(0),
      Name(NAME_None),
      OutTransitions { },
      BeginEventHandler(nullptr),
      BeginEventHandlerName(NAME_None),
      UpdateEventHandler(nullptr),
      UpdateEventHandlerName(NAME_None),
      ExitEventHandler(nullptr),
      ExitEventHandlerName(NAME_None)
{

}

void FGPlayerMovementState::RegisterHandler(
        const EventHandlerPtr HandlerPointer, const FName& HandlerName,
        EventHandlerPtr& Out_HandlerPointer, FName& Out_HandlerName)
{
    checkf(HandlerPointer,
           TEXT("FATAL: movement state event handler pointer is null!"));

    Out_HandlerPointer = HandlerPointer;
    Out_HandlerName = HandlerName;
}
