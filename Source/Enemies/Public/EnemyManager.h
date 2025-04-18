// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyStructs.h"
#include "EnemyManager.generated.h"

UCLASS()
class ENEMIES_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TMap<FName, FEnemyDataStruct> enemybasestats;
	//points go up every tick manager spends points to summon enemies
	int spawnpoints = 0;
	float deltatimesum = 0.0;
	//distance to spawn enemies from
	float spawndistance = 200;
	void SpawnEnemy(FName enemy);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
