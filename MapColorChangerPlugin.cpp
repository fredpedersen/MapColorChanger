//========================================================================================
//  
//  $File: //ai/ai18/devtech/sdk/public/samplecode/MapColorChanger/Source/MapColorChangerPlugin.cpp $
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
#include "MapColorChangerPlugin.h"
#include "AICSXS.h"

#define CHECK_RESULT if(result) { return result;}

/*
*/
Plugin* AllocatePlugin(SPPluginRef pluginRef)
{
	return new MapColorChangerPlugin(pluginRef);
}

/*
*/
void FixupReload(Plugin* plugin)
{
	MapColorChangerPlugin::FixupVTable((MapColorChangerPlugin*) plugin);
}

/*
*/
MapColorChangerPlugin::MapColorChangerPlugin(SPPluginRef pluginRef) 
	: Plugin(pluginRef),
//	fRunToolMenu(NULL),
	fAppShutdownNotifier(NULL),
	fCSXSPlugPlugSetupCompleteNotifier(NULL),
	fNumFilters(0),
	fMapColorChanger(NULL)
{
	strncpy(fPluginName, kMapColorChangerPluginName, kMaxStringLength);
}

/*
*/
ASErr MapColorChangerPlugin::Message(char* caller, char* selector, void *message) 
{
	ASErr error = kNoErr;

	try {
		error = Plugin::Message(caller, selector, message);
	}
	catch (ai::Error& ex) {
		error = ex;
	}
	catch (...) {
		error = kCantHappenErr;
	}
	if (error) {
		if (error == kUnhandledMsgErr) {
			// Defined by Plugin.hpp and used in Plugin::Message - ignore.
			error = kNoErr;
		}
		else {
			Plugin::ReportError(error, caller, selector, message);
		}
	}	
	return error;
}

/*
*/
ASErr MapColorChangerPlugin::StartupPlugin(SPInterfaceMessage* message)
{
	ASErr result = kNoErr;
	result = Plugin::StartupPlugin(message);
	CHECK_RESULT
	result = this->AddMenus(message);
    CHECK_RESULT
	//result = this->AddFilters(message);
    CHECK_RESULT
	//result = this->AddLiveEffects(message);
    CHECK_RESULT
	result = this->AddNotifiers(message);
	
	return result;
}

/*
*/
ASErr MapColorChangerPlugin::PostStartupPlugin()
{
	ASErr result = kNoErr;

	// Create LiveDropShadowGroup
	if (this->fMapColorChanger == NULL)
	{
		this->fMapColorChanger = new MapColorChanger();
		// TODO error handling
	}

	return result;
}

/*
*/
ASErr MapColorChangerPlugin::Notify(AINotifierMessage* message)
{
	ASErr result = kNoErr;
	if (message->notifier == this->fAppShutdownNotifier)
	{
		if (this->fMapColorChanger)
		{
			delete this->fMapColorChanger;
		}
        Plugin::LockPlugin(false);
	}
	else if ( message->notifier == fApplyFilterNotifier )
	{
        GoFilter((AIFilterMessage *)message);
	}
	
	else if ( message->notifier == fApplyLiveEffectNotifier )
	{
        GoLiveEffect((AILiveEffectGoMessage *) message);
	}
	
	return result;
}

/*
*/
ASErr MapColorChangerPlugin::AddNotifiers(SPInterfaceMessage* message)
{
    ASErr result = kNoErr;

	result = sAINotifier->AddNotifier(message->d.self, "MapColorChanger " kAIApplicationShutdownNotifier, 
		kAIApplicationShutdownNotifier, &this->fAppShutdownNotifier);

	result = sAINotifier->AddNotifier(message->d.self, "MapColorChanger " kAICSXSPlugPlugSetupCompleteNotifier,
		kAICSXSPlugPlugSetupCompleteNotifier, &fCSXSPlugPlugSetupCompleteNotifier);

	result = sAINotifier->AddNotifier(message->d.self, kMapColorChangerApplyCaller, kTwirlApplyFilterNotifier,
		&fApplyFilterNotifier);
	
	
	result = sAINotifier->AddNotifier(message->d.self, kMapColorChangerApplyCaller, kTwirlApplyEffectNotifier,
		&fApplyLiveEffectNotifier);
	

	return result;
}

/*
*/
ASErr MapColorChangerPlugin::AddMenus(SPInterfaceMessage* message) 
{
	ASErr error = kNoErr;

	AIPlatformAddMenuItemDataUS menuData;
	AIMenuGroup	menuGroup;
	AIMenuItemHandle menuItemHandle = nil;

	// add menu group in edit
	menuData.groupName = kEditMenuGroup;
	menuData.itemText = ai::UnicodeString( kMenuGroupText );
	error = sAIMenu->AddMenuItem( message->d.self, 
							      NULL, 
							      &menuData, 
							      kMenuItemWantsUpdateOption,
							      &menuItemHandle);
	error = sAIMenu->UpdateMenuItemAutomatically(menuItemHandle, kAutoEnableMenuItemAction, 0, 0, kIfMesh, 0, 0, 0);
	if (error) { goto error; }
	
	error = sAIMenu->AddMenuGroupAsSubMenu(kMenuGroupText, kMenuGroupNoOptions, menuItemHandle, &menuGroup);

	// add recolor menu item
	menuData.groupName = kMenuGroupText;
	menuData.itemText = ai::UnicodeString( kMenuRecolorItemText );
	error = sAIMenu->AddMenuItem( message->d.self, 
							      kMenuRecolorItemText, 
							      &menuData, 
							      kMenuGroupNoOptions,
								  &this->fRecolorMenuItem);
	if (error) { goto error; }
	/* Not yet implimented
		// add kMenuFlipHItemText menu item
	menuData.groupName = kMenuGroupText;
	menuData.itemText = ai::UnicodeString( kMenuFlipHItemText );
	error = sAIMenu->AddMenuItem( message->d.self, 
							      kMenuFlipHItemText, 
							      &menuData, 
							      kMenuGroupNoOptions,
								  &this->fFlipHMenuItem);
	if (error) { goto error; }

		// add first menu item
	menuData.groupName = kMenuGroupText;
	menuData.itemText = ai::UnicodeString( kMenuFlipVItemText );
	error = sAIMenu->AddMenuItem( message->d.self, 
							      kMenuFlipVItemText, 
							      &menuData, 
							      kMenuGroupNoOptions,
							      &this->fFlipVMenuItem);
	if (error) { goto error; }*/

			// add first menu item
	menuData.groupName = kMenuGroupText;
	menuData.itemText = ai::UnicodeString( kMenuCreateRefSpotsItemText );
	error = sAIMenu->AddMenuItem( message->d.self, 
							      kMenuCreateRefSpotsItemText, 
							      &menuData, 
							      kMenuGroupNoOptions,
								  &this->fCreateRefSpotsMenuItem);
	if (error) { goto error; }
	/*
	error = sAIMenu->UpdateMenuItemAutomatically(this->fRunToolMenu, kAutoEnableMenuItemAction, 0, 0, kIfMesh, 0, 0, 0);
	if (error) { goto error; }*/
		
error:
	return error;
}

ai::FilePath MapColorChangerPlugin::PromptForCsvFile() 
{
	ai::FilePath path;

	ai::UnicodeString title("Select csv");
	ai::UnicodeString desc("CSV map data file");
	ai::UnicodeString pattern("*.csv");

	AIFileDialogFilters options;
	options.AddFilter(desc, pattern);

	sAIUser->GetFileDialog(title, &options, path);

	return path;
}

ASErr MapColorChangerPlugin::GetMeshesFromSelection(AIArtHandle*** matches, ai::int32* numMatches){
	AIMatchingArtSpec spec[1];
	ASErr error = kNoErr;

	spec[0].type = kMeshArt;
	spec[0].whichAttr = kArtSelected;
	spec[0].attr = kArtSelected;

	error = sAIMatchingArt->GetMatchingArt( spec, 1, matches, numMatches );

	return error;
}


ASErr MapColorChangerPlugin::CreateMaps(AIArtHandle mesh){
	ASErr error = kNoErr;
	
	ai::FilePath path = this->PromptForCsvFile();
	if(path.IsEmpty()){ goto cancel; }

	this->fCSVData = new CSVData();
	this->fCSVData->ParseCsv(path);
	this->fCSVData->BuildMaps();

	for (int i = 0; i < this->fCSVData->Maps.size(); i++)
	{

		this->fCSVData->Maps[i].FlipV();
		this->fCSVData->Maps[i].FlipH();

		error = sAIArt->DuplicateArt(mesh, kPlaceAbove, mesh, &fCSVData->Maps[i].fMesh);
		error = fMapColorChanger->RecolorMap(&fCSVData->Maps[i], &fCSVData->Maps[i].fMesh);

		if(error){ // prevent looping error message
			error = sAIArt->DisposeArt(fCSVData->Maps[i].fMesh);
			break;
		}

		sAIArt->SetArtName(fCSVData->Maps[i].fMesh, ai::UnicodeString(fCSVData->Maps[i].MapTitle));
	}

	error = sAIArt->DisposeArt(mesh);

	return error;
cancel:
	return true;
}
/*
*/
ASErr MapColorChangerPlugin::GoMenuItem(AIMenuMessage* message) 
{
	AIArtHandle **matches;
	ai::int32 numMatches;

	this->GetMeshesFromSelection(&matches, &numMatches);

	if(message->menuItem == this->fRecolorMenuItem){
		if(numMatches == 1){
			this->CreateMaps((*matches)[0]);
		}else{
			char alertMessage [50];
			sprintf (alertMessage, "Can only use one mesh as template. %d selected.", numMatches);
		
			sAIUser->ErrorAlert(ai::UnicodeString(alertMessage));
		}
	}else{
		for (int i = 0; i < numMatches; i++)
		{
			if(message->menuItem == this->fCreateRefSpotsMenuItem){
				this->fMapColorChanger->CreateReferenceSpheres((*matches)[i]);
			}
		}
	}

	return kNoErr;

}

/////////////////////////////////////////
//
// Utility functions
//
/////////////////////////////////////////

/*
*/
void MapColorChangerPlugin::CStrToPStr(char *s, ai::UnicodeString::size_type len)
{
	const ai::UnicodeString sAsUnicode((const char*)s);
	ai::PStr sAsPStr((unsigned char*) s);
	sAsUnicode.getToBuffer(sAsPStr, len, kAIUTF8CharacterEncoding );
}

// End MapColorChangerPlugin.cpp
