// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BTVector.h"
#include "Engine/DataTable.h"

#include "ACSBaseTalent.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ECharacterStat : uint8
{
	Endurance	UMETA(DisplayName = "Light, +health"),
	Intellect	UMETA(DisplayName = "Blue, +critical chance"),
	Power		UMETA(DisplayName = "Dark, +damage"),
	Wit			UMETA(DisplayName = "Red, +cast speed"),
	Haste		UMETA(DisplayName = "Red, +projectile speed"),
	Wisdom		UMETA(DisplayName = "Green, -spell cost"),
	Harmony		UMETA(DisplayName = "Green, +armor"),
	Accuracy	UMETA(DisplayName = "Green/Blue, +hit chance"),
	Creativity	UMETA(DisplayName = "Red/Blue, +energy generation"),
};

USTRUCT(BlueprintType)
struct FTalentSlotData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBaseType North;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBaseType East;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBaseType South;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBaseType West;
};

USTRUCT(BlueprintType)
struct FTalentData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D *Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<ECharacterStat, float> Stats;

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
