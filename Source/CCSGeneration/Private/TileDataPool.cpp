// Fill out your copyright notice in the Description page of Project Settings.


#include "TileDataPool.h"

FTileDataPool::FTileDataPool(int8 i_numTile)
{
    for(int i = 0; i < i_numTile; ++i){
        TileDataArray.Emplace(FTileData(
            FMath::RandRange(MIN_ID, MAX_ID),
            FMath::RandRange(MIN_ID, MAX_ID),
            FMath::RandRange(MIN_ID, MAX_ID),
            FMath::RandRange(MIN_ID, MAX_ID)));
    }
}

FTileDataPool::~FTileDataPool()
{
}

FTileData FTileDataPool::Pop(){
    check(IsValidIndex());
    return TileDataArray[IDIndex++];
}

FTileData FTileDataPool::Peek(){
    check(IsValidIndex());
    return TileDataArray[IDIndex];
}