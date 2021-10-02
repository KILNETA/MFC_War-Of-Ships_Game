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
		((CButton*)GetDlgItem(Coordinate))->SetWindowText(L"");
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
			this->direction ? GetDlgItem(IDC_Direction)->SetWindowText(_T("�¦V(&R): ����")) : GetDlgItem(IDC_Direction)->SetWindowText(_T("�¦V(&R): ����"));
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
	((CButton*)GetDlgItem(uId))->SetWindowText(L"��");
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
			AfxMessageBox(_T("ĥ��G�p����"));
			return;
	}	}

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