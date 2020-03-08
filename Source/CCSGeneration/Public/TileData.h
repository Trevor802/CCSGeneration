// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

struct FTileData{
public:
	FTileData(){
		FaceIDs.Init(0, NUM_FACE);
	}
	FTileData(int8 i_up, int8 i_right, int8 i_down, int8 i_left){
		FaceIDs.Add(i_up);
		FaceIDs.Add(i_right);
		FaceIDs.Add(i_down);
		FaceIDs.Add(i_left);
	}
	FTileData& operator=(const FTileData other){
		for(int i = 0; i < NUM_FACE; ++i){
			FaceIDs[i] = other.FaceIDs[i];
		}
		return *this;
	}
	bool TryMatchTile(const FTileData& i_target, int8 & o_bitShift) const;
	void ShiftFaceID(int8 i_bitToShift);
	FORCEINLINE int8 FirstIDIndex() const {
		for(int i = 0; i < NUM_FACE; ++i){
			if (FaceIDs[i] != NULL_ID) return i;
		}
		return -1;
	}
	FORCEINLINE bool IsNull() const {
		return FirstIDIndex() == -1;
	}
	static const int8 	NUM_FACE = 4;
	static const int8 	NULL_ID = 0;
	TArray<int8, TInlineAllocator<NUM_FACE>> 	FaceIDs;
	FORCEINLINE void SetXY(int8 i_x, int8 i_y) { x = i_x; y = i_y;}
	FORCEINLINE int8 GetX() const {return x;}
	FORCEINLINE int8 GetY() const {return y;}
private:
	int8	x = 0;
	int8	y = 0;
};