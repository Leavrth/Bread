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

	HRESULT D3D_Init(float &, float &);
	HRESULT D3D_Clean();
	HRESULT D3D_infoDraw(float _mx, float _my);

	HRESULT D3D_manDraw(float _mx, float _my, short ntex, short face);
	HRESULT D3D_bgdDraw(float _cx, float _cy);
	HRESULT D3D_booDraw(float _mx, float _my);
	~D3DGraphic();
private:
	HWND hWnd;
	int width, height;
	HRESULT D3D_ObjectInit(float&, float&);
	ID3DXFont *g_pFont;

	LPDIRECT3DTEXTURE9 g_pTexMan;
	LPD3DXSPRITE       g_pSprMan;
	LPDIRECT3DTEXTURE9 g_pTexBGD;
	LPD3DXSPRITE       g_pSprBGD;
	LPDIRECT3DTEXTURE9 g_pTexBoo;
	LPD3DXSPRITE       g_pSprBoo;
};
