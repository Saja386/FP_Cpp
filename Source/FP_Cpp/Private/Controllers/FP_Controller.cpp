// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/FP_Controller.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "FP_CppCharacter.h"

AFP_Controller::AFP_Controller()
{
	bReplicates = true;
}

void AFP_Controller::BeginPlay()
{
	Super::BeginPlay();
	//Add Input Mapping Context
	check(PlayerMappingContext);
	UEnhancedInputLocalPlayerSubsystem* InputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (InputLocalPlayerSubsystem)
	{
		InputLocalPlayerSubsystem->AddMappingContext(PlayerMappingContext,0);
	}
}

void AFP_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(PlayerMoveAction, ETriggerEvent::Triggered , this , &AFP_Controller::Move);
		EnhancedInputComponent->BindAction(PlayerLookAction , ETriggerEvent::Triggered , this , &AFP_Controller::Look);
		EnhancedInputComponent->BindAction(PlayerJumpAction,ETriggerEvent::Triggered,this,&AFP_Controller::Jump);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AFP_Controller::Move(const FInputActionValue& MoveInputAction)
{FVector2D MovementVector = MoveInputAction.Get<FVector2D>();
	if(APawn* ControlledPawn = GetPawn())
	{
		Cast<AFP_CppCharacter>(ControlledPawn)->DoMove(MovementVector.X , MovementVector.Y);
	}
}

void AFP_Controller::Look(const FInputActionValue& MoveInputAction)
{
	FVector2D LookVector = MoveInputAction.Get<FVector2D>();
	if(APawn* ControlledPawn = GetPawn())
	{
		Cast<AFP_CppCharacter>(ControlledPawn)->DoAim(LookVector.X , LookVector.Y);
	}
}

void AFP_Controller::Jump(const FInputActionValue& JumpInputAction)
{
	if(APawn* ControlledPawn = GetPawn())
	{
		Cast<AFP_CppCharacter>(ControlledPawn)->Jump();
	}
}

void AFP_Controller::StopJump(const FInputActionValue& StopJumpInputAction)
{
	if(APawn* ControlledPawn = GetPawn())
	{
		Cast<AFP_CppCharacter>(ControlledPawn)->StopJumping();
	}
}
