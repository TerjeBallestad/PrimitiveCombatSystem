// Fill out your copyright notice in the Description page of Project Settings.


#include "ACSTalentGridCell.h"

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

void AACSTalentGridCell::Setup_Implementation(FTalentGridCell CellData, FTalentData TalentData,
	FIntPoint Coordinate, FTalentSlotData SlotData)
{
	
}

// Called every frame
void AACSTalentGridCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

