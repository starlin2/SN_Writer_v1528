TOOL_VERSION = 2.1448.00

EXECUTABLE_OUTPUT_NAME = SN_Write_tool_exe_v$(TOOL_VERSION).zip
SOURCECODE_OUTPUT_NAME = SN_Write_tool_src_v$(TOOL_VERSION).zip

Package_All_ExecutableFiles:
   call delete_temp.bat
   .\tool\zip -r -9 ..\$(EXECUTABLE_OUTPUT_NAME) .\Output .\Documents
Package_All_SourceCode:
   .\tool\zip -r -9 ..\$(SOURCECODE_OUTPUT_NAME) .
