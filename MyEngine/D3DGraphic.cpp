
#include "D3DGraphic.h"
#include <tchar.h>


HRESULT D3DGraphic::D3D_Init(float& mapSizex, float& mapSizey)
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

	if (FAILED(D3D_ObjectInit(mapSizex, mapSizey)))
		return E_FAIL;

	SAFE_RELEASE(pD3D);
	return S_OK;

}
HRESULT D3DGraphic::D3D_Clean()
{

	return S_OK;
}

HRESULT D3DGraphic::D3D_ObjectInit(float& mapSizex, float& mapSizey)
{
	// µ¼ÈëÈË
	if (FAILED(D3DXCreateTextureFromFileEx(g_pd3dDevice, L"WB.png", 260, 216, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_TRIANGLE, D3DX_FILTER_TRIANGLE, NULL, NULL, NULL, &g_pTexMan)))
		return E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(g_pd3dDevice, L"BGD.png", 2400, 1600, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_TRIANGLE, D3DX_FILTER_TRIANGLE, NULL, NULL, NULL, &g_pTexBGD)))
		return E_FAIL;
	mapSizex = 2400, mapSizey = 1600;
	if (FAILED(D3DXCreateTextureFromFileEx(g_pd3dDevice, L"Bomb.png", 30, 30, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_TRIANGLE, D3DX_FILTER_TRIANGLE, NULL, NULL, NULL, &g_pTexBoo)))
		return E_FAIL;
	/*
	if (FAILED(D3DXCreateTextureFromFileEx(g_pd3dDevice, L"Bgd.png", 1600, 460, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
	D3DX_FILTER_TRIANGLE, D3DX_FILTER_TRIANGLE, NULL, NULL, NULL, &g_pTexBgd))){
	MB(L"Í¼Æ¬¼ÓÔØ´íÎó", L"Bgd.png");
	return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFileEx(g_pd3dDevice, L"man.png", 396, 77, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
	D3DX_FILTER_TRIANGLE, D3DX_FILTER_TRIANGLE, NULL, NULL, NULL, &g_pTexture))){
	MB(L"Í¼Æ¬¼ÓÔØ´íÎó", L"man.png");
	return E_FAIL;
	}
	if (FAILED(D3DXCreateTextureFromFileEx(g_pd3dDevice, L"t_Bgd.png", 800, 140, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
	D3DX_FILTER_TRIANGLE, D3DX_FILTER_TRIANGLE, NULL, NULL, NULL, &g_pTexTBgd))){
	MB(L"Í¼Æ¬¼ÓÔØ´íÎó", L"t_Bgd.png");
	return E_FAIL;
	}
	if (FAILED(D3DXCreateTextureFromFileEx(g_pd3dDevice, L"skill1.png", 1428, 900, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
	D3DX_FILTER_TRIANGLE, D3DX_FILTER_TRIANGLE, NULL, NULL, NULL, &g_pTexSkill))){
	MB(L"Í¼Æ¬¼ÓÔØ´íÎó", L"skill1.png");
	return E_FAIL;
	}
	*/
	// ´´½¨¾«Áé
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &g_pSprMan)))
		return E_FAIL;
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &g_pSprBGD)))
		return E_FAIL;
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &g_pSprBoo)))
		return E_FAIL;
	/*
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &g_pSkill)))
	return E_FAIL;

	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &g_pTBgd)))
	return E_FAIL;

	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &g_pBgd)))
	return E_FAIL;

	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &g_pSprite)))
	return E_FAIL;

	*/
	if (FAILED(D3DXCreateFont(g_pd3dDevice, 14, 0, 0, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, _T("Î¢ÈíÑÅºÚ"), &g_pFont)))
		return E_FAIL;

	return S_OK;
}


HRESULT D3DGraphic::D3D_infoDraw(float _mx, float _my)
{
	static wchar_t info[80];
	static int _n;
	static RECT formatRect; GetClientRect(hWnd, &formatRect);
	formatRect.top += 15; formatRect.left += 40;
	_n = swprintf_s(info, 80, _T("mouseX:%0.3f,mouseY:%0.3f"), _mx, _my);
	if (FAILED(g_pFont->DrawText(NULL, info, _n, &formatRect, DT_TOP | DT_LEFT, D3DCOLOR_XRGB(36, 36, 36))))
		return E_FAIL;

	return S_OK;
}

HRESULT D3DGraphic::D3D_manDraw(float _mx, float _my, short ntex, short face)
{
	RECT rect;
	rect.top = face*90.5;
	rect.left = ntex*72.25;
	rect.right = (ntex+1) * 72.25;
	rect.bottom = (face+1) * 90.5;
	g_pSprMan->Begin(D3DXSPRITE_ALPHABLEND);
	if (FAILED(g_pSprMan->Draw(g_pTexMan, &rect, NULL, &D3DXVECTOR3(_mx, _my, 0.0f), 0xffffffff))) {
		g_pSprMan->End();
		return E_FAIL;
	}
	g_pSprMan->End();
	return S_OK;

}

HRESULT D3DGraphic::D3D_bgdDraw(float _cx, float _cy)
{
	RECT rect;
	rect.top = _cy;
	rect.left = _cx;
	rect.right = rect.left + 800;
	rect.bottom = rect.right + 600;
	g_pSprBGD->Begin(D3DXSPRITE_ALPHABLEND);
	if (FAILED(g_pSprBGD->Draw(g_pTexBGD, &rect, NULL, &D3DXVECTOR3(0, 0, 0.0f), 0xffffffff))) {
		g_pSprBGD->End();
		return E_FAIL;
	}
	g_pSprBGD->End();
	return S_OK;
}
HRESULT D3DGraphic::D3D_booDraw(float _mx, float _my) 
{
	RECT rect;
	rect.top = 0;
	rect.left = 0;
	rect.right = 30;
	rect.bottom = 30;
	g_pSprBoo->Begin(D3DXSPRITE_ALPHABLEND);
	if (FAILED(g_pSprBoo->Draw(g_pTexBoo, &rect, NULL, &D3DXVECTOR3(_mx, _my, 0.0f), 0xffffffcc))) {
		g_pSprBoo->End();
		return E_FAIL;
	}
	g_pSprBoo->End();
	return S_OK;
}

D3DGraphic::~D3DGraphic()
{

}

/*
LPD3DXSPRITE g_pBgd; //µØÍ¼
HRESULT D3DGraphic::D3D_manSpritDraw(float _x, float _y)
{
g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

if (FAILED(g_pSprite->Draw(g_pTexture, &t_Sprite[n_tex], NULL, &D3DXVECTOR3(_x, _y, 0.0f), 0xffffffff)))
{
g_pSprite->End();
return E_FAIL;
}
g_pSprite->End();
return S_OK;
}
*/
