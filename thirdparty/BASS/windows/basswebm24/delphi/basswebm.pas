{
  BASSWEBM 2.4 Delphi/Pascal unit
  Copyright (c) 2018-2025 Un4seen Developments Ltd.

  See the BASSWEBM.CHM file for more detailed documentation
}

unit BassHLS;

interface

{$IFDEF MSWINDOWS}
uses BASS, Windows;
{$ELSE}
uses BASS;
{$ENDIF}

const
  // Additional error codes returned by BASS_ErrorGetCode
  BASS_ERROR_TRACK             = 13; // invalid track number

  // Additional tag types
  BASS_TAG_WEBM                = $15000; // file tags : series of null-terminated UTF-8 strings
  BASS_TAG_WEBM_TRACK          = $15001; // track tags : series of null-terminated UTF-8 strings

  // Additional attributes
  BASS_ATTRIB_WEBM_TRACK       = $16000;
  BASS_ATTRIB_WEBM_TRACKS      = $16001;
  BASS_ATTRIB_WEBM             = $16002;

  // Additional BASS_ChannelGetLength/GetPosition/SetPosition mode
  BASS_POS_TRACK               = 4; // track number

const
{$IFDEF MSWINDOWS}
  basswebmdll = 'basswebm.dll';
{$ENDIF}
{$IFDEF LINUX}
  basswebmdll = 'libbasswebm.so';
{$ENDIF}
{$IFDEF ANDROID}
  basswebmdll = 'libbasswebm.so';
{$ENDIF}
{$IFDEF MACOS}
  {$IFDEF IOS}
    basswebmdll = 'basswebm.framework/basswebm';
  {$ELSE}
    basswebmdll = 'libbasswebm.dylib';
  {$ENDIF}
{$ENDIF}

function BASS_WEBM_StreamCreateFile(filetype:DWORD; fl:pointer; offset,length:QWORD; flags,track:DWORD): HSTREAM; {$IFDEF MSWINDOWS}stdcall{$ELSE}cdecl{$ENDIF}; external basswebmdll;
function BASS_WEBM_StreamCreateURL(url:PChar; flags:DWORD; proc:DOWNLOADPROC; user:Pointer; track:DWORD): HSTREAM; {$IFDEF MSWINDOWS}stdcall{$ELSE}cdecl{$ENDIF}; external basswebmdll;
function BASS_WEBM_StreamCreateFileUser(system,flags:DWORD; var procs:BASS_FILEPROCS; user:Pointer; track:DWORD): HSTREAM; {$IFDEF MSWINDOWS}stdcall{$ELSE}cdecl{$ENDIF}; external basswebmdll;

implementation

end.