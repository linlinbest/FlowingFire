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
	TArray<EFireType> validFire;

	UPROPERTY(EditAnywhere)
	EFireType fireTypeOnStart;

	UPROPERTY(EditDefaultsOnly)
	float fireZOffset;

	UPROPERTY(EditAnywhere)
	float burningDuration;

	UPROPERTY(EditAnywhere)
	float onFireCooldown;

	// Radius of spreading fire to other combustibles
	UPROPERTY(EditAnywhere)
	float spreadRadius;

	// The time it takes to spread fire
	UPROPERTY(EditAnywhere)
	float spreadDelay;


	UPROPERTY(EditDefaultsOnly, Category = "FireToSpawn")
	TSubclassOf<AFire> redFireToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "FireToSpawn")
	TSubclassOf<AFire> blueFireToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "FireToSpawn")
	TSubclassOf<AFire> yellowFireToSpawn;

	AFire* currFire;

	FTimerHandle burningTimerHandle;
	FTimerHandle spreadTimerHandle;
	float onFireCooldownTimer;

public:
	// Sets default values for this actor's properties
	ACombustible();

	AFire* GetCurrFire() const;

	UFUNCTION(BlueprintCallable)
	void SetOnFire(EFireType fireType);

private:
	void Burn();
	void BurnOut();
	void Spread();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
