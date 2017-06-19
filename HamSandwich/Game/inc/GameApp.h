#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <memory.h>

class GameApp
{
public:
	// constructor/destructor
	GameApp();
	virtual ~GameApp();

	// Interface
public:
	bool Initialize(WNDPROC wndProc, HINSTANCE hInst, int nShowCmd);
	bool Shutdown();

	void Run(); // contains the game and update loop

	void UpdateWindow(HWND hwnd);
	void Exit();

	// Member functions
private:
	bool m_running;

	// std::unique_ptrs for subsystems that GameApp owns.
};