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

//	Twirl anchor points around the path's center.

#include "IllustratorSDK.h"
#include "MapColorChanger.h"
#include "MapColorChangerSuites.h"


ASErr MapColorChanger::GoRecolor(AIMenuMessage* pb)
{
	AIErr error = kNoErr;
	
    
	AIArtHandle **matchingArt = NULL;
	ai::int32 numMatches;

	error = sAIMatchingArt->GetSelectedArt(&matchingArt,&numMatches);
	if ( error ) goto errorTag;

	AIArtHandle mesh = (*matchingArt)[1];
	AIMeshVertexIterator vertex;

	error = sAIMesh->GetStartVertex(mesh, &vertex);
	if ( error ) goto errorTag;


	// Loop through mesh vertex by vertex
	while (!sAIMeshVertexIterator->AtEnd(vertex))
	{
		error = sAIMeshVertexIterator->SetOpacity(vertex, 0.0);
		if ( error ) goto errorTag;

		sAIMeshVertexIterator->Next(vertex);
	}
	
	sAIMdMemory->MdMemoryDisposeHandle( (AIMdMemoryHandle)matchingArt );

errorTag:
	if(error){ aisdk::report_error(error); }
	return error;

}

ASErr MapColorChanger::CreateReferenceSpheres(AIArtHandle mesh)
{
	AIArtHandle mapGroup;
	ASErr error = kNoErr;
	AIMeshVertexIterator vertexIterator;
	AIRealPoint sphereSize;
	ai::UnicodeString meshName;
	ASBoolean isDefaultName;

	sAIArt->GetArtName(mesh, meshName, &isDefaultName);

	sphereSize.h = kRefSphereSize;
	sphereSize.v = kRefSphereSize;

	error = sAIArt->NewArt(kGroupArt, kPlaceAbove, mesh, &mapGroup);
	error = sAIArt->SetArtName(mapGroup, meshName);

	sAIMesh->GetStartVertex(mesh, &vertexIterator);
	
	while (!sAIMeshVertexIterator->AtEnd(vertexIterator))
	{
		AIRealPoint vertexLocation;
		AIArtHandle sphere;
		AIColor color;

		sAIMeshVertexIterator->GetPoint(vertexIterator, &vertexLocation);
		sAIMeshVertexIterator->GetColor(vertexIterator, &color);
		
		sAIShapeConstruction->NewPointSizeOval(vertexLocation, sphereSize, 1, 0, 0, &sphere);
		
		// Set style with no fill and stroke.
		AIPathStyle style;
		error = sAIPathStyle->GetInitialPathStyle(&style);

		style.fillPaint = true;
		style.fill.color = color;
		error = sAIPathStyle->SetPathStyle(sphere,&style);

		error = sAIArt->ReorderArt(sphere,kPlaceInsideOnTop,mapGroup);

		sAIMeshVertexIterator->Next(vertexIterator);
	}
	
	return error;
}

ASErr MapColorChanger::RecolorMap(MapData *mapObject, AIArtHandle *mesh)
{
	ASErr error = kNoErr;

	int I = 0, J = 0;
	error = sAIMesh->GetSize(*mesh, &I, &J);

	// +1 because getsize returns number of patches not vetexs
	error = mapObject->FitDataToMesh(I+1, J+1);
	if(error){goto cancel;}

	error = mapObject->BuildColorArray();
	if(error){goto cancel;}

	for(long i = 0; i <= I; ++i){
		for(long j = 0; j <= J; ++j){
			AIMeshVertexIterator vertex;
			error = sAIMesh->GetNode(*mesh, i, j, &vertex);
			error = sAIMeshVertexIterator->SetColor(vertex, &mapObject->XYColors[i][j]);
		}
	}
cancel:
	return error;
}
// End MapColorChanger.cpp
