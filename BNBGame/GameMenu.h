#pragma once
#include "T_Menu.h"
class GameMenu :
	public T_Menu
{
public:
	GameMenu();
	~GameMenu();
	void DrawMenu(HDC hdc, int bkgX = 0, int bkgY = 0, BYTE btnTrans = 255, bool startState = true);
	void ClearItem() { gm_menuItems.clear(); }
};

