// Fill out your copyright notice in the Description page of Project Settings.


#include "GameScreenUI.h"

void UGameScreenUI::SetCurrentHealth(int newcurrenthealth)
{
	HeartBar->SetNewCurrentHealth(newcurrenthealth);
}