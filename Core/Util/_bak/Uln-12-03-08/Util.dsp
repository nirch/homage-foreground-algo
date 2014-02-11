# Microsoft Developer Studio Project File - Name="Util" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Util - Win32 DebugMultithreadedDll
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Util.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Util.mak" CFG="Util - Win32 DebugMultithreadedDll"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Util - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Util - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "Util - Win32 DebugMultithreadedDll" (based on "Win32 (x86) Static Library")
!MESSAGE "Util - Win32 ReleaseMultithreadedDll" (based on "Win32 (x86) Static Library")
!MESSAGE "Util - Win32 ReleaseQA" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Gp_Vim/Core/Util", WBIBAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Util - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /Zi /O2 /I "..\..\Z3rdParty\jni" /I "..\..\Z3rdParty\jni\win32" /I "../Util" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\Util.lib"

!ELSEIF  "$(CFG)" == "Util - Win32 Debug"

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
MTL=midl.exe
LINK32=link.exe -lib
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /GX /Z7 /Od /I "..\..\Z3rdParty\jni" /I "..\..\Z3rdParty\jni\win32" /I "../Util" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\UtilD.lib"

!ELSEIF  "$(CFG)" == "Util - Win32 DebugMultithreadedDll"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Util___Win32_DebugMultithreadedDll"
# PROP BASE Intermediate_Dir "Util___Win32_DebugMultithreadedDll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Util___Win32_DebugMultithreadedDll"
# PROP Intermediate_Dir "Util___Win32_DebugMultithreadedDll"
# PROP Target_Dir ""
MTL=midl.exe
LINK32=link.exe -lib
# ADD BASE CPP /nologo /MTd /W3 /GX /Z7 /Od /I "../Util" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /ZI /Od /I "..\..\Z3rdParty\jni" /I "..\..\Z3rdParty\jni\win32" /I "../Util" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Util - Win32 ReleaseMultithreadedDll"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Util___Win32_ReleaseMultithreadedDll"
# PROP BASE Intermediate_Dir "Util___Win32_ReleaseMultithreadedDll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Util___Win32_ReleaseMultithreadedDll"
# PROP Intermediate_Dir "Util___Win32_ReleaseMultithreadedDll"
# PROP Target_Dir ""
MTL=midl.exe
LINK32=link.exe -lib
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "../Util" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../Util" /I "..\..\Z3rdParty\jni" /I "..\..\Z3rdParty\jni\win32" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Util - Win32 ReleaseQA"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Util___Win32_ReleaseQA"
# PROP BASE Intermediate_Dir "Util___Win32_ReleaseQA"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseQA"
# PROP Intermediate_Dir "ReleaseQA"
# PROP Target_Dir ""
MTL=midl.exe
LINK32=link.exe -lib
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "../Util" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../Util" /I "..\..\Z3rdParty\jni" /I "..\..\Z3rdParty\jni\win32" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\Util.lib"

!ENDIF 

# Begin Target

# Name "Util - Win32 Release"
# Name "Util - Win32 Debug"
# Name "Util - Win32 DebugMultithreadedDll"
# Name "Util - Win32 ReleaseMultithreadedDll"
# Name "Util - Win32 ReleaseQA"
# Begin Group "Ubase64"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Ubase64\Base64.cpp
# End Source File
# Begin Source File

SOURCE=.\Ubase64\Base64.h
# End Source File
# Begin Source File

SOURCE=.\Ubase64\Makefile
# End Source File
# End Group
# Begin Group "Ubox"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Ubox\Box2d.h
# End Source File
# Begin Source File

SOURCE=.\Ubox\Box2iTool.c
# End Source File
# Begin Source File

SOURCE=.\Ubox\Box2Tool.c
# End Source File
# Begin Source File

SOURCE=.\Ubox\Makefile
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

SOURCE=.\Ubst\BstIn.c
# End Source File
# Begin Source File

SOURCE=.\Ubst\BstPut.c
# End Source File
# Begin Source File

SOURCE=.\Ubst\BstTool.c
# End Source File
# Begin Source File

SOURCE=.\Ubst\BstType.h
# End Source File
# Begin Source File

SOURCE=.\Ubst\Makefile
# End Source File
# End Group
# Begin Group "Ucfg"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Ucfg\CfgParser.c
# End Source File
# Begin Source File

SOURCE=.\Ucfg\CfgTool.c
# End Source File
# Begin Source File

SOURCE=.\Ucfg\CfgType.h
# End Source File
# Begin Source File

SOURCE=.\Ucfg\CfgWrite.c
# End Source File
# Begin Source File

SOURCE=.\Ucfg\Makefile
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
# Begin Source File

SOURCE=.\Ucode\Makefile
# End Source File
# End Group
# Begin Group "Uconfig3d"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Uconfig3d\Config3d.h
# End Source File
# Begin Source File

SOURCE=.\Uconfig3d\Config3dIo.c
# End Source File
# Begin Source File

SOURCE=.\Uconfig3d\Config3dTool.c
# End Source File
# Begin Source File

SOURCE=.\Uconfig3d\Config3dTrajectory.c
# End Source File
# Begin Source File

SOURCE=.\Uconfig3d\Makefile
# End Source File
# End Group
# Begin Group "Ucst"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Ucst\CstFile.c
# End Source File
# Begin Source File

SOURCE=.\Ucst\CstTool.c
# End Source File
# Begin Source File

SOURCE=.\Ucst\CstType.h
# End Source File
# Begin Source File

SOURCE=.\Ucst\CstXml.c
# End Source File
# Begin Source File

SOURCE=.\Ucst\Makefile
# End Source File
# End Group
# Begin Group "Ufbst"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Ufbst\FbstGet.c
# End Source File
# Begin Source File

SOURCE=.\Ufbst\FbstPut.c
# End Source File
# Begin Source File

SOURCE=.\Ufbst\FbstTool.c
# End Source File
# Begin Source File

SOURCE=.\Ufbst\FbstType.h
# End Source File
# Begin Source File

SOURCE=.\Ufbst\Makefile
# End Source File
# End Group
# Begin Group "UGeoApp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\UGeoApp\GappTool.c
# End Source File
# Begin Source File

SOURCE=.\UGeoApp\GelmTool.c
# End Source File
# Begin Source File

SOURCE=.\UGeoApp\GelmType.h
# End Source File
# Begin Source File

SOURCE=.\UGeoApp\GeoApp.c
# End Source File
# Begin Source File

SOURCE=.\UGeoApp\GeoApp.h
# End Source File
# Begin Source File

SOURCE=.\UGeoApp\GeoApp1.c
# End Source File
# Begin Source File

SOURCE=.\UGeoApp\GeoAppLinec.c
# End Source File
# Begin Source File

SOURCE=.\UGeoApp\ls_appr.c
# End Source File
# Begin Source File

SOURCE=.\UGeoApp\ls_appr.h
# End Source File
# Begin Source File

SOURCE=.\UGeoApp\Makefile
# End Source File
# End Group
# Begin Group "Ugio"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Ugio\GioTool.c
# End Source File
# Begin Source File

SOURCE=.\Ugio\GioType.h
# End Source File
# Begin Source File

SOURCE=.\Ugio\Makefile
# End Source File
# End Group
# Begin Group "Uheap"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Uheap\HeapSTool.c
# End Source File
# Begin Source File

SOURCE=.\Uheap\HeapSType.h
# End Source File
# Begin Source File

SOURCE=.\Uheap\HeapTool.c
# End Source File
# Begin Source File

SOURCE=.\Uheap\HeapType.h
# End Source File
# Begin Source File

SOURCE=.\Uheap\Makefile
# End Source File
# End Group
# Begin Group "Uhuffman"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Uhuffman\Huffman.c
# End Source File
# Begin Source File

SOURCE=.\Uhuffman\Huffman.h
# End Source File
# Begin Source File

SOURCE=.\Uhuffman\HuffmanGet.c
# End Source File
# Begin Source File

SOURCE=.\Uhuffman\HuffmanIn.h
# End Source File
# Begin Source File

SOURCE=.\Uhuffman\HuffmanPut.c
# End Source File
# Begin Source File

SOURCE=.\Uhuffman\Makefile
# End Source File
# End Group
# Begin Group "Uigp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Uigp\GpBuildNumber.c
# End Source File
# Begin Source File

SOURCE=.\Uigp\GpBuildNumber.h
# End Source File
# Begin Source File

SOURCE=.\Uigp\GpByteOrder.c
# End Source File
# Begin Source File

SOURCE=.\Uigp\GpDir.c
# End Source File
# Begin Source File

SOURCE=.\Uigp\GpFile.c
# End Source File
# Begin Source File

SOURCE=.\Uigp\GpFile1.c
# End Source File
# Begin Source File

SOURCE=.\Uigp\GpFileName.c
# End Source File
# Begin Source File

SOURCE=.\Uigp\GpFunction.c
# End Source File
# Begin Source File

SOURCE=.\Uigp\GpIo.c
# End Source File
# Begin Source File

SOURCE=.\Uigp\GpMsg.c
# End Source File
# Begin Source File

SOURCE=.\Uigp\GpRelinquish.c
# End Source File
# Begin Source File

SOURCE=.\Uigp\GpTempFile.c
# End Source File
# Begin Source File

SOURCE=.\Uigp\igp.h
# End Source File
# Begin Source File

SOURCE=.\Uigp\M64Type.h
# End Source File
# Begin Source File

SOURCE=.\Uigp\Makefile
# End Source File
# End Group
# Begin Group "Uinf"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Uinf\inf.c
# End Source File
# Begin Source File

SOURCE=.\Uinf\Makefile
# End Source File
# Begin Source File

SOURCE=.\Uinf\uinf.h
# End Source File
# End Group
# Begin Group "Ujet1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Ujet1\Jet1Tool.c
# End Source File
# Begin Source File

SOURCE=.\Ujet1\Jet1Type.h
# End Source File
# Begin Source File

SOURCE=.\Ujet1\Makefile
# End Source File
# End Group
# Begin Group "Ujet2"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Ujet2\AppJet2.c
# End Source File
# Begin Source File

SOURCE=.\Ujet2\CuspJmap23.c
# End Source File
# Begin Source File

SOURCE=.\Ujet2\DiagonalJet2.c
# End Source File
# Begin Source File

SOURCE=.\Ujet2\FoldJmap23.c
# End Source File
# Begin Source File

SOURCE=.\Ujet2\InverseJmap23.c
# End Source File
# Begin Source File

SOURCE=.\Ujet2\Jet23Array.c
# End Source File
# Begin Source File

SOURCE=.\Ujet2\Jet23Map.c
# End Source File
# Begin Source File

SOURCE=.\Ujet2\Jet23Tool.c
# End Source File
# Begin Source File

SOURCE=.\Ujet2\Jet23Type.h
# End Source File
# Begin Source File

SOURCE=.\Ujet2\Jet2Array.c
# End Source File
# Begin Source File

SOURCE=.\Ujet2\Jet2Inverse.c
# End Source File
# Begin Source File

SOURCE=.\Ujet2\Jet2Io.c
# End Source File
# Begin Source File

SOURCE=.\Ujet2\Jet2Map.c
# End Source File
# Begin Source File

SOURCE=.\Ujet2\Jet2Tool.c
# End Source File
# Begin Source File

SOURCE=.\Ujet2\Jet2Type.h
# End Source File
# Begin Source File

SOURCE=.\Ujet2\Makefile
# End Source File
# End Group
# Begin Group "Ujni"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Ujni\Makefile
# End Source File
# Begin Source File

SOURCE=.\Ujni\VimJni.cpp
# End Source File
# Begin Source File

SOURCE=.\Ujni\VimJni.h
# End Source File
# Begin Source File

SOURCE=.\Ujni\VimJvm.cpp
# End Source File
# Begin Source File

SOURCE=.\Ujni\VimJvm.h
# End Source File
# End Group
# Begin Group "Ulz"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Ulz\lz.h
# End Source File
# Begin Source File

SOURCE=.\Ulz\lz12_decode.c
# End Source File
# Begin Source File

SOURCE=.\Ulz\lz12_encode.c
# End Source File
# Begin Source File

SOURCE=.\Ulz\lz_decode.c
# End Source File
# Begin Source File

SOURCE=.\Ulz\lz_encode.c
# End Source File
# Begin Source File

SOURCE=.\Ulz\Makefile
# End Source File
# End Group
# Begin Group "Umat"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Umat\Makefile
# End Source File
# Begin Source File

SOURCE=.\Umat\Mat2fBase.c
# End Source File
# Begin Source File

SOURCE=.\Umat\Mat2fBaseDct.c
# End Source File
# Begin Source File

SOURCE=.\Umat\Mat2fBaseJet2.c
# End Source File
# Begin Source File

SOURCE=.\Umat\Mat2fTool.c
# End Source File
# Begin Source File

SOURCE=.\Umat\Mat2fType.h
# End Source File
# End Group
# Begin Group "Umath"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Umath\LT2Tool.c
# End Source File
# Begin Source File

SOURCE=.\Umath\LT2Type.h
# End Source File
# Begin Source File

SOURCE=.\Umath\Makefile
# End Source File
# Begin Source File

SOURCE=.\Umath\MathLinearEquation.c
# End Source File
# Begin Source File

SOURCE=.\Umath\MathLinearEquation2.c
# End Source File
# Begin Source File

SOURCE=.\Umath\MathLinerExquation9.c
# End Source File
# Begin Source File

SOURCE=.\Umath\MathMatrix.c
# End Source File
# Begin Source File

SOURCE=.\Umath\MathMatrixInvese4.c
# End Source File
# Begin Source File

SOURCE=.\Umath\MathMatrixInvese6.c
# End Source File
# Begin Source File

SOURCE=.\Umath\Matrix3Tool.c
# End Source File
# Begin Source File

SOURCE=.\Umath\Matrix3Type.h
# End Source File
# Begin Source File

SOURCE=.\Umath\Matrix4Tool.c
# End Source File
# Begin Source File

SOURCE=.\Umath\Matrix4Type.h
# End Source File
# Begin Source File

SOURCE=.\Umath\umath.h
# End Source File
# End Group
# Begin Group "Umedia"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Umedia\Makefile
# End Source File
# Begin Source File

SOURCE=.\Umedia\MdFormat.cpp
# End Source File
# Begin Source File

SOURCE=.\Umedia\MdFormat.h
# End Source File
# Begin Source File

SOURCE=.\Umedia\MdFormatIn.h
# End Source File
# Begin Source File

SOURCE=.\Umedia\MdFormatXml.cpp
# End Source File
# Begin Source File

SOURCE=.\Umedia\MediaDataCo.c
# End Source File
# Begin Source File

SOURCE=.\Umedia\MediaDataRead.c
# End Source File
# Begin Source File

SOURCE=.\Umedia\MediaDataTool.c
# End Source File
# Begin Source File

SOURCE=.\Umedia\MediaDataType.h
# End Source File
# Begin Source File

SOURCE=.\Umedia\MediaFile.c
# End Source File
# Begin Source File

SOURCE=.\Umedia\MediaFormat.c
# End Source File
# End Group
# Begin Group "Uprm"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Uprm\Makefile
# End Source File
# Begin Source File

SOURCE=.\Uprm\prm.c
# End Source File
# Begin Source File

SOURCE=.\Uprm\prm.h
# End Source File
# Begin Source File

SOURCE=.\Uprm\PrmAux.c
# End Source File
# Begin Source File

SOURCE=.\Uprm\PrmGroup.c
# End Source File
# End Group
# Begin Group "Usmil"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Usmil\Makefile
# End Source File
# Begin Source File

SOURCE=.\Usmil\SmilBuild.c
# End Source File
# Begin Source File

SOURCE=.\Usmil\SmilParser.c
# End Source File
# Begin Source File

SOURCE=.\Usmil\SmilTool.c
# End Source File
# Begin Source File

SOURCE=.\Usmil\SmilType.h
# End Source File
# Begin Source File

SOURCE=.\Usmil\SmilUnion.c
# End Source File
# End Group
# Begin Group "Usynch"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Usynch\Makefile
# End Source File
# Begin Source File

SOURCE=.\Usynch\usynch.c
# End Source File
# Begin Source File

SOURCE=.\Usynch\usynch.h
# End Source File
# End Group
# Begin Group "Utime"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Utime\date.h
# End Source File
# Begin Source File

SOURCE=.\Utime\GpTime.c
# End Source File
# Begin Source File

SOURCE=.\Utime\GpTime.h
# End Source File
# Begin Source File

SOURCE=.\Utime\hrtime.cpp
# End Source File
# Begin Source File

SOURCE=.\Utime\hrtime.h
# End Source File
# Begin Source File

SOURCE=.\Utime\Makefile
# End Source File
# End Group
# Begin Group "Uunity"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Uunity\Makefile
# End Source File
# Begin Source File

SOURCE=.\Uunity\unity.c
# End Source File
# Begin Source File

SOURCE=.\Uunity\unity.h
# End Source File
# Begin Source File

SOURCE=.\Uunity\UnityS2.c
# End Source File
# Begin Source File

SOURCE=.\Uunity\UnityS3.c
# End Source File
# Begin Source File

SOURCE=.\Uunity\UnityS4.c
# End Source File
# End Group
# Begin Group "Uvec"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Uvec\BitVector.c
# End Source File
# Begin Source File

SOURCE=.\Uvec\BitVector.h
# End Source File
# Begin Source File

SOURCE=.\Uvec\Makefile
# End Source File
# Begin Source File

SOURCE=.\Uvec\Vec2d.h
# End Source File
# Begin Source File

SOURCE=.\Uvec\Vec2dTool.c
# End Source File
# Begin Source File

SOURCE=.\Uvec\Vec3d.h
# End Source File
# End Group
# Begin Group "Uview"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Uview\Makefile
# End Source File
# Begin Source File

SOURCE=.\Uview\ViewBasePrm.c
# End Source File
# Begin Source File

SOURCE=.\Uview\ViewCamera.c
# End Source File
# Begin Source File

SOURCE=.\Uview\ViewConfig.c
# End Source File
# Begin Source File

SOURCE=.\Uview\ViewCreate.c
# End Source File
# Begin Source File

SOURCE=.\Uview\ViewCreateNormal.c
# End Source File
# Begin Source File

SOURCE=.\Uview\ViewDump.c
# End Source File
# Begin Source File

SOURCE=.\Uview\ViewEulerAngle.c
# End Source File
# Begin Source File

SOURCE=.\Uview\ViewEulerV.c
# End Source File
# Begin Source File

SOURCE=.\Uview\ViewJet.c
# End Source File
# Begin Source File

SOURCE=.\Uview\ViewLoad.c
# End Source File
# Begin Source File

SOURCE=.\Uview\ViewNormal.c
# End Source File
# Begin Source File

SOURCE=.\Uview\ViewObject.c
# End Source File
# Begin Source File

SOURCE=.\Uview\ViewObject1.c
# End Source File
# Begin Source File

SOURCE=.\Uview\ViewPer.c
# End Source File
# Begin Source File

SOURCE=.\Uview\ViewPlane.c
# End Source File
# Begin Source File

SOURCE=.\Uview\ViewPrm.c
# End Source File
# Begin Source File

SOURCE=.\Uview\ViewRoll.c
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
# Begin Group "Uxml"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Uxml\Makefile
# End Source File
# Begin Source File

SOURCE=.\Uxml\Parser.c
# End Source File
# Begin Source File

SOURCE=.\Uxml\Parser.h
# End Source File
# Begin Source File

SOURCE=.\Uxml\Ustr.c
# End Source File
# Begin Source File

SOURCE=.\Uxml\Ustr.h
# End Source File
# Begin Source File

SOURCE=.\Uxml\XmlDoc.c
# End Source File
# Begin Source File

SOURCE=.\Uxml\XmlIO.c
# End Source File
# Begin Source File

SOURCE=.\Uxml\XmlStr.c
# End Source File
# Begin Source File

SOURCE=.\Uxml\XmlStr.h
# End Source File
# Begin Source File

SOURCE=.\Uxml\XmlType.c
# End Source File
# Begin Source File

SOURCE=.\Uxml\XmlType.h
# End Source File
# End Group
# Begin Group "UZlib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\UZlib\adler32.c
# End Source File
# Begin Source File

SOURCE=.\UZlib\compress.c
# End Source File
# Begin Source File

SOURCE=.\UZlib\crc32.c
# End Source File
# Begin Source File

SOURCE=.\UZlib\deflate.c
# End Source File
# Begin Source File

SOURCE=.\UZlib\deflate.h
# End Source File
# Begin Source File

SOURCE=.\UZlib\inffast.c
# End Source File
# Begin Source File

SOURCE=.\UZlib\inffast.h
# End Source File
# Begin Source File

SOURCE=.\UZlib\inffixed.h
# End Source File
# Begin Source File

SOURCE=.\UZlib\inflate.c
# End Source File
# Begin Source File

SOURCE=.\UZlib\inflate.h
# End Source File
# Begin Source File

SOURCE=.\UZlib\inftrees.c
# End Source File
# Begin Source File

SOURCE=.\UZlib\inftrees.h
# End Source File
# Begin Source File

SOURCE=.\UZlib\Makefile
# End Source File
# Begin Source File

SOURCE=.\UZlib\trees.c
# End Source File
# Begin Source File

SOURCE=.\UZlib\trees.h
# End Source File
# Begin Source File

SOURCE=.\UZlib\uncompr.c
# End Source File
# Begin Source File

SOURCE=.\UZlib\zconf.h
# End Source File
# Begin Source File

SOURCE=.\UZlib\zip.c
# End Source File
# Begin Source File

SOURCE=.\UZlib\zip.h
# End Source File
# Begin Source File

SOURCE=.\UZlib\zip_crypt.h
# End Source File
# Begin Source File

SOURCE=.\UZlib\zip_file.c
# End Source File
# Begin Source File

SOURCE=.\UZlib\zip_file.h
# End Source File
# Begin Source File

SOURCE=.\UZlib\zip_files.c
# End Source File
# Begin Source File

SOURCE=.\UZlib\zip_ioapi.c
# End Source File
# Begin Source File

SOURCE=.\UZlib\zip_ioapi.h
# End Source File
# Begin Source File

SOURCE=.\UZlib\zip_iowin32.c
# End Source File
# Begin Source File

SOURCE=.\UZlib\zip_iowin32.h
# End Source File
# Begin Source File

SOURCE=.\UZlib\zlib.h
# End Source File
# Begin Source File

SOURCE=.\UZlib\zutil.c
# End Source File
# Begin Source File

SOURCE=.\UZlib\zutil.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Makefile
# End Source File
# End Target
# End Project
