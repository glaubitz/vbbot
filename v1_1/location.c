/*
* Viewbar Bot
* the ultimative tool to fake any viewbar
*
* v 1.1.2
* date: May., 06 2001
* (C) Adrian Glaubitz
* adi007@germanynet.de
*
* location.c - location (url) management
*/

#ifndef __LOCATION_C
#define __LOCATION_C
#endif

#include "global.h"

void AddLocation (LOCATIONS * lpLocations, LPCSTR Location) {

	LPSTR * tmplpstr;
	WORD i;
	
	if (lpLocations->Locations == NULL) {

		// lpLocations = GlobalAlloc (0, sizeof (LOCATIONS *));
		lpLocations->Locations = GlobalAlloc (0, sizeof (LPSTR));
		lpLocations->Locations [0] = GlobalAlloc (0, lstrlen (Location) + 1);
		lpLocations->Locations [0] = lstrcpy (lpLocations->Locations [0], Location);

		g_LocationCount = 1;
	}

	else {

		tmplpstr = GlobalAlloc (0, (g_LocationCount + 1) * sizeof (LPSTR));

		for (i = 0; i < g_LocationCount; i++)
			tmplpstr [i] = lpLocations->Locations [i];

		tmplpstr [i] = GlobalAlloc (0, lstrlen (Location) + 1);

		tmplpstr [i] = lstrcpy (tmplpstr [i], Location);

		GlobalFree ((HGLOBAL) lpLocations->Locations);
		
		lpLocations->Locations = tmplpstr;

		g_LocationCount++;
	}
}

void RemoveLocation (LOCATIONS * lpLocations, BYTE Count) {

	WORD i;
	
	if (Count < g_LocationCount)
		GlobalFree ((HGLOBAL) lpLocations->Locations [Count]);
	
	// lpLocations->Locations [Count] = NULL;
	
	for (i = Count; i < g_LocationCount - 1; i++) {

		lpLocations->Locations [i] = lpLocations->Locations [i + 1];
		// lpLocations->Locations [i + 1] = NULL;
	}

	g_LocationCount--;

}

LPSTR GetLocationAt (LOCATIONS * lpLocations, WORD Count) {

	if (lpLocations->Locations != NULL)
		if (Count < g_LocationCount)
			return lpLocations->Locations [Count];
		else
			return NULL;
	else
		return NULL;
}