# Microsoft Developer Studio Project File - Name="VideoCodec" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=VideoCodec - Win32 DebugMultithreadedDll
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VideoCodec.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VideoCodec.mak" CFG="VideoCodec - Win32 DebugMultithreadedDll"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VideoCodec - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "VideoCodec - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "VideoCodec - Win32 DebugMultithreadedDll" (based on "Win32 (x86) Static Library")
!MESSAGE "VideoCodec - Win32 ReleaseMultiThreadedDll" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Gp_Vim/Video/VideoCodec", ORAEAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VideoCodec - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /Zi /O2 /I "..\..\core\Util" /I "..\..\core\ImageLib" /I "..\..\Audio\AudioLib" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\VideoCodec.lib"

!ELSEIF  "$(CFG)" == "VideoCodec - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /ZI /Od /I "..\..\core\Util" /I "..\..\core\ImageLib" /I "..\..\Audio\AudioLib" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\VideoCodecD.lib"

!ELSEIF  "$(CFG)" == "VideoCodec - Win32 DebugMultithreadedDll"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "VideoCodec___Win32_DebugMultithreadedDll"
# PROP BASE Intermediate_Dir "VideoCodec___Win32_DebugMultithreadedDll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "VideoCodec___Win32_DebugMultithreadedDll"
# PROP Intermediate_Dir "VideoCodec___Win32_DebugMultithreadedDll"
# PROP Target_Dir ""
LINK32=link.exe -lib
MTL=midl.exe
# ADD BASE CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "..\Util" /I "..\ImageLib" /I "..\..\VimGui\wutil" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Util" /I "..\ImageLib" /I "..\..\VimGui\wutil" /I "..\VideoCodec" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "VideoCodec - Win32 ReleaseMultiThreadedDll"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "VideoCodec___Win32_ReleaseMultiThreadedDll"
# PROP BASE Intermediate_Dir "VideoCodec___Win32_ReleaseMultiThreadedDll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "VideoCodec___Win32_ReleaseMultiThreadedDll"
# PROP Intermediate_Dir "VideoCodec___Win32_ReleaseMultiThreadedDll"
# PROP Target_Dir ""
LINK32=link.exe -lib
MTL=midl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "..\VideoCodec" /I "..\Util" /I "..\ImageLib" /I "..\..\VimGui\wutil" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\VideoCodec" /I "..\Util" /I "..\ImageLib" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "VideoCodec - Win32 Release"
# Name "VideoCodec - Win32 Debug"
# Name "VideoCodec - Win32 DebugMultithreadedDll"
# Name "VideoCodec - Win32 ReleaseMultiThreadedDll"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AudioStreamEncoder.cpp
# End Source File
# Begin Source File

SOURCE=.\VideoDecode.cpp
# End Source File
# Begin Source File

SOURCE=.\VideoDecoder.cpp
# End Source File
# Begin Source File

SOURCE=.\VideoEncoder.cpp
# End Source File
# Begin Source File

SOURCE=.\VideoStreamEncoder.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AudioStreamEncoder.h
# End Source File
# Begin Source File

SOURCE=.\VideoDecode.h
# End Source File
# Begin Source File

SOURCE=.\VideoDecoder.h
# End Source File
# Begin Source File

SOURCE=.\VideoEncoder.h
# End Source File
# Begin Source File

SOURCE=.\VideoStreamEncoder.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Makefile
# End Source File
# End Target
# End Project
