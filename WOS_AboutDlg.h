#pragma once
#include <afxwin.h>
#include <afxlinkctrl.h>
#include "resource.h"

using namespace std;

class WOS_AboutDlg : public CDialog
{
    enum {
        IDD = IDD_ABOUT,
    };
public://����
    WOS_AboutDlg(CWnd* pParentWnd = NULL);
    ~WOS_AboutDlg();

private: //�p��
    //CHyperLink m_btnLink;
    CRect m_rect;
public://����
    //�������ͫ�Ĥ@�������]�m
    virtual BOOL OnInitDialog();

    //�ާ@�����H���T��
    DECLARE_MESSAGE_MAP()

    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    //�k�W��(X)�������f
    afx_msg void Exit_Window();
};