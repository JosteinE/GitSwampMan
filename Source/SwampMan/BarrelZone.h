// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "BarrelZone.generated.h"

/**
 * 
 */
UCLASS()
class SWAMPMAN_API ABarrelZone : public ATriggerBox
{
	GENERATED_BODY()

public:
	ABarrelZone();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
