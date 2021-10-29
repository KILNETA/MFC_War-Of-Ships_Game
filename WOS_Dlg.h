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

private: //�p��

	//�ؿ��C��ŧi
	CMenu m_Menu;//�ؿ�
	bool gameStart = false;//�C���}�l
	vector<WarShips> MyWarShips;//��ĥ
	vector<WarShips> EnemyWarShips;//��ĥ
	vector<Buttons_Data> MyBlock;//�ڤ����
	vector<Buttons_Data> EnemyBlock; //�Ĥ����
	int choose = NULL;//��e���
	bool direction = true;//��V
	//�O���O
	int winner = 0 ;
	vector<int> fires_Number = { 0,0 };
	vector<int> hit_Number = { 0,0 };


	//ĵ�i�����I�s
	void WarningWindow(CString test);

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
	int CheckGameOver();

	//���m�C��
	void ReloadGame();

	//�����D����
	void Destroy_Window();
	
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
	//�k�W��(X)�������f
	afx_msg void Exit_Window();
	//���ӧ��C��
	afx_msg void AbandonGame();


	//���󤶭��I�s
	afx_msg void ABOUT();
	//���������I�s
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
public://����
	WOS_GameEndDlg(int winner, vector<int> &fires_Number, vector<int> &hit_Number,
		vector<WarShips>&MyWarShips, vector<WarShips>& EnemyWarShips,
		CWnd* pParentWnd = NULL);
	~WOS_GameEndDlg();

private: //�p��
	//�O���O
	int winner = 0;
	vector<int> fires_Number ;
	vector<int> hit_Number ;
	vector<WarShips> MyWarShips;//��ĥ
	vector<WarShips> EnemyWarShips;//��ĥ

	void Scoreboard_Display();
public://����

	//�ާ@�����H���T��
	DECLARE_MESSAGE_MAP()

	//���g �������ͫ�Ĥ@�������]�m
	virtual BOOL OnInitDialog();

	//�k�W��(X)�������f
	afx_msg void Exit_Window();
	//���}�{��
	afx_msg void Exit_Application();
	//���}�@��
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
public://����
	WOS_WarningDlg(CString text,CWnd* pParentWnd = NULL);
	~WOS_WarningDlg();

private: //�p��
	CString text;
	//���ܤ��e��r
	void ChangeText(CString text);
	//��������
	afx_msg void Exit_Window();

public://����
	//�ާ@�����H���T��
	DECLARE_MESSAGE_MAP()
	//���g �������ͫ�Ĥ@�������]�m
	virtual BOOL OnInitDialog();
	//���g ����P��
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};