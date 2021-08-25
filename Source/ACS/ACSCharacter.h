// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ACSTalentGridComponent.h"
#include "BTVector.h"
#include "Spell.h"
#include "GameFramework/Character.h"
#include "ACSCharacter.generated.h"

USTRUCT()
struct FCharacterData: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Spells;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBTVector BaseType;
	
};

UCLASS()
class ACS_API AACSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AACSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UACSTalentGridComponent *TalentGridComponent;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(VisibleAnywhere)
	FCharacterData CharacterData;

	UPROPERTY(VisibleAnywhere)
	TArray<FSpellData> Spells;

	UFUNCTION()
	void ShootSpell();

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASpell> SpellClass;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
