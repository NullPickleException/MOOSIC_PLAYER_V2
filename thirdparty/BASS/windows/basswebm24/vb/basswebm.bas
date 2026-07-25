Attribute VB_Name = "BASSWEBM"
' BASSWEBM 2.4 Visual Basic module
' Copyright (c) 2018-2025 Un4seen Developments Ltd.
'
' See the BASSWEBM.CHM file for more detailed documentation

' Additional error codes returned by BASS_ErrorGetCode
Global Const BASS_ERROR_TRACK         = 13 ' invalid track number

' Additional tag types
Global Const BASS_TAG_WEBM            = &H15000 ' file tags : series of null-terminated UTF-8 strings
Global Const BASS_TAG_WEBM_TRACK      = &H15001 ' track tags : series of null-terminated UTF-8 strings

' Additional attributes
Global Const BASS_ATTRIB_WEBM_TRACK   = &H16000
Global Const BASS_ATTRIB_WEBM_TRACKS  = &H16001
Global Const BASS_ATTRIB_WEBM         = &H16002

' Additional BASS_ChannelGetLength/GetPosition/SetPosition mode
Global Const BASS_POS_TRACK           = 4 ' track number

Declare Function BASS_WEBM_StreamCreateFile64 Lib "basswebm.dll" Alias "BASS_WEBM_StreamCreateFile" (ByVal filetype As Long, ByVal file As Any, ByVal offset As Long, ByVal offsethigh As Long, ByVal length As Long, ByVal lengthhigh As Long, ByVal flags As Long, ByVal track As Long) As Long
Declare Function BASS_WEBM_StreamCreateURL Lib "basswebm.dll" (ByVal url As String, ByVal flags As Long, ByVal proc As Long, ByVal user As Long, ByVal track As Long) As Long
Declare Function BASS_WEBM_StreamCreateFileUser Lib "basswebm.dll" (ByVal system As Long, ByVal flags As Long, ByVal procs As Long, ByVal user As Long, ByVal track As Long) As Long

' 32-bit wrapper for 64-bit BASS function
Function BASS_WEBM_StreamCreateFile(ByVal filetype As Long, ByVal file As Long, ByVal offset As Long, ByVal length As Long, ByVal flags As Long, ByVal track As Long) As Long
    BASS_WEBM_StreamCreateFile = BASS_WEBM_StreamCreateFile64(filetype, file, offset, 0, length, 0, flags Or BASS_UNICODE, track)
End Function
