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

EFireType AFire::Merge(EFireType anotherType) const
{
	EFireType mergedType;
	
	// Basic type of fire has 1 setbit (e.g Red 00000001)
	// Emerged type of fire has 2 setbits (e.g Purple 00000011)
	unsigned int currTypeSetBits = CountSetBits(type);
	unsigned int anotherTypeSetBits = CountSetBits(anotherType);

	// Emerged type of fire don't merge to a new type
	if (currTypeSetBits >= 2 && anotherTypeSetBits >= 2)
	{
		mergedType = type;
	}
	// Emerged type of fire will replace basic type
	else if (currTypeSetBits > anotherTypeSetBits)
	{
		mergedType = type;
	}
	else if (currTypeSetBits < anotherTypeSetBits)
	{
		mergedType = anotherType;
	}
	// Basic types of fire merge into a emerged type of fire
	else
	{
		mergedType = type | anotherType;
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

