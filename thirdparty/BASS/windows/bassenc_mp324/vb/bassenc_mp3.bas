Attribute VB_Name = "BASSenc_MP3"
' BASSenc_MP3 2.4 Visual Basic module
' Copyright (c) 2018 Un4seen Developments Ltd.
'
' See the BASSENC_MP3.CHM file for more detailed documentation

Declare Function BASS_Encode_MP3_GetVersion Lib "bassenc_mp3.dll" () As Long

Declare Function BASS_Encode_MP3_Start Lib "bassenc_mp3.dll" (ByVal chan As Long, ByVal options As String, ByVal flags As Long, ByVal proc As Long, ByVal user As Long) As Long
Declare Function BASS_Encode_MP3_StartFile Lib "bassenc_mp3.dll" (ByVal chan As Long, ByVal options As String, ByVal flags As Long, ByVal filename As String) As Long
