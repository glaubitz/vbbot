/*
* Viewbar Bot
* the ultimative tool to fake any viewbar
*
* v 1.1.2
* date: Jan., 19 2000
* (C) Adrian Glaubitz
* adi007@germanynet.de
*
* fmouse.c - FakeMouse initialization and interfacing
*/

#ifndef __FMOUSE_C
#define __FMOUSE_C
#endif

#include "global.h"

#define WM_MOVEMOUSE	4094
#define WM_SETMOUSE		4095

typedef struct _MOUSEDATA {

	int	X; // either units to move or new position of X
	int	Y; // either units to move or new position of Y
	BYTE	ButtonStatus; // flag variable containing the button status

} MOUSEDATA;

HANDLE hDevice;
MOUSEDATA MouseData = {0,0,0};
LPDWORD lpBytesReturned;
LPOVERLAPPED lpOverlapped;

BOOL InitDriver () {

	hDevice = CreateFile("\\\\.\\FMOUSE.VXD", 
        GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 
        (LPSECURITY_ATTRIBUTES) NULL, OPEN_EXISTING, 
        FILE_ATTRIBUTE_NORMAL, 0);
	
	if (hDevice == INVALID_HANDLE_VALUE) {
		MessageBox (NULL, "Could not load FMOUSE virtual device driver\r\nError: Invalid Handle\r\nCheck if the driver is in the current directory\r\nIf this problem persists, try a power-off reboot (wait > 1 min.)", "Error", MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	else
		return TRUE;
}

void MoveMouse (int xmickeys, int ymickeys, BYTE direction) {

	switch (direction) {

	case DIRECTION_NORTH:

		MouseData.X = 0;
		MouseData.Y = ymickeys * -1;
		break;

	case DIRECTION_WEST:

		MouseData.X = xmickeys * -1;
		MouseData.Y = 0;
		break;

	case DIRECTION_EAST:

		MouseData.X = xmickeys;
		MouseData.Y = 0;
		break;

	case DIRECTION_SOUTH:

		MouseData.X = 0;
		MouseData.Y = ymickeys;
		break;

	case DIRECTION_NONE:
		
		MouseData.X = xmickeys;
		MouseData.Y = ymickeys;
		DeviceIoControl(hDevice, WM_SETMOUSE, &MouseData, sizeof (MouseData),
			NULL, 0, lpBytesReturned, lpOverlapped);
		return;
	
	default:
		return;
	}

	DeviceIoControl(hDevice, WM_MOVEMOUSE, &MouseData, sizeof (MouseData),
		NULL, 0, lpBytesReturned, lpOverlapped);

	Sleep (500);

	DeviceIoControl(hDevice, WM_MOVEMOUSE, &MouseData, sizeof (MouseData),
		NULL, 0, lpBytesReturned, lpOverlapped);
}