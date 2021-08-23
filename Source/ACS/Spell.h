// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "Spell.generated.h"

USTRUCT()
struct FSpellData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TAssetPtr<UTexture2D> Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Light;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Blue;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Dark;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Red;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Green;
	
};

UCLASS()
class ACS_API ASpell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	UTexture2D *Icon;

};
