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

#ifndef __CSVData_H__
#define __CSVData_H__

#include "IllustratorSDK.h"
#include "XYArray.h"
#include "MapColorChangerSuites.h"

#define kHabitatMap					"habitat"
#define kVelocityMap				"velocity"
#define kDepthMap					"depth"
#define kSubstrateMap				"substrate"
#define kRefSphereSize				30

const string categoricalDataTypes [2]  = {kHabitatMap , kSubstrateMap};

typedef vector<vector<AIColor>> multiColorArray;

class MapData : public XYArray
{
    public:
		// XYColors[column][row]
		multiColorArray XYColors;
		string MapTitle;
		string MapType;

		// Check if XYData contains of numbers not strings
		boolean MapData::IsNumber(string testString);

		// populate XYColors array based on data in XYArray and swatches present in document
		ASErr BuildColorArray();

		// get color from value using swatch list
		AIColor SelectColorFromNumber(double number, AISwatchGroupRef &swatchGroupRef);

		ASErr SelectColorFromString(string input, AISwatchGroupRef &swatchGroupRef, AIColor* swatchColor);

		// Add extra column to each side
		ASErr ExtrudeSides();

		// Add extra row to each end
		ASErr ExtrudeEnds();

		ASErr FitDataToMesh(int meshColumns, int meshRows);
		double ToDouble(int column, int row);

		// handle to mesh object used for map
		AIArtHandle fMesh;
};

class CSVData 
{
public:

	ASErr ParseCsv(ai::FilePath &ioFilePath);
	ASErr BuildMaps();
	string CheckHeaderForMapType(string header);
	ASErr CreateMapFromColumn(int columnNo, string mapType, string mapTitle);

	vector< MapData > Maps;
private:
	vector< vector<string> > CSVArray;
};
#endif // End MapColorChanger.h
