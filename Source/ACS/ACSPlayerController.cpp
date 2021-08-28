// Fill out your copyright notice in the Description page of Project Settings.


#include "ACSPlayerController.h"

#include "ACSCharacter.h"
#include "ACSNonePlayerController.h"
#include "Kismet/KismetMathLibrary.h"


void AACSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetShowMouseCursor(true);
}

void AACSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAction<FActionBarInput>("Action1", EInputEvent::IE_Pressed, this, &AACSPlayerController::CastSpell, 0);
	InputComponent->BindAction<FActionBarInput>("Action2", EInputEvent::IE_Pressed, this, &AACSPlayerController::CastSpell, 1);
	InputComponent->BindAction<FActionBarInput>("Action3", EInputEvent::IE_Pressed, this, &AACSPlayerController::CastSpell, 2);
	InputComponent->BindAction<FActionBarInput>("Action4", EInputEvent::IE_Pressed, this, &AACSPlayerController::CastSpell, 3);
	InputComponent->BindAction<FActionBarInput>("Action5", EInputEvent::IE_Pressed, this, &AACSPlayerController::CastSpell, 4);
	InputComponent->BindAction("Click", EInputEvent::IE_Pressed, this, &AACSPlayerController::MouseLeftClicked);
	
}

void AACSPlayerController::CastSpell(int32 Index)
{
	auto pawn = Cast<AACSCharacter>(GetPawn());
	if(pawn)
	{
		UE_LOG(LogTemp,Warning, TEXT("Spell input index %d"), Index);
		pawn->CastSpell(Index);
	}
}

void AACSPlayerController::MouseLeftClicked()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	AACSCharacter * SelectCharacter = Cast<AACSCharacter>(Hit.GetActor());
	if (SelectCharacter)
	{
		const FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(GetPawn()->GetActorLocation(), SelectCharacter->GetActorLocation());
				
		GetCharacter()->bUseControllerRotationYaw = false;
		GetCharacter()->SetActorRotation(NewRotation);
	}	
}
     