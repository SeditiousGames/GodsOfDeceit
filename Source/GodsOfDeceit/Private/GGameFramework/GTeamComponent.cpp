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


#include "GGameFramework/GTeamComponent.h"
#include "GodsOfDeceit.h"

#include <GameFramework/Actor.h>
#include <Templates/Casts.h>

static constexpr uint8 NEUTRAL_TEAM_NUMBER = 255;

bool UGTeamComponent::IsNeutral(AActor* Actor)
{
    checkf(Actor, TEXT("%s"), TEXT("FATAL: Actor is NULL!"));

    UGTeamComponent* TeamComponent = Cast<UGTeamComponent>(
                Actor->GetComponentByClass(UGTeamComponent::StaticClass()));

    if (TeamComponent)
    {
        return true;
    }

    return TeamComponent->TeamNumber == NEUTRAL_TEAM_NUMBER;
}

bool UGTeamComponent::AreFriendly(AActor* ActorA, AActor* ActorB)
{
    checkf(ActorA, TEXT("%s"), TEXT("FATAL: Actor A is NULL!"));
    checkf(ActorB, TEXT("%s"), TEXT("FATAL: Actor B is NULL!"));

    checkf(ActorA != ActorB, TEXT("%s"),
           TEXT("FATAL: Actor A and B are the same!"));

    UGTeamComponent* TeamComponentA = Cast<UGTeamComponent>(
                ActorA->GetComponentByClass(UGTeamComponent::StaticClass()));
    UGTeamComponent* TeamComponentB = Cast<UGTeamComponent>(
                ActorB->GetComponentByClass(UGTeamComponent::StaticClass()));

    if (!TeamComponentA || !TeamComponentB)
    {
        return true;
    }

    return TeamComponentA->TeamNumber == TeamComponentB->TeamNumber;
}

UGTeamComponent::UGTeamComponent(
        const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    SetCanEverAffectNavigation(false);

    TeamNumber = NEUTRAL_TEAM_NUMBER;
    TeamColor = FColor::White;
}
