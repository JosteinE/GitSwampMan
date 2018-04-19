// Fill out your copyright notice in the Description page of Project Settings.

#include "BarrelZone.h"
#include "PlayerCharacterWithCamera.h"

ABarrelZone::ABarrelZone()
{
	//UE_LOG(LogTemp, Warning, TEXT("test!"));
	//TArray<AActor*> OverlappingActor;
	//GetOverlappingActors(OverlappingActor, TSubclassOf<APlayerCharacterWithCamera>());

	//FString ThisName = OverlappingActor[0]->GetActorLabel();

	//UE_LOG(LogTemp, Warning, TEXT("This is %s"), ThisName);

	//for (auto& Element : OverlappingActor)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Success!"));
	//}
}

// Called every frame
void ABarrelZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*UE_LOG(LogTemp, Warning, TEXT("woah!"));*/
}