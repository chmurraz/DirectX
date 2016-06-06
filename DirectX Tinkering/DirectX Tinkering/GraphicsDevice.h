#ifndef GRAPHICSDEVICE_H
#define GRAPHICSDEVICE_H

//	d3d10.h is needed for Direct3D Logic
#include <d3d9.h>

class GraphicsDevice
{
public:
	GraphicsDevice();
	~GraphicsDevice();

	//  Direct3D Functions
	bool Initialize(HWND hWnd, bool windowed);
	void Clear(D3DCOLOR color);
	void Begin();
	void End();
	void Present();

	//	Create a pointer for an interface??
	//  Shorthand for IDirect3Device9 *device;
	LPDIRECT3DDEVICE9 device;
private:
	LPDIRECT3D9 direct3d;



};

#endif /* GRAPHICSDEVICE_H */