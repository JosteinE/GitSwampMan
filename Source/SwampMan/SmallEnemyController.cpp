// Fill out your copyright notice in the Description page of Project Settings.

#include "SmallEnemyController.h"


// Sets default values
ASmallEnemyController::ASmallEnemyController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create our mesh
	EnemyMeshBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyCube"));
	EnemyMeshBox->SetupAttachment(RootComponent);

	Speed = 150.0f;
}

// Called when the game starts or when spawned
void ASmallEnemyController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASmallEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move the object
	FVector MyLocation = GetActorLocation();
	FVector PlayerLocation = Player->GetActorLocation();
	FVector TargetDestination = (PlayerLocation - MyLocation);
	TargetDestination.Z = 0;
	
	/*
	// Normalize it's speed, so it moves at a constant rate.
	TargetDestination.Normalize();

	MyLocation += TargetDestination * DeltaTime * Speed;
	SetActorLocation(MyLocation);
	*/

	AddMovementInput(GetActorForwardVector(), Speed);

	// Rotate to face the player
	FRotator FacePlayer = FRotationMatrix::MakeFromX(TargetDestination).Rotator();
	SetActorRotation(FacePlayer);
}

// Called to bind functionality to input
void ASmallEnemyController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

