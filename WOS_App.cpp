#include "WOS_App.h"

//���g�ϥΪ̤������ͤ�MFC_InitInstance function
BOOL WOS_App::InitInstance()
{
	WOS_Dlg* pdlg = new WOS_Dlg;
	pdlg->Create(IDD_GAME_WINDOW);
	m_pMainWnd = pdlg;
	pdlg->ShowWindow(SW_SHOW);
	return TRUE;
}

WOS_App theApp; //�z�}�I