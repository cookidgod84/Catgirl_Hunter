// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameScreenUI.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class CATGIRL_HUNTER_API AMyHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	void UpdateCharacterHearts(int newcharacterhealth);

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameScreenUI> GameScreenUIClass;
	UPROPERTY()
	class UGameScreenUI* GameScreenUIInstance;
};
