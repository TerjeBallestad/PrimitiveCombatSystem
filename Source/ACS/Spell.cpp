// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell.h"

// Sets default values

// TODO Rename to projectile spell
ASpell::ASpell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>("Collider");
	SetRootComponent(Collider);
	BillboardComponent = CreateDefaultSubobject<UBillboardComponent>("Sprite");
	BillboardComponent->SetupAttachment(Collider);
}

void ASpell::Setup(FSpellData data)
{
	SpellData = data;
	BillboardComponent->SetSprite(data.Image);
}

// Called when the game starts or when spawned
void ASpell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(FVector::ForwardVector * Speed * DeltaTime);
}

