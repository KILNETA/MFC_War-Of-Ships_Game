#include "WOS_App.h"

//重寫使用者介面產生之MFC_InitInstance function
BOOL WOS_App::InitInstance()
{
	WOS_Dlg* pdlg = new WOS_Dlg;
	pdlg->Create(IDD_GAME_WINDOW);
	m_pMainWnd = pdlg;
	pdlg->ShowWindow(SW_SHOW);
	return TRUE;
}

WOS_App theApp; //爆破點