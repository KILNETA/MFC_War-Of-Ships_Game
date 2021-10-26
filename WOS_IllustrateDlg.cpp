#include "WOS_IllustrateDlg.h"
#include<atlimage.h>

//視窗產生後第一次介面設置 IllustrateDlg_page1
BOOL IllustrateDlg_page1::OnInitDialog()
{
	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_ill_photo1);
	CImage image;
	image.Load(_T("Pictures\\ShipsList.png"));
	HBITMAP hBmp = image.Detach();

	pWnd->SetBitmap(hBmp);
	pWnd->SetWindowPos(NULL, 0, 0, 160, 174, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);

	return TRUE; //做一次
}
//視窗產生後第一次介面設置 IllustrateDlg_page2
BOOL IllustrateDlg_page2::OnInitDialog()
{
	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_ill_photo2);
	CImage image;
	image.Load(_T("Pictures\\ShipsPlace.png"));
	HBITMAP hBmp = image.Detach();

	pWnd->SetBitmap(hBmp);
	pWnd->SetWindowPos(NULL, 0, 0, 173, 145, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);

	return TRUE; //做一次
}
//視窗產生後第一次介面設置 IllustrateDlg_page3
BOOL IllustrateDlg_page3::OnInitDialog()
{
	return TRUE; //做一次
}

/////////////////////////////////////////////////////////////////////////
//                                   WOS_IllustrateDlg class
/////////////////////////////////////////////////////////////////////////

WOS_IllustrateDlg::WOS_IllustrateDlg(CWnd* pParentWnd) :CDialog(WOS_IllustrateDlg::IDD, pParentWnd){
	DoModal();
}
WOS_IllustrateDlg::~WOS_IllustrateDlg(void)
{}

//視窗產生後第一次介面設置 IllustrateDlg Main 
BOOL WOS_IllustrateDlg::OnInitDialog()
{
	m_p1.Create(IDD_ILLUSTRATE_Main_page1, this);
	m_p2.Create(IDD_ILLUSTRATE_Main_page2, this);
	m_p3.Create(IDD_ILLUSTRATE_Main_page3, this);

	m_p1.ShowWindow(SW_SHOW);

	return TRUE; //做一次
}

void WOS_IllustrateDlg::DestroyPage()
{
	switch (Page) {
	case 1:
		m_p1.ShowWindow(SW_HIDE);
		break;
	case 2:
		m_p2.ShowWindow(SW_HIDE);
		break;
	case 3:
		m_p3.ShowWindow(SW_HIDE);
		break;
	}
}

void WOS_IllustrateDlg::TurnPage()
{
	switch (Page) {
	case 1:
		m_p1.ShowWindow(SW_SHOW);
		break;
	case 2:
		m_p2.ShowWindow(SW_SHOW);
		break;
	case 3:
		m_p3.ShowWindow(SW_SHOW);
		break;
	}
	Page != 1 ? ((CButton*)GetDlgItem(IDC_ill_botton1_1))->EnableWindow(TRUE) : ((CButton*)GetDlgItem(IDC_ill_botton1_1))->EnableWindow(FALSE) ;
	Page != 3 ? ((CButton*)GetDlgItem(IDC_ill_botton1_2))->EnableWindow(TRUE) : ((CButton*)GetDlgItem(IDC_ill_botton1_2))->EnableWindow(FALSE);
}

BEGIN_MESSAGE_MAP(WOS_IllustrateDlg, CDialog)

	//右上角(X)關閉窗口
	ON_COMMAND(WM_DESTROY, WOS_IllustrateDlg::Exit_Window)
	ON_COMMAND(IDC_ill_botton1_1, WOS_IllustrateDlg::PreviousPage)
	ON_COMMAND(IDC_ill_botton1_2, WOS_IllustrateDlg::NextPage)

END_MESSAGE_MAP()

//右上角(X)關閉窗口
afx_msg void WOS_IllustrateDlg::Exit_Window()
{
	OnCancel();
}

afx_msg void WOS_IllustrateDlg::PreviousPage()
{
	if (Page - 1 > 0){
		WOS_IllustrateDlg::DestroyPage();
		Page--;
		WOS_IllustrateDlg::TurnPage();
	}
}

afx_msg void WOS_IllustrateDlg::NextPage()
{
	if (Page + 1 < 4) {
		WOS_IllustrateDlg::DestroyPage();
		Page++;
		WOS_IllustrateDlg::TurnPage();
	}
}