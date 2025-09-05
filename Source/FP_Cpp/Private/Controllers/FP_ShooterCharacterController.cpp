// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/FP_ShooterCharacterController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "ShooterCharacter.h"

void AFP_ShooterCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Firing
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ThisClass::StartFireTriggerd);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &AFP_ShooterCharacterController::StopFireTriggerd);

		// Switch weapon
		EnhancedInputComponent->BindAction(SwitchWeaponAction, ETriggerEvent::Triggered, this, &ThisClass::SwitchWeapenTriggerd);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AFP_ShooterCharacterController::BeginPlay()
{
	Super::BeginPlay();
	//Add Input Mapping Context
	check(ShooterMappingContext);
	UEnhancedInputLocalPlayerSubsystem* InputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (InputLocalPlayerSubsystem)
	{
		InputLocalPlayerSubsystem->AddMappingContext(ShooterMappingContext,1);
	}
}

void AFP_ShooterCharacterController::StartFireTriggerd()
{
	if(APawn* ControlledPawn = GetPawn())
	{
		Cast<AShooterCharacter>(ControlledPawn)->DoStartFiring();
	}
}

void AFP_ShooterCharacterController::StopFireTriggerd()
{
	if(APawn* ControlledPawn = GetPawn())
	{
		Cast<AShooterCharacter>(ControlledPawn)->DoStopFiring();
	}
}

void AFP_ShooterCharacterController::SwitchWeapenTriggerd()
{
	if(APawn* ControlledPawn = GetPawn())
	{
		Cast<AShooterCharacter>(ControlledPawn)->DoSwitchWeapon();
	}
}
