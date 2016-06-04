#include "GraphicsDevice.h"

GraphicsDevice::GraphicsDevice()
{
	// Constructor logic
}


GraphicsDevice::~GraphicsDevice()
{
	if (device)
	{
		// NOTE FOR CHRIS STUDY:  look up Release() function
		device->Release();
		device = NULL;
	}

	if (direct3d)
	{
		direct3d->Release();
		direct3d = NULL;
	}
}

void GraphicsDevice::Initialize(HWND hWnd, bool windowed)
{
	//  Create the Direct 3D Pointer.  Tells it which version to use
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS presentationParams;
	ZeroMemory(&presentationParams, sizeof(presentationParams));
	presentationParams.Windowed = windowed;

	//	Controls how windows is redrawn (something with backbuffer)
	presentationParams.SwapEffect = D3DSWAPEFFECT_DISCARD;

	//	Handle of the window
	presentationParams.hDeviceWindow = hWnd;

	//	Will fill in later with more parameters

	//	Create the device
	//	D3DADAPTER_DEFAULT = Primary display adapter (default graphics card)
	//	D3DDEVTYPE_HAL = Hardware rasterization
	//	D3DCREATE_MIXED_VERTEXPROCESSING = Uses both hardware and software for 3D calculations
	direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_MIXED_VERTEXPROCESSING, &presentationParams,
		&device);
}void GraphicsDevice::Clear(D3DCOLOR color)
{
	//	2nd param is set to 'NULL' so that it clears the entire back buffer
	device->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0);
}

void GraphicsDevice::Begin()
{
	device->BeginScene();
}

void GraphicsDevice::End()
{
	device->EndScene();
}

void GraphicsDevice::Present()
{
	//	Present our scene to the window
	device->Present(NULL, NULL, NULL, NULL);
}