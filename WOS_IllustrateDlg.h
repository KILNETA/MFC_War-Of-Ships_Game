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
	CRect m_rect;
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
private: //私有
	IllustrateDlg_page1 m_p1;
	IllustrateDlg_page2 m_p2;
	IllustrateDlg_page3 m_p3;
	int Page = 1;

public://公有

	//重寫 視窗產生後第一次介面設置
	virtual BOOL OnInitDialog();
	void DestroyPage();
	void TurnPage();

	//操作介面信息響應
	DECLARE_MESSAGE_MAP()

	//右上角(X)關閉窗口
	afx_msg void Exit_Window();
	afx_msg void PreviousPage();
	afx_msg void NextPage();
};

