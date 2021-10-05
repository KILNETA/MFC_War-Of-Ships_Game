#include "WOS_Dlg.h"

#include <stdlib.h> /* 亂數相關函數 */
#include <time.h>   /* 時間相關函數 */

///////////////////////////////////////////////////////////////////////////
///                     private    Function
///////////////////////////////////////////////////////////////////////////

//轉換選擇 down
void WOS_Dlg::ReplaceChoose(UINT uId){
	if (this->choose != NULL){
		((CButton*)GetDlgItem(this->choose))->EnableWindow(TRUE);
		this->choose = uId;
		((CButton*)GetDlgItem(uId))->EnableWindow(FALSE);
	}
	this->choose = uId;
	((CButton*)GetDlgItem(uId))->EnableWindow(FALSE);
	return;
}

//放下船 down
void WOS_Dlg::PlaceShip(UINT uId, int direction, int _choose, vector<WarShips>& warShips, vector<Buttons_Data>& block) {
	if ((uId % (10 * direction)) + (warShips[_choose % 10].GetCoordinate_Size() * direction) < (10*direction)+(1* direction)) {
		//未超出格子
		for (int n = 0; n < warShips[_choose % 10].GetCoordinate_Size(); n++)
		{//檢查中間有無船隻阻擋
			if (block[(uId % 1000) + (n * direction)].GiveShipID() != NULL) {
				if (!this->gameStart){
					AfxMessageBox(_T("撞船了"));
				}
				return;
		}	}
		//把該船所站之格子寫入參數 /並將船艦佔有該格的資料寫入資料中
		for (int n = 0; n < warShips[_choose % 10].GetCoordinate_Size(); n++){
			block[(uId%1000) + (n * direction)].SetShipID(_choose);
			((CButton*)GetDlgItem(uId + (n * direction)))->SetWindowText(warShips[_choose % 10].GetShipName());

			warShips[_choose % 10].setCoordinate(n, uId + (n * direction));
		}
		warShips[_choose % 10].setPlace(true);
		if (!this->gameStart) {
			this->choose = NULL; //把當前選擇清空
		}
	}else {//超出格子
		if (!this->gameStart) {
			AfxMessageBox(_T("位置不足"));
}	}	}

//選擇與把船拿走
void WOS_Dlg::ChooseAndTakeback(UINT uId , vector<WarShips>& warShips, vector<Buttons_Data>& block)
{
	//該格所在之艦船ID
	int shipID = block[uId % 1000].GiveShipID();
	//呼叫替換選擇function  //重新選擇船艦
	if (!this->gameStart) {
		WOS_Dlg::ReplaceChoose(shipID);
	}

	//把該船所站之格子還原參數 /並將船艦佔有該格的資料去除
	for (int n = 0; n < warShips[shipID % 10].GetCoordinate_Size(); n++){
		int Coordinate = warShips[shipID % 10].GetCoordinate(n);
		((CButton*)GetDlgItem(Coordinate))->SetWindowText(_T(""));
		block[Coordinate%1000].SetShipID(0);

		warShips[shipID % 10].setCoordinate(n, NULL);
		warShips[shipID % 10].setPlace(false);
	}
	return;
}

//把船放在該位置 down
void WOS_Dlg::SetChooseInCoordinate(UINT uId)
{
	if (this->direction) {//水平
		WOS_Dlg::PlaceShip(uId, 1,this->choose, this->MyWarShips, this->MyBlock);
	}else {//垂直
		WOS_Dlg::PlaceShip(uId, 10, this->choose, this->MyWarShips, this->MyBlock);
	}
	return;
}

//佈署敵方艦船
void WOS_Dlg::PlaceEnemyShips()
{
	//亂數設置
	srand(time(NULL));
	for (int shipsNum = 0; shipsNum < 5; shipsNum++){
		while (!this->EnemyWarShips[shipsNum].GetPlace()) {
			int aiUId = (rand() % 100)+1000;
			int aiDirection = rand() % 2 ? 1 : 10 ;
			int aiChoose = this->EnemyWarShips[shipsNum].GetShipID();

			WOS_Dlg::PlaceShip(aiUId, aiDirection, aiChoose, EnemyWarShips, EnemyBlock);
		}
	}
}



//開炮
int WOS_Dlg::Fire(UINT uId, vector<WarShips>& warShips, vector<Buttons_Data>& block, int shootStatic, int killStatic)
{
	if (block[uId % 100].GiveShipID() != NULL){//該處有船
		WOS_Dlg::HitShip(uId, block[uId % 100].GiveShipID(), warShips); //擊中船
		((CButton*)GetDlgItem(uId))->SetWindowText(_T("Ｘ"));
		//output //公告擊中+船的名子
		GetDlgItem(shootStatic)->SetWindowText(L"擊中" + warShips[block[uId % 100].GiveShipID() % 10].GetShipName() +
																						 L"  "+ block[uId % 100].GetButtonsName());
		//檢查船隻沉沒
		if (WOS_Dlg::CheckShipDied(block[uId % 100].GiveShipID(), warShips, killStatic)){
			return 1;
		}else{
			return 2;
	}	}
	else {//該處沒有船
		((CButton*)GetDlgItem(uId))->SetWindowText(_T("。"));

		GetDlgItem(shootStatic)->SetWindowText(L"未擊中船隻  " + block[uId % 100].GetButtonsName());
		return 0;
	}
}

//擊中敵艦
void WOS_Dlg::HitShip(UINT uId, int shipID, vector<WarShips>& warShips)
{
	for(int n = 0; n < warShips[shipID % 10].GetCoordinate_Size(); n++)
	{
		if (warShips[shipID % 10].GetCoordinate(n)== uId){
			warShips[shipID % 10].setCoordinate(n,NULL);
		}else{}
	}
}

//檢查船隻沉沒
bool WOS_Dlg::CheckShipDied(int shipID, vector<WarShips>& warShips, int killStatic)
{
	for (int n = 0; n < warShips[shipID % 10].GetCoordinate_Size(); n++){
		if (warShips[shipID % 10].GetCoordinate(n) != NULL) {//未被擊沉
			GetDlgItem(killStatic)->SetWindowText(L"");
			return false;
	}	}
	warShips[shipID % 10].setKill(true);
	//output 船隻按鈕反黑 投放公告
	((CButton*)GetDlgItem(shipID))->EnableWindow(FALSE); 
	GetDlgItem(killStatic)->SetWindowText(warShips[shipID % 10].GetShipName()+ L"已被完全擊沉");
	return true;
}

//(AI開火)紀錄上次攻擊 + 攻擊
void WOS_Dlg::RecordLastAttack(int aiUId)
{
	((CButton*)GetDlgItem(aiUId))->EnableWindow(FALSE);
	switch (WOS_Dlg::Fire(aiUId, this->MyWarShips, this->MyBlock, IDC_ENEMY_shoot, IDC_MY_kill)) {
	case 0:
		return; break;
	case 1:
		this->aiLastAttack = NULL;
		return; break;
	case 2:
		this->aiLastAttack = aiUId;
		return; break;
	}
}

//(AI開火)敵方攻擊
void WOS_Dlg::EnemyAttack(){
	bool fire = false;
	srand(time(NULL));
	while (!fire){
		if (this->aiLastAttack != NULL){
			for (int n = 0; n < 5; n++) {
				switch (n)
				{
				case 0: if (this->aiLastAttack - 1 >= (this->aiLastAttack / 10) * 10 && ((CButton*)GetDlgItem(this->aiLastAttack - 1))->IsWindowEnabled() == TRUE) {
					WOS_Dlg::RecordLastAttack(this->aiLastAttack - 1); fire = true;
				} break;
				case 1: if (this->aiLastAttack - 10 >= 2000 && ((CButton*)GetDlgItem(this->aiLastAttack - 10))->IsWindowEnabled() == TRUE) {
					WOS_Dlg::RecordLastAttack(this->aiLastAttack - 10); fire = true;
				} break;
				case 2: if (this->aiLastAttack + 1 <= ((this->aiLastAttack / 10) * 10) + 9 && ((CButton*)GetDlgItem(this->aiLastAttack + 1))->IsWindowEnabled() == TRUE) {
					WOS_Dlg::RecordLastAttack(this->aiLastAttack + 1); fire = true;
				} break;
				case 3: if (this->aiLastAttack + 10 <= 2099 && ((CButton*)GetDlgItem(this->aiLastAttack + 10))->IsWindowEnabled() == TRUE) {
					WOS_Dlg::RecordLastAttack(this->aiLastAttack + 10); fire = true;
				} break;
				case 4:
					this->aiLastAttack = NULL;
					break;
				}
				if(fire){break;}
			}
		}else{
			int aiUId = (rand() % 100) + 2000;
			if (((CButton*)GetDlgItem(aiUId))->IsWindowEnabled() == TRUE) {
				WOS_Dlg::RecordLastAttack(aiUId);
				fire = true;
			}
		}
	}
}


bool WOS_Dlg::CheckGameOver()
{
	bool gameOver;
	//我方
	if (this->MyWarShips[0].GetKill()&& 
		this->MyWarShips[1].GetKill()&&
		this->MyWarShips[2].GetKill()&&
		this->MyWarShips[3].GetKill()&&
		this->MyWarShips[4].GetKill())
	{	
		/*公告*/
		return true;
	}
	//敵人
	if (this->EnemyWarShips[0].GetKill() &&
		this->EnemyWarShips[1].GetKill() &&
		this->EnemyWarShips[2].GetKill() &&
		this->EnemyWarShips[3].GetKill() &&
		this->EnemyWarShips[4].GetKill())
	{
		/*公告*/
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////
///                     Public    Function
///////////////////////////////////////////////////////////////////////////

//視窗產生後第一次介面設置
BOOL WOS_Dlg::OnInitDialog()
{
	int warShipsSet[5] = { 5,4,3,3,2 };
	//讀取目錄並顯示
	this->m_Menu.LoadMenu(IDR_MENU);
	SetMenu(&this->m_Menu);

	//設定雙方船艦class初值
	for (int n = 0; n < 5; n++){
		this->MyWarShips.push_back(*new WarShips(2100+n, warShipsSet[n]));
		this->EnemyWarShips.push_back(*new WarShips(1100+n, warShipsSet[n]));
	}
	for (int n = 0; n < 100; n++){
		this->MyBlock.push_back(*new Buttons_Data(2000+n));
		this->EnemyBlock.push_back(*new Buttons_Data(1000+n));
	}
	return TRUE; //回傳TRUE
}

//重寫 鍵盤按鍵的反應
BOOL WOS_Dlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam ==114 || pMsg->wParam == 82 ){ //按下R/r鍵
			this->direction ? GetDlgItem(IDC_Direction)->SetWindowText(L"朝向(&R): 垂直") : GetDlgItem(IDC_Direction)->SetWindowText(L"朝向(&R): 水平");
			this->direction = this->direction ? false  : true;
			return TRUE;
		}
		if (pMsg->wParam == 116 || pMsg->wParam == 84) { //按下T/t鍵
			if (choose != NULL)
			{
				((CButton*)GetDlgItem(this->choose))->EnableWindow(TRUE);
				this->choose = NULL;
				return TRUE;
	}	}	}
	return CDialog::PreTranslateMessage(pMsg);
}

//操作介面信息響應 WOS_Dlg
BEGIN_MESSAGE_MAP(WOS_Dlg, CDialog)

	//當敵方陣營海域方塊被按下
	ON_COMMAND_RANGE(IDC_ENEMY_A1, IDC_ENEMY_J10, ENEMY_ButtonClicked)
	//當我方陣營海域方塊被按下
	ON_COMMAND_RANGE(IDC_MY_A1, IDC_MY_J10, MY_ButtonClicked)
	//當我方艦船方塊被選擇
	ON_COMMAND_RANGE(IDC_MY_CV, IDC_MY_PB, MY_WarShipClicked)
	//當遊戲開始被按下
	ON_COMMAND( IDC_GAME_START, Game_Start)
	//右上角(X)關閉窗口
	ON_COMMAND(WM_DESTROY, Exit_Window)

END_MESSAGE_MAP()

//當敵方陣營海域方塊被按下 function
afx_msg void WOS_Dlg::ENEMY_ButtonClicked(UINT uId)
{
	((CButton*)GetDlgItem(uId))->EnableWindow(FALSE);
	WOS_Dlg::Fire(uId, this->EnemyWarShips, this->EnemyBlock , IDC_MY_shoot, IDC_ENEMY_kill);
	WOS_Dlg::EnemyAttack();
	//CWnd* GetDlgItem(int nID) const;
}

//當我方陣營海域方塊被按下 function
afx_msg void WOS_Dlg::MY_ButtonClicked(UINT uId)
{
	if (!this->gameStart){
		if (this->choose == NULL) { //如果"沒有"選擇船艦
			if (this->MyBlock[uId % 1000].GiveShipID() == NULL) {//如果該位置"沒有"船艦
				return;//沒有反應
			}
			else {//如果該位置"有"船艦
				ChooseAndTakeback(uId,this->MyWarShips, this->MyBlock);
				return;
		}	}
		else{ //如果"有"選擇船艦
			if (this->MyBlock[uId % 1000].GiveShipID() == NULL) {//如果該位置"沒有"船艦
				SetChooseInCoordinate(uId); //放置船隻
			}
			else {//如果該位置"有"船艦
				/*output該位置有船了*/
				return;
}	}	}	}

//當我方艦船方塊被選擇
afx_msg void WOS_Dlg::MY_WarShipClicked(UINT   uId)
{
	if (!this->gameStart) { //選擇放置之艦船
		WOS_Dlg::ReplaceChoose(uId); //呼叫替換選擇function
		GetDlgItem(2000)->SetFocus(); //
}	}

//遊戲開始 function
afx_msg void WOS_Dlg::Game_Start()
{
	for (int n = 0; n<5; n++) {
		if (!this->MyWarShips[n].GetPlace()) {
			AfxMessageBox(L"艦船未佈署完畢");
			return;
	}	}

	((CButton*)GetDlgItem(IDC_GAME_START))->EnableWindow(FALSE);
	this->gameStart = true;
	WOS_Dlg::PlaceEnemyShips();

	for(int nID=1000; nID<1100; nID++){
		((CButton*)GetDlgItem(nID))->EnableWindow(TRUE);
}	}

//右上角(X)關閉窗口
afx_msg void WOS_Dlg::Exit_Window()
{
	if (this->gameStart){
		if (MessageBox(L"確定要退出遊戲嗎",L"War Of Ships", MB_OKCANCEL)==1){
			DestroyWindow();
	}	}
	else {
		DestroyWindow();
}	}