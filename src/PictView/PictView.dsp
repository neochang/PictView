# Microsoft Developer Studio Project File - Name="PictView" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PictView - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PictView.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PictView.mak" CFG="PictView - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PictView - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "PictView - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PictView - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 Lib/Jpeglib2.lib winmm.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libc.lib" /IGNORE:4089
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "PictView - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Lib/Jpeglib2.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc.lib" /pdbtype:sept /IGNORE:4089
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "PictView - Win32 Release"
# Name "PictView - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Lib Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Lib\CqOctree.cpp
# End Source File
# Begin Source File

SOURCE=.\Lib\Dib.cpp
# End Source File
# Begin Source File

SOURCE=.\Lib\dibapi.cpp
# End Source File
# Begin Source File

SOURCE=.\Lib\Gif.cpp
# End Source File
# Begin Source File

SOURCE=.\Lib\GIFAPI.CPP
# End Source File
# Begin Source File

SOURCE=.\Lib\IP.cpp
# End Source File
# Begin Source File

SOURCE=.\Lib\Jpeg.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ClassImage.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageBmp.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageBmpConvert.cpp
# End Source File
# Begin Source File

SOURCE=.\ImagePcx.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageTga.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\PictView.cpp
# End Source File
# Begin Source File

SOURCE=.\PictView.rc
# End Source File
# Begin Source File

SOURCE=.\PictViewDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\PictViewView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Lib Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Lib\CDERROR.H
# End Source File
# Begin Source File

SOURCE=.\Lib\CDJPEG.H
# End Source File
# Begin Source File

SOURCE=.\Lib\Dib.h
# End Source File
# Begin Source File

SOURCE=.\Lib\dibapi.h
# End Source File
# Begin Source File

SOURCE=.\Lib\Gif.h
# End Source File
# Begin Source File

SOURCE=.\Lib\GIFAPI.H
# End Source File
# Begin Source File

SOURCE=.\Lib\JCHUFF.H
# End Source File
# Begin Source File

SOURCE=.\Lib\JCONFIG.H
# End Source File
# Begin Source File

SOURCE=.\Lib\JDCT.H
# End Source File
# Begin Source File

SOURCE=.\Lib\JDHUFF.H
# End Source File
# Begin Source File

SOURCE=.\Lib\JERROR.H
# End Source File
# Begin Source File

SOURCE=.\Lib\JINCLUDE.H
# End Source File
# Begin Source File

SOURCE=.\Lib\JMEMSYS.H
# End Source File
# Begin Source File

SOURCE=.\Lib\Jmorecfg.h
# End Source File
# Begin Source File

SOURCE=.\Lib\Jpeg.h
# End Source File
# Begin Source File

SOURCE=.\Lib\JPEGINT.H
# End Source File
# Begin Source File

SOURCE=.\Lib\JPEGLIB.H
# End Source File
# Begin Source File

SOURCE=.\Lib\JVERSION.H
# End Source File
# End Group
# Begin Source File

SOURCE=.\ClassImage.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\PictView.h
# End Source File
# Begin Source File

SOURCE=.\PictViewDoc.h
# End Source File
# Begin Source File

SOURCE=.\PictViewView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\PictView.ico
# End Source File
# Begin Source File

SOURCE=.\res\PictView.rc2
# End Source File
# Begin Source File

SOURCE=.\res\PictViewDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\zHistory.txt
# End Source File
# End Target
# End Project
