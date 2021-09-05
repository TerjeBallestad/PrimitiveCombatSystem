// Fill out your copyright notice in the Description page of Project Settings.


#include "ACSPlayerController.h"

#include "ACSCharacter.h"
#include "ACSNonePlayerController.h"
#include "Kismet/KismetMathLibrary.h"


void AACSPlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void AACSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AACSPlayerController::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &AACSPlayerController::StopJumping);

	InputComponent->BindAxis("MoveForward", this, &AACSPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AACSPlayerController::MoveRight);

	InputComponent->BindAxis("Turn", this, &AACSPlayerController::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AACSPlayerController::AddControllerPitchInput);
	
	InputComponent->BindAction("Click", EInputEvent::IE_Pressed, this, &AACSPlayerController::MouseLeftClicked);

	InputComponent->BindAction<FActionBarInput>("Action1", EInputEvent::IE_Pressed, this, &AACSPlayerController::CastSpell, 0);
	InputComponent->BindAction<FActionBarInput>("Action2", EInputEvent::IE_Pressed, this, &AACSPlayerController::CastSpell, 1);
	InputComponent->BindAction<FActionBarInput>("Action3", EInputEvent::IE_Pressed, this, &AACSPlayerController::CastSpell, 2);
	InputComponent->BindAction<FActionBarInput>("Action4", EInputEvent::IE_Pressed, this, &AACSPlayerController::CastSpell, 3);
	InputComponent->BindAction<FActionBarInput>("Action5", EInputEvent::IE_Pressed, this, &AACSPlayerController::CastSpell, 4);
	
}

void AACSPlayerController::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		GetCharacter()->AddMovementInput(Direction, Value);
	}
}

void AACSPlayerController::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// find out which way is right
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		GetCharacter()->AddMovementInput(Direction, Value);
	}
}

void AACSPlayerController::Jump()
{
	GetCharacter()->Jump();
}

void AACSPlayerController::StopJumping()
{
	GetCharacter()->StopJumping();
}

void AACSPlayerController::AddControllerYawInput(const float Value)
{
	GetPawn()->AddControllerYawInput(Value);
}

void AACSPlayerController::AddControllerPitchInput(const float Value)
{
	GetPawn()->AddControllerPitchInput(Value);
}

void AACSPlayerController::CastSpell(int32 Index)
{
	auto pawn = Cast<AACSCharacter>(GetPawn());
	
	UE_LOG(LogTemp,Warning, TEXT("Spell input index %d"), Index);

	
	if(pawn && pawn->CharacterData.Spells.Num() > Index)
	{
		auto SpellName = pawn->CharacterData.Spells[Index];
		UE_LOG(LogTemp,Warning, TEXT("Spell input name %s"), *SpellName.ToString());
		pawn->CastSpell(SpellName);
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
				
		GetCharacter()->SetActorRotation(NewRotation);
	}	
}
     