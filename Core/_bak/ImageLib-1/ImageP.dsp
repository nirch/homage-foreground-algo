# Microsoft Developer Studio Project File - Name="ImageP" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ImageP - Win32 ReleaseQA
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ImageP.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ImageP.mak" CFG="ImageP - Win32 ReleaseQA"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ImageP - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ImageP - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ImageP - Win32 ReleaseQA" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Gp_Vim/Core/ImageLib", ERKCAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ImageP - Win32 Release"

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
MTL=midl.exe
LINK32=link.exe -lib
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../ImageLib" /I "../Util" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "TIF_PLATFORM_CONSOLE" /D "__SYMBIAN32__" /D "WIN32" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\ImageP.lib"

!ELSEIF  "$(CFG)" == "ImageP - Win32 Debug"

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
MTL=midl.exe
LINK32=link.exe -lib
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../ImageLib" /I "../Util" /I "./" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "WIN32" /D "PCPLAYER" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\ImagePD.lib"

!ELSEIF  "$(CFG)" == "ImageP - Win32 ReleaseQA"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ImageP___Win32_ReleaseQA"
# PROP BASE Intermediate_Dir "ImageP___Win32_ReleaseQA"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseQA"
# PROP Intermediate_Dir "ReleaseQA"
# PROP Target_Dir ""
MTL=midl.exe
LINK32=link.exe -lib
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "../ImageLib" /I "../Util" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../ImageLib" /I "../Util" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "TIF_PLATFORM_CONSOLE" /D "__SYMBIAN32__" /D "WIN32" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\ImageP.lib"

!ENDIF 

# Begin Target

# Name "ImageP - Win32 Release"
# Name "ImageP - Win32 Debug"
# Name "ImageP - Win32 ReleaseQA"
# Begin Group "ImageP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Image\Image.c
# End Source File
# Begin Source File

SOURCE=.\Image\Image4Tool.c
# End Source File
# Begin Source File

SOURCE=.\Image\ImagePreview.c

!IF  "$(CFG)" == "ImageP - Win32 Release"

!ELSEIF  "$(CFG)" == "ImageP - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ImageP - Win32 ReleaseQA"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Image\Makefile

!IF  "$(CFG)" == "ImageP - Win32 Release"

!ELSEIF  "$(CFG)" == "ImageP - Win32 Debug"

!ELSEIF  "$(CFG)" == "ImageP - Win32 ReleaseQA"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Image\PaletteTool.c
# End Source File
# End Group
# Begin Group "ImageType"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ImageType\ImageTool.h
# End Source File
# Begin Source File

SOURCE=.\ImageType\ImageType.h
# End Source File
# Begin Source File

SOURCE=.\ImageType\PaletteType.h
# End Source File
# End Group
# Begin Group "BMP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BMP\ImageBmp.h
# End Source File
# Begin Source File

SOURCE=.\BMP\ImageWriteBmp.c
# End Source File
# End Group
# Begin Source File

SOURCE=.\Makefile
# End Source File
# End Target
# End Project
