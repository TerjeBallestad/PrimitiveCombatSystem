// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BTVector.h"
#include "GameFramework/DamageType.h"
#include "ACSDamage.generated.h"



/**
 * 
 */
UCLASS()
class ACS_API UACSDamage : public UDamageType
{
	GENERATED_BODY()


public:
	FBTVector Type;
};
