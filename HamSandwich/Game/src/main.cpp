// Entry point bullshit so that this is real easy to replace.
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include "GameApp.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
GameApp* g_appInstance;

// Entry point
int CALLBACK WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdLine, int nShowCmd)
{
	try
	{
		GameApp appInstance(WndProc, hInst, nShowCmd);
		g_appInstance = &appInstance;
		g_appInstance->Run();
	}
	catch (const std::exception& e)
	{
		MessageBoxA(NULL, e.what(), "Error", MB_OK);
	}

	return 0;
}

// Window message handling process.
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		g_appInstance->Exit();
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		g_appInstance->UpdateWindow(hwnd);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}