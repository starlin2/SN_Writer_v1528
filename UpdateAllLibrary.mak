BROM_DLL_VERSION = 5.1412.00
META_DLL_VERSION = 1.1428.00

BROM_DLL_FOLDER_NAME = BROM_DLL_exe_v$(BROM_DLL_VERSION)
META_DLL_FOLDER_NAME = META_DLL_exe_v$(META_DLL_VERSION)
D_ROOT = .
Parent_ROOT = ..
BROM_DLL_SOURCE_NAME = $(Parent_ROOT)\$(BROM_DLL_FOLDER_NAME)
META_DLL_SOURCE_NAME = $(Parent_ROOT)\$(META_DLL_FOLDER_NAME)

Update_Brom_Library_and_Header_File:
  copy /Y $(BROM_DLL_SOURCE_NAME)\brom.h .\MtkLib\Brom\inc\brom.h
  copy /Y $(BROM_DLL_SOURCE_NAME)\com_enum.h .\MtkLib\Brom\inc\com_enum.h
  copy /Y $(BROM_DLL_SOURCE_NAME)\DOWNLOAD.h .\MtkLib\Brom\inc\DOWNLOAD.h
  copy /Y $(BROM_DLL_SOURCE_NAME)\external_memory_setting.h .\MtkLib\Brom\inc\external_memory_setting.h
  copy /Y $(BROM_DLL_SOURCE_NAME)\flashtool.h .\MtkLib\Brom\inc\flashtool.h
  copy /Y $(BROM_DLL_SOURCE_NAME)\flashtool_api.h .\MtkLib\Brom\inc\flashtool_api.h
  copy /Y $(BROM_DLL_SOURCE_NAME)\flashtool_handle.h .\MtkLib\Brom\inc\flashtool_handle.h
  copy /Y $(BROM_DLL_SOURCE_NAME)\mtk_mcu.h .\MtkLib\Brom\inc\mtk_mcu.h
  copy /Y $(BROM_DLL_SOURCE_NAME)\mtk_resource.h .\MtkLib\Brom\inc\mtk_resource.h
  copy /Y $(BROM_DLL_SOURCE_NAME)\mtk_status.h .\MtkLib\Brom\inc\mtk_status.h
  copy /Y $(BROM_DLL_SOURCE_NAME)\rom_setting.h .\MtkLib\Brom\inc\rom_setting.h 
  
  copy /Y $(BROM_DLL_SOURCE_NAME)\vc\Release\brom.lib .\MtkLib\Brom\lib\brom.lib

  copy /Y $(BROM_DLL_SOURCE_NAME)\vc\Release\brom.dll .\Release\brom.dll
  copy /Y $(BROM_DLL_SOURCE_NAME)\vc\Release\brom.dll .\Debug\brom.dll
  copy /Y $(BROM_DLL_SOURCE_NAME)\vc\Release\brom.dll .\Dll\brom.dll
  
  
  
Update_Meta_Library_and_Header_File:
  copy /Y $(META_DLL_SOURCE_NAME)\meta.h .\MtkLib\Meta\inc\meta.h
  copy /Y $(META_DLL_SOURCE_NAME)\spmeta.h .\MtkLib\Meta\inc\spmeta.h
  copy /Y $(META_DLL_SOURCE_NAME)\SP_META_Wrapper.h .\MtkLib\Meta\inc\SP_META_Wrapper.h
  copy /Y $(META_DLL_SOURCE_NAME)\SLA_Challenge.h .\MtkLib\Security\inc\SLA_Challenge.h
  
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\META_DLL.lib .\MtkLib\Meta\lib\META_DLL.lib 
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\SPMETA_DLL.lib .\MtkLib\Meta\lib\SPMETA_DLL.lib 
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\SP_META_Wrapper.lib .\MtkLib\Meta\lib\SP_META_Wrapper.lib 
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\Controls.lib .\MtkLib\Meta\lib\Controls.lib
  
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\META_DLL.dll .\Release\META_DLL.dll
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\SPMETA_DLL.dll .\Release\SPMETA_DLL.dll
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Debug\SPMETA_DLL.dll .\Debug\SPMETA_DLL.dll
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Dll\SPMETA_DLL.dll .\Dll\SPMETA_DLL.dll
  
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\SP_META_Wrapper.dll .\Release\SP_META_Wrapper.dll
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\Controls.dll .\Release\Controls.dll
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\Microsoft.VC90.CRT.manifest .\Release\Microsoft.VC90.CRT.manifest
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\msvcm90.dll .\Release\msvcm90.dll
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\msvcp90.dll .\Release\msvcp90.dll
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\msvcr90.dll .\Release\msvcr90.dll
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\META_DLL.dll .\Release\META_DLL.dll
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\Controls.dll .\Release\Controls.dll
  copy /Y $(META_DLL_SOURCE_NAME)\bin\DataLibrary.dll .\Release\DataLibrary.dll
  copy /Y $(META_DLL_SOURCE_NAME)\bin\FrameCommModule.dll .\Release\FrameCommModule.dll
  copy /Y $(META_DLL_SOURCE_NAME)\bin\SysUtility.dll .\Release\SysUtility.dll
  
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\META_DLL.dll .\Debug\META_DLL.dll
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\Controls.dll .\Debug\Controls.dll
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\Microsoft.VC90.CRT.manifest .\Debug\Microsoft.VC90.CRT.manifest
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\msvcm90.dll .\Debug\msvcm90.dll
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\msvcp90.dll .\Debug\msvcp90.dll
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\msvcr90.dll .\Debug\msvcr90.dll
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\META_DLL.dll .\Debug\META_DLL.dll
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\Controls.dll .\Debug\Controls.dll
  copy /Y $(META_DLL_SOURCE_NAME)\bin\DataLibrary.dll .\Debug\DataLibrary.dll
  copy /Y $(META_DLL_SOURCE_NAME)\bin\FrameCommModule.dll .\Debug\FrameCommModule.dll
  copy /Y $(META_DLL_SOURCE_NAME)\bin\SysUtility.dll .\Debug\SysUtility.dll
  
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\META_DLL.dll .\Dll\META_DLL.dll
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\Controls.dll .\Dll\Controls.dll
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\Microsoft.VC90.CRT.manifest .\Debug\Microsoft.VC90.CRT.manifest
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\msvcm90.dll .\Dll\msvcm90.dll
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\msvcp90.dll .\Dll\msvcp90.dll
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\msvcr90.dll .\Dll\msvcr90.dll
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\META_DLL.dll .\Dll\META_DLL.dll
  copy /Y $(META_DLL_SOURCE_NAME)\vc\Release\Controls.dll .\Dll\Controls.dll
  copy /Y $(META_DLL_SOURCE_NAME)\bin\DataLibrary.dll .\Dll\DataLibrary.dll
  copy /Y $(META_DLL_SOURCE_NAME)\bin\FrameCommModule.dll .\Dll\FrameCommModule.dll
  copy /Y $(META_DLL_SOURCE_NAME)\bin\SysUtility.dll .\Dll\SysUtility.dll
  
  

Update_Brom_And_Meta_Library_and_Header_File: Update_Brom_Library_and_Header_File Update_Meta_Library_and_Header_File
  
  
#





















