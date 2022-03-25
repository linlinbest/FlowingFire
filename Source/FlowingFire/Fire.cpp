// Fill out your copyright notice in the Description page of Project Settings.


#include "Fire.h"

EFireType operator|(EFireType lhs, EFireType rhs)
{
	return static_cast<EFireType>(static_cast<uint8>(lhs) |
		static_cast<uint8>(rhs));
}

unsigned int CountSetBits(EFireType fireType)
{
	unsigned int n = static_cast<uint8>(fireType);
	unsigned int count = 0;
	while (n)
	{
		count += n & 1;
		n >>= 1;
	}
	return count;
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
	EFireType mergedType;
	// Emerged type of fire will replace basic type, but basic type of fire should
	// not replace emerged type of fire.
	if (CountSetBits(type) > CountSetBits(typeBeforeMerge))
	{
		mergedType = type;
	}
	else if (CountSetBits(type) < CountSetBits(typeBeforeMerge))
	{
		mergedType = typeBeforeMerge;
	}
	else
	{
		mergedType = type | typeBeforeMerge;
	}

	return mergedType;
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

