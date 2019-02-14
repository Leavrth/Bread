
#include "D3DGraphic.h"
#include <tchar.h>


HRESULT D3DGraphic::D3D_Init()
{
	LPDIRECT3D9 pD3D = NULL;
	if (NULL == (pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	D3DCAPS9 caps; int vp = 0;
	if (FAILED(pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
		return E_FAIL;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = false;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = 0;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hWnd, vp, &d3dpp, &g_pd3dDevice)))
		return E_FAIL;

	if (FAILED(D3D_ObjectInit()))
		return E_FAIL;

	SAFE_RELEASE(pD3D);
	return S_OK;

}
HRESULT D3DGraphic::D3D_Clean()
{

	return S_OK;
}

HRESULT D3DGraphic::D3D_ObjectInit()
{
	
	if (FAILED(D3DXCreateTextureFromFileEx(g_pd3dDevice, L"grass_and_dirt.png", 224, 256, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_TRIANGLE, D3DX_FILTER_TRIANGLE, NULL, NULL, NULL, &g_pTexMap[2])))
		return E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(g_pd3dDevice, L"grass_and_dirt.png", 112, 128, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_TRIANGLE, D3DX_FILTER_TRIANGLE, NULL, NULL, NULL, &g_pTexMap[1])))
		return E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(g_pd3dDevice, L"grass_and_dirt.png", 56, 64, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_TRIANGLE, D3DX_FILTER_TRIANGLE, NULL, NULL, NULL, &g_pTexMap[0])))
		return E_FAIL;
	
	// 80*60个格子，一个格子32*32像素
	
	if (FAILED(D3DXCreateTextureFromFileEx(g_pd3dDevice, L"Bomb.png", 30, 30, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_TRIANGLE, D3DX_FILTER_TRIANGLE, NULL, NULL, NULL, &g_pTexBoo)))
		return E_FAIL;
	
	// 创建精灵
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &g_pSpr)))
		return E_FAIL;
	


	if (FAILED(D3DXCreateFont(g_pd3dDevice, 14, 0, 0, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, _T("微软雅黑"), &g_pFont)))
		return E_FAIL;


	rect[0].top = 8;
	rect[0].left = 0;
	rect[0].right = rect[0].left + 8;
	rect[0].bottom = rect[0].top + 8;

	rect[1].top = 16;
	rect[1].left = 0;
	rect[1].right = rect[1].left + 16;
	rect[1].bottom = rect[1].top + 16;

	rect[2].top = 32;
	rect[2].left = 0;
	rect[2].right = rect[2].left + 32;
	rect[2].bottom = rect[2].top + 32;

	return S_OK;
}


HRESULT D3DGraphic::D3D_infoDraw(float _mx, float _my, const float& _tmp)
{
	static wchar_t info[80];
	static int _n;
	static RECT formatRect; GetClientRect(hWnd, &formatRect);
	formatRect.top += 15; formatRect.left += 40;
	_n = swprintf_s(info, 80, _T("mouseX:%0.3f,mouseY:%0.3f,tmpData:%0.3f"), _mx, _my, _tmp);
	if (FAILED(g_pFont->DrawText(NULL, info, _n, &formatRect, DT_TOP | DT_LEFT, D3DCOLOR_XRGB(36, 36, 36))))
		return E_FAIL;

	return S_OK;
}


HRESULT D3DGraphic::D3D_bgdDraw(int _cx, int _cy, const short (*mapId)[80], const short scalingID)
{
	static const short scaling[3] = { 8, 16, 32 };

	const short SI = scaling[scalingID];
	const short dx = (_cx >= 320) ? ((_cx - 320) / SI) : 0; // mapId[dy][dx]
	const short dy = (_cy >= 240) ? ((_cy - 240) / SI) : 0;
	const short rx = _cx % SI;
	const short ry = _cy % SI;
	
	
	g_pSpr->Begin(D3DXSPRITE_ALPHABLEND);
	for (int cx = -rx, i = 0; dx+i < 80 && cx < 800; cx += SI, _cx += SI) {
		bool xOK = false;
		for (int cy = -ry, j = 0, __cy = _cy; dy+j != 60 && cy < 600; cy += SI, __cy += SI) {
			bool yOK = false;
			if (_cx >= 320 && __cy >= 240) {
				yOK = true;
				j++;
				if (FAILED(g_pSpr->Draw(g_pTexMap[scalingID], &rect[scalingID], NULL, &D3DXVECTOR3(cx, cy, 0.0f), 0xffffffff))) {
					g_pSpr->End();
					return E_FAIL;
				}
			}
			if (yOK)xOK = true;
		}
		if (xOK)i++;
	}
	g_pSpr->End();
	return S_OK;
}
HRESULT D3DGraphic::D3D_booDraw(float _mx, float _my) 
{
	RECT rect;
	rect.top = 0;
	rect.left = 0;
	rect.right = 30;
	rect.bottom = 30;
	g_pSpr->Begin(D3DXSPRITE_ALPHABLEND);
	if (FAILED(g_pSpr->Draw(g_pTexBoo, &rect, NULL, &D3DXVECTOR3(_mx, _my, 0.0f), 0xffffffcc))) {
		g_pSpr->End();
		return E_FAIL;
	}
	g_pSpr->End();
	return S_OK;
}

D3DGraphic::~D3DGraphic()
{

}

