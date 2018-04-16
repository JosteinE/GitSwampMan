// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
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

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	class UShapeComponent* EnemyRootBox;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* EnemyCapsule;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* EnemyMeshBox;

	UPROPERTY(EditAnywhere)
	float Speed = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Player;

	UPROPERTY(EditAnywhere)
	int EnemyHealth = 1;
};
