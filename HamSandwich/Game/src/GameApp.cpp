#include <Windows.h>

#include "GameApp.h"

GameApp::GameApp()
	: m_running(false)
	, m_lastUpdate()
	, m_systems()
	, m_renderingSystem()
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

	// Initialize timer
	m_lastUpdate = std::chrono::high_resolution_clock::now();

	// Initialize subsystems
	m_renderingSystem = std::make_unique<RenderingSystem>();

	// Register subsystems
	m_systems.push_back(static_cast<IEngineSystem*>(m_renderingSystem.get()));

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
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			auto now = std::chrono::high_resolution_clock::now();
			// high_resolution_clock is probably already nanosecond resolution, but we want to make sure.
			const auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now - m_lastUpdate);
			m_lastUpdate = now;

			// Update subsystems
			for (auto& system : m_systems)
			{
				system->Update(elapsed_ns.count());
			}
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