// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "ACSGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ACS_API UACSGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable *SpellData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable *CharacterData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable *CharacterGrids;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable *TalentData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable *SlotData;
};