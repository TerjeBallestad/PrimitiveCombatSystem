// Fill out your copyright notice in the Description page of Project Settings.


#include "ACSTalentGridCell.h"

#include "ACSBrainGameMode.h"
#include "ACSSaveGame.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AACSTalentGridCell::AACSTalentGridCell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AACSTalentGridCell::BeginPlay()
{
	Super::BeginPlay();
	
}

void AACSTalentGridCell::Setup_Implementation(FTalentGridCell InCellData, FTalentData InTalentData,
	FIntPoint InCoordinate, FTalentSlotData InSlotData)
{
	CellData = InCellData;
	TalentData = InTalentData;
	Coordinate = InCoordinate;
	SlotData = InSlotData;
}

void AACSTalentGridCell::SaveData(TMap<FIntPoint, FTalentGridCell> GridData )
{
	auto GameMode = Cast<AACSBrainGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	check(GameMode);
	GameMode->SaveTalentGrid(GridData);
}

TMap<FIntPoint, FTalentGridCell> AACSTalentGridCell::GetData()
{
	auto GameMode = Cast<AACSBrainGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	check(GameMode);
	return GameMode->LoadCurrentCharacterData().TalentGrid.Grid;
}

// Called every frame
void AACSTalentGridCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

