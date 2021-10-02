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

	UPROPERTY(BlueprintReadWrite)
	FTalentGridCell CellData;

	UPROPERTY(BlueprintReadWrite)
	FTalentData TalentData;

	UPROPERTY(BlueprintReadWrite)
	FIntPoint Coordinate;

	UPROPERTY(BlueprintReadWrite)
	FTalentSlotData SlotData;

public:

	UFUNCTION(BlueprintNativeEvent)
	void Setup(FTalentGridCell InCellData, FTalentData InTalentData, FIntPoint InCoordinate, FTalentSlotData InSlotData);

	UFUNCTION(BlueprintCallable)
	void SaveData(TMap<FIntPoint, FTalentGridCell> GridData);

	UFUNCTION(BlueprintCallable)
	TMap<FIntPoint, FTalentGridCell> GetData();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
