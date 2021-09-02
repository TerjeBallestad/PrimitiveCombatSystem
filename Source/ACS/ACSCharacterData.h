// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ACSCharacter.h"
#include "Engine/DataAsset.h"
#include "ACSCharacterData.generated.h"

/**
 * 
 */
UCLASS()
class ACS_API UACSCharacterData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TMap<FName, FCharacterData> Characters;
	
};
