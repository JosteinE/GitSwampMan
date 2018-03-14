// Fill out your copyright notice in the Description page of Project Settings.

#include "OutOfBoundsTB.h"
#include "DrawDebugHelpers.h"

AOutOfBoundsTB::AOutOfBoundsTB()
{
	OnActorBeginOverlap.AddDynamic(this, &AOutOfBoundsTB::OnOverlapBegin);
}

void AOutOfBoundsTB::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		GetWorld()->DestroyActor(OtherActor);
	}
}