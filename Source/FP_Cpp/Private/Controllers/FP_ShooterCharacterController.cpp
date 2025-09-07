// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/FP_ShooterCharacterController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "FP_Cpp.h"
#include "ShooterCharacter.h"
#include "Blueprint/UserWidget.h"
#include "ShooterBulletCounterUI.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"


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
	//Add The Bullet Counter Widget
	if (IsLocalPlayerController())
	{
		BulletCounterUI = CreateWidget<UShooterBulletCounterUI>(this, BulletCounterUIClass);
		if (BulletCounterUI)
		{
			BulletCounterUI->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogFP_Cpp, Error, TEXT("Could not spawn bullet counter widget."));
		}
	}
	
	//Add Input Mapping Context
	check(ShooterMappingContext);
	UEnhancedInputLocalPlayerSubsystem* InputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (InputLocalPlayerSubsystem)
	{
		InputLocalPlayerSubsystem->AddMappingContext(ShooterMappingContext , 0);
	}
}

void AFP_ShooterCharacterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	// subscribe to the pawn's OnDestroyed delegate
	InPawn->OnDestroyed.AddDynamic(this, &AFP_ShooterCharacterController::OnPawnDestroyed);

	// is this a shooter character?
	if (AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(InPawn))
	{
		// add the player tag
		ShooterCharacter->Tags.Add(PlayerPawnTag);

		// subscribe to the pawn's delegates
		ShooterCharacter->OnBulletCountUpdated.AddDynamic(this, &AFP_ShooterCharacterController::OnBulletCountUpdated);
		ShooterCharacter->OnDamaged.AddDynamic(this, &AFP_ShooterCharacterController::OnPawnDamaged);

		// force update the life bar
		ShooterCharacter->OnDamaged.Broadcast(1.0f);
	}
}

void AFP_ShooterCharacterController::OnPawnDestroyed(AActor* DestroyedActor)
{
	// reset the bullet counter HUD
	BulletCounterUI->BP_UpdateBulletCounter(0, 0);

	// find the player start
	TArray<AActor*> ActorList;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), ActorList);

	if (ActorList.Num() > 0)
	{
		// select a random player start
		AActor* RandomPlayerStart = ActorList[FMath::RandRange(0, ActorList.Num() - 1)];

		// spawn a character at the player start
		const FTransform SpawnTransform = RandomPlayerStart->GetActorTransform();

		if (AShooterCharacter* RespawnedCharacter = GetWorld()->SpawnActor<AShooterCharacter>(CharacterClass, SpawnTransform))
		{
			// possess the character
			Possess(RespawnedCharacter);
		}
	}
}

void AFP_ShooterCharacterController::OnBulletCountUpdated(int32 MagazineSize, int32 Bullets)
{if (BulletCounterUI)
{
	BulletCounterUI->BP_UpdateBulletCounter(MagazineSize, Bullets);
}
}

void AFP_ShooterCharacterController::OnPawnDamaged(float LifePercent)
{if (IsValid(BulletCounterUI))
{
	BulletCounterUI->BP_Damaged(LifePercent);
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
