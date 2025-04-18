// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleEnemyAIController.h"
#include "EngineUtils.h"  
#include "Engine/TargetPoint.h"  



void ASimpleEnemyAIController::BeginPlay() {
    Super::BeginPlay();


    for (TActorIterator<ATargetPoint> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
        // Same as with the Object Iterator, access the subclass instance with the * or -> operators.  
        ATargetPoint* point = *ActorItr;

        MoveToActor(point);
        break;
    }
}

void ASimpleEnemyAIController::Tick(float DeltaSeconds) {
    Super::Tick(DeltaSeconds);
}