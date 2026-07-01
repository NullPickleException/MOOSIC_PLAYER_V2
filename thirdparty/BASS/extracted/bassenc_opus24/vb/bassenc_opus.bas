Attribute VB_Name = "BASSenc_OPUS"
' BASSenc_OPUS 2.4 Visual Basic module
' Copyright (c) 2016-2020 Un4seen Developments Ltd.
'
' See the BASSENC_OPUS.CHM file for more detailed documentation

' BASS_Encode_OPUS_NewStream flags
Global Const BASS_ENCODE_OPUS_RESET = &H1000000
Global Const BASS_ENCODE_OPUS_CTLONLY = &H2000000

Declare Function BASS_Encode_OPUS_GetVersion Lib "bassenc_opus.dll" () As Long

Declare Function BASS_Encode_OPUS_Start Lib "bassenc_opus.dll" (ByVal chan As Long, ByVal options As String, ByVal flags As Long, ByVal proc As Long, ByVal user As Long) As Long
Declare Function BASS_Encode_OPUS_StartFile Lib "bassenc_opus.dll" (ByVal chan As Long, ByVal options As String, ByVal flags As Long, ByVal filename As String) As Long
Declare Function BASS_Encode_OPUS_NewStream Lib "bassenc_opus.dll" (ByVal chan As Long, ByVal options As String, ByVal flags As Long) As Long
