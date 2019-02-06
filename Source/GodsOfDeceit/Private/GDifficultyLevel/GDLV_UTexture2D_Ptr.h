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
 * A game difficulty level variable which represents UTexture2D* type
 */


#pragma once

#include <Engine/Texture2D.h>
#include <UObject/Object.h>
#include <UObject/ObjectMacros.h>

#include "GDLV_UTexture2D_Ptr.generated.h"

USTRUCT(BlueprintInternalUseOnly)
struct GODSOFDECEIT_API FGDLV_UTexture2D_Ptr
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY ( EditDefaultsOnly, Category = "Difficulty Level" )
    UTexture2D* Recruit;

    UPROPERTY ( EditDefaultsOnly, Category = "Difficulty Level" )
    UTexture2D* Regular;

    UPROPERTY ( EditDefaultsOnly, Category = "Difficulty Level" )
    UTexture2D* Hardened;

    UPROPERTY ( EditDefaultsOnly, Category = "Difficulty Level" )
    UTexture2D* Veteran;

private:
    UPROPERTY ( Transient )
    UObject* Outer;

    UPROPERTY ( Transient )
    UTexture2D* Dummy;

public:
    FGDLV_UTexture2D_Ptr();

public:
    FORCEINLINE void Initialize(UObject* InOuter)
    {
        Outer = InOuter;
    }

    const UTexture2D* Get() const;

    FORCEINLINE UTexture2D* Get()
    {
        return const_cast<UTexture2D*>(
                    static_cast<const FGDLV_UTexture2D_Ptr*>(this)->Get());
    }
};
