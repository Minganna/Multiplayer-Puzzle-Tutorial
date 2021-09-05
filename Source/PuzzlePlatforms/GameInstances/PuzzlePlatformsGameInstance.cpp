// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "PuzzlePlatforms/PuzzlePlatformsGameMode.h"

#include "MainMenu/UserWidget/MainMenu.h"
#include "MainMenu/UserWidget/MenuWidget.h"


UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr))
	{
		return;
	}
	MenuClass = MenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));
	if (!ensure(InGameMenuBPClass.Class != nullptr))
	{
		return;
	}
	InGameMenuClass = InGameMenuBPClass.Class;
	
}
void UPuzzlePlatformsGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *MenuClass->GetName());
	Engine = GetEngine();
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr))
	{
		return;
	}
	Menu= CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(Menu != nullptr))
	{
		return;
	}

	Menu->SetUp();

	Menu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::InGameLoadMenu()
{
	if (!ensure(InGameMenuClass != nullptr))
	{
		return;
	}
	UMenuWidget* Menu = CreateWidget<UMenuWidget>(this, InGameMenuClass);
	if (!ensure(Menu != nullptr))
	{
		return;
	}

	Menu->SetUp();

	Menu->SetMenuInterface(this);
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

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	 UWorld* World = GetWorld();
    if (World)
    {
        if (World->IsServer())
        {
            APuzzlePlatformsGameMode* GM = World->GetAuthGameMode<APuzzlePlatformsGameMode>();
            if (GM)
            {
                GM->ReturnToMainMenuHost();
            }
        }
        else
        {
            APlayerController* PC = GetFirstLocalPlayerController();
            if (PC)
            {                
                PC->ClientReturnToMainMenu("Back to main menu");
            }
        }
    }
}


