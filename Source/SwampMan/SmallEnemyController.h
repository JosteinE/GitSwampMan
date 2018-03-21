// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "SmallEnemyController.generated.h"

UCLASS()
class SWAMPMAN_API ASmallEnemyController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASmallEnemyController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	class UShapeComponent* EnemyRootBox;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* EnemyMeshBox;

	UPROPERTY(EditAnywhere)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Player;
};
