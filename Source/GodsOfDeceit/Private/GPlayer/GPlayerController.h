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
 * Base class for all Gods of Deceit player controllers.
 */


#pragma once

#include <GameFramework/PlayerController.h>
#include <UObject/ObjectMacros.h>

#include "GPlayerController.generated.h"

UCLASS(Abstract, BlueprintType, config=Game)
class GODSOFDECEIT_API AGPlayerController : public APlayerController
{
    GENERATED_UCLASS_BODY()

protected:
    virtual void BeginPlay() override;

    virtual void OnPossess(APawn* aPawn) override;
    virtual void OnUnPossess() override;

    void OnInputPausePressed();

    void OnInputAddCameraYaw(const float AxisValue);
    void OnInputAddCameraPitch(const float AxisValue);
    void OnInputMoveForward(const float AxisValue);
    void OnInputMoveRight(const float AxisValue);

    void OnInputSprintPressed();
    void OnInputSprintReleased();
    void OnInputJumpPressed();
    void OnInputJumpReleased();
    void OnInputCrouchPressed();
    void OnInputCrouchReleased();
    void OnInputToggleCrouchPressed();
    void OnInputTogglePronePressed();

    void OnInputZoomPressed();
    void OnInputZoomReleased();
\
    void OnInputFirePressed();
    void OnInputFireReleased();

    void OnInputMeleeAttackPressed();
    void OnInputMeleeAttackReleased();

    void OnInputFragmentationGrenadePressed();
    void OnInputFragmentationGrenadeReleased();
    void OnInputStunGrenadePressed();
    void OnInputStunGrenadeReleased();
    void OnInputSmokeGrenadePressed();
    void OnInputSmokeGrenadeReleased();

    void OnInputReloadWeaponPressed();
    void OnInputSelectWeapon(const float AxisValue);
    void OnInputSwitchWeaponPressed();
    void OnInputSelectPrimaryWeaponPressed();
    void OnInputSelectSecondaryWeaponPressed();

protected:
    virtual void SetupInputComponent() override;
};
