// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "EnemyController.generated.h"

UCLASS()
class SWAMPMAN_API AEnemyController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class UShapeComponent* EnemyRootBox;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* EnemyMeshBox;

	UPROPERTY(EditAnywhere)
	float Speed;

	UPROPERTY(EditAnywhere)
	AActor* Player;
};
