// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"


AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	SetMobility(EComponentMobility::Movable);
	if (HasAuthority()) //used to determine if it is a client
	{
		SetReplicates(true); //used to replicate object to all clients 
		SetReplicateMovement(true); //used to replicate movements of the object to all client
	}
	StartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HasAuthority())
	{
		
		FVector Location = GetActorLocation();
		float JourneyLenght = (GlobalTargetLocation - StartLocation).Size();
		float JourneyTravelled = (Location - StartLocation).Size();
		
		if (JourneyTravelled>=JourneyLenght)
		{
			SwapDirection();

		}
		FVector Direction = (GlobalTargetLocation - StartLocation).GetSafeNormal();
		Location += Speed * DeltaTime*Direction;
		SetActorLocation(Location);
	}
	
	
}

void AMovingPlatform::SwapDirection()
{
	FVector Swap = StartLocation;
	StartLocation = GlobalTargetLocation;
	GlobalTargetLocation = Swap;

}


