// Fill out your copyright notice in the Description page of Project Settings.

#include "TileGenerator.h"

TileGenerator::TileGenerator(FGridData* i_pGridData)
{
    pGridData = i_pGridData;
    pDataPool = new FTileDataPool(20);
}

TileGenerator::~TileGenerator()
{
    delete pDataPool;
}

void TileGenerator::Start(){
    pGridData->PlaceTileData(FGridData::NUM_GRID / 2, FGridData::NUM_GRID / 2, pDataPool->Pop(), true);
}

bool TileGenerator::TryGenerate(){
    if (!pDataPool->IsValidIndex())
        return false;
    // Get placable tileGrids
    auto tileGrids = pGridData->GetPlacableTiles();
    // Filtered by matching pattern
    TArray<int8> bitShiftArray;
    tileGrids = tileGrids.FilterByPredicate([&](const FTileData* tileData){
        int8 bitShift = 0;
        bool result = tileData->TryMatchTile(pDataPool->Peek(), bitShift);
        if (result)
            bitShiftArray.Emplace(bitShift);
        return result;
    });
    // Randomly choose one
    int8 randomIndex = FMath::RandRange(0, tileGrids.Num()-1);
    auto tileGrid = tileGrids[randomIndex];
    // Get tile data, shift data
    FTileData tile = pDataPool->Pop();
    tile.ShiftFaceID(bitShiftArray[randomIndex]);
    pGridData->PlaceTileData(tileGrid->GetX(), tileGrid->GetY(), tile);
    return true;
}