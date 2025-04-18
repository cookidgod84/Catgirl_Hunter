// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "UObject/Class.h"
#include "EnemyStructs.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/SphereComponent.h"
#include "BaseEnemy.generated.h"

UCLASS()
class ENEMIES_API ABaseEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseEnemy();
	FEnemyDataStruct enemydata;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbookComponent* flipbookcomponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPawnMovementComponent* movementcomponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* collisioncomponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	virtual void Tick(float DeltaTime) override;
	virtual UPawnMovementComponent* GetMovementComponent() const override;
	virtual void SetEnemyData(FEnemyDataStruct *data);
	virtual void Move(float DeltaTime);
	virtual void Attack();
	virtual void Die();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

UCLASS()
class ENEMIES_API UBaseEnemyMovementComponent : public UPawnMovementComponent {
	GENERATED_BODY()

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
