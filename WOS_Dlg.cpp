#include "WOS_Dlg.h"

#include <stdlib.h> /* �üƬ������ */
#include <time.h>   /* �ɶ�������� */

///////////////////////////////////////////////////////////////////////////
///                     private    Function
///////////////////////////////////////////////////////////////////////////

//�ഫ��� down
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

//��U�� down
void WOS_Dlg::PlaceShip(UINT uId, int direction, int _choose, vector<WarShips>& warShips, vector<Buttons_Data>& block) {
	if ((uId % (10 * direction)) + (warShips[_choose % 10].GetCoordinate_Size() * direction) < (10*direction)+(1* direction)) {
		//���W�X��l
		for (int n = 0; n < warShips[_choose % 10].GetCoordinate_Size(); n++)
		{//�ˬd�������L�����
			if (block[(uId % 1000) + (n * direction)].GiveShipID() != NULL) {
				if (!this->gameStart){
					AfxMessageBox(_T("����F"));
				}
				return;
		}	}
		//��Ӳ�ү�����l�g�J�Ѽ� /�ñN��ĥ�����Ӯ檺��Ƽg�J��Ƥ�
		for (int n = 0; n < warShips[_choose % 10].GetCoordinate_Size(); n++){
			block[(uId%1000) + (n * direction)].SetShipID(_choose);
			((CButton*)GetDlgItem(uId + (n * direction)))->SetWindowText(warShips[_choose % 10].GetShipName());

			warShips[_choose % 10].setCoordinate(n, uId + (n * direction));
		}
		warShips[_choose % 10].setPlace(true);
		if (!this->gameStart) {
			this->choose = NULL; //���e��ܲM��
		}
	}else {//�W�X��l
		if (!this->gameStart) {
			AfxMessageBox(_T("��m����"));
}	}	}

//��ܻP����
void WOS_Dlg::ChooseAndTakeback(UINT uId , vector<WarShips>& warShips, vector<Buttons_Data>& block)
{
	//�Ӯ�Ҧb��ĥ��ID
	int shipID = block[uId % 1000].GiveShipID();
	//�I�s�������function  //���s��ܲ�ĥ
	if (!this->gameStart) {
		WOS_Dlg::ReplaceChoose(shipID);
	}

	//��Ӳ�ү�����l�٭�Ѽ� /�ñN��ĥ�����Ӯ檺��ƥh��
	for (int n = 0; n < warShips[shipID % 10].GetCoordinate_Size(); n++){
		int Coordinate = warShips[shipID % 10].GetCoordinate(n);
		((CButton*)GetDlgItem(Coordinate))->SetWindowText(_T(""));
		block[Coordinate%1000].SetShipID(0);

		warShips[shipID % 10].setCoordinate(n, NULL);
		warShips[shipID % 10].setPlace(false);
	}
	return;
}

//����b�Ӧ�m down
void WOS_Dlg::SetChooseInCoordinate(UINT uId)
{
	if (this->direction) {//����
		WOS_Dlg::PlaceShip(uId, 1,this->choose, this->MyWarShips, this->MyBlock);
	}else {//����
		WOS_Dlg::PlaceShip(uId, 10, this->choose, this->MyWarShips, this->MyBlock);
	}
	return;
}

//�G�p�Ĥ�ĥ��
void WOS_Dlg::PlaceEnemyShips()
{
	//�üƳ]�m
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



//�}��
int WOS_Dlg::Fire(UINT uId, vector<WarShips>& warShips, vector<Buttons_Data>& block, int shootStatic, int killStatic)
{
	if (block[uId % 100].GiveShipID() != NULL){//�ӳB����
		WOS_Dlg::HitShip(uId, block[uId % 100].GiveShipID(), warShips); //������
		((CButton*)GetDlgItem(uId))->SetWindowText(_T("��"));
		//output //���i����+��W�l
		GetDlgItem(shootStatic)->SetWindowText(L"����" + warShips[block[uId % 100].GiveShipID() % 10].GetShipName() +
																						 L"  "+ block[uId % 100].GetButtonsName());
		//�ˬd��I�S
		if (WOS_Dlg::CheckShipDied(block[uId % 100].GiveShipID(), warShips, killStatic)){
			return 1;
		}else{
			return 2;
	}	}
	else {//�ӳB�S����
		((CButton*)GetDlgItem(uId))->SetWindowText(_T("�C"));

		GetDlgItem(shootStatic)->SetWindowText(L"�������  " + block[uId % 100].GetButtonsName());
		return 0;
	}
}

//������ĥ
void WOS_Dlg::HitShip(UINT uId, int shipID, vector<WarShips>& warShips)
{
	for(int n = 0; n < warShips[shipID % 10].GetCoordinate_Size(); n++)
	{
		if (warShips[shipID % 10].GetCoordinate(n)== uId){
			warShips[shipID % 10].setCoordinate(n,NULL);
		}else{}
	}
}

//�ˬd��I�S
bool WOS_Dlg::CheckShipDied(int shipID, vector<WarShips>& warShips, int killStatic)
{
	for (int n = 0; n < warShips[shipID % 10].GetCoordinate_Size(); n++){
		if (warShips[shipID % 10].GetCoordinate(n) != NULL) {//���Q���I
			GetDlgItem(killStatic)->SetWindowText(L"");
			return false;
	}	}
	warShips[shipID % 10].setKill(true);
	//output ����s�϶� ��񤽧i
	((CButton*)GetDlgItem(shipID))->EnableWindow(FALSE); 
	GetDlgItem(killStatic)->SetWindowText(warShips[shipID % 10].GetShipName()+ L"�w�Q�������I");
	return true;
}

//(AI�}��)�����W������ + ����
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

//(AI�}��)�Ĥ����
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
	//�ڤ�
	if (this->MyWarShips[0].GetKill()&& 
		this->MyWarShips[1].GetKill()&&
		this->MyWarShips[2].GetKill()&&
		this->MyWarShips[3].GetKill()&&
		this->MyWarShips[4].GetKill())
	{	
		/*���i*/
		return true;
	}
	//�ĤH
	if (this->EnemyWarShips[0].GetKill() &&
		this->EnemyWarShips[1].GetKill() &&
		this->EnemyWarShips[2].GetKill() &&
		this->EnemyWarShips[3].GetKill() &&
		this->EnemyWarShips[4].GetKill())
	{
		/*���i*/
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////
///                     Public    Function
///////////////////////////////////////////////////////////////////////////

//�������ͫ�Ĥ@�������]�m
BOOL WOS_Dlg::OnInitDialog()
{
	int warShipsSet[5] = { 5,4,3,3,2 };
	//Ū���ؿ������
	this->m_Menu.LoadMenu(IDR_MENU);
	SetMenu(&this->m_Menu);

	//�]�w�����ĥclass���
	for (int n = 0; n < 5; n++){
		this->MyWarShips.push_back(*new WarShips(2100+n, warShipsSet[n]));
		this->EnemyWarShips.push_back(*new WarShips(1100+n, warShipsSet[n]));
	}
	for (int n = 0; n < 100; n++){
		this->MyBlock.push_back(*new Buttons_Data(2000+n));
		this->EnemyBlock.push_back(*new Buttons_Data(1000+n));
	}
	return TRUE; //�^��TRUE
}

//���g ��L���䪺����
BOOL WOS_Dlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam ==114 || pMsg->wParam == 82 ){ //���UR/r��
			this->direction ? GetDlgItem(IDC_Direction)->SetWindowText(L"�¦V(&R): ����") : GetDlgItem(IDC_Direction)->SetWindowText(L"�¦V(&R): ����");
			this->direction = this->direction ? false  : true;
			return TRUE;
		}
		if (pMsg->wParam == 116 || pMsg->wParam == 84) { //���UT/t��
			if (choose != NULL)
			{
				((CButton*)GetDlgItem(this->choose))->EnableWindow(TRUE);
				this->choose = NULL;
				return TRUE;
	}	}	}
	return CDialog::PreTranslateMessage(pMsg);
}

//�ާ@�����H���T�� WOS_Dlg
BEGIN_MESSAGE_MAP(WOS_Dlg, CDialog)

	//��Ĥ�}��������Q���U
	ON_COMMAND_RANGE(IDC_ENEMY_A1, IDC_ENEMY_J10, ENEMY_ButtonClicked)
	//��ڤ�}��������Q���U
	ON_COMMAND_RANGE(IDC_MY_A1, IDC_MY_J10, MY_ButtonClicked)
	//��ڤ�ĥ�����Q���
	ON_COMMAND_RANGE(IDC_MY_CV, IDC_MY_PB, MY_WarShipClicked)
	//��C���}�l�Q���U
	ON_COMMAND( IDC_GAME_START, Game_Start)
	//�k�W��(X)�������f
	ON_COMMAND(WM_DESTROY, Exit_Window)

END_MESSAGE_MAP()

//��Ĥ�}��������Q���U function
afx_msg void WOS_Dlg::ENEMY_ButtonClicked(UINT uId)
{
	((CButton*)GetDlgItem(uId))->EnableWindow(FALSE);
	WOS_Dlg::Fire(uId, this->EnemyWarShips, this->EnemyBlock , IDC_MY_shoot, IDC_ENEMY_kill);
	WOS_Dlg::EnemyAttack();
	//CWnd* GetDlgItem(int nID) const;
}

//��ڤ�}��������Q���U function
afx_msg void WOS_Dlg::MY_ButtonClicked(UINT uId)
{
	if (!this->gameStart){
		if (this->choose == NULL) { //�p�G"�S��"��ܲ�ĥ
			if (this->MyBlock[uId % 1000].GiveShipID() == NULL) {//�p�G�Ӧ�m"�S��"��ĥ
				return;//�S������
			}
			else {//�p�G�Ӧ�m"��"��ĥ
				ChooseAndTakeback(uId,this->MyWarShips, this->MyBlock);
				return;
		}	}
		else{ //�p�G"��"��ܲ�ĥ
			if (this->MyBlock[uId % 1000].GiveShipID() == NULL) {//�p�G�Ӧ�m"�S��"��ĥ
				SetChooseInCoordinate(uId); //��m�
			}
			else {//�p�G�Ӧ�m"��"��ĥ
				/*output�Ӧ�m����F*/
				return;
}	}	}	}

//��ڤ�ĥ�����Q���
afx_msg void WOS_Dlg::MY_WarShipClicked(UINT   uId)
{
	if (!this->gameStart) { //��ܩ�m��ĥ��
		WOS_Dlg::ReplaceChoose(uId); //�I�s�������function
		GetDlgItem(2000)->SetFocus(); //
}	}

//�C���}�l function
afx_msg void WOS_Dlg::Game_Start()
{
	for (int n = 0; n<5; n++) {
		if (!this->MyWarShips[n].GetPlace()) {
			AfxMessageBox(L"ĥ��G�p����");
			return;
	}	}

	((CButton*)GetDlgItem(IDC_GAME_START))->EnableWindow(FALSE);
	this->gameStart = true;
	WOS_Dlg::PlaceEnemyShips();

	for(int nID=1000; nID<1100; nID++){
		((CButton*)GetDlgItem(nID))->EnableWindow(TRUE);
}	}

//�k�W��(X)�������f
afx_msg void WOS_Dlg::Exit_Window()
{
	if (this->gameStart){
		if (MessageBox(L"�T�w�n�h�X�C����",L"War Of Ships", MB_OKCANCEL)==1){
			DestroyWindow();
	}	}
	else {
		DestroyWindow();
}	}