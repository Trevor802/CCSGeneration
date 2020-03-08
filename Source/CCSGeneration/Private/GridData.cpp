// Fill out your copyright notice in the Description page of Project Settings.


#include "GridData.h"

FGridData::FGridData()
{
    for(int i = 0; i < NUM_GRID; ++i){
        for(int j = 0; j < NUM_GRID; ++j){
            FTileData* tileData = static_cast<FTileData*>(FMemory::Malloc(sizeof(FTileData)));
            new (tileData) FTileData();
            tileData->SetXY(i, j);
            TileDataArray.Emplace(tileData);
        }
    }
    TileStateArray.Init(ETileState::TS_Null, NUM_GRID * NUM_GRID);
}

FGridData::~FGridData()
{
    for(int i = 0; i < NUM_GRID * NUM_GRID; ++i){
        if (TileDataArray[i])
            TileDataArray[i]->~FTileData();
            FMemory::Free(TileDataArray[i]);
    }
}

TArray<FTileData*> FGridData::GetPlacableTiles() const{
    TArray<FTileData*> tiles;
    for(int i = 0; i < TileStateArray.Num(); ++i){
        if (TileStateArray[i] == ETileState::TS_Placable && TileDataArray[i])
            tiles.Emplace(TileDataArray[i]);
    }
    return tiles;
}

FTileData FGridData::GetTile(int8 i_x, int8 i_y) const{
    if (IsValidID(i_x, i_y))
        return *(TileDataArray[GetTileID(i_x, i_y)]);
    else
        return FTileData();
}

ETileState FGridData::GetTileState(const FTileData& i_tileData) const{
    if (IsValidID(i_tileData.GetX(), i_tileData.GetY()))
        return TileStateArray[GetTileID(i_tileData.GetX(), i_tileData.GetY())];
    else
        return ETileState::TS_Null;
}

bool FGridData::PlaceTileData(int8 i_x, int8 i_y, FTileData i_tileData, bool i_forcePlace){
    if (!IsValidID(i_x, i_y))
        return false;
    if (TileStateArray[GetTileID(i_x, i_y)] == ETileState::TS_Occupied)
        return false;
    if (TileStateArray[GetTileID(i_x, i_y)] == ETileState::TS_Null && !i_forcePlace)
        return false;
    TileStateArray[GetTileID(i_x, i_y)] = ETileState::TS_Occupied;
    *TileDataArray[GetTileID(i_x, i_y)] = i_tileData;
    // Up tile
    if (IsValidID(i_x, i_y-1) && TileStateArray[GetTileID(i_x, i_y-1)] != ETileState::TS_Occupied){
        TileStateArray[GetTileID(i_x, i_y-1)] = ETileState::TS_Placable;
        TileDataArray[GetTileID(i_x, i_y-1)]->FaceIDs[2] = i_tileData.FaceIDs[0];
    }
    // Right tile
    if (IsValidID(i_x+1, i_y) && TileStateArray[GetTileID(i_x+1, i_y)] != ETileState::TS_Occupied){
        TileStateArray[GetTileID(i_x+1, i_y)] = ETileState::TS_Placable;
        TileDataArray[GetTileID(i_x+1, i_y)]->FaceIDs[3] = i_tileData.FaceIDs[1];
    }
    // Down tile
    if (IsValidID(i_x, i_y+1) && TileStateArray[GetTileID(i_x, i_y+1)] != ETileState::TS_Occupied){
        TileStateArray[GetTileID(i_x, i_y+1)] = ETileState::TS_Placable;
        TileDataArray[GetTileID(i_x, i_y+1)]->FaceIDs[0] = i_tileData.FaceIDs[2];
    }
    // Left tile
    if (IsValidID(i_x-1, i_y) && TileStateArray[GetTileID(i_x-1, i_y)] != ETileState::TS_Occupied){
        TileStateArray[GetTileID(i_x-1, i_y)] = ETileState::TS_Placable;
        TileDataArray[GetTileID(i_x-1, i_y)]->FaceIDs[1] = i_tileData.FaceIDs[3];
    }
    return true;
}

int8 FGridData::GetTileID(int8 i_x, int8 i_y) const 
{ 
    check(i_x >= 0 && i_x < NUM_GRID);
    check(i_y >= 0 && i_y < NUM_GRID);
    return i_x * NUM_GRID + i_y; 
}