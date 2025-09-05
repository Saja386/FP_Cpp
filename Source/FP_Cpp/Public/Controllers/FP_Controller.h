// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FP_Controller.generated.h"


class UInputMappingContext ;
class UInputAction ;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class FP_CPP_API AFP_Controller : public APlayerController
{
	GENERATED_BODY()
public:
	AFP_Controller();
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	//Input Variables
	UPROPERTY(EditAnywhere , Category = "Input")
	TObjectPtr<UInputMappingContext> PlayerMappingContext;
	UPROPERTY(EditAnywhere , Category = "Input")
	TObjectPtr<UInputAction> PlayerMoveAction;
	UPROPERTY(EditAnywhere , Category = "Input")
	TObjectPtr<UInputAction> PlayerLookAction;
	UPROPERTY(EditAnywhere,  Category = "Input")
	TObjectPtr<UInputAction> PlayerJumpAction;
private:
	//Movement Function
	void Move (const FInputActionValue& MoveInputAction);
	void Look (const FInputActionValue& MoveInputAction);
	void Jump (const FInputActionValue& JumpInputAction);
	void StopJump (const FInputActionValue& StopJumpInputAction);


};
