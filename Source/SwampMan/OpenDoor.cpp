// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"


// Sets default values
AOpenDoor::AOpenDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create all components
	this->SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	this->RootComponent = SceneComponent;

	this->DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	this->DoorMesh->AttachToComponent(this->RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	// Create Collider
	this->BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	this->BoxCollider->bGenerateOverlapEvents = false;
	this->BoxCollider->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	this->BoxCollider->SetCollisionProfileName(TEXT("BlockAll"));
	this->BoxCollider->AttachToComponent(this->RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called when the game starts or when spawned
void AOpenDoor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AOpenDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

