#include "MyGame.h"

// 重新定义动画帧
int MyGame::FRAME_LEFT[20] = { 0,0,1,1,1,1,2,2,2,2,0,0,1,1,1,1,2,2,2,2 };
int MyGame::FRAME_RIGHT[20] = { 3,3,4,4,4,4,5,5,5,5,3,3,4,4,4,4,5,5,5,5 };
int MyGame::FRAME_UP[20] = { 6,6,7,7,7,7,8,8,8,8,6,6,7,7,7,7,8,8,8,8 };
int MyGame::FRAME_DOWN[20] = { 9,9,10,10,10,10,11,11,11,11,9,9,10,10,10,10,11,11,11,11 };


void MyGame::LoadMap()
{
	t_scene.LoadTxtMap(".\\map\\newMap.txt");
	scn_width = t_scene.getSceneLayers()->back().layer->GetWidth();
	scn_height = t_scene.getSceneLayers()->back().layer->GetHeight();
	// 视图初始位置以地图作为参照
	int scn_x = (wnd_width - scn_width) / 2;
	int scn_y = (wnd_height - scn_height) / 2;
	// 地图初始化定位到中间
	t_scene.InitScene(scn_x, scn_y, scn_width, scn_height, wnd_width, wnd_height);
	// 将所有地图图层定位到屏幕中央
	SCENE_LAYERS::iterator p;
	for(p = t_scene.getSceneLayers()->begin();p!=t_scene.getSceneLayers()->end();p++)
	{
		if (p->layer->ClassName() == "T_Map")
		{
			p->layer->SetPosition(scn_x, scn_y);
		}
	}
}

/**
 * 说明素材使用的还是方格人，因为它的长宽对应刚好
 */
void MyGame::LoadPlayer()
{
	GAMELAYER gameLayer;
	SPRITEINFO spInfo;
	// 加载玩家角色
	player = new T_Sprite(L".\\res\\blockorange.png", 80, 80);
	spInfo.Active = false;
	spInfo.Dead = false;
	spInfo.Dir = DIR_UP;
	spInfo.Rotation = TRANS_NONE;
	spInfo.Ratio = 0.5f;
	spInfo.Level = 0;
	spInfo.Score = 0;
	spInfo.Speed = 10;
	spInfo.Alpha = 255;
	
	spInfo.X = t_scene.getSceneX();
	spInfo.Y = t_scene.getSceneY();

	spInfo.Visible = true;
	player->Initiate(spInfo);
	player->SetSequence(FRAME_UP, 20);
	player->SetLayerTypeID(LAYER_PLY);
	gameLayer.layer = player;
	gameLayer.type_id = LAYER_PLY;
	// 这里就是按照加入t_scene的顺序确定的z_order
	gameLayer.z_order = t_scene.getSceneLayers()->size() + 1;
	gameLayer.layer->setZorder(gameLayer.z_order);
	t_scene.Append(gameLayer);
}

void MyGame::updatePlayerPos(int dir)
{
	if (player == NULL)
	{
		return;
	}
	int nextStepX, nextStepY;
	int SpeedX = 0, SpeedY = 0;
	if (player->IsActive() && player->IsVisible())
	{
		switch (dir)
		{
		case DIR_LEFT:
			SpeedX = -player->GetSpeed();
			SpeedY = 0;
			// 计算下一步是否越过边界
			nextStepX = player->GetX() - player->GetSpeed();
			if (nextStepX <= 0)
			{
				SpeedX = 0 - player->GetX();	
			}
			break;
		case DIR_RIGHT:
			SpeedX = player->GetSpeed();
			SpeedY = 0;
			// 计算下一步移动是否超过边界
			nextStepX = player->GetX() + player->GetRatioSize().cx + player->GetSpeed();
			if (nextStepX >= wnd_width)
			{
				SpeedX = wnd_width - player->GetRatioSize().cx - player->GetX();
			}
			break;
		case DIR_UP:
			SpeedY = -player->GetSpeed();
			SpeedX = 0;
			// 计算下一步移动是否超过边界
			nextStepY = player->GetY() - player->GetSpeed();
			if (nextStepY <= 0)
			{
				SpeedY = 0 - player->GetY();
			}
			break;
		case DIR_DOWN:
			SpeedX = 0;
			SpeedY = player->GetSpeed();
			nextStepY = player->GetY() + player->GetRatioSize().cy + SpeedY;
			if (nextStepY >= wnd_height)
			{
				SpeedY = wnd_height - player->GetRatioSize().cy - player->GetY();
			}
			break;
		}
		int x = player->GetX();	// 获得移动前的坐标
		int y = player->GetY();
		// TODO 自己的游戏需要重载这个函数实现模糊碰撞，就是差一点像素不碰撞
		if (!player->CollideWith(t_scene.getBarrier()))
		{
			player->Move(SpeedX, SpeedY);
		}
		if (player->CollideWith(t_scene.getBarrier()))
		{
			player->SetPosition(x, y);	// 还原移动前的位置
		}
		t_scene.ScrollScene(player);
	}
}

void MyGame::updateNpcPos()
{
	if (npc_set.size() == 0)
	{
		return;
	}
	T_AI* spAi = new T_AI(4);
	// 遍历所有npc
	for (vSpriteSet::iterator i = npc_set.begin(); i != npc_set.end(); i++)
	{
		if ((*i)->IsActive() && (*i)->IsVisible())
		{
			spAi->Evade((*i), player);	// 躲避玩家角色
			spAi->CheckOverlay((*i), npc_set);	// 防止互相重叠
			int npc_dir = (*i)->GetDir();
			switch (npc_dir)
			{
			case DIR_LEFT:
				(*i)->SetSequence(FRAME_LEFT, 20);
				break;
			case DIR_RIGHT:
				(*i)->SetSequence(FRAME_RIGHT, 20);
				break;
			case DIR_UP:
				(*i)->SetSequence(FRAME_UP, 20);
				break;
			case DIR_DOWN:
				(*i)->SetSequence(FRAME_DOWN, 20);
				break;
			}
			spAi->Wander((*i), npc_dir, (*i)->GetSpeed(), t_scene.getBarrier());
		}
	}
	delete spAi;
}

void MyGame::LoadGameMenu(int status)
{
	
}
// 对场景、游戏角色的内容进行加载
void MyGame::LoadGame()
{
	
}

void MyGame::LoadNPC(int NPC_NUM)
{
	for (int i = 0; i<NPC_NUM; i++)
	{
		GAMELAYER gameLayer;
		SPRITEINFO spInfo;

		spInfo.Active = true;
		spInfo.Dead = false;
		spInfo.Rotation = TRANS_NONE;
		spInfo.Ratio = 0.5f;
		spInfo.Speed = 2;
		spInfo.Alpha = 230;
		spInfo.Visible = true;
		spInfo.Level = 0;
		spInfo.Score = 0;

		int sp_width = 40;
		int sp_height = 40;
		//抽取随机方向(NPC角色在地图的四角生成)
		int sdr = rand() % 4;
		int d = rand() % 2;
		switch (sdr)
		{
		case 0://左上角
			if (d == 0)  spInfo.Dir = DIR_RIGHT;
			if (d == 1)  spInfo.Dir = DIR_DOWN;
			spInfo.X = t_scene.getSceneX();
			spInfo.Y = t_scene.getSceneY();
			break;
		case 1://右上角
			if (d == 0)  spInfo.Dir = DIR_LEFT;
			if (d == 1)  spInfo.Dir = DIR_DOWN;
			spInfo.X = t_scene.getSceneX() + scn_width - sp_width;
			spInfo.Y = t_scene.getSceneY();
			break;
		case 2://左下角
			if (d == 0)  spInfo.Dir = DIR_RIGHT;
			if (d == 1)  spInfo.Dir = DIR_UP;
			spInfo.X = t_scene.getSceneX();
			spInfo.Y = t_scene.getSceneY() + scn_height - sp_height;
			break;
		case 3://右下角
			if (d == 0)  spInfo.Dir = DIR_LEFT;
			if (d == 1)  spInfo.Dir = DIR_UP;
			spInfo.X = t_scene.getSceneX() + scn_width - sp_width;
			spInfo.Y = t_scene.getSceneY() + scn_height - sp_height;
			break;
		}

		//在NPC列表中增加新的项目
		npc_set.push_back(new T_Sprite(L".\\res\\blockgreen.png", 80, 80));

		//初始化刚增加的项目
		T_Sprite *sp = npc_set.back();
		sp->Initiate(spInfo);
		switch (spInfo.Dir)
		{
		case DIR_LEFT:
			sp->SetSequence(FRAME_LEFT, 20);
			break;
		case DIR_RIGHT:
			sp->SetSequence(FRAME_RIGHT, 20);
			break;
		case DIR_UP:
			sp->SetSequence(FRAME_UP, 20);
			break;
		case DIR_DOWN:
			sp->SetSequence(FRAME_DOWN, 20);
			break;
		}
		sp->SetLayerTypeID(LAYER_NPC);

		gameLayer.layer = sp;
		gameLayer.type_id = LAYER_NPC;
		gameLayer.z_order = t_scene.getSceneLayers()->size() + 1;
		gameLayer.layer->setZorder(gameLayer.z_order);
		t_scene.Append(gameLayer);
		sp = NULL;
	}
}


void MyGame::updateFrame()
{
	
}

void MyGame::getPlayerTrans()
{
	
}

void MyGame::UpdateAnimation()
{
	vSpriteSet::iterator i;
	if (npc_set.size() > 0)
	{
		for (i = npc_set.begin();i != npc_set.end();i++)
		{
			(*i)->LoopFrame();
		}
	}
	if (player != NULL)
	{
		if (player->IsActive() && player->IsVisible())
		{
			player->LoopFrame();
		}
	}
}

MyGame::MyGame(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle, WORD Icon, WORD SmIcon, int iWidth,
	int iHeight) :T_Engine(hInstance, szWindowClass, szTitle, Icon, SmIcon, iWidth, iHeight)
{
	wnd_width = iWidth;
	wnd_height = iHeight;
}

void MyGame::GameInit()
{
	
	// 加载地图
	LoadMap();
	// 加载玩家以及NPC
	LoadPlayer();
	LoadNPC(NPC_NUM);
}

void MyGame::GameLogic()
{
	GameKeyAction();
	updateNpcPos();		// 移动NPC
	if (player->IsActive())
	{
		updatePlayerPos(player->GetDir());
	}
	UpdateAnimation();	// 更新动画
}

void MyGame::GameEnd()
{
}

void MyGame::GamePaint(HDC hdc)
{
	t_scene.Draw(hdc,0,0);
}

void MyGame::GameKeyAction(int ActionType)
{
	if (ActionType == KEY_SYS_NONE)
	{
		if (CheckKey(VK_LEFT)&&!CheckKey(VK_DOWN) && !CheckKey(VK_UP))
		{
			player->SetActive(true);
			player->SetSequence(FRAME_LEFT, 20);
			player->SetDir(DIR_LEFT);
		}
		if (CheckKey(VK_UP) && !CheckKey(VK_LEFT) && !CheckKey(VK_RIGHT))
		{
			player->SetActive(true);
			player->SetSequence(FRAME_UP, 20);
			player->SetDir(DIR_UP);
		}
		if (CheckKey(VK_DOWN) && !CheckKey(VK_LEFT) && !CheckKey(VK_RIGHT))
		{
			player->SetActive(true);
			player->SetSequence(FRAME_DOWN, 20);
			player->SetDir(DIR_DOWN);
		}
		if (CheckKey(VK_RIGHT) && !CheckKey(VK_DOWN) && !CheckKey(VK_UP))
		{
			player->SetActive(true);
			player->SetSequence(FRAME_RIGHT, 20);
			player->SetDir(DIR_RIGHT);
		}// 没有按方向键,那么应该停下
		if (!CheckKey(VK_LEFT) && !CheckKey(VK_RIGHT) && !CheckKey(VK_DOWN) && !CheckKey(VK_UP))
		{
			player->SetActive(false);
		}
	}
	
	
}

void MyGame::GameMouseAction(int x, int y, int ActionType)
{
}

MyGame::~MyGame()
{
	delete player;
	player = NULL;
}
