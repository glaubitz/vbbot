/*
* Viewbar Bot
* the ultimative tool to fake any viewbar
*
* v 1.1.2
* date: Nov., 18 2000
* (C) Adrian Glaubitz
* adi007@germanynet.de
*
* vbbot.c - startup code
*/

#ifndef __VBBOT_C
#define __VBBOT_C
#endif

#include "global.h"

int WINAPI WinMain (HINSTANCE Instance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdShow) {

	g_Instance = Instance;
	g_MouseDelay = 0;
	g_LocationDelay = 0;
	if (InitDriver ())
		DialogBox (Instance, MAKEINTRESOURCE(ID_MAINDLG), NULL, MainDlgProc);
	return 0;
}