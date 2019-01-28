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
 * A player character implementation for Gods of Deceit
 */


#pragma once

#include <GGameFramework/GCharacter.h>
#include <UObject/ObjectMacros.h>

#include "GPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS(BlueprintType, config=Game)
class GODSOFDECEIT_API AGPlayerCharacter : public ACharacter
{
    GENERATED_UCLASS_BODY()

protected:
    /** Camera boom which positions the third-person camera behind the character */
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* ThirdPersonCameraBoom;

    /** Third-person camera */
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    UCameraComponent* ThirdPersonCamera;

    /** First-person camera */
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    UCameraComponent* FirstPersonCamera;

public:
    /** Returns ThirdPersonCameraBoom component */
    FORCEINLINE const USpringArmComponent* GetThirdPersonCameraBoom() const
    {
        return ThirdPersonCameraBoom;
    }

    /** Returns ThirdPersonCamera component */
    FORCEINLINE const UCameraComponent* GetThirdPersonCamera() const
    {
        return ThirdPersonCamera;
    }

    /** Returns FirstPersonCamera component */
    FORCEINLINE const UCameraComponent* GetFirstPersonCamera() const
    {
        return FirstPersonCamera;
    }
};
