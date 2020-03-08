// Fill out your copyright notice in the Description page of Project Settings.


#include "TileData.h"
bool FTileData::TryMatchTile(const FTileData& i_target, int8 & o_bitShift) const {
		// 1. Find starting position
		int8 myStart = 0;
		for (myStart; myStart < NUM_FACE; ++myStart)
		{
			int8 firstID = i_target.FirstIDIndex();
			// 2. Compare from the starting point
			int8 start = myStart;
			while (FaceIDs[start] == i_target.FaceIDs[firstID] 
                || i_target.FaceIDs[firstID] == NULL_ID 
                || FaceIDs[start] == NULL_ID){
                    start = ++start % NUM_FACE;
                    firstID++;
                    if (firstID == NUM_FACE) {
						o_bitShift = myStart;
                        return true;
					}
			}
		}
		if (myStart == NUM_FACE)
			return false;

		return false;
}

void FTileData::ShiftFaceID(int8 i_bitToShift){
	if (i_bitToShift % NUM_FACE == 0) return;
	// 1. Copy face array
	TArray<int8, TInlineAllocator<NUM_FACE>> newFaceIDs = FaceIDs;
	
	// 2. Shift faces
	for (int8 i = 0; i < NUM_FACE; i++)
	{
		FaceIDs[i] = newFaceIDs[(i-i_bitToShift+NUM_FACE) % NUM_FACE];
	}
}