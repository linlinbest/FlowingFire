// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fire.generated.h"

UENUM()
enum class FireType : uint8
{
	None      UMETA(DisplayName = "None"),
	Red       UMETA(DisplayName = "Red"),
	Blue      UMETA(DisplayName = "Blue"),
	Yellow    UMETA(DisplayName = "Yellow"),
};

UCLASS()
class FLOWINGFIRE_API AFire : public AActor
{
	GENERATED_BODY()
	
protected:
	FireType type;

public:	
	// Sets default values for this actor's properties
	AFire();

	FireType GetType() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
