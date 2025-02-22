// MacroDlg.Cpp : implementation file
//

#include "StdAfx.H"
#include "TestCon.H"
#include "Resource.HM"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMacroDlg dialog

CMacroDlg::CMacroDlg( CWnd* pParent ) :
   CDialog( CMacroDlg::IDD, pParent ),
   m_pScriptManager( NULL ),
   m_pScript( NULL )
{
	//{{AFX_DATA_INIT(CMacroDlg)
	m_strMacroName = _T("");
	//}}AFX_DATA_INIT
}


void CMacroDlg::DoDataExchange(CDataExchange* pDX)
{
   int iItem;

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMacroDlg)
	DDX_Control(pDX, IDOK, m_butRun);
	DDX_Control(pDX, IDC_MACROS, m_lbMacros);
	DDX_LBString(pDX, IDC_MACROS, m_strMacroName);
	//}}AFX_DATA_MAP

   if( pDX->m_bSaveAndValidate )
   {
	  iItem = m_lbMacros.GetCurSel();
	  if( iItem == LB_ERR )
	  {
		 m_pScript = NULL;
	  }
	  else
	  {
		 m_pScript = (CScript*)m_lbMacros.GetItemDataPtr( iItem );
		 ASSERT( m_pScript != NULL );
	  }
   }
}


BEGIN_MESSAGE_MAP(CMacroDlg, CDialog)
	//{{AFX_MSG_MAP(CMacroDlg)
	ON_BN_CLICKED(IDC_OPENFILE, OnOpenFile)
	ON_WM_HELPINFO()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMacroDlg message handlers

BOOL CMacroDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

   UpdateMacroList();

	return( TRUE );
}

void CMacroDlg::OnOpenFile()
{
   int nResult;
   HRESULT hResult;

   CFileDialog dlg( TRUE, _T( "dsm" ), NULL, OFN_HIDEREADONLY|
	  OFN_OVERWRITEPROMPT, _T( "Script Files (*.dsm)|*.dsm||" ) );

   nResult = dlg.DoModal();
   if( nResult != IDOK )
   {
	  return;
   }

   hResult = m_pScriptManager->LoadScript( dlg.GetPathName(),
	  dlg.GetFileTitle() );
   if( FAILED( hResult ) )
   {
	  CString strErrorMessage;
	  _com_error error( hResult );

	  AfxFormatString2( strErrorMessage, IDS_ERRORLOADINGSCRIPT,
		 dlg.GetFileTitle(), error.ErrorMessage() );
	  AfxMessageBox( strErrorMessage );
	  return;
   }

   UpdateMacroList();
}

void CMacroDlg::UpdateMacroList()
{
   POSITION posMacro;
   POSITION posScript;
   CScript* pScript;
   CString strMacroName;
   int iItem;

   m_lbMacros.ResetContent();

   posScript = m_pScriptManager->GetFirstScriptPosition();
   while( posScript != NULL )
   {
	  pScript = m_pScriptManager->GetNextScript( posScript );
	  ASSERT( pScript != NULL );

	  posMacro = pScript->GetFirstMacroPosition();
	  while( posMacro != NULL )
	  {
		 strMacroName = pScript->GetNextMacroName( posMacro );
		 iItem = m_lbMacros.AddString( strMacroName );
		 m_lbMacros.SetItemDataPtr( iItem, pScript );
	  }
   }

   if( m_lbMacros.GetCount() == 0 )
   {
	  m_lbMacros.SetCurSel( -1 );
	  m_butRun.EnableWindow( FALSE );
   }
   else
   {
	  m_lbMacros.SetCurSel( 0 );
	  m_butRun.EnableWindow( TRUE );
   }
}


static DWORD rgmapCHID[] =
{
   IDC_MACROS, HIDC_MACROS,
   IDC_OPENFILE, HIDC_OPENFILE,
   0, 0
};

BOOL CMacroDlg::OnHelpInfo( HELPINFO* pHelpInfo )
{
   return( ::WinHelp( HWND( pHelpInfo->hItemHandle ),
	  AfxGetApp()->m_pszHelpFilePath, HELP_WM_HELP, DWORD( LPVOID(
	  rgmapCHID ) ) ) );
}

void CMacroDlg::OnContextMenu( CWnd* pWnd, CPoint /* point */ )
{
   ::WinHelp( HWND( *pWnd ), AfxGetApp()->m_pszHelpFilePath, HELP_CONTEXTMENU,
	  DWORD( LPVOID( rgmapCHID ) ) );
}
