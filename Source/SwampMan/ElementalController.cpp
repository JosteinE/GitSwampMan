// Fill out your copyright notice in the Description page of Project Settings.

#include "ElementalController.h"


// Sets default values
AElementalController::AElementalController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create our mesh
	EnemyMeshBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ElementalMesh"));
	EnemyMeshBox->SetupAttachment(RootComponent);

	//Speed = 550.0f;
}

// Called when the game starts or when spawned
void AElementalController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AElementalController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*
	// Move the object
	FVector MyLocation = GetActorLocation();
	FVector PlayerLocation = Player->GetActorLocation();
	FVector TargetDestination = (PlayerLocation - MyLocation);

	// Normalize it's speed, so it moves at a constant rate.
	TargetDestination.Normalize();

	MyLocation += TargetDestination * DeltaTime * Speed;
	SetActorLocation(MyLocation);
	*/

	{
		// Rotate to face the player
		FVector MyLocation = GetActorLocation();
		FVector PlayerLocation = Player->GetActorLocation();

		// Lock the emelental's Y and Z rotations
		FVector FaceTarget = PlayerLocation - MyLocation;
		FaceTarget.Z = 0;
	

		FRotator FacePlayer = FRotationMatrix::MakeFromX(FaceTarget).Rotator();
		SetActorRotation(FacePlayer);
	}
}

// Called to bind functionality to input
void AElementalController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

