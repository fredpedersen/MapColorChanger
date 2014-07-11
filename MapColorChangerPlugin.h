//========================================================================================
//  
//  $File: //ai/ai18/devtech/sdk/public/samplecode/MapColorChanger/Source/MapColorChangerPlugin.h $
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

#ifndef __MapColorChangerPlugin_H__
#define __MapColorChangerPlugin_H__

#include "IllustratorSDK.h"
#include "Plugin.hpp"
#include "SDKDef.h"
#include "SDKAboutPluginsHelper.h"
#include "MapColorChangerID.h"
#include "MapColorChangerSuites.h"
#include "MapColorChanger.h"
#include "CSVData.h"

#define kMenuGroupText "Map tools"
#define kMenuRecolorItemText "Create meshes from CSV"
#define kMenuFlipHItemText "Flip meshes horizontally"
#define kMenuFlipVItemText "Flip meshes vertically"
#define kMenuCreateRefSpotsItemText "Create reference spots from meshes"

/** Maximum length of filter/effect name.
*/
const ASInt32 MAX_FILTER_NAME = 65;

/** Increment used when indexing through the filter/effect strings.
*/
const ASInt32 FILTER_STRING_INC = 2;

/**	Creates a new MapColorChangerPlugin.
	@param pluginRef IN unique reference to this plugin.
	@return pointer to new MapColorChangerPlugin.
*/
Plugin* AllocatePlugin(SPPluginRef pluginRef);

/**	Reloads the MapColorChangerPlugin class state when the plugin is 
	reloaded by the application.
	@param plugin IN pointer to plugin being reloaded.
*/
void FixupReload(Plugin* plugin);

/**	Provides a plugin which demonstrates adding a filter and a live effect.
*/
class MapColorChangerPlugin : public Plugin
{
public:
	/**	Constructor.
		@param pluginRef IN reference to this plugin.
	*/
	MapColorChangerPlugin(SPPluginRef pluginRef);

	/**	Destructor.
	*/
	virtual ~MapColorChangerPlugin(){}

	/**	Restores state of MapColorChangerPlugin during reload.
	*/
	FIXUP_VTABLE_EX(MapColorChangerPlugin, Plugin);

	// functions
	ASErr CreateMaps(AIArtHandle mesh);

protected:
	/** Calls Plugin::Message and handles any errors returned.
		@param caller IN sender of the message.
		@param selector IN nature of the message.
		@param message IN pointer to plugin and call information.
		@return kNoErr on success, other ASErr otherwise.
	*/
	virtual ASErr Message(char* caller, char* selector, void *message);

	/**	Calls Plugin::Startup and initialisation functions, such as 
		AddMenus and AddNotifiers.
		@param message IN pointer to plugin and call information.
		@return kNoErr on success, other ASErr otherwise.
	*/
	virtual ASErr StartupPlugin(SPInterfaceMessage* message);	

	/**	Performs plugin tasks that could not be performed until
		the application was started.
		@return kNoErr on success, other ASErr otherwise.
	*/
	virtual ASErr PostStartupPlugin();

	/** Deletes the MapColorChanger object after the application 
		shutdown notifier is received.
		@param message IN pointer to plugin and call information.
		@return kNoErr on success, other ASErr otherwise.
	*/
	virtual ASErr Notify(AINotifierMessage* message);

	/**	Performs actions required for menu item selected.
		@param message IN pointer to plugin and call information.
		@return kNoErr on success, other ASErr otherwise.
	*/
	virtual ASErr GoMenuItem(AIMenuMessage* message);
	
	/**	Applies the filter using the parameters provided by the user.
		@param message IN pointer to plugin and call information.
		@return kNoErr on success, other ASErr otherwise.
	*/
//	virtual ASErr GoFilter(AIFilterMessage* message);

	/**	Applies the live effect using the parameters provided by the user.
		@param message IN pointer to plugin and call information.
		@return kNoErr on success, other ASErr otherwise.
	*/
//	virtual ASErr GoLiveEffect(AILiveEffectGoMessage* message);

	/**	Gathers parameters from user via a dialog.
		@param message IN pointer to plugin and call information.
		@return kNoErr on success, other ASErr otherwise.
	*/
//	virtual ASErr GetFilterParameters(AIFilterMessage* message);

	/**	Gathers parameters from user via a dialog.
		@param message IN pointer to plugin and call information.
		@return kNoErr on success, other ASErr otherwise.
	*/
//	virtual ASErr EditLiveEffectParameters(AILiveEffectEditParamMessage* message);

private:
	/** Pointer to a MapColorChanger object.
	*/
	MapColorChanger* fMapColorChanger;

	/** Pointer to a CSVData object.
	*/
	CSVData* fCSVData;

	/** Menu item handles
	*/
	AIMenuItemHandle fRecolorMenuItem;
	AIMenuItemHandle fFlipHMenuItem;
	AIMenuItemHandle fFlipVMenuItem;
	AIMenuItemHandle fCreateRefSpotsMenuItem;

	/** Handle for the application shutdown notifier.
	*/
	AINotifierHandle fAppShutdownNotifier;

	/** Handle for CSXS plugplug setup complete notifier.
	*/
	AINotifierHandle fCSXSPlugPlugSetupCompleteNotifier;

	/** Handle for apply filter notifier
	*/
	AINotifierHandle fApplyFilterNotifier;

	/** Handle for apply live effect notifier
	*/
	AINotifierHandle fApplyLiveEffectNotifier;

	/** Array of AIFilterHandles to store references to this plugins filters.
	*/
	AIFilterHandle fFilters[kMaxFilters];

	/** Array of AILiveEffectHandles to store references to this plugins live effects.
	*/
	AILiveEffectHandle fEffects[kMaxEffects];

	/** Stores the number of filters added by this plugin.
	*/
	ASInt32 fNumFilters;

	/** Stores the number of effects added by this plugin.
	*/
	ASInt32 fNumEffects;

	/**	Adds the filters provided by this plugin.
		@param message IN pointer to plugin and call information.
		@return kNoErr on success, other ASErr otherwise.
	*/
	ASErr AddFilters(SPInterfaceMessage* message);

	/**	Adds the menu items for this plugin to the application UI.
		@param message IN pointer to plugin and call information.
		@return kNoErr on success, other ASErr otherwise.
	*/
	ASErr AddMenus(SPInterfaceMessage* message);

	/**	Prompt user for csv file. returns path
	*/
	ai::FilePath PromptForCsvFile();

	/**	Get mesh from selection. probably buggy, needs testing
	*/
	ASErr GetMeshesFromSelection(AIArtHandle*** matches, ai::int32* numMatches);

	/**	Adds the live effects provided by this plug-in.
		@param message IN pointer to plugin and call information.
		@return kNoErr on success, other ASErr otherwise.
	*/
	ASErr AddLiveEffects(SPInterfaceMessage* message);

	/**	Registers this plugin to receive the application shutdown notifier.
		@param message IN pointer to plugin and call information.
		@return kNoErr on success, other ASErr otherwise.
	*/
	ASErr AddNotifiers(SPInterfaceMessage* message);	
	
	/** Converts given C string into a Pascal string.
	*/
	void CStrToPStr(char *s, ai::UnicodeString::size_type len);
};

#endif // End MapColorChangerPlugin.h
