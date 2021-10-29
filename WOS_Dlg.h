#pragma once
#include <afxwin.h>
#include "Windows7_Style.h"
#include "WarShips.h"
#include "Buttons_Data.h"
#include "resource.h"
#include <vector>

using namespace std;


/////////////////////////////////////////////////////////////////////////
//                                   WOS_Dlg class
/////////////////////////////////////////////////////////////////////////
class WOS_Dlg : public CDialog
{
	friend class WOS_GameEndDlg;

private: //私有

	//目錄列表宣告
	CMenu m_Menu;//目錄
	bool gameStart = false;//遊戲開始
	vector<WarShips> MyWarShips;//我艦
	vector<WarShips> EnemyWarShips;//敵艦
	vector<Buttons_Data> MyBlock;//我方海格
	vector<Buttons_Data> EnemyBlock; //敵方海格
	int choose = NULL;//當前選擇
	bool direction = true;//方向
	//記分板
	int winner = 0 ;
	vector<int> fires_Number = { 0,0 };
	vector<int> hit_Number = { 0,0 };


	//警告視窗呼叫
	void WarningWindow(CString test);

	//轉換選擇
	void ReplaceChoose(UINT uId);
	//放下船
	void PlaceShip(UINT uId, int direction, int _choose, vector<WarShips>& warShips, vector<Buttons_Data>& block);
	//選擇與把船拿走
	void ChooseAndTakeback(UINT uId, vector<WarShips>& warShips, vector<Buttons_Data>& block);
	//把船放在該位置
	void SetChooseInCoordinate(UINT uId);
	//佈署敵方艦船
	void PlaceEnemyShips();

	//開炮
	int Fire(UINT uId, vector<WarShips>& warShips, vector<Buttons_Data>& block, int shootStatic, int killStatic);
	//擊中敵艦
	void HitShip(UINT uId, int shipID, vector<WarShips>& warShips);
	//檢查船隻沉沒
	bool CheckShipDied(int shipID, vector<WarShips>& warShips , int killStatic);

	//(AI開火)紀錄上次攻擊 + 攻擊
	bool RecordLastAttack(int aiUId, int& aiLastAttack, bool& nextFire, int& aiDirection, int mode);
	//(AI開火敵方開火
	void EnemyAttack();

	//檢查遊戲是否結束
	int CheckGameOver();

	//重置遊戲
	void ReloadGame();

	//關閉主介面
	void Destroy_Window();
	
public://公有

	//操作介面信息響應
	DECLARE_MESSAGE_MAP()

	//重寫 視窗產生後第一次介面設置
	virtual BOOL OnInitDialog();
	//重寫 鍵盤按鍵的反應
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//當敵方陣營海域方塊被按下 function
	afx_msg void ENEMY_ButtonClicked(UINT   uId);
	//當我方陣營海域方塊被按下 function
	afx_msg void MY_ButtonClicked(UINT   uId);
	//當我方艦船方塊被選擇
	afx_msg void MY_WarShipClicked(UINT   uId);
	//遊戲開始 function
	afx_msg void Game_Start();
	//右上角(X)關閉窗口
	afx_msg void Exit_Window();
	//放棄該局遊戲
	afx_msg void AbandonGame();


	//關於介面呼叫
	afx_msg void ABOUT();
	//說明介面呼叫
	afx_msg void ILLUSTRATE();
};



/////////////////////////////////////////////////////////////////////////
//                                   WOS_GameEndDlg class
/////////////////////////////////////////////////////////////////////////
class WOS_GameEndDlg : public CDialog
{
	enum {
		IDD = IDD_REPLAY,
	};
public://公有
	WOS_GameEndDlg(int winner, vector<int> &fires_Number, vector<int> &hit_Number,
		vector<WarShips>&MyWarShips, vector<WarShips>& EnemyWarShips,
		CWnd* pParentWnd = NULL);
	~WOS_GameEndDlg();

private: //私有
	//記分板
	int winner = 0;
	vector<int> fires_Number ;
	vector<int> hit_Number ;
	vector<WarShips> MyWarShips;//我艦
	vector<WarShips> EnemyWarShips;//敵艦

	void Scoreboard_Display();
public://公有

	//操作介面信息響應
	DECLARE_MESSAGE_MAP()

	//重寫 視窗產生後第一次介面設置
	virtual BOOL OnInitDialog();

	//右上角(X)關閉窗口
	afx_msg void Exit_Window();
	//離開程式
	afx_msg void Exit_Application();
	//重開一局
	afx_msg void Exit_Replay();
};



/////////////////////////////////////////////////////////////////////////
//                                   WOS_WarningDlg class
/////////////////////////////////////////////////////////////////////////
class WOS_WarningDlg : public CDialog
{
	friend class WOS_Dlg;

	enum {
		IDD = IDD_WARNING,
	};
public://公有
	WOS_WarningDlg(CString text,CWnd* pParentWnd = NULL);
	~WOS_WarningDlg();

private: //私有
	CString text;
	//改變內容文字
	void ChangeText(CString text);
	//關閉視窗
	afx_msg void Exit_Window();

public://公有
	//操作介面信息響應
	DECLARE_MESSAGE_MAP()
	//重寫 視窗產生後第一次介面設置
	virtual BOOL OnInitDialog();
	//重寫 按鍵感測
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};