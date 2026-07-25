Attribute VB_Name = "bass_aac"
Option Explicit

' additional BASS_SetConfig options
Global Const BASS_CONFIG_MP4_VIDEO = &H10700 ' play the audio from MP4 videos
Global Const BASS_CONFIG_AAC_MP4 = &H10701 ' support MP4
Global Const BASS_CONFIG_AAC_PRESCAN = &H10702 ' pre-scan ADTS AAC files for seek points and accurate length

' additional BASS_AAC_StreamCreateFile/etc flags
Global Const BASS_AAC_FRAME960 = &H1000 ' 960 samples per frame
Global Const BASS_AAC_STEREO = &H400000 ' downmatrix to stereo

' additional BASS_ChannelGetLength/GetPosition/SetPosition mode
Global Const BASS_POS_TRACK = 4 ' track number

' BASS_CHANNELINFO type
Global Const BASS_CTYPE_STREAM_AAC = &H10B00 ' AAC
Global Const BASS_CTYPE_STREAM_MP4 = &H10B01 ' AAC in MP4 container

Private Declare Function BASS_AAC_StreamCreateFile64 Lib "bass_aac.dll" Alias "BASS_AAC_StreamCreateFile" (ByVal filetype As Long, ByVal file As Any, ByVal offset As Long, ByVal offsethi As Long, ByVal length As Long, ByVal lengthhi As Long, ByVal flags As Long) As Long
Declare Function BASS_AAC_StreamCreateURL Lib "bass_aac.dll" (ByVal url As String, ByVal offset As Long, ByVal flags As Long, ByVal proc As Long, ByVal user As Long) As Long
Declare Function BASS_AAC_StreamCreateFileUser Lib "bass_aac.dll" (ByVal system As Long, ByVal flags As Long, ByVal procs As Long, ByVal user As Long) As Long

' 32-bit wrappers for 64-bit BASS functions
Function BASS_AAC_StreamCreateFile(ByVal filetype As Long, ByVal file As Long, ByVal offset As Long, ByVal length As Long, ByVal flags As Long) As Long
BASS_AAC_StreamCreateFile = BASS_AAC_StreamCreateFile64(filetype, file, offset, 0, length, 0, flags Or BASS_UNICODE)
End Function
