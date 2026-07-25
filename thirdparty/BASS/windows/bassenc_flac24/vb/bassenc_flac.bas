Attribute VB_Name = "BASSenc_FLAC"
' BASSenc_FLAC 2.4 Visual Basic module
' Copyright (c) 2017-2020 Un4seen Developments Ltd.
'
' See the BASSENC_FLAC.CHM file for more detailed documentation

' BASS_Encode_FLAC_NewStream flags
Global Const BASS_ENCODE_FLAC_RESET = &H1000000

Declare Function BASS_Encode_FLAC_GetVersion Lib "bassenc_flac.dll" () As Long

Declare Function BASS_Encode_FLAC_Start Lib "bassenc_flac.dll" (ByVal chan As Long, ByVal options As String, ByVal flags As Long, ByVal proc As Long, ByVal user As Long) As Long
Declare Function BASS_Encode_FLAC_StartFile Lib "bassenc_flac.dll" (ByVal chan As Long, ByVal options As String, ByVal flags As Long, ByVal filename As Long) As Long
Declare Function BASS_Encode_FLAC_NewStream Lib "bassenc_flac.dll" (ByVal chan As Long, ByVal options As String, ByVal flags As Long) As Long
