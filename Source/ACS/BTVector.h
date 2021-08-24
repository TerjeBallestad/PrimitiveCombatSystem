// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTVector.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FBTVector
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float l;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float b;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float d;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float r;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float g;

	FORCEINLINE FBTVector(){};

	FORCEINLINE FBTVector(float InL, float InB, float InD, float InR, float InG) {
		l = InL;
		b = InB;
		d = InD;
		r = InR;
		g = InG;
	}

	FORCEINLINE FBTVector operator*(FBTVector vector) {
		return FBTVector(
			l*vector.l,
			d*vector.d,
			b*vector.b,
			r*vector.r,
			g*vector.g
		);
	}

	FORCEINLINE FBTVector operator-(FBTVector vector) {
		return FBTVector(
			l-vector.l,
			d-vector.d,
			b-vector.b,
			r-vector.r,
			g-vector.g
		);
	}

	FORCEINLINE FBTVector operator+=(FBTVector vector) {
		return FBTVector(
			l+=vector.l,
			d+=vector.d,
			b+=vector.b,
			r+=vector.r,
			g+=vector.g
		);
	}


	FORCEINLINE bool IsAnyBelowZero() {
		return l<= 0.0 || d<= 0.0 || b <= 0.0 || r<=0.0 || g <= 0.0;
	}

	FORCEINLINE float Sum() {
		return l + b + d + r + g;
	}
};
