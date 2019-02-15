
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
	
	if (FAILED(D3DXCreateTextureFromFileEx(g_pd3dDevice, L"grass_and_dirt1.png", 224, 256, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_TRIANGLE, D3DX_FILTER_TRIANGLE, NULL, NULL, NULL, &g_pTexMap[2])))
		return E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(g_pd3dDevice, L"grass_and_dirt1.png", 112, 128, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_TRIANGLE, D3DX_FILTER_TRIANGLE, NULL, NULL, NULL, &g_pTexMap[1])))
		return E_FAIL;
	if (FAILED(D3DXCreateTextureFromFileEx(g_pd3dDevice, L"grass_and_dirt1.png", 56, 64, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_TRIANGLE, D3DX_FILTER_TRIANGLE, NULL, NULL, NULL, &g_pTexMap[0])))
		return E_FAIL;
	
	// 80*60�����ӣ�һ������32*32����
	
	if (FAILED(D3DXCreateTextureFromFileEx(g_pd3dDevice, L"Bomb.png", 30, 30, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_TRIANGLE, D3DX_FILTER_TRIANGLE, NULL, NULL, NULL, &g_pTexBoo)))
		return E_FAIL;
	
	// ��������
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &g_pSpr)))
		return E_FAIL;
	


	if (FAILED(D3DXCreateFont(g_pd3dDevice, 14, 0, 0, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, _T("΢���ź�"), &g_pFont)))
		return E_FAIL;

	for(int i = 0; i != 8; i++)
		for (int j = 0; j != 6; j++) {
			rect[i * 6 + j][0].top = 8*i;
			rect[i * 6 + j][0].left = 8*j;
			rect[i * 6 + j][0].right = rect[i * 6 + j][0].left + 8;
			rect[i * 6 + j][0].bottom = rect[i * 6 + j][0].top + 8;

			rect[i * 6 + j][1].top = 16*i;
			rect[i * 6 + j][1].left = 16*j;
			rect[i * 6 + j][1].right = rect[i * 6 + j][1].left + 16;
			rect[i * 6 + j][1].bottom = rect[i * 6 + j][1].top + 16;

			rect[i * 6 + j][2].top = 32*i;
			rect[i * 6 + j][2].left = 32*j;
			rect[i * 6 + j][2].right = rect[i * 6 + j][2].left + 32;
			rect[i * 6 + j][2].bottom = rect[i * 6 + j][2].top + 32;
		}
	

	chkrect[0].top = 8 * 7;
	chkrect[0].left = 8 * 6;
	chkrect[0].right = chkrect[0].left + 8;
	chkrect[0].bottom = chkrect[0].top + 8;
	chkrect[1].top = 16 * 7;
	chkrect[1].left = 16 * 6;
	chkrect[1].right = chkrect[1].left + 16;
	chkrect[1].bottom = chkrect[1].top + 16;
	chkrect[2].top = 32 * 7;
	chkrect[2].left = 32 * 6;
	chkrect[2].right = chkrect[2].left + 32;
	chkrect[2].bottom = chkrect[2].top + 32;

	return S_OK;
}


HRESULT D3DGraphic::D3D_infoDraw(float _mx, float _my, const float& _tmp)
{
	static wchar_t info[80];
	static int _n;
	static RECT formatRect; GetClientRect(hWnd, &formatRect);
	formatRect.top += 15; formatRect.left += 40;
	_n = swprintf_s(info, 80, _T("mouseX:%0.3f,mouseY:%0.3f,tmpData:%0.3f"), _mx, _my, _tmp);
	if (FAILED(g_pFont->DrawText(NULL, info, _n, &formatRect, DT_TOP | DT_LEFT, D3DCOLOR_XRGB(255, 255, 255))))
		return E_FAIL;

	return S_OK;
}


HRESULT D3DGraphic::D3D_bgdDraw(int _cx, int _cy, const short (*mapId)[80], const short scalingID, const _checkMsg& cmsg, short nn)
{
	static const short scaling[3] = { 8, 16, 32 };

	const short SI = scaling[scalingID];
	const short dx = (_cx >= 256) ? ((_cx - 256) / SI) : 0; // mapId[dy][dx]
	const short dy = (_cy >= 192) ? ((_cy - 192) / SI) : 0;
	const short rx = _cx % SI;
	const short ry = _cy % SI;
	
	const short ckx = cmsg.checknx * SI + 256 - _cx;
	const short cky = cmsg.checkny * SI + 192 - _cy;
	
	g_pSpr->Begin(D3DXSPRITE_ALPHABLEND);
	for (int cx = -rx, i = dx; i < 80 && cx < 800; cx += SI, _cx += SI) {
		bool xOK = false;
		for (int cy = -ry, j = dy, __cy = _cy; j < 60 && cy < 600; cy += SI, __cy += SI) {
			bool yOK = false;
			if (_cx >= 256 && __cy >= 192) {
				yOK = true;
				if (FAILED(g_pSpr->Draw(g_pTexMap[scalingID], &rect[mapId[j][i]][scalingID], NULL, &D3DXVECTOR3(cx, cy, 0.0f), 0xffffffff))) {
					g_pSpr->End();
					return E_FAIL;
				}
				j++;
			}
			if (yOK)xOK = true;
		}
		if (xOK)i++;
	}
	if(cmsg.ischeck && ckx > -SI && ckx < 800 && cky > -SI && cky < 600)
		if (FAILED(g_pSpr->Draw(g_pTexMap[scalingID], &chkrect[scalingID], NULL, &D3DXVECTOR3(ckx, cky, 0.0f), 0xffffffff))) {
			g_pSpr->End();
			return E_FAIL;
		}
	if (FAILED(g_pSpr->Draw(g_pTexMap[scalingID], &rect[nn][scalingID], NULL, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0xffffffff))) {
		g_pSpr->End();
		return E_FAIL;
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

