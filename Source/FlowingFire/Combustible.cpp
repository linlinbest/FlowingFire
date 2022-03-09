// Fill out your copyright notice in the Description page of Project Settings.

#include "Combustible.h"

#include "RedFire.h"
#include "BlueFire.h"
#include "YellowFire.h"

#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ACombustible::ACombustible()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	currFire = nullptr;
	burningDuration = 5.f;
	spreadRadius = 200.f;

	burningTimer = 0.f;

}

AFire* ACombustible::GetCurrFire() const
{
	return currFire;
}

void ACombustible::SetOnFire(FireType fireType)
{
	FVector spawnPos = GetActorLocation();
	spawnPos.Z += 100.f;
	if (currFire)
	{
		currFire->Destroy();
	}

	switch (fireType)
	{
	case FireType::Red:
		currFire = GetWorld()->SpawnActor<ARedFire>(redFireToSpawn, spawnPos, GetActorRotation());
		break;
	case FireType::Blue:
		currFire = GetWorld()->SpawnActor<ABlueFire>(blueFireToSpawn, spawnPos, GetActorRotation());
		break;
	case FireType::Yellow:
		currFire = GetWorld()->SpawnActor<AYellowFire>(yellowFireToSpawn, spawnPos, GetActorRotation());
		break;
	}

	burningTimer = burningDuration;

}

void ACombustible::Spread()
{
	if (currFire == nullptr) return;
	TArray<AActor*> overlappedActors;
	TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
	traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	// ignore self
	TArray<AActor*> ignoreActors;
	ignoreActors.Init(this, 1);

	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), spreadRadius,
		traceObjectTypes, nullptr, ignoreActors, overlappedActors);

	for (AActor* overlappedActor : overlappedActors) {
		ACombustible* overlappedCombustible = Cast<ACombustible>(overlappedActor);
		if (overlappedCombustible && overlappedCombustible->GetCurrFire() == nullptr)
		{
			overlappedCombustible->SetOnFire(currFire->GetType());
		}
	}
}

void ACombustible::Burn(float DeltaTime)
{
	if (currFire == nullptr) return;
	
	burningTimer -= DeltaTime;
	if (burningTimer < 0.f)
	{
		for (FireType validFireType : validFire)
		{
			if (currFire->GetType() == validFireType)
			{
				currFire->Destroy();
				this->Destroy();
				return;
			}
		}

		currFire->Destroy();
		currFire = nullptr;
	}
}

// Called when the game starts or when spawned
void ACombustible::BeginPlay()
{
	Super::BeginPlay();

	SetOnFire(FireType::Blue);
}

// Called every frame
void ACombustible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Burn(DeltaTime);
	Spread();

}

