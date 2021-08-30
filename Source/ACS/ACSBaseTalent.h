// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BTVector.h"
#include "Engine/DataTable.h"

#include "ACSBaseTalent.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FTalentData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D *Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Rank;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBaseType North;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBaseType East;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBaseType South;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBaseType West;
};

UCLASS()
class ACS_API UACSBaseTalent : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	FTalentData Data;
	
};
