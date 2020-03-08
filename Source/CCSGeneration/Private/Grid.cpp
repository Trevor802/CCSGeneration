// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Engine/World.h"

// Sets default values
AGrid::AGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	m_pGridData = new FGridData();
	m_TileGenerator = new TileGenerator(m_pGridData);
}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();
	m_TileGenerator->Start();
	DrawGrid();
	GetWorld()->GetTimerManager().SetTimer(GenerateTimerHandle, this, &AGrid::OnGenerate, 1.f);
}

void AGrid::BeginDestroy(){
	Super::BeginDestroy();
	delete m_pGridData;
	delete m_TileGenerator;
}

void AGrid::OnGenerate(){
	if (m_TileGenerator->TryGenerate()){
		DrawGrid();
		GetWorld()->GetTimerManager().ClearTimer(GenerateTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(GenerateTimerHandle, this, &AGrid::OnGenerate, 1.f);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	}
}

void AGrid::DrawGrid(){
	FlushPersistentDebugLines(GetWorld());
	FlushDebugStrings(GetWorld());
	for(auto& tile : m_pGridData->GetTiles()){
		DrawTile(*tile);
	}
}

void AGrid::DrawTile(const FTileData& i_tileData){
	DrawDebugLine(GetWorld(), 
		FVector(i_tileData.GetX(), 		i_tileData.GetY(), 		0) * GRID_LENGTH, 
		FVector(i_tileData.GetX()+1, 	i_tileData.GetY(), 		0) * GRID_LENGTH,
		FColor::Red, true, -1.f, 100.f);
	DrawDebugLine(GetWorld(), 
		FVector(i_tileData.GetX()+1, 	i_tileData.GetY(), 		0) * GRID_LENGTH, 
		FVector(i_tileData.GetX()+1, 	i_tileData.GetY()+1, 	0) * GRID_LENGTH,
		FColor::Red, true, -1.f, 100.f);
	DrawDebugLine(GetWorld(), 
		FVector(i_tileData.GetX()+1, 	i_tileData.GetY()+1, 	0) * GRID_LENGTH, 
		FVector(i_tileData.GetX(), 		i_tileData.GetY()+1, 	0) * GRID_LENGTH,
		FColor::Red, true, -1.f, 100.f);
	DrawDebugLine(GetWorld(), 
		FVector(i_tileData.GetX(), 		i_tileData.GetY()+1, 	0) * GRID_LENGTH, 
		FVector(i_tileData.GetX(), 		i_tileData.GetY(), 		0) * GRID_LENGTH,
		FColor::Red, true, -1.f, 100.f);
	FColor pointColor;
	switch(m_pGridData->GetTileState(i_tileData)){
		case ETileState::TS_Null:
			pointColor = NullColor; break;
		case ETileState::TS_Placable:
			pointColor = PlacableColor; break;
		case ETileState::TS_Occupied:
			pointColor = OccupiedColor; break;
	}
	DrawDebugPoint(GetWorld(), 
		FVector(i_tileData.GetX()+0.5f, 	i_tileData.GetY()+0.5f, 0) * GRID_LENGTH,
		10.f, pointColor, true);
	if (m_pGridData->GetTileState(i_tileData) == ETileState::TS_Null)
		return;
	FVector textOffset = FVector(-0.08f, -0.15f, 0);
	DrawDebugString(GetWorld(),
		(FVector(i_tileData.GetX()+0.5f, 	i_tileData.GetY()+0.3f, 0) 
			+ textOffset)* GRID_LENGTH,
		FString::FromInt(i_tileData.FaceIDs[0]), this, IDTextColor);
	DrawDebugString(GetWorld(),
		(FVector(i_tileData.GetX()+0.7f, 	i_tileData.GetY()+0.5f, 0) 
			+ textOffset)* GRID_LENGTH,
		FString::FromInt(i_tileData.FaceIDs[1]), this, IDTextColor);
	DrawDebugString(GetWorld(),
		(FVector(i_tileData.GetX()+0.5f, 	i_tileData.GetY()+0.7f, 0) 
			+ textOffset)* GRID_LENGTH,
		FString::FromInt(i_tileData.FaceIDs[2]), this, IDTextColor);
	DrawDebugString(GetWorld(),
		(FVector(i_tileData.GetX()+0.3f, 	i_tileData.GetY()+0.5f, 0) 
			+ textOffset)* GRID_LENGTH,
		FString::FromInt(i_tileData.FaceIDs[3]), this, IDTextColor);
}