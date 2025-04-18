// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SimpleEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class ENEMIES_API ASimpleEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
    private:

        virtual void BeginPlay() override;

    public:

        virtual void Tick(float DeltaSeconds) override;
};
