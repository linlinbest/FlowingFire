// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fire.generated.h"

UENUM(BlueprintType, meta = (Bitflags, UseEnumValueAsMaskValuesInEditor = "true"))
enum class EFireType : uint8
{
	None     = 0            UMETA(DisplayName = "None"),
	Red      = 1 << 0       UMETA(DisplayName = "Red"),
	Blue     = 1 << 1       UMETA(DisplayName = "Blue"),
	Yellow   = 1 << 2       UMETA(DisplayName = "Yellow"),
	Purple   = Red | Blue   UMETA(DisplayName = "Purple"),
	Orange   = Red | Yellow UMETA(DisplayName = "Orange"),
	Green    = Yellow | Blue   UMETA(DisplayName = "Green"),
};

EFireType operator|(EFireType lhs, EFireType rhs);
unsigned int CountSetBits(EFireType fireType);


UCLASS()
class FLOWINGFIRE_API AFire : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	EFireType type;

public:	
	// Sets default values for this actor's properties
	AFire();

	UFUNCTION(BlueprintCallable)
	EFireType GetType() const;
	
	UFUNCTION(BlueprintCallable)
	EFireType Merge(EFireType typeBeforeMerge) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
