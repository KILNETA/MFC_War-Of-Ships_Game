#include "WOS_AboutDlg.h"
#include<atlimage.h>
#include<Winuser.h>      

//視窗產生後第一次介面設置
BOOL WOS_AboutDlg::OnInitDialog()
{

	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_Github_Head);
	CImage image;
	image.Load(_T("Pictures\\Github_Head.png"));
	HBITMAP hBmp = image.Detach();

	pWnd->SetBitmap(hBmp);
	pWnd->SetWindowPos(NULL,0,0,200,200,SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOZORDER);

	GetDlgItem(IDC_About_text5)->GetWindowRect(&m_rect);
	ScreenToClient(&m_rect);

	return FALSE; //回傳TRUE
}

/////////////////////
BEGIN_MESSAGE_MAP(WOS_AboutDlg, CDialog)

	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CTLCOLOR()
	//右上角(X)關閉窗口
	ON_COMMAND(WM_DESTROY, Exit_Window)

END_MESSAGE_MAP()

/////////////////////

void WOS_AboutDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (point.x > m_rect.left && point.x < m_rect.right && point.y<m_rect.bottom && point.y>m_rect.top)
	{
		ShellExecute(NULL, NULL, _T("https://github.com/KILNETA"), NULL, NULL, SW_NORMAL);
	}
	CDialog::OnLButtonUp(nFlags, point);
}

void WOS_AboutDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (point.x > m_rect.left && point.x < m_rect.right && point.y < m_rect.bottom && point.y > m_rect.top)
	{
		HCURSOR hCursor;
		hCursor = ::LoadCursor(NULL, IDC_HAND);
		::SetCursor(hCursor);
	}
	CDialog::OnMouseMove(nFlags, point);
}

HBRUSH WOS_AboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_About_text5)
	{
		pDC->SetTextColor(RGB(64, 148, 199));
	}

	return hbr;
}

//右上角(X)關閉窗口
afx_msg void WOS_AboutDlg::Exit_Window()
{
	DestroyWindow();
	delete this;
}