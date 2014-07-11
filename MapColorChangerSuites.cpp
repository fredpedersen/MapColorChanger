//========================================================================================
//  
//  $File: //ai/ai18/devtech/sdk/public/samplecode/MapColorChanger/Source/MapColorChangerSuites.cpp $
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

#include "IllustratorSDK.h"
#include "MapColorChangerSuites.h"

extern "C"
{
	AIMenuSuite*			sAIMenu = NULL;
	AIUnicodeStringSuite*	sAIUnicodeString = NULL;
	SPBlocksSuite*			sSPBlocks = NULL;
	AIFilterSuite*			sAIFilter = NULL;
	AILiveEffectSuite*		sAILiveEffect = NULL;
	AIMdMemorySuite*		sAIMdMemory = NULL;
	AIDictionarySuite*		sAIDictionary = NULL;
	AIMatchingArtSuite*		sAIMatchingArt = NULL;
	AIPathSuite*			sAIPath = NULL;
	AIRealMathSuite*		sAIRealMath = NULL;
	AIArtSuite*				sAIArt = NULL;
	AIMeshSuite*			sAIMesh = NULL;
	AIMeshVertexIteratorSuite* sAIMeshVertexIterator = NULL;
	//AIUIUtilsSuite*         sAIUIUtils = NULL;
	AIStringFormatUtilsSuite*	sAIStringFormatUtils = NULL;
	AISwatchGroupSuite*	sAISwatchGroup = NULL;
	AISwatchListSuite*	sAISwatchList = NULL;
	AIShapeConstructionSuite*	sAIShapeConstruction = NULL;
	AIPathStyleSuite*			sAIPathStyle = NULL;
};

ImportSuite gImportSuites[] = 
{
	kAIMenuSuite, kAIMenuSuiteVersion, &sAIMenu,
	kAIUnicodeStringSuite, kAIUnicodeStringSuiteVersion, &sAIUnicodeString,
	kSPBlocksSuite, kSPBlocksSuiteVersion, &sSPBlocks,
	kAIFilterSuite, kAIFilterVersion, &sAIFilter,
	kAILiveEffectSuite, kAILiveEffectVersion, &sAILiveEffect,
	kAIMdMemorySuite, kAIMdMemorySuiteVersion, &sAIMdMemory,
	kAIDictionarySuite, kAIDictionaryVersion, &sAIDictionary,
	kAIMatchingArtSuite, kAIMatchingArtSuiteVersion, &sAIMatchingArt,
	kAIPathSuite, kAIPathSuiteVersion,	&sAIPath,
	kAIRealMathSuite, kAIRealMathVersion, &sAIRealMath,
	kAIArtSuite, kAIArtVersion, &sAIArt,
	kAIMeshSuite, kAIMeshVersion, &sAIMesh,
	kAISwatchGroupSuite, kAISwatchGroupVersion, &sAISwatchGroup,
	kAIShapeConstructionSuite,  kAIShapeConstructionVersion, &sAIShapeConstruction,
	kAIPathStyleSuite, kAIPathStyleSuiteVersion, &sAIPathStyle,
	kAISwatchListSuite, kAISwatchListVersion, &sAISwatchList,
	kAIMeshVertexIteratorSuite, kAIMeshVertexIteratorVersion, &sAIMeshVertexIterator,
	//kAIUIUtilsSuite, kAIUIUtilsSuiteVersion, &sAIUIUtils,
	kAIStringFormatUtilsSuite, kAIStringFormatUtilsSuiteVersion, &sAIStringFormatUtils,
	nil, 0, nil
};

// End MapColorChangerSuites.cpp
