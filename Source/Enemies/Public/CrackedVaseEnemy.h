// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "CrackedVaseEnemy.generated.h"

/**
 * 
 */
UCLASS()
class ENEMIES_API ACrackedVaseEnemy: public ABaseEnemy {
	GENERATED_BODY()
public:
	ACrackedVaseEnemy();
	virtual void Tick(float DeltaTime) override;
private:
	

	
};
