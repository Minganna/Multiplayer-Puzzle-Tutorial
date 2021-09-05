// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"



bool UMainMenu::Initialize()
{
	bool Success=Super::Initialize();
	if (!Success) return false;

	//TODO Setup
	if (!ensure(HostButton != nullptr))
	{
		return false;
	}
	HostButton->OnClicked.AddDynamic(this,&UMainMenu::HostClicked);
	if (!ensure(JoinButton != nullptr))
	{
		return false;
	}
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	if (!ensure(CancelButton != nullptr))
	{
		return false;
	}
	CancelButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	if (!ensure(JoinGameButton != nullptr))
	{
		return false;
	}
	JoinGameButton->OnClicked.AddDynamic(this, &UMainMenu::JoinGame);

	if (!ensure(QuitButton != nullptr))
	{
		return false;
	}
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

	return true;
}


void UMainMenu::HostClicked()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
}

void UMainMenu::JoinGame()
{
	if (!ensure(IPAdressField != nullptr))
	{
		return;
	}
	if (MenuInterface != nullptr)
	{
		const FString Address=IPAdressField->GetText().ToString();
		MenuInterface->Join(Address);
	}

}

void UMainMenu::QuitGame()
{
	auto* world = GetWorld();
	if (!ensure(world != nullptr))
		return;
	auto* playerController = world->GetFirstPlayerController();
	if (!ensure(playerController != nullptr))
		return;
	playerController->ConsoleCommand("quit");
}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr))
	{
		return;
	}
	if (!ensure(JoinMenu != nullptr))
	{
		return;
	}
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OpenMainMenu()
{
	if (!ensure(MenuSwitcher != nullptr))
	{
		return;
	}
	if (!ensure(MainMenu != nullptr))
	{
		return;
	}
	MenuSwitcher->SetActiveWidget(MainMenu);
}


