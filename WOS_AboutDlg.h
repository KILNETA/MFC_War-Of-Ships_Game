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
public://公有
    WOS_AboutDlg(CWnd* pParentWnd = NULL);
    ~WOS_AboutDlg();

private: //私有
    //CHyperLink m_btnLink;
    CRect m_rect;
public://公有
    //視窗產生後第一次介面設置
    virtual BOOL OnInitDialog();

    //操作介面信息響應
    DECLARE_MESSAGE_MAP()

    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    //右上角(X)關閉窗口
    afx_msg void Exit_Window();
};