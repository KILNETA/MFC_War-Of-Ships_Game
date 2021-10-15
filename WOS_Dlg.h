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
private: //�p��

	//�ؿ��C��ŧi
	CMenu m_Menu;//�ؿ�
	bool gameStart=false;//�C���}�l
	vector<WarShips> MyWarShips;//��ĥ
	vector<WarShips> EnemyWarShips;//��ĥ
	vector<Buttons_Data> MyBlock;//�ڤ����
	vector<Buttons_Data> EnemyBlock; //�Ĥ����
	int choose=NULL;//��e���
	bool direction = true;

	//�ഫ���
	void ReplaceChoose(UINT uId);
	//��U��
	void PlaceShip(UINT uId, int direction, int _choose, vector<WarShips>& warShips, vector<Buttons_Data>& block);
	//��ܻP����
	void ChooseAndTakeback(UINT uId, vector<WarShips>& warShips, vector<Buttons_Data>& block);
	//����b�Ӧ�m
	void SetChooseInCoordinate(UINT uId);
	//�G�p�Ĥ�ĥ��
	void PlaceEnemyShips();

	//�}��
	int Fire(UINT uId, vector<WarShips>& warShips, vector<Buttons_Data>& block, int shootStatic, int killStatic);
	//������ĥ
	void HitShip(UINT uId, int shipID, vector<WarShips>& warShips);
	//�ˬd��I�S
	bool CheckShipDied(int shipID, vector<WarShips>& warShips , int killStatic);

	//(AI�}��)�����W������ + ����
	bool RecordLastAttack(int aiUId, int& aiLastAttack, bool& nextFire, int& aiDirection, int mode);
	//(AI�}���Ĥ�}��
	void EnemyAttack();

	//�ˬd�C���O�_����
	bool CheckGameOver();

	//���m�C��
	void reloadGame();
	
public://����

	//�ާ@�����H���T��
	DECLARE_MESSAGE_MAP()

	//���g �������ͫ�Ĥ@�������]�m
	virtual BOOL OnInitDialog();
	//���g ��L���䪺����
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//��Ĥ�}��������Q���U function
	afx_msg void ENEMY_ButtonClicked(UINT   uId);
	//��ڤ�}��������Q���U function
	afx_msg void MY_ButtonClicked(UINT   uId);
	//��ڤ�ĥ�����Q���
	afx_msg void MY_WarShipClicked(UINT   uId);
	//�C���}�l function
	afx_msg void Game_Start();
	//�C���}�l function
	afx_msg void Exit_Window();

	//���󤶭��I�s
	afx_msg void ABOUT();
};