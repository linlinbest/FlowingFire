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

	fireTypeOnStart = EFireType::None;
	fireZOffset = 100.f;
	currFire = nullptr;
	burningDuration = 5.f;
	spreadRadius = 200.f;
	spreadDelay = 3.f;

	onFireCooldown = 5.f;
	onFireCooldownTimer = 0.f;

}

AFire* ACombustible::GetCurrFire() const
{
	return currFire;
}

void ACombustible::SetOnFire(EFireType fireType)
{
	if (fireType == EFireType::None || onFireCooldownTimer > 0.f) return;

	if (currFire)
	{
		currFire->Destroy();
	}

	FVector spawnPos = GetActorLocation();
	spawnPos.Z += fireZOffset;
	switch (fireType)
	{
	case EFireType::Red:
		currFire = GetWorld()->SpawnActor<ARedFire>(redFireToSpawn, spawnPos, GetActorRotation());
		break;
	case EFireType::Blue:
		currFire = GetWorld()->SpawnActor<ABlueFire>(blueFireToSpawn, spawnPos, GetActorRotation());
		break;
	case EFireType::Yellow:
		currFire = GetWorld()->SpawnActor<AYellowFire>(yellowFireToSpawn, spawnPos, GetActorRotation());
		break;
	}

	Burn();
	GetWorldTimerManager().SetTimer(spreadTimerHandle, this, &ACombustible::Spread, spreadDelay, false);

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

void ACombustible::Burn()
{
	if (currFire == nullptr) return;
	
	GetWorldTimerManager().SetTimer(burningTimerHandle, this, &ACombustible::BurnOut, burningDuration, false);
}

void ACombustible::BurnOut()
{
	for (EFireType validFireType : validFire)
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

	onFireCooldownTimer = onFireCooldown;
}

// Called when the game starts or when spawned
void ACombustible::BeginPlay()
{
	Super::BeginPlay();

	SetOnFire(fireTypeOnStart);
}

// Called every frame
void ACombustible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (onFireCooldownTimer > 0.f) onFireCooldownTimer -= DeltaTime;
}

