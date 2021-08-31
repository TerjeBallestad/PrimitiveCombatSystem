// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ACSGameModeBase.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool InCombat = false;

	UPROPERTY()
	AACSGameModeBase * GameMode;

	//Stats
	UPROPERTY(EditAnywhere)
	TMap<ECharacterStat, float> Stats;
	
	UPROPERTY(VisibleAnywhere)
	float MaxHealth;

	UPROPERTY(VisibleAnywhere)
	float CurrentHealth;
	
	UPROPERTY(VisibleAnywhere)
	float Endurance; // Light, +health
	
	UPROPERTY(VisibleAnywhere)
	float Intellect; // Blue, +critical chance

	UPROPERTY(VisibleAnywhere)
	float Power; // Dark, +damage

	UPROPERTY(VisibleAnywhere)
	float Wit; // Red, +cast speed

	UPROPERTY(VisibleAnywhere)
	float Haste; // Red, +projectile speed

	UPROPERTY(VisibleAnywhere)
	float Wisdom; // Green, -spell cost

	UPROPERTY(VisibleAnywhere)
	float Harmony; // Green, +armor

	UPROPERTY(VisibleAnywhere)
	float Accuracy; // Green/Blue, +hit chance

	UPROPERTY(VisibleAnywhere)
	float Creativity; // Red/Blue, +energy generation

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetCurrentHealth(float NewAmount);

	UFUNCTION(BlueprintCallable)
	void AddCurrentHealth(float Amount);

	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() const;

	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(float NewAmount);

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthBar();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FCharacterData CharacterData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FSpellData> Spells;

	UFUNCTION()
	void LearnSpell(FString SpellName);

	UFUNCTION(BlueprintNativeEvent)
	void CastSpell(int32 SpellIndex);

	UFUNCTION(BlueprintCallable)
	void ShootSpell(FString SpellName, FSpellData SpellData);

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASpell> SpellClass;

	UFUNCTION(BlueprintNativeEvent)
	void EnteringCombat(AActor *Enemy);

	UFUNCTION(BlueprintNativeEvent)
	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
