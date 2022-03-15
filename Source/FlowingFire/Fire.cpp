// Fill out your copyright notice in the Description page of Project Settings.


#include "Fire.h"

EFireType operator|(EFireType lhs, EFireType rhs)
{
	return static_cast<EFireType>(static_cast<uint8>(lhs) |
		static_cast<uint8>(rhs));
}

// Sets default values
AFire::AFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	type = EFireType::None;

}

EFireType AFire::GetType() const
{
	return type;
}

EFireType AFire::Merge(EFireType typeBeforeMerge) const
{
	return type | typeBeforeMerge;
}

// Called when the game starts or when spawned
void AFire::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

