// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "CrackedVaseEnemy.h"
#include "BaseEnemy.h"

// Sets default values
AEnemyManager::AEnemyManager()
{

	PrimaryActorTick.bCanEverTick = true;
	//load tileset from datatable
	UDataTable* DT_tileset;
	const FString DT_AssetPath = "/Game/Enemies/Enemydata.Enemydata";
	ConstructorHelpers::FObjectFinder<UDataTable> ASSET(*DT_AssetPath);
	if (ASSET.Object)
	{
		DT_tileset = ASSET.Object;
		for (auto& it : DT_tileset->GetRowMap()) {
			FEnemyDataStruct* temprow = (FEnemyDataStruct*)(it.Value);
			
			enemybasestats.Add(it.Key, *temprow);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("enemy data not found"));
	}
}



// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();	
}



// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//
	spawnpoints += 2;

	if (spawnpoints > 300) {
		SpawnEnemy("BaseEnemy");
		//SpawnEnemy("CrackedVase");
		spawnpoints = 0;
	}
	
}

void AEnemyManager::SpawnEnemy(FName enemyname) {
	FVector CharacterPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	int randomoptions[] = { -1,1 };
	float xspawnpos = CharacterPosition.X + randomoptions[FMath::RandRange(0, 1)] * spawndistance;
	float yspawnpos = CharacterPosition.Y + randomoptions[FMath::RandRange(0, 1)] * spawndistance;
	float zspawnpos = -100.0;
	FTransform transform(FQuat(0.0,0.0,90.0,90.0), FVector(xspawnpos, yspawnpos, zspawnpos), FVector(1));
	if (enemyname == "BaseEnemy") {
		FEnemyDataStruct* temp = enemybasestats.Find(enemyname);
		ABaseEnemy* enemy = GetWorld()->SpawnActorDeferred<ABaseEnemy>(ABaseEnemy::StaticClass(), transform);
		UE_LOG(LogTemp, Warning, TEXT("calling setup"));
		enemy->SetEnemyData(temp);
		enemy->FinishSpawning(transform);
	}
	else if (enemyname == "CrackedVase") {
		FEnemyDataStruct* temp = enemybasestats.Find(enemyname);
		ACrackedVaseEnemy* enemy = GetWorld()->SpawnActorDeferred<ACrackedVaseEnemy>(ACrackedVaseEnemy::StaticClass(), transform);
		enemy->SetEnemyData(temp);
		enemy->FinishSpawning(transform);
	}
	
}

