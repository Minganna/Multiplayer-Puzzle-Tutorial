// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("Game Instance constructor"));
}
void UPuzzlePlatformsGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Instance Init"));
	Engine = GetEngine();
}

void UPuzzlePlatformsGameInstance::Host()
{

	if (!ensure(Engine != nullptr))
	{
		return;
	}							// replace text, time on screen, color of text, actual text
	Engine->AddOnScreenDebugMessage(0,2,FColor::Green,TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr))
	{
		return;
	}
	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString address)
{
	if (!ensure(Engine != nullptr))
	{
		return;
	}							// replace text, time on screen, color of text, actual text
	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"),*address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr))
	{
		return;
	}
	PlayerController->ClientTravel(*address, ETravelType::TRAVEL_Absolute);
}
