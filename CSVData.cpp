//========================================================================================
//  
//  $File: //ai/ai18/devtech/sdk/public/samplecode/MapColorChanger/Source/MapColorChanger.cpp $
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

//	Import and structure csv map data.

#include "IllustratorSDK.h"
#include "MapColorChanger.h"
#include "MapColorChangerSuites.h"
#include "CSVData.h"

// Converts cell to numeric value. i.e. depths to float, substrates to int based on categories
double MapData::ToDouble(int column, int row){
	return atof(this->xyArray[column][row].c_str());
}

// checks whether this map data type is based on numbers by checking first data cell for digits
boolean MapData::IsNumber(string testString){
	if (std::string::npos != testString.find_first_of("0123456789")){
		return true;
	}else{
		return false;
	}
}

ASErr MapData::ExtrudeSides(){
	this->xyArray.insert(this->xyArray.begin(), this->xyArray[0]);
	this->xyArray.push_back(this->xyArray[this->xyArray.size()-1]);

	return kNoErr;
}
ASErr MapData::ExtrudeEnds(){
	for (int i = 0; i < this->xyArray.size(); i++)
	{
		this->xyArray[i].insert(this->xyArray[i].begin(), this->xyArray[i][0]);
		this->xyArray[i].push_back(this->xyArray[i][this->xyArray[i].size()-1]);
	}

	return kNoErr;
}


ASErr MapData::FitDataToMesh(int meshColumns, int meshRows){
	// Does data equal dimenions?
	// +1 because mesh columns, rows = patches not vertexes
	if(this->Size() == (meshColumns*meshRows)){
		this->Spread(meshColumns);
	}else if(this->Size() == ((meshColumns-2)*meshRows)){
		this->Spread(meshColumns-2);
		this->ExtrudeSides();
	}else if(this->Size() == ((meshColumns-2)*(meshRows-2))){
		this->Spread(meshColumns-2);
		this->ExtrudeSides();
		this->ExtrudeEnds();
	}else if(this->Size() == (meshColumns*(meshRows-2))){
		this->Spread(meshColumns);
		this->ExtrudeEnds();
	}else{
		//cant match data to mesh
		char alertMessage [50];
		sprintf (alertMessage, "Data doesn't fit mesh. Mesh(%d,%d) data(%d)", meshColumns, meshRows, this->Size());
		
		sAIUser->ErrorAlert(ai::UnicodeString(alertMessage));

		return kBadParameterErr;
	}

	return kNoErr;
}

AIColor MapData::SelectColorFromNumber(double number, AISwatchGroupRef &swatchGroupRef){
	// fetch colors where there is an existing swatch group for map type.
	int swatchCount = sAISwatchGroup->CountSwatches(swatchGroupRef);
	double boundryBar = 0.0;
	AIColor swatchColor;

	// for each swatch
	for (int i = 0; i < swatchCount; i++) {
		// get name
		AISwatchRef swatchRef = sAISwatchGroup->GetNthSwatch(swatchGroupRef, i);

		double swatchLowerBoundry;
		ai::UnicodeString swatchName;

		// convert name to double
		sAISwatchList->GetSwatchName(swatchRef, swatchName);
		swatchLowerBoundry = atof(swatchName.as_UTF8().c_str());

		if(boundryBar <= swatchLowerBoundry && number >= swatchLowerBoundry){
			sAISwatchList->GetAIColor(swatchRef, &swatchColor);

			boundryBar = swatchLowerBoundry;
		}
	}

	return swatchColor;
}

ASErr MapData::SelectColorFromString(string input, AISwatchGroupRef &swatchGroupRef, AIColor* swatchColor){
	// fetch colors where there is an existing swatch group for map type.
	int swatchCount = sAISwatchGroup->CountSwatches(swatchGroupRef);
	boolean found = false;
	ASErr error = kNoErr;

	// for each swatch
	for (int i = 0; i < swatchCount; i++) {
		// get name
		AISwatchRef swatchRef = sAISwatchGroup->GetNthSwatch(swatchGroupRef, i);

		ai::UnicodeString swatchName;

		// convert name to double
		sAISwatchList->GetSwatchName(swatchRef, swatchName);

		if(swatchName.toLower() == ai::UnicodeString(input).toLower()){
			sAISwatchList->GetAIColor(swatchRef, swatchColor);

			found = true;
		}
	}

	if(!found){
		// program hasnt returned a color
		char alertMessage [100];
		sprintf (alertMessage, "Couldn't find color for data value \"%s\"", input.c_str());
		
		sAIUser->ErrorAlert(ai::UnicodeString(alertMessage));
		return kInvalidFormatErr;
	}else{
		return error;
	}
}

ASErr MapData::BuildColorArray()
{
	AISwatchGroupRef swatchGroupRef = sAISwatchGroup->GetSwatchGroupByName(NULL,ai::UnicodeString(this->MapType));
	ASErr error = kNoErr;

	multiColorArray newXYColors(this->xyArray.size());

	// for each value in xydata
	for (int column = 0; column < this->xyArray.size(); column++){

		newXYColors[column].resize(this->xyArray[column].size());
		for(int row = 0; row < this->xyArray[column].size(); row++) {
			// foreach swatch
			if(swatchGroupRef){
				
				if(this->IsNumber(this->xyArray[column][0])){
					newXYColors[column][row] = this->SelectColorFromNumber(this->ToDouble(column, row), swatchGroupRef);
				}else{
					error = this->SelectColorFromString(this->xyArray[column][row], swatchGroupRef, &newXYColors[column][row]);
					if(error){goto cancel;};
				}
			}else{
				char alertMessage [50];
				sprintf (alertMessage, "Couldn't find swatch group for %s", this->MapType.c_str());
		
				sAIUser->ErrorAlert(ai::UnicodeString(alertMessage));
				return kInvalidFormatErr;
			}
		}
	}

	this->XYColors = newXYColors;
cancel:
	return error;
}

ASErr CSVData::ParseCsv(ai::FilePath &ioFilePath)
{
	ifstream file; // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/
	file.open(ioFilePath.GetFullPath().as_WCHARStr()); 
	string value;

    string line, field;

	vector<vector<string>> CSVArray;
    vector<string> v;                // array of values for one line only

    while ( getline(file,line) )    // get next line in file
    {
        v.clear();
        stringstream ss(line);

		// check is csv line contains any data
		if(string::npos != line.find_first_not_of(",")){

			while (getline(ss,field,','))  // break line into comma delimitted fields
			{
				v.push_back(field);  // add each field to the 1D array
			}

			this->CSVArray.push_back(v);  // add the 1D array to the 2D array
		}
    }
	
	file.close(); 

	return ASErr();
}

ASErr CSVData::BuildMaps()
{

	// For each map (data column)
	for(int i = 0; i != this->CSVArray[0].size(); i++) 
	{
		string mapType = CheckHeaderForMapType(this->CSVArray[0][i]);
		string mapTitle = this->CSVArray[0][i];

		if(mapType != "")
		{
			this->CreateMapFromColumn(i, mapType, mapTitle);
		}
	}

	return ASErr();
}

string CSVData::CheckHeaderForMapType(string header)
{
	// make lowercase to avoid capital related non matching
	transform(header.begin(), header.end(), header.begin(), tolower);

	if (header.find(kHabitatMap) != std::string::npos) {
		return kHabitatMap;
	}
/*	if (header.find(kSubstrateMap) != std::string::npos) {
		return kSubstrateMap;
	}*/
	if (header.find(kVelocityMap) != std::string::npos) {
		return kVelocityMap;
	}
	if (header.find(kDepthMap) != std::string::npos) {
		return kDepthMap;
	}

	return "";
}

ASErr CSVData::CreateMapFromColumn(int columnNo, string mapType, string mapTitle)
{

	// fetch single column of data
	multiArray dataColumn(1);

	// i = 1 to skip header row
	// cut out data frim single column
	for (int i = 1; i < this->CSVArray.size(); i++)
	{
		if(columnNo < this->CSVArray[i].size() && this->CSVArray[i][columnNo] != ""){
			dataColumn[0].push_back( this->CSVArray[i][columnNo]);
		}else{
			char alertMessage [50];
			sprintf (alertMessage, "Missing data point from column(%s) line %d", mapTitle, columnNo);
		
			sAIUser->ErrorAlert(ai::UnicodeString(alertMessage));
		}
	}

		// create map
	MapData NewMap;
	NewMap.xyArray = dataColumn;
	NewMap.MapTitle = mapTitle;
	NewMap.MapType = mapType;

	this->Maps.push_back(NewMap);

	return ASErr();
}
