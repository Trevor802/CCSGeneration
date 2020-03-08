// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "TileData.h"
#include "CoreMinimal.h"

/**
 * 
 */
enum class ETileState : int8
{
	TS_Null, TS_Placable, TS_Occupied
};

class CCSGENERATION_API FGridData
{
public:
	FGridData();
	~FGridData();
	bool PlaceTileData(int8 i_x, int8 i_y, FTileData i_tileData, bool i_forcePlace = false);
	int8 GetTileID(int8 i_x, int8 i_y) const;
	FORCEINLINE bool IsValidID(int8 i_x, int8 i_y) const 
		{return i_x >= 0 && i_x < NUM_GRID && i_y >= 0 && i_y < NUM_GRID;}
	static const uint8 NUM_GRID = 10;
	TArray<FTileData*> GetPlacableTiles() const;
	FTileData 	GetTile(int8 i_x, int8 i_y) const;
	ETileState 	GetTileState(const FTileData& i_tileData) const;
	FORCEINLINE TArray<FTileData*, TInlineAllocator<NUM_GRID * NUM_GRID>> GetTiles() const 
		{ return TileDataArray; }
private:
	TArray<FTileData*, TInlineAllocator<NUM_GRID * NUM_GRID>> TileDataArray;
	TArray<ETileState, TInlineAllocator<NUM_GRID * NUM_GRID>> TileStateArray;
};
