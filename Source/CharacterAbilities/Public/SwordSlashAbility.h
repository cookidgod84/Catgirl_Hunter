// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "SwordSlashAbility.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERABILITIES_API USwordSlashAbility : public UPaperFlipbookComponent
{
	GENERATED_BODY()
public:
	// Sets default values for this component's properties
	USwordSlashAbility();

private:
	UPROPERTY(EditAnywhere)
	UPaperFlipbook* flipbook;
	const float defaulttimeperswing = 1000;
	float currenttimeperswing = defaulttimeperswing;
	float swordswingtimer = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SwingSword();
};
