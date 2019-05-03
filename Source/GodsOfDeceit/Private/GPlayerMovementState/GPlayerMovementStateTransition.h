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
 * A struct which defines transition data between movement states.
 */


#pragma once

#include <CoreTypes.h>
#include <UObject/ObjectMacros.h>

#include <GTypes/GGodsOfDeceitTypes.h>

#include "GAnimation/GAnimation.h"

#include "GPlayerMovementStateTransition.generated.h"

USTRUCT(BlueprintInternalUseOnly)
struct GODSOFDECEIT_API FGPlayerMovementStateTransition
{
    GENERATED_USTRUCT_BODY()

protected:
    UPROPERTY ( EditAnywhere, BlueprintReadOnly )
    EGPlayerMovementState To;

    UPROPERTY ( EditDefaultsOnly, BlueprintReadOnly, Category = "Animation" )
    float BlendTime;

    UPROPERTY ( EditDefaultsOnly, BlueprintReadOnly, Category = "Animation" )
    float TransitionAnimationBlendInTime;

    UPROPERTY ( EditDefaultsOnly, BlueprintReadOnly, Category = "Animation" )
    float TransitionAnimationBlendOutTime;

    UPROPERTY ( EditDefaultsOnly, BlueprintReadOnly, Category = "Animation" )
    FGAnimation Animation;

public:
    FGPlayerMovementStateTransition();
    explicit FGPlayerMovementStateTransition(
                const EGPlayerMovementState& InTo);

public:
    FORCEINLINE float GetBlendTime() const
    {
        return BlendTime;
    }

    FORCEINLINE float GetTransitionAnimationBlendInTime() const
    {
        return TransitionAnimationBlendInTime;
    }

    FORCEINLINE float GetTransitionAnimationBlendOutTime() const
    {
        return TransitionAnimationBlendOutTime;
    }

    FORCEINLINE const FGAnimation& GetAnimation() const
    {
        return Animation;
    }

    FORCEINLINE const EGPlayerMovementState& GetTo() const
    {
        return To;
    }
};
