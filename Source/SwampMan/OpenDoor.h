// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "OpenDoor.generated.h"

UCLASS()
class SWAMPMAN_API AOpenDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOpenDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//SceneComponent as Root
	UPROPERTY(EditAnywhere, Category = Doors)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, Category = Doors)
	UStaticMeshComponent* DoorMesh;

	// Box Collider
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxCollider;
};
