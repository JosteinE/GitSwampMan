// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "HealthItem.generated.h"

UCLASS()
class SWAMPMAN_API AHealthItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Rotationrate
	UPROPERTY(EditAnywhere, Category = Pickup)
	FRotator RotationRate;

	//SceneComponent as Root
	UPROPERTY(EditAnywhere, Category = Pickup)
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, Category = Pickup)
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, Category = Pickup)
	float Speed;

	// Box Collider and overlap function
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollider;	
};
