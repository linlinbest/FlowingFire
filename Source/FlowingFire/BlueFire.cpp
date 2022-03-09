// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueFire.h"

// Sets default values
ABlueFire::ABlueFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	type = EFireType::Blue;
}

// Called when the game starts or when spawned
void ABlueFire::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlueFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

