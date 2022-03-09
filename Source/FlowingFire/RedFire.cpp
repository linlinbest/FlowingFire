// Fill out your copyright notice in the Description page of Project Settings.


#include "RedFire.h"

// Sets default values
ARedFire::ARedFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	type = FireType::Red;
}

// Called when the game starts or when spawned
void ARedFire::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARedFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

