// OptionsKeyBoard.cpp : implementation file
//

#include "stdafx.h"
#include "CP_Main.h"
#include "OptionsKeyBoard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsKeyBoard property page

IMPLEMENT_DYNCREATE(COptionsKeyBoard, CPropertyPage)

COptionsKeyBoard::COptionsKeyBoard() : CPropertyPage(COptionsKeyBoard::IDD)
{
	//{{AFX_DATA_INIT(COptionsKeyBoard)
	//}}AFX_DATA_INIT
}

COptionsKeyBoard::~COptionsKeyBoard()
{
}

void COptionsKeyBoard::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsKeyBoard)
	DDX_Control(pDX, IDC_CHECK_SEND_PASTE, m_btSendPaste);
	DDX_Control(pDX, IDC_HOTKEY9, m_Nine);
	DDX_Control(pDX, IDC_HOTKEY8, m_Eight);
	DDX_Control(pDX, IDC_HOTKEY7, m_Seven);
	DDX_Control(pDX, IDC_HOTKEY6, m_Six);
	DDX_Control(pDX, IDC_HOTKEY5, m_Five);
	DDX_Control(pDX, IDC_HOTKEY4, m_Four);
	DDX_Control(pDX, IDC_HOTKEY3, m_Three);
	DDX_Control(pDX, IDC_HOTKEY2, m_Two);
	DDX_Control(pDX, IDC_HOTKEY10, m_Ten);
	DDX_Control(pDX, IDC_HOTKEY1, m_One);
	DDX_Control(pDX, IDC_NAMED_COPY, m_NamedCopy);
	DDX_Control(pDX, IDC_HOTKEY, m_HotKey);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COptionsKeyBoard, CPropertyPage)
	//{{AFX_MSG_MAP(COptionsKeyBoard)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsKeyBoard message handlers

BOOL COptionsKeyBoard::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	m_pParent = (COptionsSheet *)GetParent();

	theApp.m_pDittoHotKey->CopyToCtrl( m_HotKey );
	theApp.m_pCopyHotKey->CopyToCtrl( m_NamedCopy );

	theApp.m_pPosOne->CopyToCtrl( m_One );
	theApp.m_pPosTwo->CopyToCtrl( m_Two );
	theApp.m_pPosThree->CopyToCtrl( m_Three );
	theApp.m_pPosFour->CopyToCtrl( m_Four );
	theApp.m_pPosFive->CopyToCtrl( m_Five );
	theApp.m_pPosSix->CopyToCtrl( m_Six );
	theApp.m_pPosSeven->CopyToCtrl( m_Seven );
	theApp.m_pPosEight->CopyToCtrl( m_Eight );
	theApp.m_pPosNine->CopyToCtrl( m_Nine );
	theApp.m_pPosTen->CopyToCtrl( m_Ten );

	//Unregister hotkeys and Reregister them on cancel or ok
	g_HotKeys.UnregisterAll();

	m_btSendPaste.SetCheck(g_Opt.m_bSendPasteOnFirstTenHotKeys);

	m_HotKey.SetFocus();

	return FALSE;
}

LRESULT COptionsKeyBoard::OnWizardNext() 
{
	return CPropertyPage::OnWizardNext();
}

BOOL COptionsKeyBoard::OnWizardFinish() 
{
	return CPropertyPage::OnWizardFinish();
}

BOOL COptionsKeyBoard::OnApply()
{
	CGetSetOptions::SetSendPasteOnFirstTenHotKeys(m_btSendPaste.GetCheck());
					
	int x,y;
	CString str;
	ARRAY keys;
	
	g_HotKeys.GetKeys( keys ); // save old keys just in case new ones are invalid
	
	theApp.m_pDittoHotKey->CopyFromCtrl(m_HotKey);
	theApp.m_pCopyHotKey->CopyFromCtrl(m_NamedCopy);
	
	theApp.m_pPosOne->CopyFromCtrl(m_One);
	theApp.m_pPosTwo->CopyFromCtrl(m_Two);
	theApp.m_pPosThree->CopyFromCtrl(m_Three);
	theApp.m_pPosFour->CopyFromCtrl(m_Four);
	theApp.m_pPosFive->CopyFromCtrl(m_Five);
	theApp.m_pPosSix->CopyFromCtrl(m_Six);
	theApp.m_pPosSeven->CopyFromCtrl(m_Seven);
	theApp.m_pPosEight->CopyFromCtrl(m_Eight);
	theApp.m_pPosNine->CopyFromCtrl(m_Nine);
	theApp.m_pPosTen->CopyFromCtrl(m_Ten);

	ARRAY NewKeys;
	g_HotKeys.GetKeys(NewKeys);
	
	if( g_HotKeys.FindFirstConflict(NewKeys, &x, &y) )
	{
		str =  g_HotKeys.ElementAt(x)->GetName();
		str += " and ";
		str += g_HotKeys.ElementAt(y)->GetName();
		str += " cannot be the same.";
		MessageBox(str);
		g_HotKeys.SetKeys( keys ); // restore the original values
		return FALSE;
	}
	
	g_HotKeys.SaveAllKeys();
	g_HotKeys.RegisterAll(true);
	
	return CPropertyPage::OnApply();
}

/*
BOOL COptionsKeyBoard::ValidateHotKey(WORD wHotKey)
{
	ATOM id = GlobalAddAtom("HK_VALIDATE");
	BOOL bResult = CGetSetOptions::RegisterHotKey(theApp.m_MainhWnd, wHotKey, FALSE);
	
	if(bResult)
		UnregisterHotKey(GetSafeHwnd(), id);

	GlobalDeleteAtom(id);

	return bResult;
}
*/

void COptionsKeyBoard::OnCancel() 
{
	g_HotKeys.RegisterAll( true );
	CPropertyPage::OnCancel();
}
