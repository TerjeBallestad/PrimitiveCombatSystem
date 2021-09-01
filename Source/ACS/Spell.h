// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BillboardComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "Spell.generated.h"

USTRUCT()
struct FSpellData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D *Image;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CastTime;

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

	UFUNCTION()
	void Setup(AActor* actor, FSpellData data);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName SpellName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USphereComponent * Collider;

	UPROPERTY()
	AActor *SpellInstigator;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> DamageTypeClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 1;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem *ImpactParticles;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetSpellName(const FName Name){	SpellName = Name;	};

	UFUNCTION()
	FName GetSpellName() const {	return SpellName;	};
	
	UPROPERTY()
	UBillboardComponent *BillboardComponent;

	UPROPERTY(VisibleAnywhere)
	FSpellData SpellData;	
};
