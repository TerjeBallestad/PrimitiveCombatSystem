// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ACSPlayerController.generated.h"

/**
 * 
 */
DECLARE_DELEGATE_OneParam(FActionBarInput, const int32);

UCLASS()
class ACS_API AACSPlayerController : public APlayerController
{
	GENERATED_BODY()

	void BeginPlay() override;

protected:
	void MoveForward(float Value);

	void MoveRight(float Value);

	void Jump();
	void StopJumping();
	void AddControllerYawInput(float Value);
	void AddControllerPitchInput(float Value);
	

public:
	
	UFUNCTION()
	virtual void SetupInputComponent() override;

	UFUNCTION()
	void CastSpell(int32 Index);
	void MouseLeftClicked();
};
