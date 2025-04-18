// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorldGenerator.h"
#include "Templates/Tuple.h"
#include "Math/UnrealMathUtility.h"


// Sets default values
AGameWorldGenerator::AGameWorldGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//load tileset from datatable
	UDataTable* DT_tileset;
	const FString DT_AssetPath = "/Game/Tilesets/demotileset/demotileset.demotileset";
	ConstructorHelpers::FObjectFinder<UDataTable> ASSET(*DT_AssetPath);
	if (ASSET.Object)
	{
		DT_tileset = ASSET.Object;
		for (auto& it : DT_tileset->GetRowMap()) {
			FWorldGenTile* temprow = (FWorldGenTile*)(it.Value);

			tileset.tileweights.Add(temprow->tile_weighting);
			tileset.tilematerial.Add(temprow->tile_material);
			tileset.tilemesh.Add(temprow->tile_mesh);
			tileset.allowed_north_tiles.Add(temprow->allowed_north_tiles);
			tileset.allowed_east_tiles.Add(temprow->allowed_east_tiles);
			tileset.allowed_south_tiles.Add(temprow->allowed_south_tiles);
			tileset.allowed_west_tiles.Add(temprow->allowed_west_tiles);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("tileset not found"));
	}
}

// Called when the game starts or when spawned
void AGameWorldGenerator::BeginPlay()
{
	Super::BeginPlay();
}


void AGameWorldGenerator::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	FVector CharacterPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	TTuple<int, int> CharacterChunk = { FMath::RoundToInt(CharacterPosition.X / (TILES_PER_CHUNK * TILE_SIZE)),FMath::RoundToInt(CharacterPosition.Y / (TILES_PER_CHUNK * TILE_SIZE)) };
	for (int xoffset = -CHUNK_LOAD_SIZE; xoffset < CHUNK_LOAD_SIZE; xoffset++) {
		for (int yoffset = -CHUNK_LOAD_SIZE; yoffset < CHUNK_LOAD_SIZE; yoffset++) {
			TTuple<int, int> offsetchunk = { CharacterChunk.Get<0>() + xoffset, CharacterChunk.Get<1>() + yoffset };
			if (!loaded_chunks.Contains(offsetchunk)) {
				TArray<TArray<int>> northchunk;
				TArray<TArray<int>> eastchunk;
				TArray<TArray<int>> southchunk;
				TArray<TArray<int>> westchunk;
				bool whatchunks[4] = { 0,0,0,0 };
				if (loaded_chunks.Contains({ offsetchunk.Get<0>(), offsetchunk.Get<1>() + 1 })) {
					northchunk = loaded_chunks[{ offsetchunk.Get<0>(), offsetchunk.Get<1>() + 1 }];
					whatchunks[0] = 1;
				}
				if (loaded_chunks.Contains({ offsetchunk.Get<0>() + 1, offsetchunk.Get<1>() })) {
					eastchunk = loaded_chunks[{ offsetchunk.Get<0>() + 1, offsetchunk.Get<1>() }];
					whatchunks[1] = 1;
				}
				if (loaded_chunks.Contains({ offsetchunk.Get<0>(), offsetchunk.Get<1>() - 1 })) {
					southchunk = loaded_chunks[{ offsetchunk.Get<0>(), offsetchunk.Get<1>() - 1 }];
					whatchunks[2] = 1;
				}
				if (loaded_chunks.Contains({ offsetchunk.Get<0>() - 1, offsetchunk.Get<1>() })) {
					westchunk = loaded_chunks[{ offsetchunk.Get<0>() - 1, offsetchunk.Get<1>() }];
					whatchunks[3] = 1;
				}
				TArray<TArray<int>> tempchunk = GenerateChunk(northchunk, eastchunk, southchunk, westchunk, whatchunks);
				loaded_chunks.Add(offsetchunk, tempchunk);
				LoadChunk(tempchunk, offsetchunk.Get<0>(), offsetchunk.Get<1>());
			}
		}
	}
}

// Called every frame
void AGameWorldGenerator::oldTick()
{

	FVector CharacterPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	TTuple<int, int> CharacterChunk = { FMath::RoundToInt(CharacterPosition.X / (TILES_PER_CHUNK * TILE_SIZE)),FMath::RoundToInt(CharacterPosition.X / (TILES_PER_CHUNK * TILE_SIZE)) };
	for (int x = CHUNK_LOAD_SIZE / 2 * -1; x < CHUNK_LOAD_SIZE / 2; x++) {
		for (int y = CHUNK_LOAD_SIZE / 2 * -1; y < CHUNK_LOAD_SIZE / 2; y++) {
			TTuple<int, int> chunk_pos = { CharacterChunk.Get<0>() + x,CharacterChunk.Get<1>() + y };
			if (!loaded_chunks.Contains(chunk_pos)) {
				 //generate chunk
				//get bordering chunks
				TArray<TArray<int>> northchunk;
				TArray<TArray<int>> eastchunk;
				TArray<TArray<int>> southchunk;
				TArray<TArray<int>> westchunk;
				bool whatchunks[4] = { 0,0,0,0 };
				if (loaded_chunks.Contains({ CharacterChunk.Get<0>(), CharacterChunk.Get<1>() + 1 })) {
					northchunk = loaded_chunks[{ CharacterChunk.Get<0>(), CharacterChunk.Get<1>() + 1 }];
					whatchunks[0] = 1;
				}
				if (loaded_chunks.Contains({ CharacterChunk.Get<0>() + 1, CharacterChunk.Get<1>() })) {
					eastchunk = loaded_chunks[{ CharacterChunk.Get<0>() + 1, CharacterChunk.Get<1>() }];
					whatchunks[1] = 1;
				}
				if (loaded_chunks.Contains({ CharacterChunk.Get<0>(), CharacterChunk.Get<1>() - 1 })) {
					southchunk = loaded_chunks[{ CharacterChunk.Get<0>(), CharacterChunk.Get<1>() - 1 }];
					whatchunks[2] = 1;
				}
				if (loaded_chunks.Contains({ CharacterChunk.Get<0>() - 1, CharacterChunk.Get<1>() })) {
					westchunk = loaded_chunks[{ CharacterChunk.Get<0>() - 1, CharacterChunk.Get<1>() }];
					whatchunks[3] = 1;
				}
				
				loaded_chunks.Add(chunk_pos, GenerateChunk(northchunk, eastchunk, southchunk, westchunk, whatchunks));
				
			}
		}
	}
	initial_chunk_loaded = true;
}

TArray<TArray<int>> AGameWorldGenerator::GenerateChunk(TArray<TArray<int>> northchunk, TArray<TArray<int>> eastchunk, TArray<TArray<int>> southchunk, TArray<TArray<int>> westchunk, bool* whatborders)
{
	Fchunk chunk = Fchunk(MAX_FLOAT,tileset);
	int lowest_entropy_pos[2] = { 0,0 };
	if (!initial_chunk_loaded) {
		lowest_entropy_pos[0] = random.RandRange(0, 15);
		lowest_entropy_pos[1] = random.RandRange(0, 15);
	}
	else {
		int northborder[16];
		int eastborder[16];
		int southborder[16];
		int westborder[16];
		//GetBorder(northchunk, 'n', northborder);
		//GetBorder(eastchunk, 'e', eastborder);
		//GetBorder(southchunk, 's', southborder);
		//GetBorder(westchunk, 'w', westborder);

		CollapseBorders(&chunk, northborder, eastborder, southborder, westborder, whatborders);
		FindLowestEntropy(&chunk, lowest_entropy_pos);
	}
	for (int i = 0; i < (TILES_PER_CHUNK * TILES_PER_CHUNK); i++) {

		FindLowestEntropy(&chunk, lowest_entropy_pos);
		FillTile(&chunk, lowest_entropy_pos);
		UpdateFilledTileNeighbours(&chunk, lowest_entropy_pos);
	}
	return chunk.chunkids;
}

void AGameWorldGenerator::CollapseBorders(Fchunk* chunk, int* northborder, int* eastborder, int* southborder, int* westborder, bool* whatborders)
{
	//north
	if (whatborders[0]) {
		for (int i = 0; i < TILES_PER_CHUNK; i++) {
			TSet<int> tempset;
			for (auto& it : chunk->allowed_tiles[TILES_PER_CHUNK - 1][i]) {
				bool allowed = tileset.allowed_north_tiles[it].Contains(northborder[i]);
				if (allowed) {
					tempset.Add(it);
				}
			}
			chunk->allowed_tiles[TILES_PER_CHUNK - 1][i] = tempset;
			chunk->chunkentropies[TILES_PER_CHUNK - 1][i] = CalculateEntropy(chunk->allowed_tiles[TILES_PER_CHUNK - 1][i]);
		}
	}
	//east
	if (whatborders[1]) {
		for (int i = 0; i < TILES_PER_CHUNK; i++) {
			TSet<int> tempset;
			for (auto& it : chunk->allowed_tiles[i][TILES_PER_CHUNK - 1]) {
				bool allowed = tileset.allowed_east_tiles[it].Contains(eastborder[i]);
				if (allowed) {
					tempset.Add(it);
				}
			}
			chunk->allowed_tiles[i][TILES_PER_CHUNK - 1] = tempset;
			chunk->chunkentropies[i][TILES_PER_CHUNK - 1] = CalculateEntropy(chunk->allowed_tiles[i][TILES_PER_CHUNK - 1]);
		}
	}
	//south
	if (whatborders[2]) {
		for (int i = 0; i < TILES_PER_CHUNK; i++) {
			TSet<int> tempset;
			for (auto& it : chunk->allowed_tiles[0][i]) {
				bool allowed = tileset.allowed_south_tiles[it].Contains(southborder[i]);
				if (allowed) {
					tempset.Add(it);
				}
			}
			chunk->allowed_tiles[0][i] = tempset;
			chunk->chunkentropies[0][i] = CalculateEntropy(chunk->allowed_tiles[0][i]);
		}
	}
	//west
	if (whatborders[3]) {
		for (int i = 0; i <TILES_PER_CHUNK; i++) {
			TSet<int> tempset;
			for (auto& it : chunk->allowed_tiles[i][0]) {
				bool allowed = tileset.allowed_west_tiles[it].Contains(westborder[i]);
				if (allowed) {
					tempset.Add(it);
				}
			}
			chunk->allowed_tiles[i][0] = tempset;
			chunk->chunkentropies[i][0] = CalculateEntropy(chunk->allowed_tiles[i][0]);
		}
	}
}

void AGameWorldGenerator::UpdateFilledTileNeighbours(Fchunk* chunk, int* filledtilepos)
{
	int northpos[2] = { filledtilepos[0],filledtilepos[1] - 1 };
	int eastpos[2] = { filledtilepos[0] + 1,filledtilepos[1] };
	int southpos[2] = { filledtilepos[0],filledtilepos[1] + 1 };
	int westpos[2] = { filledtilepos[0] - 1,filledtilepos[1] };

	//north tiles
	if (filledtilepos[1] > 1) {
		TSet<int> tempset;
		for (auto& it : chunk->allowed_tiles[northpos[0]][northpos[1]]) {
			bool allowed = tileset.allowed_south_tiles[it].Contains(chunk->chunkids[filledtilepos[0]][filledtilepos[1]]);
			if (allowed) {
				tempset.Add(it);
			}
		}
		chunk->allowed_tiles[northpos[0]][northpos[1]] = tempset;
	}

	//east tiles
	if (filledtilepos[0] < TILES_PER_CHUNK - 1) {
		TSet<int> tempset;
		for (auto& it : chunk->allowed_tiles[eastpos[0]][eastpos[1]]) {
			bool allowed = tileset.allowed_west_tiles[it].Contains(chunk->chunkids[filledtilepos[0]][filledtilepos[1]]);
			if (allowed) {
				tempset.Add(it);
			}
		}
		chunk->allowed_tiles[eastpos[0]][eastpos[1]] = tempset;
	}

	//south tiles
	if (filledtilepos[1] < TILES_PER_CHUNK - 1) {
		TSet<int> tempset;
		for (auto& it : chunk->allowed_tiles[southpos[0]][southpos[1]]) {
			bool allowed = tileset.allowed_north_tiles[it].Contains(chunk->chunkids[filledtilepos[0]][filledtilepos[1]]);
			if (allowed) {
				tempset.Add(it);
			}
		}
		chunk->allowed_tiles[southpos[0]][southpos[1]] = tempset;
	}

	//west tiles
	if (filledtilepos[0] > 1) {
		TSet<int> tempset;
		for (auto& it : chunk->allowed_tiles[westpos[0]][westpos[1]]) {
			bool allowed = tileset.allowed_east_tiles[it].Contains(chunk->chunkids[filledtilepos[0]][filledtilepos[1]]);
			if (allowed) {//greater than 1 not zero because the universal tile will always be valid
				tempset.Add(it);
			}
		}
		chunk->allowed_tiles[westpos[0]][westpos[1]] = tempset;
	}
}

void AGameWorldGenerator::FillTile(Fchunk* chunk, int* pos)
{
	//set as universal tile if no other options are available
	if (chunk->allowed_tiles[pos[0]][pos[1]].Num() == 1) {//only universal tile is left
		chunk->chunkids[pos[0]][pos[1]] = tileset.tileweights.Num() - 1;
		chunk->allowed_tiles[pos[0]][pos[1]] = { chunk->chunkids[pos[0]][pos[1]] };
		chunk->chunkentropies[pos[0]][pos[1]] = MAX_FLOAT;
	}
	else {
		//otherwise pick weighted random tile from options
		float tileweightsum = 0.0;
		for (auto& it : chunk->allowed_tiles[pos[0]][pos[1]]) {
			tileweightsum += tileset.tileweights[it];
		}
		float randomnum = random.RandRange(0.0, tileweightsum);

		float cdf = 0;
		for (auto& it : chunk->allowed_tiles[pos[0]][pos[1]]) {
			cdf = cdf + tileset.tileweights[it];
			if (cdf >= randomnum) {
				chunk->chunkids[pos[0]][pos[1]] = it;
				chunk->allowed_tiles[pos[0]][pos[1]] = { chunk->chunkids[pos[0]][pos[1]] };
				chunk->chunkentropies[pos[0]][pos[1]] = MAX_FLOAT;
				return;
			}
		}
	}
}

float AGameWorldGenerator::CalculateEntropy(TSet<int> allowed_tiles)
{
	float temp = 0.0;
	for (auto it = allowed_tiles.CreateIterator(); it; ++it) {
		if (*it < tileset.tileweights.Num() - 1) {
			int tileweight = tileset.tileweights[*it];
			temp = temp + tileweight * log(tileweight);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("entropy out of bounds %i"), *it);
		}

	}
	return temp;
}

void AGameWorldGenerator::FindLowestEntropy(Fchunk* chunk, int* lowestpos)
{
	float lowestval = MAX_FLOAT;
	for (int x = 0; x < TILES_PER_CHUNK; x++) {
		for (int y = 0; y < TILES_PER_CHUNK; y++) {
			if (chunk->chunkentropies[x][y] < lowestval) {
				lowestval = chunk->chunkentropies[x][y];
				lowestpos[0] = x;
				lowestpos[1] = y;
			}
		}
	}
}

void AGameWorldGenerator::GetBorder(TArray<TArray<int>> chunk, char border_code, int* borderarray)
{
	if (border_code == 'n') {
		for (int i = 0; i < TILES_PER_CHUNK; i++) {
			borderarray[i] = chunk[i][TILES_PER_CHUNK - 1];
		}
	}
	else if (border_code == 'e') {
		for (int i = 0; i < TILES_PER_CHUNK; i++) {
			borderarray[i] = chunk[TILES_PER_CHUNK - 1][i];
		}
	}
	else if (border_code == 's') {
		for (int i = 0; i < TILES_PER_CHUNK; i++) {
			borderarray[i] = chunk[i][0];
		}
	}
	else if (border_code == 'w') {
		for (int i = 0; i < TILES_PER_CHUNK; i++) {
			borderarray[i] = chunk[0][i];
		}
	}
}

void AGameWorldGenerator::LoadChunk(TArray<TArray<int>> chunk, int xchunk, int ychunk) {
	int xchunkpos = xchunk * TILES_PER_CHUNK * TILE_SIZE;
	int ychunkpos = ychunk * TILES_PER_CHUNK * TILE_SIZE;
	for (int x = 0; x < TILES_PER_CHUNK; x++) {
		for (int y = 0; y < TILES_PER_CHUNK; y++) {
			UStaticMeshComponent* StaticMeshComponent = NewObject<UStaticMeshComponent>(this);
			StaticMeshComponent->SetStaticMesh(tileset.tilemesh[chunk[x][y]]);
			StaticMeshComponent->SetNotifyRigidBodyCollision(false);
			StaticMeshComponent->SetWorldScale3D(FVector(0.1, 0.1, 0.1));
			StaticMeshComponent->RegisterComponentWithWorld(GetWorld());
			StaticMeshComponent->SetMaterial(0, tileset.tilematerial[chunk[x][y]]);
			
			FVector tilelocation(xchunkpos + x * TILE_SIZE, ychunkpos + y * TILE_SIZE,-200);
			//FVector tilelocation(0, 0, -200);
			StaticMeshComponent->SetWorldLocation(tilelocation);
		}
	}
	
}