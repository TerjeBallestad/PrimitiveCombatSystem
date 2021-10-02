// Fill out your copyright notice in the Description page of Project Settings.


#include "ACSCharacter.h"

#include "ACSGameInstance.h"
#include "ACSSaveGame.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AACSCharacter::AACSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Configure character movement
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	TalentGridComponent = CreateDefaultSubobject<UACSTalentGridComponent>("TalentGrid");

}

// Called when the game starts or when spawned
void AACSCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (!Name.IsNone())
		Setup(Name);
	

}

void AACSCharacter::Setup_Implementation(FName CharacterName)
{
	auto GameInstance = CastChecked<UACSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	Name = CharacterName;
	FCharacterData Data;
	
	if (UACSSaveGame::CharacterDataExists(CharacterName))
	{
		Data = UACSSaveGame::LoadCharacterData(CharacterName);
		UE_LOG(LogTemp, Warning, TEXT("Loading character %s from savegame"), *CharacterName.ToString());
	} else
	{
		Data = *GameInstance->CharacterData->FindRow<FCharacterData>(CharacterName, "");
		Data.TalentGrid = *GameInstance->CharacterGrids->FindRow<FTalentGridCharacter>(CharacterName, "");
		UACSSaveGame::SaveCharacterData(CharacterName, Data);
		UE_LOG(LogTemp, Warning, TEXT("Character %s does not exist, loading from datatable"), *CharacterName.ToString());
	}

	CharacterData = Data;
	
	for (const auto SpellName : CharacterData.Spells)
	{
		LearnSpell(SpellName);
	}

	SetMaxHealth(CharacterData.MaxHealth);
	SetCurrentHealth(CharacterData.CurrentHealth);
}

// Called every frame
void AACSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AACSCharacter::SetCurrentHealth(const float NewAmount)
{
	CharacterData.CurrentHealth = NewAmount;
	CharacterData.CurrentHealth = FMath::Clamp<float>(CharacterData.CurrentHealth, 0.0, CharacterData.MaxHealth);
	UACSSaveGame::SaveCharacterData(Name, CharacterData);
	UpdateHealthBar();
}


void AACSCharacter::AddCurrentHealth(const float Amount)
{
	CharacterData.CurrentHealth += Amount;
	CharacterData.CurrentHealth = FMath::Clamp<float>(CharacterData.CurrentHealth, 0.0, CharacterData.MaxHealth);
	UACSSaveGame::SaveCharacterData(Name, CharacterData);
	UpdateHealthBar();
}

float AACSCharacter::GetCurrentHealth() const
{
	return CharacterData.CurrentHealth;
}

void AACSCharacter::SetMaxHealth(const float NewAmount)
{
	CharacterData.MaxHealth = NewAmount;
	UACSSaveGame::SaveCharacterData(Name, CharacterData);
	UpdateHealthBar();
}

float AACSCharacter::GetMaxHealth() const
{
	return CharacterData.MaxHealth;
}

void AACSCharacter::CastSpell(FName SpellName)
{
	if (IsCasting) return;

	auto SpellData = GetSpellData(SpellName);

	FTimerDelegate TimerCallback;
	TimerCallback.BindLambda([=]
	{
		ShootSpell(SpellName);
		SpellCastEnd();
		IsCasting = false;
	});

	GetWorld()->GetTimerManager().SetTimer(CastTimeHandle, TimerCallback, SpellData.CastTime, false);
	SpellCastStart();
	IsCasting = true;
}

void AACSCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (CastTimeHandle.IsValid())
		GetWorld()->GetTimerManager().ClearTimer(CastTimeHandle);
}

void AACSCharacter::LearnSpell(FName SpellName)
{
	if(!CharacterData.Spells.Contains(SpellName))
	{
		CharacterData.Spells.Add(SpellName);	
		UE_LOG(LogTemp, Warning, TEXT("Learned new spell: %s"), *SpellName.ToString());
		UACSSaveGame::SaveCharacterData(Name, CharacterData);
	}
}


FSpellData AACSCharacter::GetSpellData(const FName SpellName) const
{
	auto const SpellData = * Cast<UACSGameInstance>(GetGameInstance())->SpellData->FindRow<FSpellData>(FName(SpellName), "");
	return SpellData;
}



void AACSCharacter::ShootSpell(const FName SpellName)
{
	const auto SpellData = GetSpellData(SpellName);
	AACSSpell * NewSpell = GetWorld()->SpawnActor<AACSSpell>(SpellClass, GetActorLocation(), GetActorRotation());
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
	AACSSpell *Spell = Cast<AACSSpell>(DamageCauser);
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
	if(CharacterData.CurrentHealth <= 0)
	{
		Die();
	}

	return DamageAmount * 10;
}

void AACSCharacter::Die_Implementation()
{
	if( UGameplayStatics::GetCurrentLevelName(GetWorld()) != "InsideBrain")
	{
		UGameplayStatics::OpenLevel(GetWorld(), "InsideBrain", true, "?CharacterName=" + Name.ToString() +"?EnemyName=" + Target->Name.ToString());
	} else
	{
		UGameplayStatics::OpenLevel(GetWorld(), "CombatArena");
	}
}



