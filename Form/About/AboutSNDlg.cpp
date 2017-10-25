// AboutSNDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SN Writer.h"
#include "AboutSNDlg.h"
#include "SNBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutSNDlg dialog

extern const char* g_strToolVersion;

CAboutSNDlg::CAboutSNDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutSNDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAboutSNDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAboutSNDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutSNDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutSNDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutSNDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutSNDlg message handlers

BOOL CAboutSNDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    //void  __stdcall META_GetDLLInfo(const char** pp_version, const char** pp_release_type, const char** pp_build_date, const char** pp_load_path);
    const char *p_version;
    CString strVersion;
    CString toolVersion = g_strToolVersion;
    ((CWnd*)GetDlgItem(IDC_SN_VERSION))->SetWindowText(toolVersion);

	META_GetDLLInfo(&p_version, NULL, NULL, NULL);
    strVersion = p_version;
    ((CWnd*)GetDlgItem(IDC_METADLL_VERSION))->SetWindowText(strVersion);

    SPMETA_DLL::SP_META_GetDLLInfo(&p_version, NULL, NULL, NULL);
    strVersion = p_version;
    ((CWnd*)GetDlgItem(IDC_SPMETADLL_VERSION))->SetWindowText(strVersion);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
