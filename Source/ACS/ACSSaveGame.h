// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ACSCharacter.h"
#include "GameFramework/SaveGame.h"
#include "ACSSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class ACS_API UACSSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TMap<FName, FCharacterData> Characters;

	static FCharacterData LoadCharacterData(FName name);
	static void SaveCharacterData(FName name, FCharacterData);
	static bool CharacterDataExists(FName name);
};
