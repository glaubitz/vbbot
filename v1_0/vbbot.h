// vbbot.h : Haupt-Header-Datei f�r die Anwendung VBBOT
//

#if !defined(AFX_VBBOT_H__9A6F833B_8E76_4D92_9FCA_D1133FAE0829__INCLUDED_)
#define AFX_VBBOT_H__9A6F833B_8E76_4D92_9FCA_D1133FAE0829__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CVbbotApp:
// Siehe vbbot.cpp f�r die Implementierung dieser Klasse
//

class CVbbotApp : public CWinApp
{
public:
	CVbbotApp();

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CVbbotApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CVbbotApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_VBBOT_H__9A6F833B_8E76_4D92_9FCA_D1133FAE0829__INCLUDED_)
