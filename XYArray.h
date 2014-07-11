
//========================================================================================
//  
//  $File: //ai/ai18/devtech/sdk/public/samplecode/MapColorChanger/Source/MapColorChanger.h $
//
//  $Revision: #1 $
//
//  Copyright 1987 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __XYArray_H__
#define __XYArray_H__

#include "IllustratorSDK.h"

typedef vector<vector<string>> multiArray;

class XYArray 
{
public:
	// xyArray[column][row]
	multiArray xyArray;

	/* Splits single column of data into multiple columns
	   1, 2, 3, 4, 5 -> Spread(2) = (1, 2), (3, 4), (5, ) */
	ASErr Spread(int width);

	// returns size of array(Columns x rows)
	int Size();

	void FlipV();

	void FlipH();

};
#endif // End MapColorChanger.h
