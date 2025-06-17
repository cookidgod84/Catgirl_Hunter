// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PaperSprite.h"
#include "CoreMinimal.h"
#include "MyPaper2DFunctions.generated.h"

/**
 * 
 */
UCLASS()
class CATGIRL_HUNTER_API UMyPaper2DFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Source Size", Keywords = "Source Texture Sprite"), Category = Custom) //Here you can change the keywords, name and category
	static FVector2D GetSourceSize(UPaperSprite* sprite);
};
