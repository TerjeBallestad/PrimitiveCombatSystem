// Fill out your copyright notice in the Description page of Project Settings.


#include "ACSSaveGame.h"

#include "Kismet/GameplayStatics.h"

UACSSaveGame *GetCharacterDatabase()
{
	if (UGameplayStatics::DoesSaveGameExist("Characters", 0))
	{
		return Cast<UACSSaveGame>(UGameplayStatics::LoadGameFromSlot("Characters", 0));
	}
	
	return Cast<UACSSaveGame> (UGameplayStatics::CreateSaveGameObject(UACSSaveGame::StaticClass()));
}

void SaveCharacterDatabase(UACSSaveGame *SaveGame)
{
	UGameplayStatics::SaveGameToSlot(SaveGame, "Characters", 0);	
}

FCharacterData UACSSaveGame::LoadCharacterData(FName key)
{
	auto SaveGame = GetCharacterDatabase();

	return SaveGame->Characters[key];
}

void UACSSaveGame::SaveCharacterData(FName key, FCharacterData val)
{
	auto SaveGame = GetCharacterDatabase();

	SaveGame->Characters.Add(key, val);

	SaveCharacterDatabase(SaveGame);
}

bool UACSSaveGame::CharacterDataExists(FName name)
{
	auto SaveGame = GetCharacterDatabase();

	return SaveGame->Characters.Contains(name);
}

void UACSSaveGame::SaveCharacterTalentGridCell(FName Name, FIntPoint Coordinate, FTalentGridCell CellData)
{
	auto GameSave = GetCharacterDatabase();
	auto CharacterData=  GameSave->Characters;
	CharacterData[Name].TalentGrid.Grid[Coordinate] = CellData;

	SaveCharacterDatabase(GameSave);
}


