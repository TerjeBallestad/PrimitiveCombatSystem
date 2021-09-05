// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ACSCharacter.h"
#include "ACSTalentGridCell.h"
#include "Components/SpotLightComponent.h"
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
	UFUNCTION(BlueprintCallable)
	void LoadTalentGrid(FName name);

	UFUNCTION(BlueprintCallable)
	FCharacterData LoadCurrentCharacterData();
	
	UFUNCTION(BlueprintCallable)
	void SaveTalentGrid(TMap<FIntPoint, FTalentGridCell> GridData);

	virtual  void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	void SetupSpotlight(AACSCharacter* Character);

	UPROPERTY(EditAnywhere)
	TSubclassOf<AACSCharacter> NPCClass;

private:
	UPROPERTY()
	FName CharacterToLoad;

	UPROPERTY()
	FVector GridOrigin;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AACSTalentGridCell> TalentGridCellClass;
};
