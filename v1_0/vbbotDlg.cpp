// vbbotDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "vbbot.h"
#include "vbbotDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString SiteURL;
CVbbotDlg * pVbbotDlg;
int SiteCount = 0;
HWND hWnd;
UINT uMsg, idEvent;
DWORD dwTime;

int elapse;

void CALLBACK SetURL (HWND, UINT, UINT, DWORD);
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg-Dialogfeld für Anwendungsbefehl "Info"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialogfelddaten
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// Keine Nachrichten-Handler
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVbbotDlg Dialogfeld

CVbbotDlg::CVbbotDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVbbotDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVbbotDlg)
	m_delay = 2;
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVbbotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVbbotDlg)
	DDX_Control(pDX, IDC_SITES, m_sites);
	DDX_Text(pDX, IDC_DELAY, m_delay);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVbbotDlg, CDialog)
	//{{AFX_MSG_MAP(CVbbotDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPENLIST, OnOpenlist)
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVbbotDlg Nachrichten-Handler

BOOL CVbbotDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Hinzufügen des Menübefehls "Info..." zum Systemmenü.

	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{	
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
			pSysMenu->RemoveMenu (2,MF_BYPOSITION);
			pSysMenu->RemoveMenu (3,MF_BYPOSITION);
		}
	}

	// Symbol für dieses Dialogfeld festlegen. Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	
	// ZU ERLEDIGEN: Hier zusätzliche Initialisierung einfügen
	
	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

void CVbbotDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// Wollen Sie Ihrem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch für Sie erledigt.

void CVbbotDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext für Zeichnen

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Symbol in Client-Rechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Die Systemaufrufe fragen den Cursorform ab, die angezeigt werden soll, während der Benutzer
//  das zum Symbol verkleinerte Fenster mit der Maus zieht.
HCURSOR CVbbotDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void LoadURLS (CString filename, CVbbotDlg * pDlg) { /* filename includes full-path name */

	HANDLE FileHandle;
	DWORD FileSize;
	DWORD BytesRead;
	LPSTR LoadText;
	CString StringData;
	CString tmpString;

	int j = 0;
	DWORD i = 0;


	FileHandle = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);

		FileSize = GetFileSize(FileHandle, NULL);
		
		if(FileSize != 0xFFFFFFFF) {

			
			LoadText = new char [FileSize + 1];
			
			if(LoadText != NULL) {
				
				if(ReadFile (FileHandle, LoadText, FileSize, &BytesRead, NULL))
					LoadText[FileSize] = 0; // Null terminator
					
				
			}
		}
		
		CloseHandle(FileHandle);

		StringData = LoadText;
		
		while (i < FileSize) {

			while (i < FileSize) {
				
				if (StringData.GetAt(i) == '\r')
					break;

				tmpString += StringData.GetAt(i);
				i++;
			}
			
			i++; /* because of \n */
			i++;
			
			pDlg->m_sites.AddString (tmpString);
				
			tmpString = "";
		}
}

void CVbbotDlg::OnOpenlist() 
{
	CFileDialog openDlg (TRUE, NULL, NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "TextFiles (*.txt)|*.txt||\0", NULL);
	CString filename;
	int msg = openDlg.DoModal();
	
	if (msg == IDOK) {
	
		filename = openDlg.GetPathName ();
		LoadURLS (filename, this);
		CWnd * hButton = GetDlgItem (IDC_START);
		hButton->EnableWindow (TRUE);
		
	}

	UpdateData(FALSE);
}

void CVbbotDlg::OnStart() 
{
	
	UpdateData (TRUE);
	pVbbotDlg = this;
	elapse = pVbbotDlg->m_delay * 60000;
	
	if (elapse >= 60000 && elapse <= 600000)
		::SetTimer (GetSafeHwnd(), IDC_TIMER, elapse, SetURL);
	else
		MessageBox ("The delay between site switch is out of range (1-10 mins).", "Error", MB_OK|MB_ICONSTOP);
}

void CALLBACK SetURL (HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime) {

	pVbbotDlg->m_sites.GetLBText (SiteCount, SiteURL);
	pVbbotDlg->m_sites.SetCurSel (SiteCount);
	SiteCount++;

	if (SiteCount == pVbbotDlg->m_sites.GetCount ())
		SiteCount = 0;

	::ShellExecute (NULL, "open", SiteURL.operator LPCSTR(), "","", SW_SHOWDEFAULT);
	
}
void CVbbotDlg::OnStop() 
{
	::KillTimer (GetSafeHwnd (), IDC_TIMER);	
}
