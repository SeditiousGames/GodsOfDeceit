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


#include "GPlayer/GPlayerController.h"
#include "GodsOfDeceit.h"

#include <Engine/EngineBaseTypes.h>

AGPlayerController::AGPlayerController(
        const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}

void AGPlayerController::BeginPlay()
{
    Super::BeginPlay();
}

void AGPlayerController::OnPossess(APawn* aPawn)
{
    Super::OnPossess(aPawn);
}

void AGPlayerController::OnUnPossess()
{
    Super::OnUnPossess();
}

void AGPlayerController::OnInputPausePressed()
{

}

void AGPlayerController::OnInputMoveForward(const float AxisValue)
{
    (void)AxisValue;
}

void AGPlayerController::OnInputMoveRight(const float AxisValue)
{
    (void)AxisValue;
}

void AGPlayerController::OnInputCameraYaw(const float AxisValue)
{
    (void)AxisValue;
}

void AGPlayerController::OnInputCameraPitch(const float AxisValue)
{
    (void)AxisValue;
}

void AGPlayerController::OnInputSprintPressed()
{

}

void AGPlayerController::OnInputSprintReleased()
{

}

void AGPlayerController::OnInputJumpPressed()
{

}

void AGPlayerController::OnInputJumpReleased()
{

}

void AGPlayerController::OnInputCrouchPressed()
{

}

void AGPlayerController::OnInputCrouchReleased()
{

}

void AGPlayerController::OnInputToggleCrouchPressed()
{

}

void AGPlayerController::OnInputTogglePronePressed()
{

}

void AGPlayerController::OnInputZoomPressed()
{

}

void AGPlayerController::OnInputZoomReleased()
{

}

void AGPlayerController::OnInputFirePressed()
{

}

void AGPlayerController::OnInputFireReleased()
{

}

void AGPlayerController::OnInputMeleeAttackPressed()
{

}

void AGPlayerController::OnInputMeleeAttackReleased()
{

}

void AGPlayerController::OnInputFragmentationGrenadePressed()
{

}

void AGPlayerController::OnInputFragmentationGrenadeReleased()
{

}

void AGPlayerController::OnInputStunGrenadePressed()
{

}

void AGPlayerController::OnInputStunGrenadeReleased()
{

}

void AGPlayerController::OnInputSmokeGrenadePressed()
{

}

void AGPlayerController::OnInputSmokeGrenadeReleased()
{

}

void AGPlayerController::OnInputReloadWeapon()
{

}

void AGPlayerController::OnInputSelectWeapon(const float AxisValue)
{
    (void)AxisValue;
}

void AGPlayerController::OnInputSwitchWeapon()
{

}

void AGPlayerController::OnInputSelectPrimaryWeapon()
{

}

void AGPlayerController::OnInputSelectSecondaryWeapon()
{

}

void AGPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    checkf(InputComponent, TEXT("FATAL: the input component has not been"
                                " initialized!"));

    this->InputComponent->BindAction(
                "Pause", EInputEvent::IE_Pressed,
                this, &AGPlayerController::OnInputPausePressed);

    this->InputComponent->BindAxis(
                "CameraYaw",
                this,
                &AGPlayerController::OnInputCameraYaw);
    this->InputComponent->BindAxis(
                "CameraPitch",
                this,
                &AGPlayerController::OnInputCameraPitch);

    this->InputComponent->BindAxis(
                "MoveForward",
                this,
                &AGPlayerController::OnInputMoveForward);
    this->InputComponent->BindAxis(
                "MoveRight",
                this,
                &AGPlayerController::OnInputMoveRight);

    this->InputComponent->BindAction(
                "Sprint", EInputEvent::IE_Pressed,
                this, &AGPlayerController::OnInputSprintPressed);
    this->InputComponent->BindAction(
                "Sprint", EInputEvent::IE_Released,
                this, &AGPlayerController::OnInputSprintReleased);
    this->InputComponent->BindAction(
                "Jump", EInputEvent::IE_Pressed,
                this, &AGPlayerController::OnInputJumpPressed);
    this->InputComponent->BindAction(
                "Jump", EInputEvent::IE_Released,
                this, &AGPlayerController::OnInputJumpReleased);
    this->InputComponent->BindAction(
                "Crouch", EInputEvent::IE_Pressed,
                this, &AGPlayerController::OnInputCrouchPressed);
    this->InputComponent->BindAction(
                "Crouch", EInputEvent::IE_Released,
                this, &AGPlayerController::OnInputCrouchReleased);
    this->InputComponent->BindAction(
                "ToggleCrouch", EInputEvent::IE_Pressed,
                this, &AGPlayerController::OnInputToggleCrouchPressed);
    this->InputComponent->BindAction(
                "ToggleProne", EInputEvent::IE_Pressed,
                this, &AGPlayerController::OnInputTogglePronePressed);

    this->InputComponent->BindAction(
                "Zoom", EInputEvent::IE_Pressed,
                this, &AGPlayerController::OnInputZoomPressed);
    this->InputComponent->BindAction(
                "Zoom", EInputEvent::IE_Released,
                this, &AGPlayerController::OnInputZoomReleased);

    this->InputComponent->BindAction(
                "Fire", EInputEvent::IE_Pressed,
                this, &AGPlayerController::OnInputFirePressed);
    this->InputComponent->BindAction(
                "Fire", EInputEvent::IE_Released,
                this, &AGPlayerController::OnInputFireReleased);

    this->InputComponent->BindAction(
                "MeleeAttack", EInputEvent::IE_Pressed,
                this, &AGPlayerController::OnInputMeleeAttackPressed);
    this->InputComponent->BindAction(
                "MeleeAttack", EInputEvent::IE_Released,
                this, &AGPlayerController::OnInputMeleeAttackReleased);

    this->InputComponent->BindAction(
                "FragmentationGrenade", EInputEvent::IE_Pressed,
                this, &AGPlayerController::OnInputFragmentationGrenadePressed);
    this->InputComponent->BindAction(
                "FragmentationGrenade", EInputEvent::IE_Released,
                this, &AGPlayerController::OnInputFragmentationGrenadeReleased);
    this->InputComponent->BindAction(
                "StunGrenade", EInputEvent::IE_Pressed,
                this, &AGPlayerController::OnInputStunGrenadePressed);
    this->InputComponent->BindAction(
                "StunGrenade", EInputEvent::IE_Released,
                this, &AGPlayerController::OnInputStunGrenadeReleased);
    this->InputComponent->BindAction(
                "SmokeGrenade", EInputEvent::IE_Pressed,
                this, &AGPlayerController::OnInputSmokeGrenadePressed);
    this->InputComponent->BindAction(
                "SmokeGrenade", EInputEvent::IE_Released,
                this, &AGPlayerController::OnInputSmokeGrenadeReleased);

    this->InputComponent->BindAction(
                "ReloadWeapon", EInputEvent::IE_Pressed,
                this, &AGPlayerController::OnInputReloadWeapon);
    this->InputComponent->BindAxis(
                "SelectWeapon",
                this, &AGPlayerController::OnInputSelectWeapon);
    this->InputComponent->BindAction(
                "SwitchWeapon", EInputEvent::IE_Pressed,
                this, &AGPlayerController::OnInputSwitchWeapon);
    this->InputComponent->BindAction(
                "SelectPrimaryWeapon", EInputEvent::IE_Pressed,
                this, &AGPlayerController::OnInputSelectPrimaryWeapon);
    this->InputComponent->BindAction(
                "SelectSecondaryWeapon", EInputEvent::IE_Pressed,
                this, &AGPlayerController::OnInputSelectSecondaryWeapon);
}
