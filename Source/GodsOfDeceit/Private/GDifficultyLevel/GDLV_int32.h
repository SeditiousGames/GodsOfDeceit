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
 * A game difficulty level variable which represents int32 type
 */


#pragma once

#include <CoreTypes.h>
#include <UObject/Object.h>
#include <UObject/ObjectMacros.h>

#include "GDLV_int32.generated.h"

USTRUCT(BlueprintInternalUseOnly)
struct GODSOFDECEIT_API FGDLV_int32
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY ( EditDefaultsOnly, Category = "Difficulty Level" )
    int32 Recruit;

    UPROPERTY ( EditDefaultsOnly, Category = "Difficulty Level" )
    int32 Regular;

    UPROPERTY ( EditDefaultsOnly, Category = "Difficulty Level" )
    int32 Hardened;

    UPROPERTY ( EditDefaultsOnly, Category = "Difficulty Level" )
    int32 Veteran;

private:
    UPROPERTY ( Transient )
    UObject* Outer;

    UPROPERTY ( Transient )
    int32 Dummy;

public:
    FGDLV_int32();

public:
    FORCEINLINE void Initialize(UObject* InOuter)
    {
        Outer = InOuter;
    }

    const int32& Get() const;

    FORCEINLINE int32& Get()
    {
        return const_cast<int32&>(
                    static_cast<const FGDLV_int32*>(this)->Get());
    }
};
