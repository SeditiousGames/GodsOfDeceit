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
 * A health component which manages damage and healing.
 */


#include "GGameFramework/GHealthComponent.h"
#include "GodsOfDeceit.h"

#include <utility>

#include <Async/Async.h>
#include <Engine/EngineTypes.h>
#include <GameFramework/Actor.h>

struct UGHealthComponent::Impl
{
public:
    FTimerHandle HealthRegenerationTimer;
    bool bPlummetingStarted;

private:
    UGHealthComponent* Owner;

public:
    explicit Impl(UGHealthComponent* InOwner);
    ~Impl();

public:
    void UpdateFallingDamage(const FVector& DeltaLocation);
};

UGHealthComponent::UGHealthComponent(
        const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    PrimaryComponentTick.bCanEverTick = true;

    SetCanEverAffectNavigation(false);

    Health = 100.0f;
    bHealthRegeneration = false;

    AsyncTask(ENamedThreads::GameThread, [&]()
    {
        HealthRegenerationDelay.Initialize(this);
        HealthRegenerationDelay.Recruit = 5.0f;
        HealthRegenerationDelay.Regular = 5.0f;
        HealthRegenerationDelay.Hardened = 5.0f;
        HealthRegenerationDelay.Veteran = 5.0f;

        HealthRegenerationInterval.Initialize(this);
        HealthRegenerationInterval.Recruit = 0.1f;
        HealthRegenerationInterval.Regular = 0.1f;
        HealthRegenerationInterval.Hardened = 0.1f;
        HealthRegenerationInterval.Veteran = 0.1f;

        HealthRegenerationPerSecond.Initialize(this);
        HealthRegenerationPerSecond.Recruit = 5.0f;
        HealthRegenerationPerSecond.Regular = 5.0f;
        HealthRegenerationPerSecond.Hardened = 5.0f;
        HealthRegenerationPerSecond.Veteran = 5.0f;

        SafeFallingDistance.Initialize(this);
        SafeFallingDistance.Recruit = 300.0f;
        SafeFallingDistance.Regular = 300.0f;
        SafeFallingDistance.Hardened = 300.0f;
        SafeFallingDistance.Veteran = 300.0f;

        FallingDamagePerMeter.Initialize(this);
        FallingDamagePerMeter.Recruit = 30.0f;
        FallingDamagePerMeter.Regular = 30.0f;
        FallingDamagePerMeter.Hardened = 30.0f;
        FallingDamagePerMeter.Veteran = 30.0f;
    });
}

void UGHealthComponent::OnTakeAnyDamage(
        AActor* DamagedActor, float Damage, const UDamageType* DamageType,
        AController* InstigatedBy, AActor* DamageCauser)
{

}

void UGHealthComponent::OnFallingBegin(const FVector& StartLocation)
{

}

void UGHealthComponent::OnFallingUpdate(const FVector& StartLocation,
                                        const FVector& LocationDelta)
{

}

void UGHealthComponent::OnFallingEnd(const FVector& StartLocation,
                                     const FVector& EndLocation,
                                     const FVector& LocationDelta)
{

}

void UGHealthComponent::OnHealthRegenerationTick()
{

}


void UGHealthComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UGHealthComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
}

void UGHealthComponent::TickComponent(
        float DeltaTime, ELevelTick TickType,
        FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGHealthComponent::SetHealth(const float Amount,
                                  const UDamageType* DamageType,
                                  AController* InstigatedBy,
                                  AActor* DamageCauser)
{

}

void UGHealthComponent::Damage(const float Amount,
                               const UDamageType* DamageType,
                               AController* InstigatedBy,
                               AActor* DamageCauser)
{

}

void UGHealthComponent::Heal(const float Amount)
{

}

UGHealthComponent::Impl::Impl(UGHealthComponent* InOwner)
    : bPlummetingStarted(false),
      Owner(InOwner)
{

}

UGHealthComponent::Impl::~Impl() = default;

void UGHealthComponent::Impl::UpdateFallingDamage(const FVector& DeltaLocation)
{

}

void UGHealthComponent::ImplDeleter::operator()(
        UGHealthComponent::Impl* Pointer)
{
    delete Pointer;
}
