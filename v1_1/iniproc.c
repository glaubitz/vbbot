/*
* Viewbar Bot
* the ultimative tool to fake any viewbar
*
* v 1.1.2
* date: Jan., 18 2001
* (C) Adrian Glaubitz
* adi007@germanynet.de
*
* iniproc.c - ini file processor
*/

#ifndef __INIPROC_C
#define __INIPROC_C
#endif

#include "global.h"

BOOL ReadSettings () {

	HANDLE FileHandle;
	LPSTR LoadText;
	char _tmpString [64];
	char tmpChar [2];
	LPSTR tmpString = _tmpString;
	DWORD i = 0, j = 0, FileSize, BytesRead = 0, ItemsToLoad;

	_tmpString [0] = 0;
	tmpChar [1] = 0;


	FileHandle = CreateFile ("vbbot.ini", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	
	FileSize = GetFileSize(FileHandle, NULL);
		
	if(FileSize != 0xFFFFFFFF) {

			
		LoadText = (LPSTR) GlobalAlloc (0, FileSize + 1);
			
		if(LoadText != NULL) {
				
			if(ReadFile (FileHandle, LoadText, FileSize, &BytesRead, NULL))
				LoadText[FileSize] = 0;
				
		}
	}
		
	CloseHandle(FileHandle);

	if (BytesRead == 0)
		return FALSE;

	ItemsToLoad = 0;
	i = 0;
	j = 0;
		
	while (i < FileSize) {

		if (LoadText [i] == ';')
			ItemsToLoad++;
		i++;
	}

	i = 0;
		
	while (j < ItemsToLoad - 2) {

		while (LoadText [i] != ';' && i < FileSize) {

			tmpChar [0] = LoadText [i];
			tmpString = lstrcat (tmpString, tmpChar);
			i++;
		}
			
		j++;
		i++;
			
		AddLocation (&g_Locations, tmpString);
			
		_tmpString [0] = 0;
	}


	while (LoadText [i] != ';' && i < FileSize) {
			
		tmpChar [0] = LoadText [i];
		tmpString = lstrcat (tmpString, tmpChar);
		i++;
	}

	g_MouseDelay = atoi (tmpString);

	_tmpString [0] = 0;

	i++;

	while (LoadText [i] != ';' && i < FileSize) {
			
		tmpChar [0] = LoadText [i];
		tmpString = lstrcat (tmpString, tmpChar);
		i++;
	}

	g_LocationDelay = atoi (tmpString);

	GlobalFree ((HGLOBAL) LoadText);

	return TRUE;
}

void WriteSettings () {

	HANDLE FileHandle;
	DWORD BytesWritten;
	LPSTR SaveText = GlobalAlloc (0, 4096);
	char tmpString [64];
	WORD i;

	SaveText [0] = '\0';

	for (i = 0; i < 64; i++) {
	
		if (GetLocationAt (& g_Locations, i) != NULL) {
			SaveText = lstrcat (SaveText, GetLocationAt (& g_Locations, i));
			SaveText = lstrcat (SaveText, ";");
		}
	}

	SaveText = lstrcat (SaveText, itoa (g_MouseDelay, tmpString, 10));
	SaveText = lstrcat (SaveText, ";");
	SaveText = lstrcat (SaveText, itoa (g_LocationDelay, tmpString, 10));
	SaveText = lstrcat (SaveText, ";");
	
	FileHandle = CreateFile ("vbbot.ini", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

	WriteFile(FileHandle, SaveText, lstrlen (SaveText), &BytesWritten, NULL);

	CloseHandle(FileHandle);

	GlobalFree ((HGLOBAL) SaveText);

}