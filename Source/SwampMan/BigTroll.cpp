// Fill out your copyright notice in the Description page of Project Settings.

#include "BigTroll.h"


// Sets default values
ABigTroll::ABigTroll()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create the Box Collider
	/*BigTrollRootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BigTrollBoxCollider"));
	BigTrollRootBox->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	BigTrollRootBox->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	BigTrollRootBox->SetCollisionProfileName(TEXT("BlockAll"));
	BigTrollRootBox->SetSimulatePhysics(false);
	BigTrollRootBox->SetEnableGravity(false);*/

	//RootComponent = BigTrollRootBox;

	//Create our mesh
	BigTrollMeshBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BigTrollCube"));
	BigTrollMeshBox->SetupAttachment(RootComponent);

	this->RotationRate = FRotator(0.0f, 0.0f, 45.0f);
	this->Speed = 1.0f;
}

// Called when the game starts or when spawned
void ABigTroll::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABigTroll::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// Rotate the object
	this->AddActorLocalRotation(this->RotationRate * DeltaTime * Speed);
}

// Called to bind functionality to input
void ABigTroll::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

