// Fill out your copyright notice in the Description page of Project Settings.

#include "ElementalController.h"


// Sets default values
AElementalController::AElementalController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyCapsule = GetCapsuleComponent();
	EnemyCapsule->SetSimulatePhysics(false);
	//Create our mesh
	EnemyMeshBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ElementalMesh"));
	EnemyMeshBox->SetCollisionProfileName("NoCollision");
	EnemyMeshBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AElementalController::BeginPlay()
{
	Super::BeginPlay();
	
	//Calculate health
	EnemyCapsule->OnComponentHit.AddDynamic(this, &AElementalController::OnHit);
}

// Called every frame
void AElementalController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	{
		// Rotate to face the player
		FVector MyLocation = GetActorLocation();
		FVector PlayerLocation = Player->GetActorLocation();

		// Lock the emelental's Y and Z rotations
		FVector FaceTarget = PlayerLocation - MyLocation;
		FaceTarget.Z = 0;

		FRotator FacePlayer = FRotationMatrix::MakeFromX(FaceTarget).Rotator();
		SetActorRotation(FacePlayer);

		if (EnemyHealth <= 0)
		{
			Destroy();
		}
	}
}

// Called to bind functionality to input
void AElementalController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AElementalController::OnHit(UPrimitiveComponent* HitComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
		EnemyHealth -= 1;
		UE_LOG(LogTemp, Warning, TEXT("Elemental is now on: %i"), EnemyHealth);
		OtherActor->Destroy();
}