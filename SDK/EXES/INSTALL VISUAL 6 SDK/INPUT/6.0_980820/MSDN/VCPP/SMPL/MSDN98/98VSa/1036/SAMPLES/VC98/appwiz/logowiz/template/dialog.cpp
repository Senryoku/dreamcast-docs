// $$dlg_ifile$$.cpp : implementation file
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1995-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "$$root$$.h"
#include "$$dlg_hfile$$.h"
$$IF(AUTOMATION)
#include "$$dlgautoproxy_hfile$$.h"
$$ENDIF //AUTOMATION
$$IF(PRESS_ME_DIALOG)
#include "pressdlg.h"
$$ENDIF //PRESS_ME_DIALOG

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

$$IF(ABOUT)
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
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
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

$$ENDIF //ABOUT
/////////////////////////////////////////////////////////////////////////////
// $$DLG_CLASS$$ dialog
$$IF(AUTOMATION)

IMPLEMENT_DYNAMIC($$DLG_CLASS$$, $$DLG_BASE_CLASS$$);
$$ENDIF //AUTOMATION

$$DLG_CLASS$$::$$DLG_CLASS$$(CWnd* pParent /*=NULL*/)
	: $$DLG_BASE_CLASS$$($$DLG_CLASS$$::IDD, pParent)
{
	//{{AFX_DATA_INIT($$DLG_CLASS$$)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
$$IF(VERBOSE)
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
$$ENDIF
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
$$IF(AUTOMATION)
	m_pAutoProxy = NULL;
$$ENDIF //AUTOMATION
}
$$IF(AUTOMATION)

$$DLG_CLASS$$::~$$DLG_CLASS$$()
{
$$IF(VERBOSE)
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
$$ENDIF //VERBOSE
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}
$$ENDIF //AUTOMATION

void $$DLG_CLASS$$::DoDataExchange(CDataExchange* pDX)
{
	$$DLG_BASE_CLASS$$::DoDataExchange(pDX);
	//{{AFX_DATA_MAP($$DLG_CLASS$$)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP($$DLG_CLASS$$, $$DLG_BASE_CLASS$$)
	//{{AFX_MSG_MAP($$DLG_CLASS$$)
$$IF(ABOUT)
	ON_WM_SYSCOMMAND()
$$ENDIF
$$IF(HELP)
	ON_WM_DESTROY()
$$ENDIF
$$IF(AUTOMATION)
	ON_WM_CLOSE()
$$ENDIF
$$IF(PRESS_ME_DIALOG)
	ON_COMMAND(IDC_PRESS_ME, OnPressMe)
$$ENDIF
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// $$DLG_CLASS$$ message handlers

BOOL $$DLG_CLASS$$::OnInitDialog()
{
	$$DLG_BASE_CLASS$$::OnInitDialog();
$$IF(ABOUT)

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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
		}
	}
$$ENDIF //ABOUT

$$IF(VERBOSE)
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
$$ENDIF //VERBOSE
	SetIcon(m_hIcon, TRUE);         // Set big icon
	SetIcon(m_hIcon, FALSE);        // Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}
$$IF(ABOUT)

void $$DLG_CLASS$$::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		$$DLG_BASE_CLASS$$::OnSysCommand(nID, lParam);
	}
}
$$ENDIF //ABOUT
$$IF(HELP)

void $$DLG_CLASS$$::OnDestroy()
{
	WinHelp(0L, HELP_QUIT);
	$$DLG_BASE_CLASS$$::OnDestroy();
}
$$ENDIF //HELP
$$IF(PRESS_ME_DIALOG)

void $$DLG_CLASS$$::OnPressMe()
{
	CPressMeDlg dlg;
	dlg.DoModal();
}
$$ENDIF //PRESS_ME_DIALOG

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void $$DLG_CLASS$$::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		$$DLG_BASE_CLASS$$::OnPaint();
	}
}

$$IF(VERBOSE)
// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
$$ENDIF
HCURSOR $$DLG_CLASS$$::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
$$IF(AUTOMATION)
$$IF(VERBOSE)

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.
$$ENDIF //VERBOSE

void $$DLG_CLASS$$::OnClose()
{
	if (CanExit())
		$$DLG_BASE_CLASS$$::OnClose();
}

void $$DLG_CLASS$$::OnOK()
{
	if (CanExit())
		$$DLG_BASE_CLASS$$::OnOK();
}

void $$DLG_CLASS$$::OnCancel()
{
	if (CanExit())
		$$DLG_BASE_CLASS$$::OnCancel();
}

BOOL $$DLG_CLASS$$::CanExit()
{
$$IF(VERBOSE)
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
$$ENDIF //VERBOSE
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}
$$ENDIF //AUTOMATION
