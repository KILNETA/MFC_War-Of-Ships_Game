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
		//((CButton*)GetDlgItem(uId))->SetWindowText(_T("Ｘ")); //設置擊中標示
		//output //公告擊中+船的名子+座標
		GetDlgItem(shootStatic)->SetWindowText(L"擊中" + warShips[block[uId % 100].GiveShipID() % 10].GetShipName() +
																						 L"  "+ block[uId % 100].GetButtonsName());
		//檢查船隻沉沒
		if (WOS_Dlg::CheckShipDied(block[uId % 100].GiveShipID(), warShips, killStatic)){
			return 1; //回報擊中+已擊沉
		}else{
			return 2; //回報擊中+未擊沉
	}	}
	else {//該處沒有船
		//((CButton*)GetDlgItem(uId))->SetWindowText(_T("。"));//設置落彈標示

		//公告未擊中+座標
		GetDlgItem(shootStatic)->SetWindowText(L"未擊中船隻  " + block[uId % 100].GetButtonsName());
		return 0; //未擊中
}	}

//擊中敵艦
void WOS_Dlg::HitShip(UINT uId, int shipID, vector<WarShips>& warShips)
{
	//將該船的座標紀錄刪除
	for(int n = 0; n < warShips[shipID % 10].GetCoordinate_Size(); n++)
	{
		if (warShips[shipID % 10].GetCoordinate(n)== uId){
			warShips[shipID % 10].setCoordinate(n,NULL);
}	}	}

//檢查船隻沉沒
bool WOS_Dlg::CheckShipDied(int shipID, vector<WarShips>& warShips, int killStatic)
{
	//檢查該船是否有座標未被擊中 //檢測到就直接回報未被擊沉
	for (int n = 0; n < warShips[shipID % 10].GetCoordinate_Size(); n++){
		if (warShips[shipID % 10].GetCoordinate(n) != NULL) {//未被擊沉
			GetDlgItem(killStatic)->SetWindowText(L"");
			return false; //回報未被擊沉
	}	}
	//設置該船已沉沒
	warShips[shipID % 10].setKill(true);
	//output 船隻按鈕反黑 投放公告
	((CButton*)GetDlgItem(shipID))->EnableWindow(FALSE); 
	GetDlgItem(killStatic)->SetWindowText(warShips[shipID % 10].GetShipName()+ L"已被完全擊沉");
	return true; //回報已擊沉
}


//(AI開火)紀錄上次攻擊 + 攻擊
bool WOS_Dlg::RecordLastAttack(int aiUId, int &aiLastAttack, bool& nextFire , int &aiDirection, int mode)
{
	((CButton*)GetDlgItem(aiUId))->EnableWindow(FALSE);
	switch (WOS_Dlg::Fire(aiUId, this->MyWarShips, this->MyBlock, IDC_ENEMY_shoot, IDC_MY_kill)) {
	case 0: //未擊中
		return false;
	case 1:  //回報擊中+已擊沉
		aiLastAttack = NULL;
		aiDirection = 0;
		nextFire = false; 
		return true;
	case 2: //回報擊中+未擊沉
		if (!mode) {
			aiLastAttack = aiUId; 
			nextFire = true; 
			return true;
		}
	}
}

//(AI開火)敵方攻擊
void WOS_Dlg::EnemyAttack(){

	static bool nextFire = false;  //是否為第二次發射
	static int aiDirection = 0; //ai在第二發命中之後所判斷該船隻的方向
	static int aiLastAttack = NULL;
	bool fire = false; //是否開火了 脫離無限嘗試迴圈
	srand(time(NULL)); //採集即刻時間作為隨機數依據

	while (!fire){
		if (aiLastAttack == NULL) { //盲猜落點//第一次射擊
			int aiUId = (rand() % 100) + 2000; //設定隨機變數
			if (((CButton*)GetDlgItem(aiUId))->IsWindowEnabled() == TRUE) {
				WOS_Dlg::RecordLastAttack(aiUId, aiLastAttack, nextFire, aiDirection, 0);
				fire = true;
		}	}
		else { //已知第一次的落點 
			//先設定個嘗試方向的計算結果 與各方向之最大.小邊界
			int newAttack[4] = { -1 , 1 , -10 , 10 };
			int boundary[4] = { (aiLastAttack / 10) * 10 ,((aiLastAttack / 10) * 10) + 9 ,2000 ,2099 };

			if(aiDirection==0){ //基於第一次落點 進行船隻定位 //如果尚未確定方向則執行
				for (int n = 0; n < 4; n++) { //對周邊四個方向嘗試射擊 //第二次射擊
					//確認座標無溢出 且 該按鈕未被射擊過
					if (n < 2 && aiLastAttack+newAttack[n] >= boundary[0] && aiLastAttack + newAttack[n] <= boundary[1] 
						&& ((CButton*)GetDlgItem(aiLastAttack + newAttack[n]))->IsWindowEnabled() == TRUE
						|| n >= 2 && aiLastAttack + newAttack[n] >= boundary[2] && aiLastAttack + newAttack[n] <= boundary[3] 
						&& ((CButton*)GetDlgItem(aiLastAttack + newAttack[n]))->IsWindowEnabled() == TRUE) {

						if (WOS_Dlg::RecordLastAttack(aiLastAttack+newAttack[n],aiLastAttack, nextFire, aiDirection, 0)) {//(AI開火)紀錄上次攻擊 + 攻擊
							aiDirection = n+1; //紀錄方向
						}
						fire = true; //已成功發射
						return;
			}	}	}
			else { //已定位成功
				if (aiDirection - 1 < 2 && aiLastAttack + newAttack[aiDirection-1] >= boundary[0] && aiLastAttack + newAttack[aiDirection - 1] <= boundary[1]
					&& ((CButton*)GetDlgItem(aiLastAttack + newAttack[aiDirection - 1]))->IsWindowEnabled() == TRUE
					|| aiDirection - 1 >= 2 && aiLastAttack + newAttack[aiDirection - 1] >= boundary[2] && aiLastAttack + newAttack[aiDirection - 1] <= boundary[3]
					&& ((CButton*)GetDlgItem(aiLastAttack + newAttack[aiDirection - 1]))->IsWindowEnabled() == TRUE) {

					WOS_Dlg::RecordLastAttack(aiLastAttack+newAttack[aiDirection-1], aiLastAttack,nextFire, aiDirection, 0); //(AI開火)紀錄上次攻擊 + 攻擊
					fire = true; //已成功發射
					return;
			}	}
			for (int m = 1; m <=5; m++) {
				if (aiDirection != 0) {
					if (aiDirection==1 || aiDirection == 2){
						if (m <= 4 && ((CButton*)GetDlgItem(aiLastAttack + (newAttack[2 - aiDirection] * m)))->IsWindowEnabled() == TRUE) {
							WOS_Dlg::RecordLastAttack(aiLastAttack+newAttack[2-aiDirection] * m, aiLastAttack, nextFire, aiDirection, 1); fire = true;
							return;
						}
					}else {
						if (aiDirection == 3 || aiDirection == 4) {
							if (m <= 4 && ((CButton*)GetDlgItem(aiLastAttack + (newAttack[6 - aiDirection] * m)))->IsWindowEnabled() == TRUE) {
								WOS_Dlg::RecordLastAttack(aiLastAttack+(newAttack[6 -aiDirection ] * m), aiLastAttack, nextFire, aiDirection, 1); fire = true;
								return;
				}	}	}	}
				if (m == 5) {
					aiLastAttack = NULL;
					aiDirection = 0;
					return;
			}	}
			if (fire) { return; }
	}	}	}

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
		AfxMessageBox(_T("你輸了"));
		this->gameStart = false;
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
		AfxMessageBox(_T("你贏了"));
		this->gameStart = false;
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

	CheckGameOver();
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

	for (int nID = 2100; nID <= 2104; nID++) {
		((CButton*)GetDlgItem(nID))->EnableWindow(TRUE);
	}
	for(int nID = 1000; nID <= 1099; nID++){
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