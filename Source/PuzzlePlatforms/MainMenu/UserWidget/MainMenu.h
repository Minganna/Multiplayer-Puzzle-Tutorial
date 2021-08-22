// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu/Interface/MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */
class UButton;
class UWidgetSwitcher;
class UEditableTextBox;
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
public: 
	void SetMenuInterface(IMenuInterface* MenuInterface);
	void SetUp();
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

protected:
	virtual bool Initialize() override;
	

private:
	UPROPERTY(meta = (BindWidget))
	UButton* HostButton;
	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;
	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;
	UPROPERTY(meta = (BindWidget))
	UButton* JoinGameButton;
	

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	UWidget* MainMenu;
	UPROPERTY(meta = (BindWidget))
	UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* IPAdressField;


	UFUNCTION()
	void HostClicked();
	UFUNCTION()
	void OpenJoinMenu();
	UFUNCTION()
	void OpenMainMenu();
	UFUNCTION()
	void JoinGame();


	IMenuInterface* MenuInterface;
};
