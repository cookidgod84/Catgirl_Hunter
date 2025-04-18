// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameScreenUI.generated.h"

UCLASS()
class CATGIRL_HUNTER_API UHeartBar : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(blueprintimplementableevent)
	void SetNewCurrentHealth(int newcurrenthealth);
};

/**
 * 
 */
UCLASS()
class CATGIRL_HUNTER_API UGameScreenUI : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetCurrentHealth(int newcurrenthealth);
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UHeartBar* HeartBar;
};


