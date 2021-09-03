// Fill out your copyright notice in the Description page of Project Settings.


#include "ACSBrainGameMode.h"

#include "ACSGameInstance.h"
#include "ACSTalentGridComponent.h"
#include "Kismet/GameplayStatics.h"


void AACSBrainGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options,ErrorMessage);

	CharacterToLoad = UGameplayStatics::ParseOption(Options, "CharacterName");

	UE_LOG(LogTemp, Warning, TEXT("Loading Character: %s"), *CharacterToLoad)

	if(CharacterToLoad.IsEmpty())
	{
		CharacterToLoad = "Player";
	}
}

void AACSBrainGameMode::BeginPlay()
{
	Super::BeginPlay();
	LoadTalentGrid(FName (CharacterToLoad));
	
	auto Character = GetWorld()->SpawnActor<AACSCharacter>(NPCClass, GridOrigin + FVector(100, 0, 200), FRotator());
	
	auto Spotlight = NewObject<USpotLightComponent>(Character, "Spotlight");
	Spotlight->SetupAttachment(Character->GetRootComponent());
	Spotlight->RegisterComponent();
	 


	if(IsValid(Character))
	{
		Character->Setup(FName(CharacterToLoad));
	}
	GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorLocation(GridOrigin + FVector(-100, 0, 200));

	
}

void AACSBrainGameMode::LoadTalentGrid(FName name)
{
	auto GameInstance = Cast<UACSGameInstance>(GetGameInstance());

	auto Grid = GameInstance->CharacterGrids->FindRow<FTalentGridCharacter>(name, "")->Grid;

	auto CellSize = 501;
	int CollumnCount = 0;
	int RowCount = 0;
	
	for (auto Row : Grid)
	{
		auto XY = Row.Get<0>();
		auto Cell = Row.Get<1>();
		CollumnCount = FMath::Max(XY.X, CollumnCount);
		RowCount = FMath::Max(XY.Y, RowCount);
		auto CellActor = GetWorld()->SpawnActor<AACSTalentGridCell>(TalentGridCellClass);
		CellActor->SetActorLocation(FVector( XY.X * CellSize, XY.Y * CellSize, 0));
		CellActor->Setup(Cell, *GameInstance->TalentData->FindRow<FTalentData>(Cell.TalentName, ""), XY, *GameInstance->SlotData->FindRow<FTalentSlotData>(Cell.SlotName, ""));
	}

	GridOrigin = FVector(CollumnCount * CellSize / 2, RowCount * CellSize / 2, 0);
}
