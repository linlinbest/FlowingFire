// Fill out your copyright notice in the Description page of Project Settings.

#include "Combustible.h"

#include "Kismet/KismetSystemLibrary.h"

//Hanlin add includes:
#include "Engine/World.h"
#include "GameFrameWork/Actor.h"
#include "DrawDebugHelpers.h"

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

	EFireType mergedType = fireType; 
	if (currFire)
	{
		// avoid meaningless setOnFire
		if (currFire->GetType() == fireType) return;
		mergedType = currFire->Merge(fireType);
		if (currFire->GetType() == mergedType) return;
		currFire->Destroy();
		currFire = nullptr;
	}

	FVector spawnPos = GetActorLocation();
	spawnPos.Z += fireZOffset;
	switch (mergedType)
	{
	case EFireType::Red:
		currFire = GetWorld()->SpawnActor<AFire>(redFireToSpawn, spawnPos, GetActorRotation());
		break;
	case EFireType::Blue:
		currFire = GetWorld()->SpawnActor<AFire>(blueFireToSpawn, spawnPos, GetActorRotation());
		break;
	case EFireType::Yellow:
		currFire = GetWorld()->SpawnActor<AFire>(yellowFireToSpawn, spawnPos, GetActorRotation());
		break;
	case EFireType::Green:
		currFire = GetWorld()->SpawnActor<AFire>(greenFireToSpawn, spawnPos, GetActorRotation());
		break;
	case EFireType::Purple:
		currFire = GetWorld()->SpawnActor<AFire>(purpleFireToSpawn, spawnPos, GetActorRotation());
		break;
	case EFireType::Orange:
		currFire = GetWorld()->SpawnActor<AFire>(orangeFireToSpawn, spawnPos, GetActorRotation());
		break;
	default:
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, "Unkown merged fire type!");
		break;
	}

	Burn();
	GetWorldTimerManager().SetTimer(spreadTimerHandle, this, &ACombustible::Spread, spreadDelay, false);
}



void ACombustible::Spread()
{
	if (currFire == nullptr) return;
	bool hitCombustible;
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

		if (overlappedCombustible)
		{
			//Hanlin added: do the raycast between two objects
			CombustibleObjRayCast(this, overlappedCombustible, hitCombustible);
			if (hitCombustible)
			{
				//Debug
				overlappedCombustible->SetOnFire(currFire->GetType());
			}
		}
	}
}

void ACombustible::OnBurnOutEnd()
{

}

void ACombustible::OnBurnBegin()
{

}

void ACombustible::Burn()
{
	if (currFire == nullptr) return;
	
	ReceiveOnBurnBegin();
	GetWorldTimerManager().SetTimer(burningTimerHandle, this, &ACombustible::BurnOut, burningDuration, false);
}

void ACombustible::BurnOut()
{
	if (currFire == nullptr) return;

	onFireCooldownTimer = onFireCooldown;

	for (EFireType validFireType : validFire)
	{
		if (currFire->GetType() == validFireType)
		{
			currFire->Destroy();
			currFire = nullptr;
			//this->Destroy();
			ReceiveOnBurnOutEnd();
			return;
		}
	}
	

	currFire->Destroy();
	currFire = nullptr;
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

//Hanlin Added in 3/10
void ACombustible::CombustibleObjRayCast(AActor* startObj, AActor* targetObj, bool& hitCombustible)
{
	FVector startPoint = startObj->GetActorLocation();
	FVector endPoint = targetObj->GetActorLocation();
	FVector rayDir = endPoint - startPoint;
	rayDir = rayDir.GetSafeNormal();
	//startPoint = startPoint + rayDir * 60;
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, startPoint.ToString());

	FHitResult hit;

	if (GetWorld())
	{
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);

		bool actorHit = GetWorld()->LineTraceSingleByChannel(hit, startPoint, endPoint, ECC_WorldDynamic, CollisionParams, FCollisionResponseParams());

		if (actorHit&&hit.GetActor())
		{
			if (hit.GetActor() == targetObj)
			{
				hitCombustible = true;
			}
			else
			{
				hitCombustible = false;
			}
		}
	}

}

