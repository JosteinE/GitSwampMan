// Fill out your copyright notice in the Description page of Project Settings.

#include "SmallEnemyController.h"


// Sets default values
ASmallEnemyController::ASmallEnemyController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyCapsule = GetCapsuleComponent();

	//Create our mesh
	EnemyMeshBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyCube"));
	EnemyMeshBox->SetCollisionProfileName("NoCollision");
	EnemyMeshBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASmallEnemyController::BeginPlay()
{
	Super::BeginPlay();
	
	//Calculate health
	EnemyCapsule->OnComponentHit.AddDynamic(this, &ASmallEnemyController::OnHit);
}

// Called every frame
void ASmallEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EnemyHealth == 0)
	{
		Destroy();
	}

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

void ASmallEnemyController::OnHit(UPrimitiveComponent* HitComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherComp->GetCollisionProfileName() == "EnemyBullet")
	{
		EnemyHealth -= 1;

		OtherActor->Destroy();
	}
}
