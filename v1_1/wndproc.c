/*
* Viewbar Bot
* the ultimative tool to fake any viewbar
*
* v 1.1.2
* date: Jan., 19 2001
* (C) Adrian Glaubitz
* adi007@germanynet.de
*
* wndproc.c - the window procedures
*/

#ifndef __WNDPROC_C
#define __WNDPROC_C
#endif

#include "global.h"

/*
HWND hListBox;
HWND hAddLocationDlg;
*/

BOOL CALLBACK MainDlgProc (HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	HMENU hMenu;

	switch (uMsg) {

	case WM_INITDIALOG:
		
		if (!ReadSettings ()) {

			hMenu = GetMenu (hwndDlg);
			hMenu = GetSubMenu (hMenu, 0);
			EnableMenuItem (hMenu, ID_BOTSTART, MF_BYCOMMAND | MF_GRAYED);
		}

		hMenu = GetSystemMenu (hwndDlg, FALSE);
		EnableMenuItem (hMenu, 0, MF_BYPOSITION | MF_GRAYED);
		EnableMenuItem (hMenu, 2, MF_BYPOSITION | MF_GRAYED);
		EnableMenuItem (hMenu, 4, MF_BYPOSITION | MF_GRAYED);
		break;

	case WM_ACTIVATE:

		RefreshWindow (hwndDlg, TRUE);
		hMenu = GetMenu (hwndDlg);
		hMenu = GetSubMenu (hMenu, 0);
		if (g_LocationCount >= 1 && GetMenuState (hMenu, ID_BOTSTOP, MF_BYCOMMAND) == MF_GRAYED)
			EnableMenuItem (hMenu, ID_BOTSTART, MF_BYCOMMAND | MF_ENABLED);
		else
			EnableMenuItem (hMenu, ID_BOTSTART, MF_BYCOMMAND | MF_GRAYED);

		break;

	case WM_SIZE:

		if (wParam == SIZE_MINIMIZED) {
		
			hMenu = GetSystemMenu (hwndDlg, FALSE);
			EnableMenuItem (hMenu, 0, MF_BYPOSITION | MF_ENABLED);
		}
		else {
			hMenu = GetSystemMenu (hwndDlg, FALSE);
			EnableMenuItem (hMenu, 0, MF_BYPOSITION | MF_GRAYED);
		}
		break;

	case WM_CLOSE:

		EndDialog (hwndDlg, 0);
		break;

	case WM_COMMAND:

		switch (LOWORD(wParam)) {

		case ID_BOTSTART:

			EnableMenuItem (GetMenu (hwndDlg), ID_STARTBOT, MF_GRAYED);
			EnableMenuItem (GetMenu (hwndDlg), ID_STOPBOT, MF_ENABLED);
			StartMouseTimer (TRUE, hwndDlg);
			StartLocationTimer (TRUE, hwndDlg);
			MoveMouse (100000, 100000, DIRECTION_NONE);
			break;

		case ID_BOTSTOP:

			EnableMenuItem (GetMenu (hwndDlg), ID_STOPBOT, MF_GRAYED);
			EnableMenuItem (GetMenu (hwndDlg), ID_STARTBOT, MF_ENABLED);
			StartMouseTimer (FALSE, hwndDlg);
			StartLocationTimer (FALSE, hwndDlg);
			break;

		case ID_BOTPREFS:

			DialogBox (g_Instance, MAKEINTRESOURCE(ID_PREFSDLG), hwndDlg, PrefsDlgProc);
			break;

		case ID_QUESTIONHELP:

			DialogBox (g_Instance, MAKEINTRESOURCE(ID_HELPDLG), hwndDlg, HelpDlgProc);
			break;

		case ID_QUESTIONABOUT:

			DialogBox (g_Instance, MAKEINTRESOURCE(ID_ABOUTDLG), hwndDlg, AboutDlgProc);
			break;

		case ID_EXITBOT:

			EndDialog (hwndDlg, ID_EXITBOT);
			break;

		default:
			break;
		}
	
	default:
		return 0;

	}
}

BOOL CALLBACK HelpDlgProc (HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) {

	case WM_CLOSE:

		EndDialog (hwndDlg, 0);
		break;

	case WM_COMMAND:

		switch (LOWORD(wParam)) {

		case ID_CLOSE:
		
			EndDialog (hwndDlg, 0);

		default:
			break;
		}

	default:
		return 0;
	}
}

BOOL CALLBACK AboutDlgProc (HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) {

	case WM_CLOSE:

		EndDialog (hwndDlg, 0);
		break;

	case WM_COMMAND:

		switch (LOWORD(wParam)) {

		case ID_CLOSE:
		
			EndDialog (hwndDlg, 0);

		default:
			break;
		}

	default:
		return 0;
	}
}

BOOL CALLBACK PrefsDlgProc (HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	char tmpString [64];
	WORD i;
	BYTE ListBoxSelection;
	
	switch (uMsg) {

	case WM_INITDIALOG:

		for (i = 0; i < 10; i++) {
		
			LoadString (g_Instance, ID_STRING1 + i, tmpString, sizeof (tmpString));
			SendMessage (GetDlgItem (hwndDlg, ID_MOUSEINTERVAL), CB_ADDSTRING, 0, (LPARAM) (LPCSTR) tmpString);
			SendMessage (GetDlgItem (hwndDlg, ID_LOCATIONINTERVAL), CB_ADDSTRING, 0, (LPARAM) (LPCSTR) tmpString);
		}

		SendMessage (GetDlgItem (hwndDlg, ID_MOUSEINTERVAL), CB_SETCURSEL, 0, 0);
		SendMessage (GetDlgItem (hwndDlg, ID_LOCATIONINTERVAL), CB_SETCURSEL, 0, 0);

		break;

	case WM_ACTIVATE:

		/*if ((HWND) lParam != hAddLocationDlg)*/
			RefreshWindow (hwndDlg, FALSE);
		break;

	case WM_CLOSE:

		EndDialog (hwndDlg, 0);

	case WM_COMMAND:

		switch (LOWORD(wParam)) {

		case ID_CLOSE:
		
			EndDialog (hwndDlg, 0);
			break;

		case ID_ADDLOCATION:

			DialogBoxParam (g_Instance, MAKEINTRESOURCE(ID_ADDLOCATIONDLG), hwndDlg, AddLocationDlgProc, (LPARAM) GetDlgItem (hwndDlg, ID_LOCATIONS));
			break;

		case ID_REMOVELOCATION:

			ListBoxSelection = (BYTE) SendMessage (GetDlgItem (hwndDlg, ID_LOCATIONS), LB_GETCURSEL, 0, 0);
			SendMessage (GetDlgItem (hwndDlg, ID_LOCATIONS), LB_DELETESTRING, (WPARAM) ListBoxSelection, 0);
			RemoveLocation (&g_Locations, ListBoxSelection);
			break;
		
		case ID_APPLY:
			
			GetWindowText (GetDlgItem (hwndDlg, ID_MOUSEINTERVAL), tmpString, 4);
			g_MouseDelay = atoi (tmpString);
			GetWindowText (GetDlgItem (hwndDlg, ID_LOCATIONINTERVAL), tmpString, 4);
			g_LocationDelay = atoi (tmpString);

			WriteSettings ();
			break;

		default:
			break;
		}

	default:
		return 0;
	}
}

BOOL CALLBACK AddLocationDlgProc (HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	char UrlString [256];
	
	switch (uMsg) {

	case WM_INITDIALOG:

		/*
		hListBox = (HWND) lParam;
		hAddLocationDlg = hwndDlg;
		*/
		SetWindowText (GetDlgItem (hwndDlg, ID_LOCATION), &"http://");
		break;
	
	case WM_CLOSE:

		EndDialog (hwndDlg, 0);
		break;

	case WM_COMMAND:

		switch (LOWORD(wParam)) {

		case ID_ADDLOCATION:

			GetWindowText (GetDlgItem (hwndDlg, ID_LOCATION), UrlString, sizeof (UrlString));
			AddLocation (& g_Locations, UrlString);
			/*
			SendMessage (hListBox, LB_ADDSTRING, 0, (LPARAM) UrlString);
			*/
			SetWindowText (GetDlgItem (hwndDlg, ID_LOCATION), &"http://");
			SetFocus (GetDlgItem (hwndDlg, ID_LOCATION));
			SendMessage (GetDlgItem (hwndDlg, ID_LOCATION), EM_SETSEL, (WPARAM) 0, (LPARAM) -1);
			break;
		case ID_CLOSE:
		
			EndDialog (hwndDlg, 0);

		default:
			break;
		}

	default:
		return 0;
	}
}

void RefreshWindow (HWND hParent, BOOL IsMainWnd) {
		
		HWND hItem;
		char Text [50];
		LPSTR lpText = Text;
		WORD i;

		if (IsMainWnd) {
			
			wsprintf (lpText, "Location is changed in %u sec. intervals",
				g_LocationDelay);
			
			hItem = GetDlgItem (hParent, ID_LOCATIONINTERVAL);
			SetWindowText (hItem, lpText);

			wsprintf (lpText, "Mouse is moved in %u sec. intervals",
				g_MouseDelay);

			hItem = GetDlgItem (hParent, ID_MOUSEINTERVAL);
			SetWindowText (hItem, lpText);
		}
		else {

			hItem = GetDlgItem (hParent, ID_MOUSEINTERVAL);
			SendMessage (hItem, CB_SELECTSTRING, 0, (LPARAM) itoa (g_MouseDelay, Text, 10));

			hItem = GetDlgItem (hParent, ID_LOCATIONINTERVAL);
			SendMessage (hItem, CB_SELECTSTRING, 0, (LPARAM) itoa (g_LocationDelay, Text, 10));
		}

		SendMessage (GetDlgItem (hParent, ID_LOCATIONS), LB_RESETCONTENT, 0, 0);

		for (i = 0; i < 64; i++) {
	
			if (GetLocationAt (&g_Locations, i) != NULL)
				SendMessage (GetDlgItem (hParent, ID_LOCATIONS), LB_ADDSTRING,
						0, (LPARAM) GetLocationAt (&g_Locations, i));
		}
}