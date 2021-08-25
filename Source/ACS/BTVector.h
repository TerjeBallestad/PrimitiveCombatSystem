// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTVector.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EBaseType : uint8
{
	N	UMETA(DisplayName = "None"),
	L	UMETA(DisplayName = "Light"),
	B	UMETA(DisplayName = "Blue"),
	D	UMETA(DisplayName = "Dark"),
	R	UMETA(DisplayName = "Red"),
	G   UMETA(DisplayName = "Green"),
	A	UMETA(DisplayName = "All"),
};

USTRUCT(BlueprintType)
struct FBTVector
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float L;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float B;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float D;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float R;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float G;

	FORCEINLINE FBTVector()
	{
		L = 0;
		B = 0;
		D = 0;
		R = 0;
		G = 0;
	};

	FORCEINLINE FBTVector(float InL, float InB, float InD, float InR, float InG) {
		L = InL;
		B = InB;
		D = InD;
		R = InR;
		G = InG;
	}

	FORCEINLINE FBTVector operator*(FBTVector vector) {
		return FBTVector(
			L*vector.L,
			D*vector.D,
			B*vector.B,
			R*vector.R,
			G*vector.G
		);
	}

	FORCEINLINE FBTVector operator-(FBTVector vector) {
		return FBTVector(
			L-vector.L,
			D-vector.D,
			B-vector.B,
			R-vector.R,
			G-vector.G
		);
	}

	FORCEINLINE FBTVector operator+=(FBTVector vector) {
		return FBTVector(
			L+=vector.L,
			D+=vector.D,
			B+=vector.B,
			R+=vector.R,
			G+=vector.G
		);
	}


	FORCEINLINE bool IsAnyBelowZero() {
		return L<= 0.0 || D<= 0.0 || B <= 0.0 || R<=0.0 || G <= 0.0;
	}

	FORCEINLINE float Sum() {
		return L + B + D + R + G;
	}
};
