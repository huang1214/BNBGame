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
	int wnd_height;	// 窗口宽高

	// 重新定义四个方向的动画帧
	static int FRAME_LEFT[20];
	static int FRAME_RIGHT[20];
	static int FRAME_UP[20];
	static int FRAME_DOWN[20];
	// 关于场景类
	T_Scene t_scene;	// 游戏场景
	int scn_width, scn_height;	// 游戏窗口宽高
	
	static const int NPC_NUM = 10;	// NPC总数
	
	// 定义要使用的类对象
	T_Sprite* player;	// 玩家
	vSpriteSet npc_set;	// NPC角色集合
	

	// 一些功能函数
	// 加载游戏地图场景
	void LoadMap();
	// 根据传入的游戏状态加载菜单
	void LoadGameMenu(int status);
	// 初始化玩家
	void LoadPlayer();
	// 初始化一些数据
	void LoadGame();
	// 加载NPC
	void LoadNPC(int);
	// 处理玩家的位置，并且要负责切换场景
	void updatePlayerPos(int dir);
	// 更新NPC的位置
	void updateNpcPos();
	// 更新动画帧序列号
	void updateFrame();
	// 获得鱼的反转方向
	void getPlayerTrans();
	// 更新动画
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

