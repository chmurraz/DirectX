#define VK_AKEY 0x41

#include <windows.h>
#include "Game.h"

//	Download and install the Microsoft SDK for DirectX (June 2010 build)
//	Debug | Win32 --> Microsoft.Cpp.Win32.user
//	Include Directories - Make sure C:\Program Files (x86)\Microsoft DirectX (June 2010)\Include has been added
//	Library Directories - Make sure C:\Program Files (x86)\Microsoft DirectX (June 2010)\Lib\x86 has been added
//	Linker input - Make sure d3d9.lib and d3dx9.lib are there
//	VIEW - PROPERTY MANAGER


//	Prototypes for the GenerateWindow function, otherwise WinMain cannot call GenerateWindow
bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle, int width, int height, HWND& hWnd);
bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle, int x, int y, int width, int height, HWND& hWnd);

//	Another prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
bool InitializeInput();
Game *game;

//WinMain function set up a window and enter a message loop
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MessageBox(NULL, "Tutorial 4 @ 14:30 lists cool realign tricks", NULL, NULL);

	HWND hWnd;
	if (GenerateWindow(hInstance, nCmdShow, "Drawing Sprites", "Drawing a PNG Image as a Sprite", 1280, 720, hWnd)
		&& InitializeInput())
	{
		MSG msg;
		game = new Game();

		if (game->Initialize(hWnd))
		{
			while (true)
			{

				//	PeekMessage section controls if window updates (it doesn't) while the window is being dragged around by the user
				while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);

					DispatchMessage(&msg);
				}

				if (msg.message == WM_QUIT) break;
				else
				{
					game->Run();
				}
			}

			delete game;
			return msg.wParam;
		}
	}
	return 0;
}

bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle, int width, int height, HWND& hWnd)
{
	return GenerateWindow(hInstance, nCmdShow, className, windowTitle, (GetSystemMetrics(SM_CXSCREEN) - width) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - height) / 2, width, height, hWnd);
}

bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle, int x, int y, int width, int height, HWND& hWnd)
{
	WNDCLASSEX wcex;

	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProc;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wcex.lpszClassName = className;
	wcex.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	if (!RegisterClassEx(&wcex))
	{
		return false;
	}

	// Change WS options to control ability to resize window, etc.  See DirectX 9 Basic Training video 3/13 @ 32:20 for more
	hWnd = CreateWindowEx(NULL, className, windowTitle, WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, x, y, width, height, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	return true;

}

bool InitializeInput()
{
	RAWINPUTDEVICE rawinput[1];		//	only one input for now, keyboard
	
	rawinput[0].usUsagePage = 0x01;
	rawinput[0].usUsage = 0x06;		//	use 0x02 for mouse
	rawinput[0].dwFlags = 0;
	rawinput[0].hwndTarget = 0;

	if (RegisterRawInputDevices(rawinput, 1, sizeof(rawinput[0])) == FALSE)
	{
		return false;
	}

	return true;
}

//WindowProc - Handles input sent to the window
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		} break;

	//	See Tutorial 9 for more detail on all this stuff in WM_INPUT.  This information appears in the Output window
	case WM_INPUT:
		{
			UINT dwSize;
			GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));
			LPBYTE lpb = new BYTE[dwSize];
			if (lpb == NULL)
			{
				return 0;
			}

			GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));
			RAWINPUT* raw = (RAWINPUT*)lpb;

			if (raw->header.dwType == RIM_TYPEKEYBOARD)
			{
				if (raw->data.keyboard.Message == WM_KEYDOWN || raw->data.keyboard.Message == WM_SYSKEYDOWN)
				{
					std::string information =
						"Make Code - " + std::to_string(raw->data.keyboard.MakeCode) +
						"; Flag - " + std::to_string(raw->data.keyboard.Flags) +
						"; Reserved - " + std::to_string(raw->data.keyboard.Reserved) +
						"; Extra Information - " + std::to_string(raw->data.keyboard.ExtraInformation) +
						"; Message - " + std::to_string(raw->data.keyboard.Message) +
						"; VKey - " + std::to_string(raw->data.keyboard.VKey) +
						"\n";

					OutputDebugString(information.c_str());
					//	use VK_SPACE, etc... make new defines at very top of Main.cpp
					if (raw->data.keyboard.VKey == VK_SPACE)
					{
						MessageBox(NULL, "A key was pressed", NULL, NULL);
					}
				}
			}

		} break;

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}