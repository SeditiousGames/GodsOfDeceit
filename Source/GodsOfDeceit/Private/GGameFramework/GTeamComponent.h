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
 * A team component which allows distinguishing friends from enemies or
 * neutrals.
 */


#pragma once

#include <Components/ActorComponent.h>
#include <CoreTypes.h>
#include <Math/Color.h>
#include <UObject/ObjectMacros.h>

#include "GTeamComponent.generated.h"

UCLASS(ClassGroup=(GODSOFDECEIT), meta=(BlueprintSpawnableComponent))
class GODSOFDECEIT_API UGTeamComponent : public UActorComponent
{
    GENERATED_UCLASS_BODY()

public:
    /** Determines whether an actor is neutral or not */
    static bool IsNeutral(AActor* Actor);

    /** Determines whether actors A and B are firnedly or not */
    static bool AreFriendly(AActor* ActorA, AActor* ActorB);

    /** Determines whether actors A and B are enemies or not */
    FORCEINLINE static bool AreEnemies(AActor* ActorA, AActor* ActorB)
    {
        return (!IsNeutral(ActorA) && !IsNeutral(ActorB)
                && !AreFriendly(ActorA, ActorB));
    }

protected:
    /** The team number */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Team Component")
    uint8 TeamNumber;

    /** The team color */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Team Component")
    FColor TeamColor;

public:
    /** Returns TeamNumber */
    FORCEINLINE uint8 GetTeamNumber() const
    {
        return TeamNumber;
    }

    /** Sets TeamNumber */
    FORCEINLINE void SetTeamNumber(const uint8 Number)
    {
        TeamNumber = Number;
    }

    /** Returns TeamColor */
    FORCEINLINE const FColor& GetTeamColor() const
    {
        return TeamColor;
    }

    /** Sets TeamColor */
    FORCEINLINE void SetTeamColor(const FColor& Color)
    {
        TeamColor = Color;
    }
};
