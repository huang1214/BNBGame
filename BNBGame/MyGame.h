#pragma once
#include "T_Engine.h"
#include "T_Sprite.h"
#include "T_AI.h"
#include "T_Scene.h"

typedef  vector<T_Sprite*> vSpriteSet;

class MyGame :
	public T_Engine
{
private:
	int wnd_width;
	int wnd_height;	// ���ڿ��

	// ���¶����ĸ�����Ķ���֡
	static int FRAME_LEFT[20];
	static int FRAME_RIGHT[20];
	static int FRAME_UP[20];
	static int FRAME_DOWN[20];
	// ���ڳ�����
	T_Scene t_scene;	// ��Ϸ����
	int scn_width, scn_height;	// ��Ϸ���ڿ��
	
	static const int NPC_NUM = 10;	// NPC����
	
	// ����Ҫʹ�õ������
	T_Sprite* player;	// ���
	vSpriteSet npc_set;	// NPC��ɫ����
	

	// һЩ���ܺ���
	// ������Ϸ��ͼ����
	void LoadMap();
	// ���ݴ������Ϸ״̬���ز˵�
	void LoadGameMenu(int status);
	// ��ʼ�����
	void LoadPlayer();
	// ��ʼ��һЩ����
	void LoadGame();
	// ����NPC
	void LoadNPC(int);
	// ������ҵ�λ�ã�����Ҫ�����л�����
	void updatePlayerPos(int dir);
	// ����NPC��λ��
	void updateNpcPos();
	// ���¶���֡���к�
	void updateFrame();
	// �����ķ�ת����
	void getPlayerTrans();
	// ���¶���
	void UpdateAnimation();
	
public:
	MyGame(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle, WORD Icon = NULL, WORD SmIcon = NULL, int iWidth = 800,
		int iHeight = 600);
	~MyGame();

	void GameInit() override;
	void GameLogic() override;
	void GameEnd() override;
	void GamePaint(HDC hdc) override;
	void GameKeyAction(int ActionType = KEY_SYS_NONE) override;
	void GameMouseAction(int x, int y, int ActionType) override;
};

