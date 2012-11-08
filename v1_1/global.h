/*
* Viewbar Bot
* the ultimative tool to fake any viewbar
*
* v 1.1.2
* date: Jan., 18 2001
* (C) Adrian Glaubitz
* adi007@germanynet.de
*
* global.h - global declarations
*/

#include <windows.h>
#include "resource.h"
#include <stdlib.h>

struct _LOCATIONS {
	
	char ** Locations;
};

#define LOCATIONS struct _LOCATIONS

HINSTANCE	g_Instance;
DWORD		g_MouseDelay;
DWORD		g_LocationDelay;
LOCATIONS	g_Locations;
WORD		g_LocationCount;

#define	DIRECTION_NORTH		0
#define DIRECTION_WEST		1
#define DIRECTION_EAST		2
#define DIRECTION_SOUTH		3
#define DIRECTION_NONE		4

#define MOUSE_XMICKEYS		15000
#define MOUSE_YMICKEYS		15000

#ifndef __VBBOT_C
#define	VBBOT_EXTERN extern
#else
#define	VBBOT_EXTERN
#endif

#ifndef __WNDPROC_C
#define WNDPROC_EXTERN extern
#else
#define WNDPROC_EXTERN
#endif

#ifndef __FMOUSE_C
#define FMOUSE_EXTERN extern
#else
#define FMOUSE_EXTERN
#endif

#ifndef __INIPROC_C
#define INIPROC_EXTERN extern
#else
#define INIPROC_EXTERN
#endif

#ifndef __TIMER_C
#define TIMER_EXTERN extern
#else
#define TIMER_EXTERN
#endif

#ifndef __LOCATION_C
#define LOCATION_EXTERN extern
#else
#define LOCATION_EXTERN
#endif

VBBOT_EXTERN	int WINAPI WinMain (HINSTANCE, HINSTANCE, LPSTR, int);

WNDPROC_EXTERN	BOOL CALLBACK MainDlgProc (HWND, UINT, WPARAM, LPARAM);
WNDPROC_EXTERN	BOOL CALLBACK HelpDlgProc (HWND, UINT, WPARAM, LPARAM);
WNDPROC_EXTERN	BOOL CALLBACK AboutDlgProc (HWND, UINT, WPARAM, LPARAM);
WNDPROC_EXTERN	BOOL CALLBACK PrefsDlgProc (HWND, UINT, WPARAM, LPARAM);
WNDPROC_EXTERN	BOOL CALLBACK AddLocationDlgProc (HWND, UINT, WPARAM, LPARAM);
WNDPROC_EXTERN	void RefreshWindow (HWND, BOOL);

FMOUSE_EXTERN	BOOL InitDriver ();
FMOUSE_EXTERN	void MoveMouse (int, int, BYTE);

INIPROC_EXTERN	BOOL ReadSettings ();
INIPROC_EXTERN	void WriteSettings ();

TIMER_EXTERN	void StartMouseTimer (BOOL, HWND);
TIMER_EXTERN	void StartLocationTimer (BOOL, HWND);
TIMER_EXTERN	void CALLBACK MouseTimerProc (HWND, UINT, UINT, DWORD);
TIMER_EXTERN	void CALLBACK LocationTimerProc (HWND, UINT, UINT, DWORD);

LOCATION_EXTERN void AddLocation (LOCATIONS *, LPCSTR);
LOCATION_EXTERN void RemoveLocation (LOCATIONS *, BYTE);
LOCATION_EXTERN LPSTR GetLocationAt (LOCATIONS * lpLocations, WORD Count);