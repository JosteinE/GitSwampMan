// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "ElementalController.generated.h"

UCLASS()
class SWAMPMAN_API AElementalController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AElementalController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* EnemyMeshBox;

	UPROPERTY(EditAnywhere)
	float Speed;

	UPROPERTY(EditAnywhere)
	AActor* Player;	
};
