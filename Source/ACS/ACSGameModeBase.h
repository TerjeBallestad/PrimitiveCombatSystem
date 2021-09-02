// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"
#include "GameFramework/GameModeBase.h"
#include "ACSGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ACS_API AACSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable *SpellData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable *CharacterData;
	
protected:
	virtual void BeginPlay() override;
};
