// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GridData.h"
#include "TileData.h"
#include "TileDataPool.h"
#include "CoreMinimal.h"

/**
 * 
 */
class CCSGENERATION_API TileGenerator
{
public:
	TileGenerator(FGridData* i_pGridData);
	~TileGenerator();
	void Start();
	bool TryGenerate();
private:
	FGridData* pGridData;
	FTileDataPool* pDataPool;
};
