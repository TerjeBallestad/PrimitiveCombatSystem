// Fill out your copyright notice in the Description page of Project Settings.


#include "ACSCharacter.h"

#include "ACSGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AACSCharacter::AACSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AACSCharacter::BeginPlay()
{
	Super::BeginPlay();

	const auto GameMode = CastChecked<AACSGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
	CharacterData = *GameMode->CharacterData->FindRow<FCharacterData>(FName(Name), "");
	for (auto SpellName : CharacterData.Spells)
	{
		Spells.Add(* GameMode->SpellData->FindRow<FSpellData>(FName(SpellName), ""));
	}
}

// Called every frame
void AACSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AACSCharacter::ShootSpell()
{
	ASpell * NewSpell = GetWorld()->SpawnActor<ASpell>(SpellClass, GetActorLocation(), GetActorRotation());
	NewSpell->Setup(Spells[0]);
}	

