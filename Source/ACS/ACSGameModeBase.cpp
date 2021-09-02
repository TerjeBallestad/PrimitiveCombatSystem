// Copyright Epic Games, Inc. All Rights Reserved.


#include "ACSGameModeBase.h"

#include "ACSSaveGame.h"
#include "Kismet/GameplayStatics.h"

void AACSGameModeBase::BeginPlay()
{
	Super::BeginPlay();


	FCharacterData test;
	test.Spells.Add("test");
	test.MaxHealth = 1337;	
	UACSSaveGame::SaveCharacterData("Test", test);

	auto data = UACSSaveGame::LoadCharacterData("Test");

	
	
}
