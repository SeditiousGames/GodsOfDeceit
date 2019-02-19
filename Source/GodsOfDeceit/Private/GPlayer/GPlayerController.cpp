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

#include <GLog/GLog.h>

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
    GLOG_INPUT("Pause Pressed");
}

void AGPlayerController::OnInputAddCameraYaw(const float AxisValue)
{
    (void)AxisValue;

    GLOG_INPUT_LOG(GLOG_KEY_INPUT + 1, "Add Camera Yaw", AxisValue);
}

void AGPlayerController::OnInputAddCameraPitch(const float AxisValue)
{
    (void)AxisValue;

    GLOG_INPUT_LOG(GLOG_KEY_INPUT + 2, "Add Camera Pitch", AxisValue);
}

void AGPlayerController::OnInputMoveForward(const float AxisValue)
{
    (void)AxisValue;

    GLOG_INPUT_LOG(GLOG_KEY_INPUT + 3, "Move Forward", AxisValue);
}

void AGPlayerController::OnInputMoveRight(const float AxisValue)
{
    (void)AxisValue;

    GLOG_INPUT_LOG(GLOG_KEY_INPUT + 4, "Move Right", AxisValue);
}

void AGPlayerController::OnInputSprintPressed()
{
    GLOG_INPUT("Sprint Pressed");
}

void AGPlayerController::OnInputSprintReleased()
{
    GLOG_INPUT("Sprint Released");
}

void AGPlayerController::OnInputJumpPressed()
{
    GLOG_INPUT("Jump Pressed");
}

void AGPlayerController::OnInputJumpReleased()
{
    GLOG_INPUT("Jump Released");
}

void AGPlayerController::OnInputCrouchPressed()
{
    GLOG_INPUT("Crouch Pressed");
}

void AGPlayerController::OnInputCrouchReleased()
{
    GLOG_INPUT("Crouch Released");
}

void AGPlayerController::OnInputToggleCrouchPressed()
{
    GLOG_INPUT("Toggle Crouch Pressed");
}

void AGPlayerController::OnInputTogglePronePressed()
{
    GLOG_INPUT("Toggle Prone Pressed");
}

void AGPlayerController::OnInputZoomPressed()
{
    GLOG_INPUT("Zoom Pressed");
}

void AGPlayerController::OnInputZoomReleased()
{
    GLOG_INPUT("Zoom Released");
}

void AGPlayerController::OnInputFirePressed()
{
    GLOG_INPUT("Fire Pressed");
}

void AGPlayerController::OnInputFireReleased()
{
    GLOG_INPUT("Fire Released");
}

void AGPlayerController::OnInputMeleeAttackPressed()
{
    GLOG_INPUT("Melee Attack Pressed");
}

void AGPlayerController::OnInputMeleeAttackReleased()
{
    GLOG_INPUT("Melee Attack Released");
}

void AGPlayerController::OnInputFragmentationGrenadePressed()
{
    GLOG_INPUT("Fragmentation Grenade Pressed");
}

void AGPlayerController::OnInputFragmentationGrenadeReleased()
{
    GLOG_INPUT("Fragmentation Grenade Released");
}

void AGPlayerController::OnInputStunGrenadePressed()
{
    GLOG_INPUT("Stun Grenade Pressed");
}

void AGPlayerController::OnInputStunGrenadeReleased()
{
    GLOG_INPUT("Stun Grenade Released");
}

void AGPlayerController::OnInputSmokeGrenadePressed()
{
    GLOG_INPUT("SmokeGrenade Pressed");
}

void AGPlayerController::OnInputSmokeGrenadeReleased()
{
    GLOG_INPUT("Smoke Grenade Released");
}

void AGPlayerController::OnInputReloadWeaponPressed()
{
    GLOG_INPUT("Reload Weapon");
}

void AGPlayerController::OnInputSelectWeapon(const float AxisValue)
{
    (void)AxisValue;

    GLOG_INPUT_LOG(GLOG_KEY_INPUT + 5, "Select Weapon", AxisValue);
}

void AGPlayerController::OnInputSwitchWeaponPressed()
{
    GLOG_INPUT("Switch Weapon");
}

void AGPlayerController::OnInputSelectPrimaryWeaponPressed()
{
    GLOG_INPUT("Select Primary Weapon");
}

void AGPlayerController::OnInputSelectSecondaryWeaponPressed()
{
    GLOG_INPUT("Select Secondary Weapon");
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
                "AddCameraYaw",
                this,
                &AGPlayerController::OnInputAddCameraYaw);
    this->InputComponent->BindAxis(
                "AddCameraPitch",
                this,
                &AGPlayerController::OnInputAddCameraPitch);

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
                this, &AGPlayerController::OnInputReloadWeaponPressed);
    this->InputComponent->BindAxis(
                "SelectWeapon",
                this, &AGPlayerController::OnInputSelectWeapon);
    this->InputComponent->BindAction(
                "SwitchWeapon", EInputEvent::IE_Pressed,
                this, &AGPlayerController::OnInputSwitchWeaponPressed);
    this->InputComponent->BindAction(
                "SelectPrimaryWeapon", EInputEvent::IE_Pressed,
                this, &AGPlayerController::OnInputSelectPrimaryWeaponPressed);
    this->InputComponent->BindAction(
                "SelectSecondaryWeapon", EInputEvent::IE_Pressed,
                this, &AGPlayerController::OnInputSelectSecondaryWeaponPressed);
}
