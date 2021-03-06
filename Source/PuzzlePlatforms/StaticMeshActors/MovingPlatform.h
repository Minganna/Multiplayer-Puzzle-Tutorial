// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	AMovingPlatform();
	
	void AddActiveTrigger();
	void RemoveActiveTrigger();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	void MovePlatform(float DeltaTime);
	UPROPERTY(EditAnywhere)
	float Speed = 5.0f;
	UPROPERTY(EditAnywhere,Meta=(MakeEditWidget=true))
	FVector TargetLocation;
private:
	FVector StartLocation;
	FVector GlobalTargetLocation;
	void SwapDirection();

	UPROPERTY(EditAnywhere)
		int ActiveTriggers = 1;

};
