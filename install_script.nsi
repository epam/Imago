
!define PRODUCT_NAME "Imago Toolkit"
!define PRODUCT_VERSION "1.0 Release Candidate"
!define PRODUCT_PUBLISHER "GGA Software Services LLC"
!define PRODUCT_WEB_SITE "http://www.ggasoftware.com"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\alter_ego.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

!define NameStrAe "Recognize with Imago:Alter-Ego" 
!define NameStrE "Open with Imago:Ego"

SetCompressor lzma

!include "MUI.nsh"
!include "x64.nsh"

!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "LICENSE.GPL"
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "ImagoToolkit-1.0-RC-install.exe"
InstallDir $INSTDIR
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show

Function .onInit
  ${If} ${RunningX64}
        StrCpy $INSTDIR "$PROGRAMFILES64\Imago Toolkit"
  ${Else}
        StrCpy $INSTDIR "$PROGRAMFILES\Imago Toolkit"
  ${EndIf}
FunctionEnd

Function WriteToFile
 Exch $0 ;file to write to
 Exch
 Exch $1 ;text to write

  FileOpen $0 $0 a #open file
   ;FileSeek $0 0 END #go to end
   FileWrite $0 $1 #write to file
  FileClose $0

 Pop $1
 Pop $0
FunctionEnd

!macro WriteToFile String File
 Push "${String}"
 Push "${File}"
  Call WriteToFile
!macroend
!define WriteToFile "!insertmacro WriteToFile"

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite try
  File "output\release\ego\ego.jar"
  File "LICENSE.GPL"
  SetOutPath "$INSTDIR\lib"
  File "output\release\ego\lib\imago.jar"
  File "output\release\ego\lib\indigo-java.jar"
  File "output\release\ego\lib\indigo-renderer-java.jar"
  File "output\release\ego\lib\jai_codec.jar"
  File "output\release\ego\lib\jai_core.jar"
  File "output\release\ego\lib\PDFRenderer.jar"
  
  ${If} ${RunningX64}
    SetOutPath "$INSTDIR\lib\Win\x64"
    File "output\release\ego\lib\Win\x64\imagojni.dll"
    File "output\release\ego\lib\Win\x64\indigo-jni.dll"
    File "output\release\ego\lib\Win\x64\indigo-renderer-jni.dll"
    File "output\release\ego\lib\Win\x64\zlib.dll"
    
    SetOutPath "$INSTDIR"
    SetOverwrite ifnewer
    File "output\release\alter-ego\x64\alter_ego.exe"
  ${Else}
    SetOutPath "$INSTDIR\lib\Win\x86"
    File "output\release\ego\lib\Win\x86\imagojni.dll"
    File "output\release\ego\lib\Win\x86\indigo-jni.dll"
    File "output\release\ego\lib\Win\x86\indigo-renderer-jni.dll"
    File "output\release\ego\lib\Win\x86\zlib.dll"

    SetOutPath "$INSTDIR"
    SetOverwrite ifnewer
    File "output\release\alter-ego\x86\alter_ego.exe"
  ${EndIf}
  
  SetOutPath "$INSTDIR\examples"
  SetOverwrite try
  
  File "data\release_examples\1.png"
  File "data\release_examples\2.png"
  File "data\release_examples\3.png"
  File "data\release_examples\4.png"
  File "data\release_examples\5.png"

  SetOutPath "$INSTDIR"
  
  ${WriteToFile} "@ECHO OFF $\nSET JAVAOPTS=$\njava %JAVAOPTS% -jar $\"$INSTDIR\ego.jar$\" %1 " "$INSTDIR\ego.bat"
  
  ReadRegStr $0 HKCR .pdf ""
  WriteRegStr HKCR "$0\shell\${NameStrE}\command" ""  "$\"$INSTDIR\ego.bat$\" $\"%1$\" "
  
  ReadRegStr $0 HKCR .tif ""
  WriteRegStr HKCR "$0\shell\${NameStrE}\command" ""  "$\"$INSTDIR\ego.bat$\" $\"%1$\" "
  
  ReadRegStr $0 HKCR .tiff ""
  WriteRegStr HKCR "$0\shell\${NameStrE}\command" ""  "$\"$INSTDIR\ego.bat$\" $\"%1$\" "

  ReadRegStr $0 HKCR .png ""
  WriteRegStr HKCR "$0\shell\${NameStrAE}\command" "" "$\"$INSTDIR\alter_ego.exe$\" -q $\"%1$\" "
  WriteRegStr HKCR "$0\shell\${NameStrE}\command" ""  "$\"$INSTDIR\ego.bat$\" $\"%1$\" "
  
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\alter_ego.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\alter_ego.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd


Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) was successfully removed from your computer."
FunctionEnd

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove $(^Name) and all of its components?" IDYES +2
  Abort
FunctionEnd

Section Uninstall
  Delete "$INSTDIR\LICENSE.GPL"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\examples\1.png"
  Delete "$INSTDIR\examples\2.png"
  Delete "$INSTDIR\examples\3.png"
  Delete "$INSTDIR\examples\4.png"
  Delete "$INSTDIR\examples\5.png"
  Delete "$INSTDIR\alter_ego.exe"

  Delete "$INSTDIR\lib\Win\x86\imagojni.dll"
  Delete "$INSTDIR\lib\Win\x86\imagojni.lib"
  Delete "$INSTDIR\lib\Win\x86\imagojni.exp"
  Delete "$INSTDIR\lib\Win\x86\zlib.dll"
  Delete "$INSTDIR\lib\Win\x86\indigo-jni.dll"
  Delete "$INSTDIR\lib\Win\x86\indigo-renderer-jni.dll"

  Delete "$INSTDIR\lib\Win\x64\imagojni.dll"
  Delete "$INSTDIR\lib\Win\x64\imagojni.lib"
  Delete "$INSTDIR\lib\Win\x64\imagojni.exp"
  Delete "$INSTDIR\lib\Win\x64\zlib.dll"
  Delete "$INSTDIR\lib\Win\x64\indigo-jni.dll"
  Delete "$INSTDIR\lib\Win\x64\indigo-renderer-jni.dll"
  
  Delete "$INSTDIR\lib\PDFRenderer.jar"
  Delete "$INSTDIR\lib\jpedal_lgpl.jar"
  Delete "$INSTDIR\lib\jai_core.jar"
  Delete "$INSTDIR\lib\jai_codec.jar"
  Delete "$INSTDIR\lib\indigo-java.jar"
  Delete "$INSTDIR\lib\indigo-renderer-java.jar"
  Delete "$INSTDIR\lib\imago.jar"
  Delete "$INSTDIR\ego.jar"
  Delete "$INSTDIR\ego.cfg"
  Delete "$INSTDIR\ego.bat"

  RMDir "$INSTDIR\lib\Win\x86"
  RMDir "$INSTDIR\lib\Win\x64"
  RMDir "$INSTDIR\lib\Win"
  RMDir "$INSTDIR\lib"
  RMDir "$INSTDIR\examples"
  RMDir "$INSTDIR"
  
  ReadRegStr $0 HKCR .png ""
  DeleteRegKey HKCR "$0\shell\${NameStrAE}"
  DeleteRegKey HKCR "$0\shell\${NameStrE}"
  
  ReadRegStr $0 HKCR .pdf ""
  DeleteRegKey HKCR "$0\shell\${NameStrE}"

  ReadRegStr $0 HKCR .tif ""
  DeleteRegKey HKCR "$0\shell\${NameStrE}"

  ReadRegStr $0 HKCR .tiff ""
  DeleteRegKey HKCR "$0\shell\${NameStrE}"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd
