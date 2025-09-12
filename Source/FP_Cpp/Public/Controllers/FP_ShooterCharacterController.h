// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FP_Controller.h"
#include "FP_ShooterCharacterController.generated.h"

class UShooterBulletCounterUI;
class AShooterCharacter;
class UShooterBulletCounterUI;

/**
 * 
 */
UCLASS()
class FP_CPP_API AFP_ShooterCharacterController : public AFP_Controller
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere , Category = "Input")
	TObjectPtr<UInputMappingContext> ShooterMappingContext;
	
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* FireAction;
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* SwitchWeaponAction;

	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	//Shooter character
	UPROPERTY(EditAnywhere, Category="Shooter|Respawn")
	TSubclassOf<AShooterCharacter> CharacterClass;
	
	UPROPERTY(EditAnywhere, Category="Shooter|UI")
	TSubclassOf<UShooterBulletCounterUI> BulletCounterUIClass;

	UPROPERTY(EditAnywhere, Category="Shooter|Player")
	FName PlayerPawnTag = FName("Player");

	UPROPERTY()
	TObjectPtr<UShooterBulletCounterUI> BulletCounterUI;
	
	UFUNCTION()
	void OnPawnDestroyed(AActor* DestroyedActor);

	/** Called when the bullet count on the possessed pawn is updated */
	UFUNCTION()
	void OnBulletCountUpdated(int32 MagazineSize, int32 Bullets);

	/** Called when the possessed pawn is damaged */
	UFUNCTION()
	void OnPawnDamaged(float LifePercent);
private:
	void StartFireTriggerd ();
	void StopFireTriggerd();
	void SwitchWeapenTriggerd();
};
