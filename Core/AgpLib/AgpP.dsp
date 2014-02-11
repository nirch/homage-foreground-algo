# Microsoft Developer Studio Project File - Name="AgpP" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=AgpP - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AgpP.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AgpP.mak" CFG="AgpP - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AgpP - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "AgpP - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "AgpP - Win32 ReleaseQA" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Gp_Vim/Core/AgpLib", ARGBAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AgpP - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\EpnLib" /I "..\AgpLib" /I "..\EpLib" /I "..\VimageLib" /I "..\ExpandiLib" /I "..\Util" /I "..\CodingLib" /I "..\CorTransformLib" /I "..\ImageLib" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "_WINDOWS" /D "WIN32" /D "__SYMBIAN32__" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\AgpP.lib"

!ELSEIF  "$(CFG)" == "AgpP - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugP"
# PROP Intermediate_Dir "DebugP"
# PROP Target_Dir ""
LINK32=link.exe -lib
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\EpnLib" /I "..\AgpLib" /I "..\EpLib" /I "..\VimageLib" /I "..\ExpandiLib" /I "..\Util" /I "..\CodingLib" /I "..\CorTransformLib" /I "..\ImageLib" /D "_MBCS" /D "_LIB" /D "_WINDOWS" /D "_DEBUG" /D "WIN32" /D "PCPLAYER" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\AgpPD.lib"

!ELSEIF  "$(CFG)" == "AgpP - Win32 ReleaseQA"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "AgpP___Win32_ReleaseQA"
# PROP BASE Intermediate_Dir "AgpP___Win32_ReleaseQA"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseQA"
# PROP Intermediate_Dir "ReleaseQA"
# PROP Target_Dir ""
LINK32=link.exe -lib
MTL=midl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "..\AgpLib" /I "..\EpLib" /I "..\VimageLib" /I "..\ExpandiLib" /I "..\Util" /I "..\ExpandLib" /I "..\CodingLib" /I "..\CorTransformLib" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\EpnLib" /I "..\AgpLib" /I "..\EpLib" /I "..\VimageLib" /I "..\ExpandiLib" /I "..\Util" /I "..\CodingLib" /I "..\CorTransformLib" /I "..\ImageLib" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "_WINDOWS" /D "WIN32" /D "__SYMBIAN32__" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\AgpP.lib"

!ENDIF 

# Begin Target

# Name "AgpP - Win32 Release"
# Name "AgpP - Win32 Debug"
# Name "AgpP - Win32 ReleaseQA"
# Begin Group "AgpColor"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AgpColor\AgpColor.h
# End Source File
# Begin Source File

SOURCE=.\AgpColor\AgpRgbRange.c
# End Source File
# Begin Source File

SOURCE=.\AgpColor\AgpYCrCbRgb.c
# End Source File
# End Group
# Begin Group "AgpDepth"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AgpDepth\AgpDepth.h
# End Source File
# Begin Source File

SOURCE=.\AgpDepth\AgpDepthDefault.c
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

SOURCE=.\AgpLayer\AgpLayerContourPolylink.c
# End Source File
# Begin Source File

SOURCE=.\AgpLayer\AgpLayerInit.c
# End Source File
# Begin Source File

SOURCE=.\AgpLayer\AgpLayerSelect.c
# End Source File
# End Group
# Begin Group "AgpTool"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AgpTool\AgpFlipH.c
# End Source File
# Begin Source File

SOURCE=.\AgpTool\AgpTransparentWidth.c
# End Source File
# End Group
# Begin Group "Depth"

# PROP Default_Filter ""
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

SOURCE=.\Depth\DmPlane.c
# End Source File
# Begin Source File

SOURCE=.\Depth\DmTool.c
# End Source File
# End Group
# Begin Group "GpTool"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GpTool\AdepthTool.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\AgpLnf.c
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

SOURCE=.\GpTool\JntRN3.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\JntTool.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\LayerTool.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\LinkN3.c

!IF  "$(CFG)" == "AgpP - Win32 Release"

!ELSEIF  "$(CFG)" == "AgpP - Win32 Debug"

!ELSEIF  "$(CFG)" == "AgpP - Win32 ReleaseQA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GpTool\LinkTool.c
# End Source File
# Begin Source File

SOURCE=.\GpTool\LinkTool1.c
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

SOURCE=.\GpType\VimFile.h
# End Source File
# Begin Source File

SOURCE=.\GpType\WidthType.h
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
# End Target
# End Project
