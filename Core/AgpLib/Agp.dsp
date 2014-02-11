# Microsoft Developer Studio Project File - Name="Agp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Agp - Win32 DebugMultithreadedDll
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Agp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Agp.mak" CFG="Agp - Win32 DebugMultithreadedDll"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Agp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Agp - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "Agp - Win32 DebugMultithreadedDll" (based on "Win32 (x86) Static Library")
!MESSAGE "Agp - Win32 ReleaseMultithreadedDll" (based on "Win32 (x86) Static Library")
!MESSAGE "Agp - Win32 ReleaseQA" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Gp_Vim/Core/AgpLib", ARGBAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Agp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
LINK32=link.exe -lib
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\AgpLib" /I "..\EpLib" /I "..\EpnLib" /I "..\VimageLib" /I "..\ExpandiLib" /I "..\Util" /I "..\ExpandLib" /I "..\CodingLib" /I "..\CorTransformLib" /I "..\ImageLib" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "_WINDOWS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\Agp.lib"

!ELSEIF  "$(CFG)" == "Agp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
LINK32=link.exe -lib
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\AgpLib" /I "..\EpLib" /I "..\EpnLib" /I "..\VimageLib" /I "..\ExpandiLib" /I "..\Util" /I "..\ExpandLib" /I "..\CodingLib" /I "..\CorTransformLib" /I "..\ImageLib" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "_WINDOWS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\AgpD.lib"

!ELSEIF  "$(CFG)" == "Agp - Win32 DebugMultithreadedDll"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Agp___Win32_DebugMultithreadedDll"
# PROP BASE Intermediate_Dir "Agp___Win32_DebugMultithreadedDll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Agp___Win32_DebugMultithreadedDll"
# PROP Intermediate_Dir "Agp___Win32_DebugMultithreadedDll"
# PROP Target_Dir ""
LINK32=link.exe -lib
MTL=midl.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\AgpLib" /I "..\EpLib" /I "..\VimageLib" /I "..\ExpandiLib" /I "..\Util" /I "..\ExpandLib" /I "..\CodingLib" /I "..\CorTransformLib" /I "..\ImageLib" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\AgpLib" /I "..\EpLib" /I "..\VimageLib" /I "..\ExpandiLib" /I "..\Util" /I "..\ExpandLib" /I "..\CodingLib" /I "..\CorTransformLib" /I "..\ImageLib" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "_WINDOWS" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Agp - Win32 ReleaseMultithreadedDll"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Agp___Win32_ReleaseMultithreadedDll"
# PROP BASE Intermediate_Dir "Agp___Win32_ReleaseMultithreadedDll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Agp___Win32_ReleaseMultithreadedDll"
# PROP Intermediate_Dir "Agp___Win32_ReleaseMultithreadedDll"
# PROP Target_Dir ""
LINK32=link.exe -lib
MTL=midl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "..\AgpLib" /I "..\EpLib" /I "..\VimageLib" /I "..\ExpandiLib" /I "..\Util" /I "..\ExpandLib" /I "..\CodingLib" /I "..\CorTransformLib" /I "..\ImageLib" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\AgpLib" /I "..\EpLib" /I "..\VimageLib" /I "..\ExpandiLib" /I "..\Util" /I "..\ExpandLib" /I "..\CodingLib" /I "..\CorTransformLib" /I "..\ImageLib" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Agp - Win32 ReleaseQA"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Agp___Win32_ReleaseQA"
# PROP BASE Intermediate_Dir "Agp___Win32_ReleaseQA"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseQA"
# PROP Intermediate_Dir "ReleaseQA"
# PROP Target_Dir ""
LINK32=link.exe -lib
MTL=midl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "..\AgpLib" /I "..\EpLib" /I "..\VimageLib" /I "..\ExpandiLib" /I "..\Util" /I "..\ExpandLib" /I "..\CodingLib" /I "..\CorTransformLib" /I "..\ImageLib" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "_WINDOWS" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\AgpLib" /I "..\EpLib" /I "..\EpnLib" /I "..\VimageLib" /I "..\ExpandiLib" /I "..\Util" /I "..\ExpandLib" /I "..\CodingLib" /I "..\CorTransformLib" /I "..\ImageLib" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "_WINDOWS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\Agp.lib"

!ENDIF 

# Begin Target

# Name "Agp - Win32 Release"
# Name "Agp - Win32 Debug"
# Name "Agp - Win32 DebugMultithreadedDll"
# Name "Agp - Win32 ReleaseMultithreadedDll"
# Name "Agp - Win32 ReleaseQA"
# Begin Group "AgpColor"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AgpColor\AgpAdaptivePalette.c
# End Source File
# Begin Source File

SOURCE=.\AgpColor\AgpChangeProfile.c
# End Source File
# Begin Source File

SOURCE=.\AgpColor\AgpColor.h
# End Source File
# Begin Source File

SOURCE=.\AgpColor\AgpColorF.c
# End Source File
# Begin Source File

SOURCE=.\AgpColor\AgpColorF.h
# End Source File
# Begin Source File

SOURCE=.\AgpColor\AgpColorF1.c
# End Source File
# Begin Source File

SOURCE=.\AgpColor\AgpColorFN.c
# End Source File
# Begin Source File

SOURCE=.\AgpColor\AgpGrbRgb.c
# End Source File
# Begin Source File

SOURCE=.\AgpColor\AgpRgbRange.c
# End Source File
# Begin Source File

SOURCE=.\AgpColor\AgpRgbY.c
# End Source File
# Begin Source File

SOURCE=.\AgpColor\AgpRgbYCrCb.c
# End Source File
# Begin Source File

SOURCE=.\AgpColor\AgpRgbYiq.c
# End Source File
# Begin Source File

SOURCE=.\AgpColor\AgpRgbYmax.c
# End Source File
# Begin Source File

SOURCE=.\AgpColor\AgpYCrCbRangeY.c
# End Source File
# Begin Source File

SOURCE=.\AgpColor\AgpYCrCbRgb.c
# End Source File
# Begin Source File

SOURCE=.\AgpColor\AgpYiqRgb.c
# End Source File
# Begin Source File

SOURCE=.\AgpColor\FillAux.c
# End Source File
# Begin Source File

SOURCE=.\AgpColor\FillAux.h
# End Source File
# Begin Source File

SOURCE=.\AgpColor\Makefile
# End Source File
# End Group
# Begin Group "AgpCutout"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AgpCutout\AgpCutout.c
# End Source File
# Begin Source File

SOURCE=.\AgpCutout\AgpCutout.h
# End Source File
# Begin Source File

SOURCE=.\AgpCutout\AgpCutoutFit.c
# End Source File
# Begin Source File

SOURCE=.\AgpCutout\AgpCutoutN.c
# End Source File
# Begin Source File

SOURCE=.\AgpCutout\AgpCutoutNWrapper.c
# End Source File
# Begin Source File

SOURCE=.\AgpCutout\AgpCutoutWrapper.c
# End Source File
# End Group
# Begin Group "AgpDepth"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AgpDepth\AgpDepth.h
# End Source File
# Begin Source File

SOURCE=.\AgpDepth\AgpDepthAdd.c
# End Source File
# Begin Source File

SOURCE=.\AgpDepth\AgpDepthDefault.c
# End Source File
# Begin Source File

SOURCE=.\AgpDepth\AgpDepthIn.h
# End Source File
# Begin Source File

SOURCE=.\AgpDepth\AgpDepthRange.c
# End Source File
# Begin Source File

SOURCE=.\AgpDepth\AgpDepthSet.c
# End Source File
# Begin Source File

SOURCE=.\AgpDepth\AgpDepthSetBottle.c
# End Source File
# Begin Source File

SOURCE=.\AgpDepth\AgpDepthSetCorner.c
# End Source File
# Begin Source File

SOURCE=.\AgpDepth\AgpDepthSetL.c
# End Source File
# Begin Source File

SOURCE=.\AgpDepth\AgpDepthSmooth0x4.c
# End Source File
# Begin Source File

SOURCE=.\AgpDepth\AgpDepthValue.c
# End Source File
# Begin Source File

SOURCE=.\AgpDepth\Makefile
# End Source File
# End Group
# Begin Group "AgpEdit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AgpEdit\AgpDefaultProfile.c
# End Source File
# Begin Source File

SOURCE=.\AgpEdit\AgpEditTool.h
# End Source File
# Begin Source File

SOURCE=.\AgpEdit\AgpJnt.c
# End Source File
# Begin Source File

SOURCE=.\AgpEdit\AgpJntConnect.c
# End Source File
# Begin Source File

SOURCE=.\AgpEdit\AgpJntCutBrn.c
# End Source File
# Begin Source File

SOURCE=.\AgpEdit\AgpJntEdgeReorder.c
# End Source File
# Begin Source File

SOURCE=.\AgpEdit\AgpJntN3.c
# End Source File
# Begin Source File

SOURCE=.\AgpEdit\AgpJntN3Reposition.c
# End Source File
# Begin Source File

SOURCE=.\AgpEdit\AgpLink2Jnt.c
# End Source File
# Begin Source File

SOURCE=.\AgpEdit\AgpLinkDelete.c
# End Source File
# Begin Source File

SOURCE=.\AgpEdit\AgpLinkFilter.c
# End Source File
# Begin Source File

SOURCE=.\AgpEdit\AgpLinkInverse.c
# End Source File
# Begin Source File

SOURCE=.\AgpEdit\AgpLinkN3rToRidge.c
# End Source File
# Begin Source File

SOURCE=.\AgpEdit\AgpLinkN3ToEdge.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpLinkProf.c
# End Source File
# Begin Source File

SOURCE=.\AgpEdit\AgpLinkSplit.c
# End Source File
# Begin Source File

SOURCE=.\AgpEdit\AgpPolylinkDelete.c
# End Source File
# Begin Source File

SOURCE=.\AgpEdit\AgpPolylinkInsert.c
# End Source File
# Begin Source File

SOURCE=.\AgpEdit\AgpPolylinkSelect.c
# End Source File
# Begin Source File

SOURCE=.\AgpEdit\AgpProfileLoad.c
# End Source File
# Begin Source File

SOURCE=.\AgpEdit\AgpSelect.c
# End Source File
# Begin Source File

SOURCE=.\AgpEdit\AgpSelect.h
# End Source File
# Begin Source File

SOURCE=.\AgpEdit\Makefile
# End Source File
# End Group
# Begin Group "AgpLayer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AgpLayer\AgpLayer.c
# End Source File
# Begin Source File

SOURCE=.\AgpLayer\AgpLayer.h
# End Source File
# Begin Source File

SOURCE=.\AgpLayer\AgpLayerBorder.c
# End Source File
# Begin Source File

SOURCE=.\AgpLayer\AgpLayerBox.c
# End Source File
# Begin Source File

SOURCE=.\AgpLayer\AgpLayerClear.c
# End Source File
# Begin Source File

SOURCE=.\AgpLayer\AgpLayerColor.c
# End Source File
# Begin Source File

SOURCE=.\AgpLayer\AgpLayerContourPolylink.c
# End Source File
# Begin Source File

SOURCE=.\AgpLayer\AgpLayerCopy.c
# End Source File
# Begin Source File

SOURCE=.\AgpLayer\AgpLayerCopyContour.c
# End Source File
# Begin Source File

SOURCE=.\AgpLayer\AgpLayerCut.c
# End Source File
# Begin Source File

SOURCE=.\AgpLayer\AgpLayerF.c
# End Source File
# Begin Source File

SOURCE=.\AgpLayer\AgpLayerF.h
# End Source File
# Begin Source File

SOURCE=.\AgpLayer\AgpLayerF1.c
# End Source File
# Begin Source File

SOURCE=.\AgpLayer\AgpLayerFC.c
# End Source File
# Begin Source File

SOURCE=.\AgpLayer\AgpLayerFC1.c
# End Source File
# Begin Source File

SOURCE=.\AgpLayer\AgpLayerFlattening.c
# End Source File
# Begin Source File

SOURCE=.\AgpLayer\AgpLayerFn3.c
# End Source File
# Begin Source File

SOURCE=.\AgpLayer\AgpLayerHole.c
# End Source File
# Begin Source File

SOURCE=.\AgpLayer\AgpLayerInit.c
# End Source File
# Begin Source File

SOURCE=.\AgpLayer\AgpLayerMiddle.c
# End Source File
# Begin Source File

SOURCE=.\AgpLayer\AgpLayerRenumbering.c
# End Source File
# Begin Source File

SOURCE=.\AgpLayer\AgpLayerSelect.c
# End Source File
# Begin Source File

SOURCE=.\AgpLayer\Makefile
# End Source File
# End Group
# Begin Group "AgpTool"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AgpTool\AgpAddBorder.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpAddConstLayer.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpAppend.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpBgpFill.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpBgpFillHole.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpBgpFillN.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpBgpTest.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpBgValue.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpBrList.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpCheckLinkFbr.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpCjeckIn.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpCleare.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpCloseHole.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpConnectJnt.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpConst.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpCopy.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpCountorLink.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpDelete.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpDither.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpDitherEdge.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpDumpRead.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpDumpWrite.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpExtend.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpFlipH.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpFlipV.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpImage.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpJntBrn4.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpLinkForceMaxLA.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpLinkLen.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpLinkNo.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpMakeUnion.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpMold.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpN3ToEdge.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpNf.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpProfile.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpProfileWidth.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpRemoveN3R_06.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpRepositionLayer.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpScriptRead.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpScriptWrite.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpSetBr1_06.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpTool.h
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpTransparent2Flat.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpTransparentWidth.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpUnion.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpUpgrade06.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpZoom.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpZoomP.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\Makefile
# End Source File
# End Group
# Begin Group "EmbedLink"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\EMBEDLINK\EmbedFitBorder.c
# End Source File
# Begin Source File

SOURCE=.\EmbedLink\EmbedFitJnt.c
# End Source File
# Begin Source File

SOURCE=.\EmbedLink\EmbedGapp.c
# End Source File
# Begin Source File

SOURCE=.\EmbedLink\EmbedHunch.c
# End Source File
# Begin Source File

SOURCE=.\EmbedLink\EmbedJntN3.c
# End Source File
# Begin Source File

SOURCE=.\EmbedLink\EmbedLink.c
# End Source File
# Begin Source File

SOURCE=.\EmbedLink\EmbedLink.h
# End Source File
# Begin Source File

SOURCE=.\EmbedLink\EmbedLinkFinal.c
# End Source File
# Begin Source File

SOURCE=.\EmbedLink\EmbedLinkFit.c
# End Source File
# Begin Source File

SOURCE=.\EmbedLink\EmbedLinkFitCurve.c
# End Source File
# Begin Source File

SOURCE=.\EmbedLink\EmbedLinkIn.h
# End Source File
# Begin Source File

SOURCE=.\EmbedLink\EmbedMarkBr.c
# End Source File
# Begin Source File

SOURCE=.\EmbedLink\EmbedN3.c
# End Source File
# Begin Source File

SOURCE=.\EmbedLink\EmbedRidge.c
# End Source File
# Begin Source File

SOURCE=.\EmbedLink\EmbedRlLink.c
# End Source File
# Begin Source File

SOURCE=.\EmbedLink\EmbedSegment.c
# End Source File
# Begin Source File

SOURCE=.\EmbedLink\EmbedSelect.c
# End Source File
# Begin Source File

SOURCE=.\EmbedLink\Makefile
# End Source File
# End Group
# Begin Group "Filter"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Filter\Filter.h
# End Source File
# Begin Source File

SOURCE=.\Filter\FilterAgp.c
# End Source File
# Begin Source File

SOURCE=.\Filter\FilterEdge.c
# End Source File
# Begin Source File

SOURCE=.\Filter\FilterHunch.c
# End Source File
# Begin Source File

SOURCE=.\Filter\FilterLinkLen.c
# End Source File
# Begin Source File

SOURCE=.\Filter\FilterN3.c
# End Source File
# Begin Source File

SOURCE=.\Filter\FilterRh2Hunch.c
# End Source File
# Begin Source File

SOURCE=.\Filter\FilterRidge.c
# End Source File
# Begin Source File

SOURCE=.\Filter\Makefile
# End Source File
# End Group
# Begin Group "GpTool"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GpTool\AdepthTool.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\AgpBox.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\AgpIn.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\AgpInsert.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\AgpLnf.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\AgpNfArray.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\EdgeTool.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\GpTool.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\HunchTool.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\JntEdge.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\JntN3.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\JntN3In.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\JntRN3.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\JntTool.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\LayerTool.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\LinkIn.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\LinkN3.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\LinkTool.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\LinkTool1.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\Makefile
# End Source File
# Begin Source File

SOURCE=.\GpTool\N3Tool.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\NfAux.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\ProfileTool.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\RidgeTool.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\WidthTool.c
# End Source File
# End Group
# Begin Group "GpType"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GpType\AdepthType.h
# End Source File
# Begin Source File

SOURCE=.\GpType\BgpType.h
# End Source File
# Begin Source File

SOURCE=.\GpType\ColorType.h
# End Source File
# Begin Source File

SOURCE=.\GpType\Configuration.h
# End Source File
# Begin Source File

SOURCE=.\GpType\DepthType.h
# End Source File
# Begin Source File

SOURCE=.\GpType\EdgeType.h
# End Source File
# Begin Source File

SOURCE=.\GpType\GpType.h
# End Source File
# Begin Source File

SOURCE=.\GpType\HunchType.h
# End Source File
# Begin Source File

SOURCE=.\GpType\JntType.h
# End Source File
# Begin Source File

SOURCE=.\GpType\LayerType.h
# End Source File
# Begin Source File

SOURCE=.\GpType\LinkType.h
# End Source File
# Begin Source File

SOURCE=.\GpType\MbrType.h
# End Source File
# Begin Source File

SOURCE=.\GpType\N3Type.h
# End Source File
# Begin Source File

SOURCE=.\GpType\NfType.h
# End Source File
# Begin Source File

SOURCE=.\GpType\ProfileType.h
# End Source File
# Begin Source File

SOURCE=.\GpType\RidgeType.h
# End Source File
# Begin Source File

SOURCE=.\GpType\WidthType.h
# End Source File
# End Group
# Begin Group "Inf"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Inf\Inf.h
# End Source File
# Begin Source File

SOURCE=.\Inf\InfAgp.c
# End Source File
# Begin Source File

SOURCE=.\Inf\InfBgp.c
# End Source File
# Begin Source File

SOURCE=.\Inf\InfEdge.c
# End Source File
# Begin Source File

SOURCE=.\Inf\InfHunch.c
# End Source File
# Begin Source File

SOURCE=.\Inf\InfIn.h
# End Source File
# Begin Source File

SOURCE=.\Inf\InfJnt.c
# End Source File
# Begin Source File

SOURCE=.\Inf\InfN3.c
# End Source File
# Begin Source File

SOURCE=.\Inf\InfProfile.c
# End Source File
# Begin Source File

SOURCE=.\Inf\InfRHnch.c
# End Source File
# Begin Source File

SOURCE=.\Inf\InfRidge.c
# End Source File
# Begin Source File

SOURCE=.\Inf\Makefile
# End Source File
# End Group
# Begin Group "LinkTool"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LinkTool\Bezier2Links.c
# End Source File
# Begin Source File

SOURCE=.\LinkTool\LinkAppend.c
# End Source File
# Begin Source File

SOURCE=.\LinkTool\LinkBox.c
# End Source File
# Begin Source File

SOURCE=.\LinkTool\LinkClip.c
# End Source File
# Begin Source File

SOURCE=.\LinkTool\LinkDistance.c
# End Source File
# Begin Source File

SOURCE=.\LinkTool\LinkFilter.c

!IF  "$(CFG)" == "Agp - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Agp - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Agp - Win32 DebugMultithreadedDll"

!ELSEIF  "$(CFG)" == "Agp - Win32 ReleaseMultithreadedDll"

!ELSEIF  "$(CFG)" == "Agp - Win32 ReleaseQA"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\LinkTool\LinkFromGapp.c
# End Source File
# Begin Source File

SOURCE=.\LinkTool\LinkFromLine.c
# End Source File
# Begin Source File

SOURCE=.\LinkTool\LinkInsidePoint.c
# End Source File
# Begin Source File

SOURCE=.\LinkTool\LinkInternalSide.c
# End Source File
# Begin Source File

SOURCE=.\LinkTool\LinkIo.c
# End Source File
# Begin Source File

SOURCE=.\LinkTool\LinkLayer.c
# End Source File
# Begin Source File

SOURCE=.\LinkTool\LinkLayer.h
# End Source File
# Begin Source File

SOURCE=.\LinkTool\LinkReapproximae.c
# End Source File
# Begin Source File

SOURCE=.\LinkTool\LinkSet.c
# End Source File
# Begin Source File

SOURCE=.\LinkTool\LinkSetProfile.c
# End Source File
# Begin Source File

SOURCE=.\LinkTool\LinkSimplify.c
# End Source File
# Begin Source File

SOURCE=.\LinkTool\LinkSplit.c
# End Source File
# Begin Source File

SOURCE=.\LinkTool\LinkTool.h
# End Source File
# Begin Source File

SOURCE=.\LinkTool\LinkTool2.c
# End Source File
# Begin Source File

SOURCE=.\LinkTool\Makefile
# End Source File
# Begin Source File

SOURCE=.\LinkTool\PolylinkCopy.c
# End Source File
# Begin Source File

SOURCE=.\LinkTool\TlSelect.c
# End Source File
# Begin Source File

SOURCE=.\LinkTool\TlType.h
# End Source File
# End Group
# Begin Group "Mold"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Mold\LnAttCConnect.c
# End Source File
# Begin Source File

SOURCE=.\Mold\LnAttCmp.c
# End Source File
# Begin Source File

SOURCE=.\Mold\LnAttCmp.h
# End Source File
# Begin Source File

SOURCE=.\Mold\LnAttCmpBuild.c
# End Source File
# Begin Source File

SOURCE=.\Mold\LnAttCmpFinal.c
# End Source File
# Begin Source File

SOURCE=.\Mold\LnAttCmpStep.c
# End Source File
# Begin Source File

SOURCE=.\Mold\LnAttCmpStep4.c
# End Source File
# Begin Source File

SOURCE=.\Mold\LnAttCmpStepN.c
# End Source File
# Begin Source File

SOURCE=.\Mold\LnAttCmpStepNS.c
# End Source File
# Begin Source File

SOURCE=.\Mold\LnAttCmpStepW.c
# End Source File
# Begin Source File

SOURCE=.\Mold\LnAttCPos.c
# End Source File
# Begin Source File

SOURCE=.\Mold\LnAttCTied.c
# End Source File
# Begin Source File

SOURCE=.\Mold\LnAttCTool.c
# End Source File
# Begin Source File

SOURCE=.\Mold\LnAttCType.h
# End Source File
# Begin Source File

SOURCE=.\Mold\LnAttTool.c
# End Source File
# Begin Source File

SOURCE=.\Mold\LnAttType.h
# End Source File
# Begin Source File

SOURCE=.\Mold\LnDisTool.c
# End Source File
# Begin Source File

SOURCE=.\Mold\LnDisType.h
# End Source File
# Begin Source File

SOURCE=.\Mold\LnSegTool.c
# End Source File
# Begin Source File

SOURCE=.\Mold\LnSegType.h
# End Source File
# Begin Source File

SOURCE=.\Mold\Mold.c
# End Source File
# Begin Source File

SOURCE=.\Mold\Mold.h
# End Source File
# Begin Source File

SOURCE=.\Mold\MoldCrossSeg.c
# End Source File
# Begin Source File

SOURCE=.\Mold\MoldIn.h
# End Source File
# Begin Source File

SOURCE=.\Mold\MoldParallelSeg.c
# End Source File
# End Group
# Begin Group "N3Prime"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\N3Prime\Makefile
# End Source File
# Begin Source File

SOURCE=.\N3Prime\N3Prime.h
# End Source File
# Begin Source File

SOURCE=.\N3Prime\N3PrimeAgp.c
# End Source File
# Begin Source File

SOURCE=.\N3Prime\N3PrimeFree.c
# End Source File
# Begin Source File

SOURCE=.\N3Prime\N3PrimeIn.h
# End Source File
# Begin Source File

SOURCE=.\N3Prime\N3PrimeInNull.c
# End Source File
# Begin Source File

SOURCE=.\N3Prime\N3PrimeLink.c
# End Source File
# Begin Source File

SOURCE=.\N3Prime\N3PrimeLoad.c
# End Source File
# Begin Source File

SOURCE=.\N3Prime\N3PrimeN3ToEdge.c
# End Source File
# Begin Source File

SOURCE=.\N3Prime\N3PrimeProfile.c
# End Source File
# End Group
# Begin Group "RelValue"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\RelValue\AbsValue.c
# End Source File
# Begin Source File

SOURCE=.\RelValue\AbsValueO.c
# End Source File
# Begin Source File

SOURCE=.\RelValue\Makefile
# End Source File
# Begin Source File

SOURCE=.\RelValue\RelValue.c
# End Source File
# Begin Source File

SOURCE=.\RelValue\RelValue.h
# End Source File
# Begin Source File

SOURCE=.\RelValue\RelValueIn.h
# End Source File
# Begin Source File

SOURCE=.\RelValue\SetWidth.c
# End Source File
# End Group
# Begin Group "RlLink"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\RlLink\LinkReplace.c
# End Source File
# Begin Source File

SOURCE=.\RlLink\Makefile
# End Source File
# Begin Source File

SOURCE=.\RlLink\RlCorner.c
# End Source File
# Begin Source File

SOURCE=.\RlLink\RlCornerArc.c

!IF  "$(CFG)" == "Agp - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Agp - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Agp - Win32 DebugMultithreadedDll"

!ELSEIF  "$(CFG)" == "Agp - Win32 ReleaseMultithreadedDll"

!ELSEIF  "$(CFG)" == "Agp - Win32 ReleaseQA"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RlLink\RlGapp.c
# End Source File
# Begin Source File

SOURCE=.\RlLink\RlLink.c
# End Source File
# Begin Source File

SOURCE=.\RlLink\RlLink.h
# End Source File
# Begin Source File

SOURCE=.\RlLink\RlLink2.c
# End Source File
# Begin Source File

SOURCE=.\RlLink\RlTool.c
# End Source File
# Begin Source File

SOURCE=.\RlLink\RlTool2.c
# End Source File
# Begin Source File

SOURCE=.\RlLink\RlType.h
# End Source File
# Begin Source File

SOURCE=.\RlLink\RlType2.h
# End Source File
# End Group
# Begin Group "Texture"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Texture\Texture.h
# End Source File
# Begin Source File

SOURCE=.\Texture\TextureCopy.c
# End Source File
# Begin Source File

SOURCE=.\Texture\TextureCopyHunch.c
# End Source File
# Begin Source File

SOURCE=.\Texture\TexturePaste.c
# End Source File
# Begin Source File

SOURCE=.\Texture\TexturePasteHunch.c
# End Source File
# End Group
# Begin Group "Depth"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Depth\Depth.h
# End Source File
# Begin Source File

SOURCE=.\Depth\DepthModelType.h
# End Source File
# Begin Source File

SOURCE=.\Depth\DmBottle.c
# End Source File
# Begin Source File

SOURCE=.\Depth\DmBottleType.h
# End Source File
# Begin Source File

SOURCE=.\Depth\DmCorner.c
# End Source File
# Begin Source File

SOURCE=.\Depth\DmCorner90View.c
# End Source File
# Begin Source File

SOURCE=.\Depth\DmCornerType.h
# End Source File
# Begin Source File

SOURCE=.\Depth\DmPlane.c
# End Source File
# Begin Source File

SOURCE=.\Depth\DmPlaneType.h
# End Source File
# Begin Source File

SOURCE=.\Depth\DmTool.c
# End Source File
# End Group
# Begin Group "Layer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Layer\AgpLayerFiletr.c
# End Source File
# Begin Source File

SOURCE=.\Layer\AgpLayerIdF.c
# End Source File
# Begin Source File

SOURCE=.\Layer\AgpLayerIdF1.c
# End Source File
# Begin Source File

SOURCE=.\Layer\AgpLayerValidate.c
# End Source File
# Begin Source File

SOURCE=.\Layer\Layer.h
# End Source File
# Begin Source File

SOURCE=.\Layer\LayerAux.c
# End Source File
# Begin Source File

SOURCE=.\Layer\LayerAux.h
# End Source File
# End Group
# Begin Group "Contour"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Contour\ContourIo.c
# End Source File
# Begin Source File

SOURCE=.\Contour\ContourTool.c
# End Source File
# Begin Source File

SOURCE=.\Contour\ContourType.h
# End Source File
# Begin Source File

SOURCE=.\Contour\LinkDisTool.c
# End Source File
# Begin Source File

SOURCE=.\Contour\LinkDisType.h
# End Source File
# Begin Source File

SOURCE=.\Contour\PlinkTool.c
# End Source File
# Begin Source File

SOURCE=.\Contour\PlinkType.h
# End Source File
# End Group
# Begin Group "Log"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Log\Log.c
# End Source File
# Begin Source File

SOURCE=.\Log\Log.h
# End Source File
# End Group
# Begin Group "N3Aux"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\N3Aux\N3Aux.c
# End Source File
# Begin Source File

SOURCE=.\N3Aux\N3Aux.h
# End Source File
# Begin Source File

SOURCE=.\N3Aux\N3Aux_1.c
# End Source File
# Begin Source File

SOURCE=.\N3Aux\N3AuxFree.c
# End Source File
# Begin Source File

SOURCE=.\N3Aux\N3AuxIn.c
# End Source File
# Begin Source File

SOURCE=.\N3Aux\N3AuxIn.h
# End Source File
# Begin Source File

SOURCE=.\N3Aux\N3AuxInDegenric.c
# End Source File
# Begin Source File

SOURCE=.\N3Aux\N3AuxInNull.c
# End Source File
# Begin Source File

SOURCE=.\N3Aux\N3AuxJnt.c
# End Source File
# Begin Source File

SOURCE=.\N3Aux\N3AuxLink.c
# End Source File
# Begin Source File

SOURCE=.\N3Aux\N3AuxLoad.c
# End Source File
# Begin Source File

SOURCE=.\N3Aux\N3AuxProfile.c
# End Source File
# Begin Source File

SOURCE=.\N3Aux\N3AuxTool.c
# End Source File
# Begin Source File

SOURCE=.\N3Aux\N3AuxType.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Makefile
# End Source File
# End Target
# End Project
