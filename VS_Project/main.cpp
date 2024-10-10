#include "DxLib.h"
#include "Application.h"

//int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
int main()
{
	auto& application = Application::getInstance();
	if (!application.Init()) return-1;

	application.Run();

	return 0;
}
