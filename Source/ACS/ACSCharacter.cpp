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

	GameMode = CastChecked<AACSGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
	CharacterData = *GameMode->CharacterData->FindRow<FCharacterData>(FName(Name), "");
	for (const auto SpellName : CharacterData.Spells)
	{
		LearnSpell(SpellName);
	}

	SetMaxHealth(200);
	SetCurrentHealth(200);
}

// Called every frame
void AACSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AACSCharacter::SetCurrentHealth(const float NewAmount)
{
	CurrentHealth = NewAmount;
	CurrentHealth = FMath::Clamp<float>(CurrentHealth, 0.0, MaxHealth);
	UpdateHealthBar();
}

void AACSCharacter::AddCurrentHealth(const float Amount)
{
	CurrentHealth += Amount;
	CurrentHealth = FMath::Clamp<float>(CurrentHealth, 0.0, MaxHealth);
	UpdateHealthBar();
}

float AACSCharacter::GetCurrentHealth() const
{
	return CurrentHealth;
}

void AACSCharacter::SetMaxHealth(const float NewAmount)
{
	MaxHealth = NewAmount;
	UpdateHealthBar();
}

float AACSCharacter::GetMaxHealth() const
{
	return MaxHealth;
}

void AACSCharacter::CastSpell_Implementation(FName SpellName)
{
}

void AACSCharacter::LearnSpell(FName SpellName)
{
	if(!CharacterData.Spells.Contains(SpellName))
	{
		CharacterData.Spells.Add(SpellName);	
	}
	UE_LOG(LogTemp, Warning, TEXT("Learned new spell: %s"), *SpellName.ToString());
}


FSpellData AACSCharacter::GetSpellData(const FName SpellName) const
{
	auto const SpellData = * GameMode->SpellData->FindRow<FSpellData>(FName(SpellName), "");
	return SpellData;
}



void AACSCharacter::ShootSpell(const FName SpellName)
{
	const auto SpellData = GetSpellData(SpellName);
	ASpell * NewSpell = GetWorld()->SpawnActor<ASpell>(SpellClass, GetActorLocation(), GetActorRotation());
	NewSpell->SetSpellName(SpellName);
	NewSpell->Setup(this, SpellData);
}

void AACSCharacter::EnteringCombat_Implementation(AACSCharacter* Enemy)
{
	InCombat = true;
	Target = Enemy;
}

float AACSCharacter::TakeDamage_Implementation(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	ASpell *Spell = Cast<ASpell>(DamageCauser);
	if(IsValid(Spell) && !CharacterData.Spells.Contains(Spell->GetSpellName()))
	{
		LearnSpell(Spell->GetSpellName());
		UE_LOG(LogTemp, Warning, TEXT("New spell: %s"), *Spell->GetSpellName().ToString());
	}
	DamageCauser->Destroy();

	if(!InCombat)
	{
		AACSCharacter * EnemyCharacter = Cast<AACSCharacter>(EventInstigator->GetCharacter());
		EnteringCombat(EnemyCharacter);
		EnemyCharacter->EnteringCombat(this);
	}	
	
	AddCurrentHealth(-DamageAmount * 10);
	/*auto dmg = Cast<UACSDamage>(DamageEvent.DamageTypeClass->GetDefaultObject());

	if (!dmg) return 0.0f;

	*/
	return DamageAmount * 10;
}



