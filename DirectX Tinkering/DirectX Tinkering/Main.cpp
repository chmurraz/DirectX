#include <windows.h>
#include "GraphicsDevice.h"
#include "GameSprite.h"

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

//	UPDATE and DRAW functions (written when GraphicsDevice class was written)
void Update(float gameTime);
void Draw(GraphicsDevice *gDevice, float gameTime);

//	Global Player SPrites
GameSprite *player;

//WinMain function set up a window and enter a message loop
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MessageBox(NULL, "Left off on DirectX Tutorial 3 @ 23:00 minutes", NULL, NULL);

	HWND hWnd;
	if (GenerateWindow(hInstance, nCmdShow, "Drawing Sprites", "Drawing a PNG Image as a Sprite", 1280, 720, hWnd))
	{
		MSG msg;
		GraphicsDevice *gDevice = new GraphicsDevice();
		gDevice->Initialize(hWnd, true);
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
				//Update and draw our game (written after creating GraphicsDevice class)
				Update(0.0f);
				Draw(gDevice, 0.0f);
			}
		}

		//	Added this line in tutorial 2
		delete gDevice;

		return msg.wParam;
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

//WindowProc - Handles input sent to the window
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void Update(float gameTime)
{
	//	Update our sprites and other game logic
}

void Draw(GraphicsDevice *gDevice, float gameTime)
{
	//	Clear, Begin and Present in that order
	gDevice->Clear(D3DCOLOR_XRGB(0, 100, 100));
	gDevice->Begin();
	gDevice->End();
	gDevice->Present();
}