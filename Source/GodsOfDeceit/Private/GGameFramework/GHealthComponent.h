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


#pragma once

#include <memory>

#include <Components/ActorComponent.h>
#include <CoreTypes.h>
#include <Math/Vector.h>
#include <UObject/ObjectMacros.h>

#include "GDifficultyLevel/GDLV_float.h"

#include "GHealthComponent.generated.h"

UCLASS(ClassGroup=(GODSOFDECEIT), meta=(BlueprintSpawnableComponent))
class GODSOFDECEIT_API UGHealthComponent : public UActorComponent
{
    GENERATED_UCLASS_BODY()

private:
    struct Impl;
    struct ImplDeleter
    {
      void operator()(Impl* Pointer);
    };
    std::unique_ptr<Impl, ImplDeleter> Pimpl;
    ImplDeleter PimplDeleter;

public:
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthLevelChangedSignature, UGHealthComponent*, OwningHealthComponent, float, Health, float, HealthDelta, const UDamageType*, DamageType, AController*, InstigatedBy, AActor*, DamageCauser);

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlummetingBeginSignature, const float, Health);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlummetingUpdateSignature, const float, Health);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlummetingEndSignature, const float, Health);

public:
    FOnHealthLevelChangedSignature OnHealthLevelChanged;

    FOnPlummetingBeginSignature OnPlummetingBegin;
    FOnPlummetingUpdateSignature OnPlummetingUpdate;
    FOnPlummetingEndSignature OnPlummetingEnd;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health Component")
    float Health;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health Component")
    uint8 bHealthRegeneration : 1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health Component")
    FGDLV_float HealthRegenerationDelay;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health Component")
    FGDLV_float HealthRegenerationInterval;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health Component")
    FGDLV_float HealthRegenerationPerSecond;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health Component")
    FGDLV_float SafeFallingDistance;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health Component")
    FGDLV_float FallingDamagePerMeter;

protected:
    UFUNCTION (  )
    virtual void OnTakeAnyDamage(
            AActor* DamagedActor, float Damage, const UDamageType* DamageType,
            AController* InstigatedBy, AActor* DamageCauser);

    UFUNCTION (  )
    virtual void OnFallingBegin(const FVector& StartLocation);

    UFUNCTION (  )
    virtual void OnFallingUpdate(const FVector& StartLocation,
                                 const FVector& LocationDelta);

    UFUNCTION (  )
    virtual void OnFallingEnd(const FVector& StartLocation,
                              const FVector& EndLocation,
                              const FVector& LocationDelta);

    void OnHealthRegenerationTick();

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    virtual void TickComponent(
            float DeltaTime, ELevelTick TickType,
            FActorComponentTickFunction *ThisTickFunction) override;

public:
    FORCEINLINE float GetMaxHealth() const
    {
        return GetClass()->GetDefaultObject<UGHealthComponent>()->Health;
    }

    FORCEINLINE float GetHealth() const
    {
        return Health;
    }

    void SetHealth(const float Amount,
                   const UDamageType* DamageType = nullptr,
                   AController* InstigatedBy = nullptr,
                   AActor* DamageCauser = nullptr);

    void Damage(const float Amount,
                const UDamageType* DamageType,
                AController* InstigatedBy,
                AActor* DamageCauser);
    void Heal(const float Amount);

    FORCEINLINE bool IsAlive() const
    {
        return Health > 0.0f;
    }

    FORCEINLINE bool IsDead() const
    {
        return Health <= 0.0f;
    }
};
