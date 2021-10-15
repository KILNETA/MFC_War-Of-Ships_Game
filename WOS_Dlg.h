#pragma once
#include <afxwin.h>
#include "Windows7_Style.h"
#include "WarShips.h"
#include "Buttons_Data.h"
#include "resource.h"
#include <vector>

using namespace std;

class WOS_Dlg : public CDialog
{
private: //私有

	//目錄列表宣告
	CMenu m_Menu;//目錄
	bool gameStart=false;//遊戲開始
	vector<WarShips> MyWarShips;//我艦
	vector<WarShips> EnemyWarShips;//敵艦
	vector<Buttons_Data> MyBlock;//我方海格
	vector<Buttons_Data> EnemyBlock; //敵方海格
	int choose=NULL;//當前選擇
	bool direction = true;

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
	bool CheckGameOver();

	//重置遊戲
	void reloadGame();
	
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
	//遊戲開始 function
	afx_msg void Exit_Window();

	//關於介面呼叫
	afx_msg void ABOUT();
};