// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TilesetStructs.generated.h"

USTRUCT(BlueprintType)
struct Ftileset {
	GENERATED_BODY()
	TArray<float> tileweights;
	TArray<UMaterialInterface*> tilematerial;
	TArray<UStaticMesh*> tilemesh;
	TArray<TSet<int>> allowed_north_tiles;
	TArray<TSet<int>> allowed_east_tiles;
	TArray<TSet<int>> allowed_south_tiles;
	TArray<TSet<int>> allowed_west_tiles;
	
};

typedef Ftileset Ftileset;

USTRUCT(BlueprintType)
struct FWorldGenTile : public FTableRowBase {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int tile_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialInterface* tile_material;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* tile_mesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float tile_weighting;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSet<int> allowed_north_tiles;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSet<int> allowed_east_tiles;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSet<int> allowed_south_tiles;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSet<int> allowed_west_tiles;
};
