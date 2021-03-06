#pragma once

#include <afxwin.h>
#include "resource.h"

using namespace std;

class IllustrateDlg_page1 : public CDialog
{
private: //私有

public://公有
	//重寫 視窗產生後第一次介面設置
	virtual BOOL OnInitDialog();

};

class IllustrateDlg_page2 : public CDialog
{
private: //私有

public://公有
	//重寫 視窗產生後第一次介面設置
	virtual BOOL OnInitDialog();

};

class IllustrateDlg_page3 : public CDialog
{
private: //私有

public://公有
	//重寫 視窗產生後第一次介面設置
	virtual BOOL OnInitDialog();

};


class WOS_IllustrateDlg : public CDialog
{
	enum {
		IDD = IDD_ILLUSTRATE_Main,
	};
public://公有
	WOS_IllustrateDlg(CWnd* pParentWnd = NULL);
	~WOS_IllustrateDlg();

private: //私有
	IllustrateDlg_page1 m_p1;
	IllustrateDlg_page2 m_p2;
	IllustrateDlg_page3 m_p3;
	int Page = 1;

public://公有
	//重寫 視窗產生後第一次介面設置
	virtual BOOL OnInitDialog();

	//關閉分頁
	void DestroyPage();
	//換頁
	void TurnPage();

	//操作介面信息響應
	DECLARE_MESSAGE_MAP()

	//右上角(X)關閉窗口
	afx_msg void Exit_Window();
	//上一頁
	afx_msg void PreviousPage();
	//下一頁
	afx_msg void NextPage();
};

