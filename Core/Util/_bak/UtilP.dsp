# Microsoft Developer Studio Project File - Name="UtilP" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=UtilP - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "UtilP.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "UtilP.mak" CFG="UtilP - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "UtilP - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "UtilP - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "UtilP - Win32 ReleaseQA" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Gp_Vim/Core/Util", WBIBAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "UtilP - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseP"
# PROP BASE Intermediate_Dir "ReleaseP"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
MTL=midl.exe
LINK32=link.exe -lib
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../Util" /D "NDEBUG" /D "_WINDOWS" /D "__SYMBIAN32__" /D "WIN32" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\UtilP.lib"

!ELSEIF  "$(CFG)" == "UtilP - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugP"
# PROP BASE Intermediate_Dir "DebugP"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugP"
# PROP Intermediate_Dir "DebugP"
# PROP Target_Dir ""
MTL=midl.exe
LINK32=link.exe -lib
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /GX /ZI /Od /I "../Util" /D "_WINDOWS" /D "_DEBUG" /D "WIN32" /D "PCPLAYER" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\UtilPD.lib"

!ELSEIF  "$(CFG)" == "UtilP - Win32 ReleaseQA"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "UtilP___Win32_ReleaseQA"
# PROP BASE Intermediate_Dir "UtilP___Win32_ReleaseQA"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseQA"
# PROP Intermediate_Dir "ReleaseQA"
# PROP Target_Dir ""
MTL=midl.exe
LINK32=link.exe -lib
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "../UtilP" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../Util" /D "NDEBUG" /D "_WINDOWS" /D "__SYMBIAN32__" /D "WIN32" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Lib\UtilP.lib"
# ADD LIB32 /nologo /out:"..\Lib\UtilP.lib"

!ENDIF 

# Begin Target

# Name "UtilP - Win32 Release"
# Name "UtilP - Win32 Debug"
# Name "UtilP - Win32 ReleaseQA"
# Begin Group "Uview"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Uview\ViewCamera.c
# End Source File
# Begin Source File

SOURCE=.\Uview\ViewCreateNormal.c
# End Source File
# Begin Source File

SOURCE=.\Uview\ViewNormal.c
# End Source File
# Begin Source File

SOURCE=.\Uview\ViewPer.c
# End Source File
# Begin Source File

SOURCE=.\Uview\ViewPlane.c
# End Source File
# Begin Source File

SOURCE=.\Uview\ViewSub.c
# End Source File
# Begin Source File

SOURCE=.\Uview\ViewTool.c
# End Source File
# Begin Source File

SOURCE=.\Uview\ViewType.h
# End Source File
# End Group
# Begin Group "Ubst"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Ubst\BstFile.c
# End Source File
# Begin Source File

SOURCE=.\Ubst\BstGet.c
# End Source File
# Begin Source File

SOURCE=.\Ubst\BstTool.c
# End Source File
# Begin Source File

SOURCE=.\Ubst\BstType.h
# End Source File
# End Group
# Begin Group "Ucst"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Ucst\CstTool.c
# End Source File
# Begin Source File

SOURCE=.\Ucst\CstType.h
# End Source File
# End Group
# Begin Group "Ucode"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Ucode\code.c
# End Source File
# Begin Source File

SOURCE=.\Ucode\code.h
# End Source File
# End Group
# Begin Group "Uconfig3d"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Uconfig3d\Config3d.h
# End Source File
# Begin Source File

SOURCE=.\Uconfig3d\Config3dTool.c
# End Source File
# End Group
# Begin Group "Uigp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Uigp\GpBuildNumber.c

!IF  "$(CFG)" == "UtilP - Win32 Release"

!ELSEIF  "$(CFG)" == "UtilP - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UtilP - Win32 ReleaseQA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Uigp\GpBuildNumber.h

!IF  "$(CFG)" == "UtilP - Win32 Release"

!ELSEIF  "$(CFG)" == "UtilP - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UtilP - Win32 ReleaseQA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Uigp\GpByteOrder.c

!IF  "$(CFG)" == "UtilP - Win32 Release"

!ELSEIF  "$(CFG)" == "UtilP - Win32 Debug"

!ELSEIF  "$(CFG)" == "UtilP - Win32 ReleaseQA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Uigp\GpFile.c

!IF  "$(CFG)" == "UtilP - Win32 Release"

!ELSEIF  "$(CFG)" == "UtilP - Win32 Debug"

!ELSEIF  "$(CFG)" == "UtilP - Win32 ReleaseQA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Uigp\GpFile1.c

!IF  "$(CFG)" == "UtilP - Win32 Release"

!ELSEIF  "$(CFG)" == "UtilP - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UtilP - Win32 ReleaseQA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Uigp\GpFileName.c

!IF  "$(CFG)" == "UtilP - Win32 Release"

!ELSEIF  "$(CFG)" == "UtilP - Win32 Debug"

!ELSEIF  "$(CFG)" == "UtilP - Win32 ReleaseQA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Uigp\GpFunction.c
# End Source File
# Begin Source File

SOURCE=.\Uigp\GpIo.c
# End Source File
# Begin Source File

SOURCE=.\Uigp\GpRelinquish.c
# End Source File
# Begin Source File

SOURCE=.\Uigp\igp.h
# End Source File
# End Group
# Begin Group "Umedia"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Umedia\MediaDataTool.c
# End Source File
# End Group
# Begin Group "Uheap"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Uheap\HeapTool.c
# End Source File
# End Group
# End Target
# End Project
