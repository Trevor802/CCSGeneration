// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridData.h"
#include "TileGenerator.h"
#include "Grid.generated.h"

UCLASS()
class CCSGENERATION_API AGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrid();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor NullColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor PlacableColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor OccupiedColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor IDTextColor;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

private:
	FGridData*		m_pGridData;
	TileGenerator* 	m_TileGenerator;
	FTimerHandle GenerateTimerHandle;
	UFUNCTION()
	void OnGenerate();
	static const uint8 GRID_LENGTH = 100;
	void DrawGrid();
	void DrawTile(const FTileData& i_tileData);
};