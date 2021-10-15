#pragma once
#include <afxwin.h>
#include <afxlinkctrl.h>
#include "resource.h"

using namespace std;

class WOS_AboutDlg : public CDialog
{
private: //私有
    //CHyperLink m_btnLink;
    CRect m_rect;
public://公有
    //操作介面信息響應
    DECLARE_MESSAGE_MAP()

    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

    virtual BOOL OnInitDialog();
};