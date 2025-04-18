// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbook.h"
#include "UObject/NoExportTypes.h"
#include "EnemyStructs.generated.h"

USTRUCT(BlueprintType)
struct FEnemyDataStruct : public FTableRowBase {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float base_health;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float base_EXP_value;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int damage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float base_speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int cost_to_spawn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperFlipbook* move_flipbook;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperFlipbook* attack_flipbook;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperFlipbook* die_flipbook;

};

typedef FEnemyDataStruct FEnemyDataStruct;
