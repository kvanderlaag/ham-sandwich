#include <Windows.h>

#include "GameApp.h"

GameApp::GameApp()
	: m_running(false)
{
}

GameApp::~GameApp()
{
}

bool GameApp::Initialize(WNDPROC wndProc, HINSTANCE hInst, int nShowCmd)
{
	// Register the window class.
	const LPCSTR CLASS_NAME = "Rendering Window";

	WNDCLASS wc = {};

	wc.lpfnWndProc = wndProc;
	wc.hInstance = hInst;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the window.

	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		"Rendering Window",			    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,       // Parent window    
		NULL,       // Menu
		hInst,		// Instance handle
		NULL        // Additional application data
	);

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nShowCmd);
	return true;
}

bool GameApp::Shutdown()
{
	return true;
}

void GameApp::Run()
{
	m_running = true;
	while (m_running)
	{
		MSG msg = {};
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void GameApp::UpdateWindow(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

	EndPaint(hwnd, &ps);
}

void GameApp::Exit()
{
	m_running = false;
}