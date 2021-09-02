// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <Actor.h>

#include "ACSGameModeBase.h"
#include "ACSTalentGridComponent.h"
#include "BTVector.h"
#include "ACSSpell.h"
#include "GameFramework/Character.h"
#include "ACSCharacter.generated.h"

USTRUCT()
struct FCharacterData: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> Spells;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FTimerHandle CastTimeHandle;


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

	UFUNCTION(BlueprintImplementableEvent)
	void SpellCastStart();

	UFUNCTION(BlueprintImplementableEvent)
	void SpellCastEnd();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FCharacterData CharacterData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FSpellData> Spells;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AACSCharacter *Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsCasting;

	void CastSpell();
	UFUNCTION()
	void LearnSpell(FName SpellName);

	UFUNCTION(BlueprintCallable)
	FSpellData GetSpellData(const FName SpellName) const;

	UFUNCTION(BlueprintCallable)
	void CastSpell(FName SpellName);

	UFUNCTION(BlueprintCallable)
	void ShootSpell(const FName SpellName);

	UPROPERTY(EditAnywhere)
	TSubclassOf<AACSSpell> SpellClass;

	UFUNCTION(BlueprintNativeEvent)
	void EnteringCombat(AACSCharacter *Enemy);

	UFUNCTION(BlueprintNativeEvent)
	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
