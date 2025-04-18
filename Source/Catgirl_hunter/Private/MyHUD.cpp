// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "UObject/ConstructorHelpers.h"

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("base hud called"));
	GameScreenUIInstance = CreateWidget<UGameScreenUI>(GetWorld()->GetFirstPlayerController(), GameScreenUIClass);
	GameScreenUIInstance->AddToViewport();
}

void AMyHUD::UpdateCharacterHearts(int newcharacterhealth)
{
	GameScreenUIInstance->SetCurrentHealth(newcharacterhealth);
}
