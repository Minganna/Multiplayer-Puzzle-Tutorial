// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"

void UMainMenu::SetUp()
{
	this->AddToViewport();
	this->bIsFocusable = true;

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr))
	{
		return;
	}


	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr))
	{
		return;
	}

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = true;
}

void UMainMenu::OnLevelRemovedFromWorld(ULevel * InLevel, UWorld * InWorld)
{
	RemoveFromViewport();
	auto* world = GetWorld();
	if (!ensure(world != nullptr))
		return;
	auto* playerController = world->GetFirstPlayerController();
	if (!ensure(playerController != nullptr))
		return;
	FInputModeGameOnly inputMode;
	playerController->SetInputMode(inputMode);
	playerController->bShowMouseCursor = false;
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);
}

bool UMainMenu::Initialize()
{
	bool Success=Super::Initialize();
	if (!Success) return false;

	//TODO Setup
	if (!ensure(Host != nullptr))
	{
		return false;
	}
	Host->OnClicked.AddDynamic(this,&UMainMenu::HostClicked);

	return true;
}

void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterface)
{
	this->MenuInterface = MenuInterface;
}

void UMainMenu::HostClicked()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
}
