// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Fire.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RedFire.generated.h"

UCLASS()
class FLOWINGFIRE_API ARedFire : public AFire
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARedFire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
