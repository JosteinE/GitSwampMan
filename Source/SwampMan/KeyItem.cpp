// Fill out your copyright notice in the Description page of Project Settings.

#include "KeyItem.h"


// Sets default values
AKeyItem::AKeyItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create all components
	this->SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	this->RootComponent = SceneComponent;

	this->ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	this->ItemMesh->SetupAttachment(RootComponent);

	this->RotationRate = FRotator(45.0f, 45.0f, 0.0f);

	this->Speed = 1.0f;

	// Create Collider
	this->BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	this->BoxCollider->bGenerateOverlapEvents = true;
	this->BoxCollider->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	this->BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AKeyItem::OnOverlapBegin);
	this->BoxCollider->SetupAttachment(RootComponent);
}

// Overlap handler
void AKeyItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// Check if the OtherActor is not me and if it is not NULL
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		FString pickup = FString::Printf(TEXT("You picked up a key and a door was opened."));
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::White, pickup);
		GetWorld()->DestroyActor(Door);

		Destroy();
	}
}

// Called when the game starts or when spawned
void AKeyItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKeyItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Rotate the object
	this->AddActorLocalRotation(this->RotationRate * DeltaTime * Speed);
}

