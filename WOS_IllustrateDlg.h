#pragma once

#include <afxwin.h>
#include "resource.h"

using namespace std;

class IllustrateDlg_page1 : public CDialog
{
private: //�p��

public://����

	//���g �������ͫ�Ĥ@�������]�m
	virtual BOOL OnInitDialog();

};

class IllustrateDlg_page2 : public CDialog
{
private: //�p��
	CRect m_rect;
public://����

	//���g �������ͫ�Ĥ@�������]�m
	virtual BOOL OnInitDialog();

};

class IllustrateDlg_page3 : public CDialog
{
private: //�p��

public://����

	//���g �������ͫ�Ĥ@�������]�m
	virtual BOOL OnInitDialog();

};


class WOS_IllustrateDlg : public CDialog
{
private: //�p��
	IllustrateDlg_page1 m_p1;
	IllustrateDlg_page2 m_p2;
	IllustrateDlg_page3 m_p3;
	int Page = 1;

public://����

	//���g �������ͫ�Ĥ@�������]�m
	virtual BOOL OnInitDialog();
	void DestroyPage();
	void TurnPage();

	//�ާ@�����H���T��
	DECLARE_MESSAGE_MAP()

	//�k�W��(X)�������f
	afx_msg void Exit_Window();
	afx_msg void PreviousPage();
	afx_msg void NextPage();
};

