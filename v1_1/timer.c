/*
* Viewbar Bot
* the ultimative tool to fake any viewbar
*
* v 1.1.2
* date: Jan., 19 2001
* (C) Adrian Glaubitz
* adi007@germanynet.de
*
* timer.c - timer functions
*/

#ifndef __TIMER_C
#define __TIMER_C
#endif

#include "global.h"

BYTE MouseDirection = DIRECTION_NORTH;
WORD CurrentLocation = 0;

void StartMouseTimer (BOOL Start, HWND hOwner) {

	if (Start)
		SetTimer (hOwner, ID_MOUSETIMER, g_MouseDelay * 1000, MouseTimerProc);
	else
		KillTimer (hOwner, ID_MOUSETIMER);
}

void StartLocationTimer (BOOL Start, HWND hOwner) {

	if (Start)
		SetTimer (hOwner, ID_LOCATIONTIMER, g_LocationDelay * 1000, LocationTimerProc);
	else
		KillTimer (hOwner, ID_LOCATIONTIMER);
}

void CALLBACK MouseTimerProc (HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime) {

	if (MouseDirection == DIRECTION_SOUTH + 1)
			MouseDirection = DIRECTION_NORTH;
	
	MoveMouse (MOUSE_XMICKEYS, MOUSE_YMICKEYS, MouseDirection);
	MouseDirection++;
}

void CALLBACK LocationTimerProc (HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime) {

	ShellExecute (NULL, "open", GetLocationAt (&g_Locations, CurrentLocation), NULL,
						NULL, SW_SHOWNORMAL);
	CurrentLocation++;

	if (CurrentLocation == g_LocationCount)
		CurrentLocation = 0;
}
