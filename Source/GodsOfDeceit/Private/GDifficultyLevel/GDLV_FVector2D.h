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


#pragma once

#include <Math/Vector2D.h>
#include <UObject/Object.h>
#include <UObject/ObjectMacros.h>

#include "GDLV_FVector2D.generated.h"

USTRUCT(BlueprintInternalUseOnly)
struct GODSOFDECEIT_API FGDLV_FVector2D
{
    GENERATED_USTRUCT_BODY()

public:
    /** The desired value for Recruit difficuly level */
    UPROPERTY ( EditDefaultsOnly, Category = "Difficulty Level" )
    FVector2D Recruit;

    /** The desired value for Regular difficuly level */
    UPROPERTY ( EditDefaultsOnly, Category = "Difficulty Level" )
    FVector2D Regular;

    /** The desired value for Hardened difficuly level */
    UPROPERTY ( EditDefaultsOnly, Category = "Difficulty Level" )
    FVector2D Hardened;

    /** The desired value for Veteran difficuly level */
    UPROPERTY ( EditDefaultsOnly, Category = "Difficulty Level" )
    FVector2D Veteran;

private:
    /** The transient outer uboject class in order to obtain a valied world
     *  object */
    UPROPERTY ( Transient )
    UObject* Outer;

    /** Nothing special but a dummy value */
    UPROPERTY ( Transient )
    FVector2D Dummy;

public:
    FGDLV_FVector2D();

public:
    /** Initializes the wrapper object by providing the outer uobject;
     *  this function should be called prior to setting/getting any values,
     *  or the game will crash. */
    FORCEINLINE void Initialize(UObject* InOuter)
    {
        Outer = InOuter;
    }

    /** Returns the const value for current difficuly level */
    const FVector2D& Get() const;

    /** Returns the non-const value for current difficuly level */
    FORCEINLINE FVector2D& Get()
    {
        return const_cast<FVector2D&>(
                    static_cast<const FGDLV_FVector2D*>(this)->Get());
    }
};
