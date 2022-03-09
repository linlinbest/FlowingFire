// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Fire.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YellowFire.generated.h"

UCLASS()
class FLOWINGFIRE_API AYellowFire : public AFire
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AYellowFire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
