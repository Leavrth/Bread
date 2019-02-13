#pragma once
#include <d3d9.h>
#include <D3dx9tex.h>
#include <windows.h>
#include "D3DUtil.h"

class D3DGraphic
{
public:
	D3DGraphic(HWND g_hWnd, int g_width, int g_height) :hWnd(g_hWnd), width(g_width), height(g_height) {};
	LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;

	HRESULT D3D_Init(const float &, const float &);
	HRESULT D3D_Clean();
	HRESULT D3D_infoDraw(float _mx, float _my, const float& _tmp);

	HRESULT D3D_bgdDraw(float _cx, float _cy, const short (*mapId)[80]);
	HRESULT D3D_booDraw(float _mx, float _my);
	~D3DGraphic();
private:
	HWND hWnd;
	int width, height;
	HRESULT D3D_ObjectInit(const float&, const float&);
	ID3DXFont *g_pFont;

	LPDIRECT3DTEXTURE9 g_pTexMap[3];
	LPDIRECT3DTEXTURE9 g_pTexMan;
	LPDIRECT3DTEXTURE9 g_pTexBGD;
	LPDIRECT3DTEXTURE9 g_pTexBoo;
	LPD3DXSPRITE       g_pSpr;
};
