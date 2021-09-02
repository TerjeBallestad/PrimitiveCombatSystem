// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ACSTalentGridCell.h"
#include "GameFramework/GameModeBase.h"
#include "ACSBrainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ACS_API AACSBrainGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	void LoadTalentGrid(FName name);

	virtual  void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

private:
	UPROPERTY()
	FString CharacterToLoad;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AACSTalentGridCell> TalentGridCellClass;
};
