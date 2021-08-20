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
	UButton* Host;
	UPROPERTY(meta = (BindWidget))
	UButton* Join;
	UFUNCTION()
	void HostClicked();

	IMenuInterface* MenuInterface;
};
