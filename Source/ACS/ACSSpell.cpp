// Fill out your copyright notice in the Description page of Project Settings.


#include "ACSSpell.h"

#include "Kismet/GameplayStatics.h"


// TODO Rename to projectile spell
AACSSpell::AACSSpell()
{
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>("Collider");
	SetRootComponent(Collider);
	BillboardComponent = CreateDefaultSubobject<UBillboardComponent>("Sprite");
	BillboardComponent->SetupAttachment(Collider);
}

void AACSSpell::Setup(AActor *instigator, FSpellData data)
{
	SpellData = data;
	BillboardComponent->SetSprite(data.Image);
	SpellInstigator = instigator;
	UE_LOG(LogTemp, Warning, TEXT("Instigator %s"), *instigator->GetName());	

	Collider->MoveIgnoreActors.Add(instigator);
	Collider->SetGenerateOverlapEvents(true);
}

void AACSSpell::BeginPlay()
{
	Super::BeginPlay();
}

void AACSSpell::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if(OtherActor != SpellInstigator && OtherActor->GetClass() != this->GetClass())
	{

	/* 

		TSubclassOf<UDamageType> DamageType;


		FRTSAttackData DefaultAttack;
		DefaultAttack.Cooldown = 0.5f;
		DefaultAttack.Damage = 10.0f;
		DefaultAttack.Range = 200.0f;

		Attacks.Add(DefaultAttack);

		const FRTSAttackData& Attack = Attacks[AttackIndex];

		DamageType = Attack.DamageType
	 
		TSubclassOf<class UDamageType> DamageType = ProjectileDamageType;
		FDamageEvent(DamageType)
	 
	 */


		const FDamageEvent dmg(DamageTypeClass);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, GetActorLocation(), GetActorRotation(), true);
		
		if(SpellData.Light > 0)
		{
			OtherActor->TakeDamage(SpellData.Light, dmg, SpellInstigator->GetInstigatorController(), this);
			UE_LOG(LogTemp, Warning, TEXT("Hit %s for %d Light damage"), *OtherActor->GetName(), SpellData.Light);
		}

		if(SpellData.Blue > 0)
		{
			OtherActor->TakeDamage(SpellData.Blue, dmg, SpellInstigator->GetInstigatorController(), this);
			UE_LOG(LogTemp, Warning, TEXT("Hit %s for %d Blue damage"), *OtherActor->GetName(), SpellData.Blue);
		}

		if(SpellData.Dark > 0)
		{
			OtherActor->TakeDamage(SpellData.Dark, dmg, SpellInstigator->GetInstigatorController(), this);
			UE_LOG(LogTemp, Warning, TEXT("Hit %s for %d Dark damage"), *OtherActor->GetName(), SpellData.Dark);
		}
		if(SpellData.Red > 0)
		{
			OtherActor->TakeDamage(SpellData.Red, dmg, SpellInstigator->GetInstigatorController(), this);
			UE_LOG(LogTemp, Warning, TEXT("Hit %s for %d Red damage"), *OtherActor->GetName(), SpellData.Red);
		}
		if(SpellData.Green > 0)
		{
			OtherActor->TakeDamage(SpellData.Green, dmg, SpellInstigator->GetInstigatorController(), this);
			UE_LOG(LogTemp, Warning, TEXT("Hit %s for %d Green damage"), *OtherActor->GetName(), SpellData.Green);
		}
	}
}

void AACSSpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalOffset(FVector::ForwardVector * Speed * DeltaTime);
}
