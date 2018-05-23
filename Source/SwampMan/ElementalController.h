// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
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

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* EnemyMeshBox;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* EnemyCapsule;

	UPROPERTY(EditAnywhere)
	float Speed;

	UPROPERTY(EditAnywhere)
	int EnemyHealth = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Player;	
};
