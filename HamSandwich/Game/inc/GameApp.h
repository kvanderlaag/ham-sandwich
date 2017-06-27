#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <memory>
#include <vector>
#include <chrono>

#include <core/inc/IEngineSystem.h>

#include <renderer/inc/RenderingSystem.h>

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

	std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::high_resolution_clock::duration> m_lastUpdate;

	// Container of systems.
	std::vector<IEngineSystem*> m_systems;

	// std::unique_ptrs for subsystems that GameApp owns.
	std::unique_ptr<RenderingSystem> m_renderingSystem;
};