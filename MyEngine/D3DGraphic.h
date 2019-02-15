#pragma once
#include <d3d9.h>
#include <D3dx9tex.h>
#include <windows.h>
#include "D3DUtil.h"
struct _checkMsg;

class D3DGraphic
{
public:
	D3DGraphic(HWND g_hWnd, int g_width, int g_height) :hWnd(g_hWnd), width(g_width), height(g_height) {};
	LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;

	HRESULT D3D_Init();
	HRESULT D3D_Clean();
	HRESULT D3D_infoDraw(float _mx, float _my, const float& _tmp);

	HRESULT D3D_bgdDraw(int _cx, int _cy, const short (*mapId)[80], const short, const _checkMsg&, short);
	HRESULT D3D_booDraw(float _mx, float _my);
	~D3DGraphic();
private:
	HWND hWnd;
	int width, height;
	HRESULT D3D_ObjectInit();
	ID3DXFont *g_pFont;

	RECT rect[48][3];
	RECT chkrect[3];
	LPDIRECT3DTEXTURE9 g_pTexMap[3];
	LPDIRECT3DTEXTURE9 g_pTexBoo;
	LPD3DXSPRITE       g_pSpr;
};
