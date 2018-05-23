// Fill out your copyright notice in the Description page of Project Settings.

#include "SmallEnemyController.h"


// Sets default values
ASmallEnemyController::ASmallEnemyController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyCapsule = GetCapsuleComponent();
	EnemyCapsule->SetSimulatePhysics(false);
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

	// Rotate to face the player
	if (PlayerSpotted)
	{
		FRotator FacePlayer = FRotationMatrix::MakeFromX(TargetDestination).Rotator();
		SetActorRotation(FacePlayer);
	}
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