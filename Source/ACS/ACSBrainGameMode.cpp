// Fill out your copyright notice in the Description page of Project Settings.


#include "ACSBrainGameMode.h"

#include "ACSGameInstance.h"
#include "ACSTalentGridComponent.h"
#include "Kismet/GameplayStatics.h"


void AACSBrainGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options,ErrorMessage);

	CharacterToLoad = UGameplayStatics::ParseOption(Options, "CharacterName");

	if(CharacterToLoad.IsEmpty())
	{
		CharacterToLoad = "Player";
	}
	
}

void AACSBrainGameMode::BeginPlay()
{
	Super::BeginPlay();
	LoadTalentGrid(FName (CharacterToLoad));
	
}

void AACSBrainGameMode::LoadTalentGrid(FName name)
{
	auto GameInstance = Cast<UACSGameInstance>(GetGameInstance());

	auto Grid = GameInstance->CharacterGrids->FindRow<FTalentGridCharacter>(name, "")->Grid;

	auto CellSize = 501;
	
	for (auto Row : Grid)
	{
		auto XY = Row.Get<0>();
		auto Cell = Row.Get<1>();
		
		auto CellActor = GetWorld()->SpawnActor<AACSTalentGridCell>(TalentGridCellClass);
		CellActor->SetActorLocation(FVector( XY.X * CellSize, XY.Y * CellSize, 0));
		CellActor->Setup(Cell, *GameInstance->TalentData->FindRow<FTalentData>(Cell.TalentName, ""), XY, *GameInstance->SlotData->FindRow<FTalentSlotData>(Cell.SlotName, ""));
		
		
	}	
}
