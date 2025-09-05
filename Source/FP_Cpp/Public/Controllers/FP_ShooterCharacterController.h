// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FP_Controller.h"
#include "FP_ShooterCharacterController.generated.h"

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
	

private:
	void StartFireTriggerd ();
	void StopFireTriggerd();
	void SwitchWeapenTriggerd();
};
