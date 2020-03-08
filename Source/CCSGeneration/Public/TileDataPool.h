// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "TileData.h"
#include "CoreMinimal.h"

/**
 * 
 */
class CCSGENERATION_API FTileDataPool
{
public:
	FTileDataPool(int8 i_numTile);
	~FTileDataPool();
	FTileData Pop();
	FTileData Peek();
	FORCEINLINE bool IsValidIndex() { return IDIndex >= 0 && IDIndex < TileDataArray.Num(); }

private:
	static const int8 MIN_ID = 1;
	static const int8 MAX_ID = 3;
	int8 IDIndex = 0;
	TArray<FTileData> TileDataArray;
};
