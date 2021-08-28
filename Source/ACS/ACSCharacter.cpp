// Fill out your copyright notice in the Description page of Project Settings.


#include "ACSCharacter.h"

#include "ACSDamage.h"
#include "ACSGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AACSCharacter::AACSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TalentGridComponent = CreateDefaultSubobject<UACSTalentGridComponent>("TalentGrid");

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

void AACSCharacter::CastSpell_Implementation(int32 SpellIndex)
{
	
}

void AACSCharacter::ShootSpell(FSpellData SpellData)
{
	ASpell * NewSpell = GetWorld()->SpawnActor<ASpell>(SpellClass, GetActorLocation(), GetActorRotation());
	NewSpell->Setup(this, SpellData);
}

float AACSCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageCauser->Destroy();

	if(!InCombat)
	{
		EnteringCombat(EventInstigator->GetCharacter());
		InCombat = true;
	}
	
	
	/*auto dmg = Cast<UACSDamage>(DamageEvent.DamageTypeClass->GetDefaultObject());

	if (!dmg) return 0.0f;

	*/
	return 0.0f;
}



