// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ACSTalentGridComponent.h"
#include "GameFramework/Actor.h"
#include "ACSTalentGridCell.generated.h"

UCLASS()
class ACS_API AACSTalentGridCell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AACSTalentGridCell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintNativeEvent)
	void Setup(FTalentGridCell CellData, FTalentData TalentData, FIntPoint Coordinate, FTalentSlotData SlotData);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
