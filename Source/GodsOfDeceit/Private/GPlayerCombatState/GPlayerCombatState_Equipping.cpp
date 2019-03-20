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
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLCombat, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @section DESCRIPTION
 *
 * Equipping state's data for the Combat state machine.
 */


#include "GPlayerCombatState/GPlayerCombatState_Equipping.h"
#include "GodsOfDeceit.h"

#include <Containers/UnrealString.h>

#include <GTypes/GGodsOfDeceitTypes.h>

#include "GPlayer/GPlayerCharacter.h"

UGPlayerCombatState_Equipping::UGPlayerCombatState_Equipping(
        const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    State = EGPlayerCombatState::Equipping;
    Id = static_cast<uint8>(State);
    Name = FName(TEXT("Equipping"));

    RegisterBeginHandler(&AGPlayerCharacter::OnCombat_Equipping_Begin);
    RegisterUpdateHandler(&AGPlayerCharacter::OnCombat_Equipping_Update);
    RegisterExitHandler(&AGPlayerCharacter::OnCombat_Equipping_Exit);
}
