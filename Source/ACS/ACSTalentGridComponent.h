// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ACSBaseTalent.h"
#include "Components/ActorComponent.h"
#include "ACSTalentGridComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACS_API UACSTalentGridComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACSTalentGridComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TMap<FIntVector, TSubclassOf<UACSBaseTalent> > TalentGrid;

	UPROPERTY(VisibleAnywhere)
	TMap<FIntVector, TSubclassOf<UACSBaseTalent> > SlotGrid;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
