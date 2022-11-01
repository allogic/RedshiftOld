/****************************************************************************************
 
   Copyright (C) 2016 Autodesk, Inc.
   All rights reserved.
 
   Use of this software is subject to the terms of the Autodesk license agreement
   provided at the time of installation or download, or which otherwise accompanies
   this software in either electronic or hard copy form.
 
****************************************************************************************/

//! \file fbxsdk.h
#ifndef _FBXSDK_H_
#define _FBXSDK_H_

/**
  * \mainpage FBX SDK Reference
  * <p>
  * \section welcome Welcome to the FBX SDK Reference
  * The FBX SDK Reference contains reference information on every header file, 
  * namespace, class, method, enum, typedef, variable, and other C++ elements 
  * that comprise the FBX software development kit (SDK).
  * <p>
  * The FBX SDK Reference is organized into the following sections:
  * <ul><li>Class List: an alphabetical list of FBX SDK classes
  *     <li>Class Hierarchy: a textual representation of the FBX SDK class structure
  *     <li>Graphical Class Hierarchy: a graphical representation of the FBX SDK class structure
  *     <li>File List: an alphabetical list of all documented header files</ul>
  * <p>
  * \section otherdocumentation Other Documentation
  * Apart from this reference guide, an FBX SDK Programming Guide and many FBX 
  * SDK examples are also provided.
  * <p>
  * \section aboutFBXSDK About the FBX SDK
  * The FBX SDK is a C++ software development kit (SDK) that lets you import 
  * and export 3D scenes using the Autodesk FBX file format. The FBX SDK 
  * reads FBX files created with FiLMBOX version 2.5 and later and writes FBX 
  * files compatible with MotionBuilder version 6.0 and up. 
  */

#include <Vendor/FbxSdk/fbxsdk/fbxsdk_def.h>

#ifndef FBXSDK_NAMESPACE_USING
	#define FBXSDK_NAMESPACE_USING 1
#endif

//---------------------------------------------------------------------------------------
//Core Base Includes
#include <Vendor/FbxSdk/fbxsdk/core/base/fbxarray.h>
#include <Vendor/FbxSdk/fbxsdk/core/base/fbxbitset.h>
#include <Vendor/FbxSdk/fbxsdk/core/base/fbxcharptrset.h>
#include <Vendor/FbxSdk/fbxsdk/core/base/fbxcontainerallocators.h>
#include <Vendor/FbxSdk/fbxsdk/core/base/fbxdynamicarray.h>
#include <Vendor/FbxSdk/fbxsdk/core/base/fbxstatus.h>
#include <Vendor/FbxSdk/fbxsdk/core/base/fbxfile.h>
#ifndef FBXSDK_ENV_WINSTORE
	#include <Vendor/FbxSdk/fbxsdk/core/base/fbxfolder.h>
#endif
#include <Vendor/FbxSdk/fbxsdk/core/base/fbxhashmap.h>
#include <Vendor/FbxSdk/fbxsdk/core/base/fbxintrusivelist.h>
#include <Vendor/FbxSdk/fbxsdk/core/base/fbxmap.h>
#include <Vendor/FbxSdk/fbxsdk/core/base/fbxmemorypool.h>
#include <Vendor/FbxSdk/fbxsdk/core/base/fbxpair.h>
#include <Vendor/FbxSdk/fbxsdk/core/base/fbxset.h>
#include <Vendor/FbxSdk/fbxsdk/core/base/fbxstring.h>
#include <Vendor/FbxSdk/fbxsdk/core/base/fbxstringlist.h>
#include <Vendor/FbxSdk/fbxsdk/core/base/fbxtime.h>
#include <Vendor/FbxSdk/fbxsdk/core/base/fbxtimecode.h>
#include <Vendor/FbxSdk/fbxsdk/core/base/fbxutils.h>

//---------------------------------------------------------------------------------------
//Core Math Includes
#include <Vendor/FbxSdk/fbxsdk/core/math/fbxmath.h>
#include <Vendor/FbxSdk/fbxsdk/core/math/fbxdualquaternion.h>
#include <Vendor/FbxSdk/fbxsdk/core/math/fbxmatrix.h>
#include <Vendor/FbxSdk/fbxsdk/core/math/fbxquaternion.h>
#include <Vendor/FbxSdk/fbxsdk/core/math/fbxvector2.h>
#include <Vendor/FbxSdk/fbxsdk/core/math/fbxvector4.h>

//---------------------------------------------------------------------------------------
//Core Sync Includes
#ifndef FBXSDK_ENV_WINSTORE
	#include <Vendor/FbxSdk/fbxsdk/core/sync/fbxatomic.h>
	#include <Vendor/FbxSdk/fbxsdk/core/sync/fbxclock.h>
	#include <Vendor/FbxSdk/fbxsdk/core/sync/fbxsync.h>
	#include <Vendor/FbxSdk/fbxsdk/core/sync/fbxthread.h>
#endif /* !FBXSDK_ENV_WINSTORE */

//---------------------------------------------------------------------------------------
//Core Includes
#include <Vendor/FbxSdk/fbxsdk/core/fbxclassid.h>
#include <Vendor/FbxSdk/fbxsdk/core/fbxconnectionpoint.h>
#include <Vendor/FbxSdk/fbxsdk/core/fbxdatatypes.h>
#ifndef FBXSDK_ENV_WINSTORE
	#include <Vendor/FbxSdk/fbxsdk/core/fbxmodule.h>
	#include <Vendor/FbxSdk/fbxsdk/core/fbxloadingstrategy.h>
#endif /* !FBXSDK_ENV_WINSTORE */
#include <Vendor/FbxSdk/fbxsdk/core/fbxmanager.h>
#include <Vendor/FbxSdk/fbxsdk/core/fbxobject.h>
#include <Vendor/FbxSdk/fbxsdk/core/fbxperipheral.h>
#ifndef FBXSDK_ENV_WINSTORE
	#include <Vendor/FbxSdk/fbxsdk/core/fbxplugin.h>
	#include <Vendor/FbxSdk/fbxsdk/core/fbxplugincontainer.h>
#endif /* !FBXSDK_ENV_WINSTORE */
#include <Vendor/FbxSdk/fbxsdk/core/fbxproperty.h>
#include <Vendor/FbxSdk/fbxsdk/core/fbxpropertydef.h>
#include <Vendor/FbxSdk/fbxsdk/core/fbxpropertyhandle.h>
#include <Vendor/FbxSdk/fbxsdk/core/fbxpropertypage.h>
#include <Vendor/FbxSdk/fbxsdk/core/fbxpropertytypes.h>
#include <Vendor/FbxSdk/fbxsdk/core/fbxquery.h>
#include <Vendor/FbxSdk/fbxsdk/core/fbxqueryevent.h>
#ifndef FBXSDK_ENV_WINSTORE
	#include <Vendor/FbxSdk/fbxsdk/core/fbxscopedloadingdirectory.h>
	#include <Vendor/FbxSdk/fbxsdk/core/fbxscopedloadingfilename.h>
#endif /* !FBXSDK_ENV_WINSTORE */
#include <Vendor/FbxSdk/fbxsdk/core/fbxxref.h>

//---------------------------------------------------------------------------------------
//File I/O Includes
#include <Vendor/FbxSdk/fbxsdk/fileio/fbxexporter.h>
#include <Vendor/FbxSdk/fbxsdk/fileio/fbxexternaldocreflistener.h>
#include <Vendor/FbxSdk/fbxsdk/fileio/fbxfiletokens.h>
#include <Vendor/FbxSdk/fbxsdk/fileio/fbxglobalcamerasettings.h>
#include <Vendor/FbxSdk/fbxsdk/fileio/fbxgloballightsettings.h>
#include <Vendor/FbxSdk/fbxsdk/fileio/fbxgobo.h>
#include <Vendor/FbxSdk/fbxsdk/fileio/fbximporter.h>
#include <Vendor/FbxSdk/fbxsdk/fileio/fbxiobase.h>
#include <Vendor/FbxSdk/fbxsdk/fileio/fbxiopluginregistry.h>
#include <Vendor/FbxSdk/fbxsdk/fileio/fbxiosettings.h>
#include <Vendor/FbxSdk/fbxsdk/fileio/fbxstatisticsfbx.h>
#include <Vendor/FbxSdk/fbxsdk/fileio/fbxstatistics.h>
#include <Vendor/FbxSdk/fbxsdk/fileio/fbxcallbacks.h>

//---------------------------------------------------------------------------------------
//Scene Includes
#include <Vendor/FbxSdk/fbxsdk/scene/fbxaudio.h>
#include <Vendor/FbxSdk/fbxsdk/scene/fbxaudiolayer.h>
#include <Vendor/FbxSdk/fbxsdk/scene/fbxcollection.h>
#include <Vendor/FbxSdk/fbxsdk/scene/fbxcollectionexclusive.h>
#include <Vendor/FbxSdk/fbxsdk/scene/fbxcontainer.h>
#include <Vendor/FbxSdk/fbxsdk/scene/fbxcontainertemplate.h>
#include <Vendor/FbxSdk/fbxsdk/scene/fbxdisplaylayer.h>
#include <Vendor/FbxSdk/fbxsdk/scene/fbxdocument.h>
#include <Vendor/FbxSdk/fbxsdk/scene/fbxdocumentinfo.h>
#include <Vendor/FbxSdk/fbxsdk/scene/fbxenvironment.h>
#include <Vendor/FbxSdk/fbxsdk/scene/fbxgroupname.h>
#include <Vendor/FbxSdk/fbxsdk/scene/fbxlibrary.h>
#include <Vendor/FbxSdk/fbxsdk/scene/fbxmediaclip.h>
#include <Vendor/FbxSdk/fbxsdk/scene/fbxobjectmetadata.h>
#include <Vendor/FbxSdk/fbxsdk/scene/fbxpose.h>
#include <Vendor/FbxSdk/fbxsdk/scene/fbxreference.h>
#include <Vendor/FbxSdk/fbxsdk/scene/fbxscene.h>
#include <Vendor/FbxSdk/fbxsdk/scene/fbxselectionset.h>
#include <Vendor/FbxSdk/fbxsdk/scene/fbxselectionnode.h>
#include <Vendor/FbxSdk/fbxsdk/scene/fbxtakeinfo.h>
#include <Vendor/FbxSdk/fbxsdk/scene/fbxthumbnail.h>
#include <Vendor/FbxSdk/fbxsdk/scene/fbxvideo.h>

//---------------------------------------------------------------------------------------
//Scene Animation Includes
#include <Vendor/FbxSdk/fbxsdk/scene/animation/fbxanimcurve.h>
#include <Vendor/FbxSdk/fbxsdk/scene/animation/fbxanimcurvebase.h>
#include <Vendor/FbxSdk/fbxsdk/scene/animation/fbxanimcurvefilters.h>
#include <Vendor/FbxSdk/fbxsdk/scene/animation/fbxanimcurvenode.h>
#include <Vendor/FbxSdk/fbxsdk/scene/animation/fbxanimevalclassic.h>
#include <Vendor/FbxSdk/fbxsdk/scene/animation/fbxanimevalstate.h>
#include <Vendor/FbxSdk/fbxsdk/scene/animation/fbxanimevaluator.h>
#include <Vendor/FbxSdk/fbxsdk/scene/animation/fbxanimlayer.h>
#include <Vendor/FbxSdk/fbxsdk/scene/animation/fbxanimstack.h>
#include <Vendor/FbxSdk/fbxsdk/scene/animation/fbxanimutilities.h>

//---------------------------------------------------------------------------------------
//Scene Constraint Includes
#include <Vendor/FbxSdk/fbxsdk/scene/constraint/fbxcharacternodename.h>
#include <Vendor/FbxSdk/fbxsdk/scene/constraint/fbxcharacter.h>
#include <Vendor/FbxSdk/fbxsdk/scene/constraint/fbxcharacterpose.h>
#include <Vendor/FbxSdk/fbxsdk/scene/constraint/fbxconstraint.h>
#include <Vendor/FbxSdk/fbxsdk/scene/constraint/fbxconstraintaim.h>
#include <Vendor/FbxSdk/fbxsdk/scene/constraint/fbxconstraintcustom.h>
#include <Vendor/FbxSdk/fbxsdk/scene/constraint/fbxconstraintparent.h>
#include <Vendor/FbxSdk/fbxsdk/scene/constraint/fbxconstraintposition.h>
#include <Vendor/FbxSdk/fbxsdk/scene/constraint/fbxconstraintrotation.h>
#include <Vendor/FbxSdk/fbxsdk/scene/constraint/fbxconstraintscale.h>
#include <Vendor/FbxSdk/fbxsdk/scene/constraint/fbxconstraintsinglechainik.h>
#include <Vendor/FbxSdk/fbxsdk/scene/constraint/fbxconstraintutils.h>
#include <Vendor/FbxSdk/fbxsdk/scene/constraint/fbxcontrolset.h>
#include <Vendor/FbxSdk/fbxsdk/scene/constraint/fbxhik2fbxcharacter.h>

//---------------------------------------------------------------------------------------
//Scene Geometry Includes
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxblendshape.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxblendshapechannel.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxcache.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxcachedeffect.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxcamera.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxcamerastereo.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxcameraswitcher.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxcluster.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxdeformer.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxgenericnode.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxgeometry.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxgeometrybase.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxgeometryweightedmap.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxlight.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxlimitsutilities.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxline.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxlodgroup.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxmarker.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxmesh.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxnode.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxnodeattribute.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxnull.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxnurbs.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxnurbscurve.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxnurbssurface.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxopticalreference.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxpatch.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxproceduralgeometry.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxshape.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxskeleton.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxskin.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxsubdeformer.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxsubdiv.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxtrimnurbssurface.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxvertexcachedeformer.h>
#include <Vendor/FbxSdk/fbxsdk/scene/geometry/fbxweightedmapping.h>

//---------------------------------------------------------------------------------------
//Scene Shading Includes
#include <Vendor/FbxSdk/fbxsdk/scene/shading/fbxshadingconventions.h>
#include <Vendor/FbxSdk/fbxsdk/scene/shading/fbxbindingsentryview.h>
#include <Vendor/FbxSdk/fbxsdk/scene/shading/fbxbindingtable.h>
#include <Vendor/FbxSdk/fbxsdk/scene/shading/fbxbindingtableentry.h>
#include <Vendor/FbxSdk/fbxsdk/scene/shading/fbxbindingoperator.h>
#include <Vendor/FbxSdk/fbxsdk/scene/shading/fbxconstantentryview.h>
#include <Vendor/FbxSdk/fbxsdk/scene/shading/fbxentryview.h>
#include <Vendor/FbxSdk/fbxsdk/scene/shading/fbxfiletexture.h>
#include <Vendor/FbxSdk/fbxsdk/scene/shading/fbximplementation.h>
#include <Vendor/FbxSdk/fbxsdk/scene/shading/fbximplementationfilter.h>
#include <Vendor/FbxSdk/fbxsdk/scene/shading/fbximplementationutils.h>
#include <Vendor/FbxSdk/fbxsdk/scene/shading/fbxlayeredtexture.h>
#include <Vendor/FbxSdk/fbxsdk/scene/shading/fbxoperatorentryview.h>
#include <Vendor/FbxSdk/fbxsdk/scene/shading/fbxproceduraltexture.h>
#include <Vendor/FbxSdk/fbxsdk/scene/shading/fbxpropertyentryview.h>
#include <Vendor/FbxSdk/fbxsdk/scene/shading/fbxsemanticentryview.h>
#include <Vendor/FbxSdk/fbxsdk/scene/shading/fbxsurfacelambert.h>
#include <Vendor/FbxSdk/fbxsdk/scene/shading/fbxsurfacematerial.h>
#include <Vendor/FbxSdk/fbxsdk/scene/shading/fbxsurfacephong.h>
#include <Vendor/FbxSdk/fbxsdk/scene/shading/fbxtexture.h>

//---------------------------------------------------------------------------------------
//Utilities Includes
#include <Vendor/FbxSdk/fbxsdk/utils/fbxdeformationsevaluator.h>
#include <Vendor/FbxSdk/fbxsdk/utils/fbxprocessor.h>
#include <Vendor/FbxSdk/fbxsdk/utils/fbxprocessorxref.h>
#include <Vendor/FbxSdk/fbxsdk/utils/fbxprocessorxrefuserlib.h>
#include <Vendor/FbxSdk/fbxsdk/utils/fbxprocessorshaderdependency.h>
#include <Vendor/FbxSdk/fbxsdk/utils/fbxclonemanager.h>
#include <Vendor/FbxSdk/fbxsdk/utils/fbxgeometryconverter.h>
#include <Vendor/FbxSdk/fbxsdk/utils/fbxmanipulators.h>
#include <Vendor/FbxSdk/fbxsdk/utils/fbxmaterialconverter.h>
#include <Vendor/FbxSdk/fbxsdk/utils/fbxrenamingstrategyfbx5.h>
#include <Vendor/FbxSdk/fbxsdk/utils/fbxrenamingstrategyfbx6.h>
#include <Vendor/FbxSdk/fbxsdk/utils/fbxrenamingstrategyutilities.h>
#include <Vendor/FbxSdk/fbxsdk/utils/fbxrootnodeutility.h>
#include <Vendor/FbxSdk/fbxsdk/utils/fbxusernotification.h>
#include <Vendor/FbxSdk/fbxsdk/utils/fbxscenecheckutility.h>

//---------------------------------------------------------------------------------------
#if defined(FBXSDK_NAMESPACE) && (FBXSDK_NAMESPACE_USING == 1)
	using namespace FBXSDK_NAMESPACE;
#endif

#endif /* _FBXSDK_H_ */
