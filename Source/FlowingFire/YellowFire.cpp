// Fill out your copyright notice in the Description page of Project Settings.


#include "YellowFire.h"

// Sets default values
AYellowFire::AYellowFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	type = EFireType::Yellow;
}

// Called when the game starts or when spawned
void AYellowFire::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AYellowFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

