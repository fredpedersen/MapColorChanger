//========================================================================================
//  
//  $File: //ai/ai18/devtech/sdk/public/samplecode/MapColorChanger/Source/MapColorChangerID.h $
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

#ifndef __MapColorChangerID_H__
#define __MapColorChangerID_H__

#define kMapColorChangerPluginName		"MapColorChanger"

#define kMaxFilters					10
#define kMaxEffects					10

#define kFilterStrings				16050

// TODO: A lot of these constants are to do with the old ADM dialog - let's delete them

#define kDlgOKButton				1
#define kDlgCancelButton			2

#define kTwirlDialogID				16100
#define kTwirlFewDialogID			16101
#define kTwirlDialogName			"Twirl"

#define kTwirlAngleDItem			3
#define kTwirlAngleDTextItem		4
#define kTwirlAngleCHCK				(kTwirlDLOG + kTwirlAngleDItem)

#define kMapColorChangerApplyCaller		"MapColorChanger Apply"
#define kTwirlApplyFilterNotifier	"MapColorChanger Apply Filter Notifier"
#define kTwirlApplyEffectNotifier	"MapColorChanger Apply LiveEffect Notifier"

#endif // End MapColorChangerID.h
