// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/StaticMesh.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacterWithCamera.generated.h"

UCLASS()
class SWAMPMAN_API APlayerCharacterWithCamera : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacterWithCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Cast a ray
	void RayCast();

	UFUNCTION()
	void OnPlayerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPlayerHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* OurCameraSpringArm;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* OurCamera;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* PlayerBox;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* CamuflageMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AActor> BulletToSpawn;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* PlayerCapsule;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* WindMesh;

	UPROPERTY(EditAnywhere)
	float MovementSpeed = 300.0f;

	UPROPERTY(EditAnywhere)
	float SprintSpeed = 200.0f;

	UPROPERTY(EditAnywhere)
	float ZoomedInCameraDistance = 300.0f;

	UPROPERTY(EditAnywhere)
	float ZoomedOutCameraDistance = 800.0f;

	UPROPERTY(EditAnywhere)
	float FOVZoomedIn = 90.0f;

	UPROPERTY(EditAnywhere)
	float FOVZoomedOut = 90.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PlayerHealth = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayerMana = 100.f;

	UPROPERTY(EditAnywhere)
	float WindForce = -200.0f;

	UPROPERTY(EditAnywhere)
	float WindLength = 130.f;

	UPROPERTY(EditAnywhere)
	float WindAngle = 20.f;

	UPROPERTY(EditAnywhere)
	bool GodMode = false;

	//Input variables
	APlayerController* PcMouse;
	FVector2D MovementInput;
	FVector2D MouseLoc;
	float ZoomFactor;
	bool bZoomingIn;
	bool bFireProjectile;
	bool bSprinting;
	bool bWindSelected;
	bool bCamuflageSelected;
	bool bDistractionSelected;

	//Input functions
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void MouseY(float AxisValue);
	void MouseX(float AxisValue);
	void ZoomIn();
	void ZoomOut();
	void ShootingProjectile();
	void NotShootingProjectile();
	void IsSprinting();
	void IsNotSprinting();
	void WindSelected();
	void CamuflageSelected();
	void DistractionSelected();

	//Spells unlocked
	bool bWindSpellUnlocked = false;
	bool bCamuflageSpellUnlocked = false;
	bool bDistractionShotUnlocked = false;

	//
	bool BarrelVisible = false;
};
