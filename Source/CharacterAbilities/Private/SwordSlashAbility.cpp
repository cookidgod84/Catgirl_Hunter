// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordSlashAbility.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values for this component's properties
USwordSlashAbility::USwordSlashAbility()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UPaperFlipbook> ASSET(TEXT("/Game/characterabilitysprites/swordslash.swordslash"));
	flipbook = ASSET.Object;
	Stop();//stops flipbook playback
	SetFlipbook(flipbook);
	SetLooping(false);
}


// Called when the game starts
void USwordSlashAbility::BeginPlay()
{
	Super::BeginPlay();


}


// Called every frame
void USwordSlashAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	swordswingtimer += DeltaTime;
	while (swordswingtimer >= currenttimeperswing) {
		swordswingtimer -= currenttimeperswing;
		SwingSword();
	}
	// ...
}

void USwordSlashAbility::SwingSword()
{
	SetNewTime(0);
	Play();
}