// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "OutOfBoundsTB.generated.h"

/**
 * 
 */
UCLASS()
class SWAMPMAN_API AOutOfBoundsTB : public ATriggerBox
{
	GENERATED_BODY()
	
public:

	AOutOfBoundsTB();
	
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
};
