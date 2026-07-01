Attribute VB_Name = "BASSenc_OGG"
' BASSenc_OGG 2.4 Visual Basic module
' Copyright (c) 2016-2020 Un4seen Developments Ltd.
'
' See the BASSENC_OGG.CHM file for more detailed documentation

' BASS_Encode_OGG_NewStream flags
Global Const BASS_ENCODE_OGG_RESET = &H1000000

Declare Function BASS_Encode_OGG_GetVersion Lib "bassenc_ogg.dll" () As Long

Declare Function BASS_Encode_OGG_Start Lib "bassenc_ogg.dll" (ByVal chan As Long, ByVal options As String, ByVal flags As Long, ByVal proc As Long, ByVal user As Long) As Long
Declare Function BASS_Encode_OGG_StartFile Lib "bassenc_ogg.dll" (ByVal chan As Long, ByVal options As String, ByVal flags As Long, ByVal filename As Long) As Long
Declare Function BASS_Encode_OGG_NewStream Lib "bassenc_ogg.dll" (ByVal chan As Long, ByVal options As String, ByVal flags As Long) As Long
