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
	
	InputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &AACSPlayerController::ShootSpell);
	InputComponent->BindAction("Click", EInputEvent::IE_Pressed, this, &AACSPlayerController::MouseLeftClicked);
	
}

void AACSPlayerController::ShootSpell()
{
	auto pawn = Cast<AACSCharacter>(GetPawn());
	if(pawn)
	{
		UE_LOG(LogTemp,Warning, TEXT("Spell"));
		pawn->ShootSpell();
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
		UE_LOG(LogTemp, Warning, TEXT("%s"), *NewRotation.ToString())
		GetCharacter()->SetActorRotation(NewRotation);
		//GetPawn()->SetActorRotation(NewRotation);
	}
	
}
     