// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TilesetStructs.h"
#include "GameWorldGenerator.generated.h"


UCLASS(Blueprintable, BlueprintType)
class WORLD_GEN_API AGameWorldGenerator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGameWorldGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	Ftileset tileset;
	bool initial_chunk_loaded = false;
	static const int TILES_PER_CHUNK = 16;
	const int TILE_SIZE = 20;
	const int CHUNK_LOAD_SIZE = 2; //how many chunks away from the character chunks will load
	TMap<TTuple<int, int>, TArray<TArray<int>>> loaded_chunks;
	inline static float MAX_FLOAT = 9999999999.0;
	inline static float MIN_FLOAT = -9999999999.0;
	FRandomStream random;

	struct Fchunk {

	public:

		TArray<TArray<int>> chunkids;
		TArray<TArray<float>> chunkentropies;
		TArray<TArray<TSet<int>>> allowed_tiles;
		Fchunk(float max_float,Ftileset tileset) {
			TSet<int> temp;
			for (int i = 0; i < tileset.tileweights.Num(); i++) {
				temp.Add(i);
			}
			for (int x = 0; x < TILES_PER_CHUNK; x++) {
				TArray<int> tempids = TArray<int>();
				TArray<float> tempentropies = TArray<float>();
				TArray<TSet<int>> tempallowed = TArray<TSet<int>>();
				for (int y = 0; y < TILES_PER_CHUNK; y++) {
					tempids.Add(-1);
					tempentropies.Add(max_float / 10.0);
					tempallowed.Emplace(temp);
				}
				chunkids.Emplace(tempids);
				chunkentropies.Emplace(tempentropies);
				allowed_tiles.Emplace(tempallowed);
			}
		}
	};

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void oldTick();
private:
	TArray<TArray<int>> GenerateChunk(TArray<TArray<int>> northchunk, TArray<TArray<int>> eastchunk, TArray<TArray<int>> southchunk, TArray<TArray<int>> westchunk, bool* whatborders);
	void CollapseBorders( Fchunk* chunk, int* northborder, int* eastborder, int* southborder, int* westborder, bool* whatborders);
	void UpdateFilledTileNeighbours(Fchunk* chunk,  int* filledtilepos);
	void FillTile(Fchunk* chunk, int* pos);
	float CalculateEntropy(TSet<int> allowed_tiles);
	void FindLowestEntropy(Fchunk* chunk, int* lowestpos);
	void GetBorder(TArray<TArray<int>> chunk, char border_code, int* borderarray);
	void LoadChunk(TArray<TArray<int>> chunk,int xchunk,int ychunk);
};





