// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Fire.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Combustible.generated.h"

UCLASS()
class FLOWINGFIRE_API ACombustible : public AActor
{
	GENERATED_BODY()

protected:
	// Types of fire which can destroy this combustible.
	UPROPERTY(EditAnywhere)
	TArray<FireType> validFire;

	UPROPERTY(EditAnywhere)
	float burningDuration;

	// Radius of spreading fire to other combustibles
	UPROPERTY(EditAnywhere)
	float spreadRadius;


	UPROPERTY(EditDefaultsOnly, Category = "FireToSpawn")
	TSubclassOf<AFire> redFireToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "FireToSpawn")
	TSubclassOf<AFire> blueFireToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "FireToSpawn")
	TSubclassOf<AFire> yellowFireToSpawn;

	AFire* currFire;

	float burningTimer;

public:
	// Sets default values for this actor's properties
	ACombustible();

	AFire* GetCurrFire() const;

	void SetOnFire(FireType fireType);

private:
	void Burn(float DeltaTime);
	void Spread();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
