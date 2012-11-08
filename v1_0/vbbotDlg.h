// vbbotDlg.h : Header-Datei
//

#if !defined(AFX_VBBOTDLG_H__B47FA538_4AB6_4773_AE82_94C400449A4C__INCLUDED_)
#define AFX_VBBOTDLG_H__B47FA538_4AB6_4773_AE82_94C400449A4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CVbbotDlg Dialogfeld

class CVbbotDlg : public CDialog
{
// Konstruktion
public:
	CVbbotDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CVbbotDlg)
	enum { IDD = IDD_VBBOT_DIALOG };
	CComboBox	m_sites;
	int		m_delay;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CVbbotDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CVbbotDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpenlist();
	afx_msg void OnStart();
	afx_msg void OnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_VBBOTDLG_H__B47FA538_4AB6_4773_AE82_94C400449A4C__INCLUDED_)
