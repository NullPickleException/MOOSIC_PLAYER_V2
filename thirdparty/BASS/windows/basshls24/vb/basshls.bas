Attribute VB_Name = "BASSHLS"
' BASSHLS 2.4 Visual Basic module
' Copyright (c) 2015-2025 Un4seen Developments Ltd.
'
' See the BASSHLS.CHM file for more detailed documentation

' Additional BASS_SetConfig options
Global Const BASS_CONFIG_HLS_DOWNLOAD_TAGS	= &H10900
Global Const BASS_CONFIG_HLS_BANDWIDTH		= &H10901
Global Const BASS_CONFIG_HLS_DELAY			= &H10902
Global Const BASS_CONFIG_HLS_TSSCAN         = &H10903

' Additional sync type
Global Const BASS_SYNC_HLS_SEGMENT    = &H10300
Global Const BASS_SYNC_HLS_SDT        = &H10301
Global Const BASS_SYNC_HLS_EMSG       = &H10302

' Additional tag types
Global Const BASS_TAG_HLS_EXTINF      = &H14000 ' segment's EXTINF tag : UTF-8 string
Global Const BASS_TAG_HLS_STREAMINF   = &H14001 ' EXT-X-STREAM-INF tag : UTF-8 string
Global Const BASS_TAG_HLS_DATE        = &H14002 ' EXT-X-PROGRAM-DATE-TIME tag : UTF-8 string
Global Const BASS_TAG_HLS_SDT         = &H14003 ' DVB SDT : variable length block
Global Const BASS_TAG_HLS_EMSG        = &H14004 ' fMP4 emsg : variable length block
Global Const BASS_TAG_HLS_SDT_BINARY  = &H14005 ' DVB SDT : TAB_BINARY
Global Const BASS_TAG_HLS_EMSG_BINARY = &H14006 ' fMP4 emsg : TAB_BINARY

' Additional BASS_StreamGetFilePosition mode
Global Const BASS_FILEPOS_HLS_SEGMENT = &H10000 ' segment sequence number

Declare Function BASS_HLS_StreamCreateFile64 Lib "basshls.dll" Alias "BASS_HLS_StreamCreateFile" (ByVal filetype As Long, ByVal file As Any, ByVal offset As Long, ByVal offsethigh As Long, ByVal length As Long, ByVal lengthhigh As Long, ByVal flags As Long) As Long
Declare Function BASS_HLS_StreamCreateURL Lib "basshls.dll" (ByVal url As String, ByVal flags As Long, ByVal proc As Long, ByVal user As Long) As Long

' 32-bit wrapper for 64-bit BASS function
Function BASS_HLS_StreamCreateFile(ByVal filetype As Long, ByVal file As Long, ByVal offset As Long, ByVal length As Long, ByVal flags As Long) As Long
    BASS_HLS_StreamCreateFile = BASS_HLS_StreamCreateFile64(filetype, file, offset, 0, length, 0, flags Or BASS_UNICODE)
End Function
