
#include "MyGame.h"

// WinMain����
//
int WINAPI WinMain(HINSTANCE h_instance, HINSTANCE hPrevInstance, 
				   PSTR szCmdLine, int iCmdShow)
{
	LPCTSTR WinTitle = L"ը����";
	MyGame* mygame = new MyGame(h_instance,WIN_CLASS,WinTitle,
									NULL, NULL, WIN_WIDTH, WIN_HEIGHT);
	T_Engine::pEngine = mygame;
	mygame->SetFrame(20);
	mygame->StartEngine();

	return TRUE;
}
