// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainMenu/UserWidget/MenuWidget.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
class UButton;
UCLASS()
class PUZZLEPLATFORMS_API UInGameMenu : public UMenuWidget
{
	GENERATED_BODY()
protected:
	virtual bool Initialize() override;
private:
	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;
	UPROPERTY(meta = (BindWidget))
	UButton* MenuButton;

	UFUNCTION()
	void CancelPressed();
	UFUNCTION()
	void QuitPressed();

};
