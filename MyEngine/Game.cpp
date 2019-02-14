#include "Game.h"
bool Game::DoInit()
{
	// ����ִ��Ӧ�ó����ʼ����������������ͼ�Ρ����������磬�ȵ�
	D3DGph = new D3DGraphic(hWnd, width, height);
	if (FAILED(D3DGph->D3D_Init()))
		return false;
	// ���ִ�гɹ����ͷ��� true �����򷵻� FALSE
	return true;
}

bool Game::DoShutdown()
{
	// ����ִ��Ӧ�ó���رպ���������ر�ͼ�Ρ��������ȵ�
	D3DGph->D3D_Clean();
	SAFE_DELETE(D3DGph);
	//PoolManager::purge();
	// ���ִ�гɹ����ͷ��� true �����򷵻� FALSE
	return true;
}

bool Game::DoPreFrame()
{
	// ִ�� pre-frame ������̣��������ü�ʱ��
	// ���ִ�гɹ����ͷ��� true �����򷵻� FALSE
	checkPos();
	move = false;
	if (GetAsyncKeyState(75))//K
	{
		float str1;
		str1 = x_mps;
		str1 = y_mps;

	}
	if (GetAsyncKeyState(87)){// w
		if (face == 3)ntex = (ntex + 1) % 4;
		else { face = 3; ntex = 2; }
		move = true;
		if (mancoord[1] - 12 <= 96)
			mancoord[1] = 96;
		else
			mancoord[1] -= 12;
	}
	else if (GetAsyncKeyState(83)) {// s
		if (face == 0)ntex = (ntex + 1) % 4;
		else { face = 0; ntex = 0; }
		move = true;
		if (mancoord[1] + 12 >= 408)
			mancoord[1] = 408;
		else
			mancoord[1] += 12;
	}
	else if (GetAsyncKeyState(65)) {// a
		if (face == 1)ntex = (ntex + 1) % 4;
		else { face = 1; ntex = 0; }
		move = true;
		if (mancoord[0] - 12 <= 84)
			mancoord[0] = 84;
		else
			mancoord[0] -= 12;
	}
	else if (GetAsyncKeyState(68)) {// d
		if (face == 2)ntex = (ntex + 1) % 4;
		else { face = 2; ntex = 0; }
		move = true;
		if (mancoord[0] + 12 >= 636)
			mancoord[0] = 636;
		else
			mancoord[0] += 12;
	}
	// ��96 ��408 ��84 ��636
	if (!move) ntex = face*(face-1)*(face-2)/3;
	return true;
}

bool Game::DoFrame()
{
	// ִ�� per-frame ������̣�������Ⱦ
	D3DGph->g_pd3dDevice->BeginScene();
	D3DGph->g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0L);
	//-��Ⱦ����--------------------------------
	D3DGph->D3D_bgdDraw(cameraPos.x, cameraPos.y, mapID, scalingLevel);
	D3DGph->D3D_booDraw(mancoord[0]+21, mancoord[1]+50);
	D3DGph->D3D_infoDraw(cameraPos.x, cameraPos.y, mwhl);  // �������������ڴ�����ʱ����
	//D3DGph->D3D_manDraw(mancoord[0], mancoord[1], ntex, face);
	//------------------------------------------
	D3DGph->g_pd3dDevice->EndScene();
	D3DGph->g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
	// ���ִ�гɹ����ͷ��� true �����򷵻� FALSE
	return true;
}

bool Game::DoPostFrame()
{
	// ִ�� post-frame ������̣�����ʱ��ͬ����
	static float currentTime = 0.0f;
	static float formerTime = 0.0f;
	static float delayTime = 0.0f;
	formerTime = currentTime;
	currentTime = (float)timeGetTime();
 	delayTime = 16.66667 - (currentTime - formerTime)/1000; // 1000�������60֡
	if(delayTime > 0)
		Sleep(delayTime);
	//while (delayTime > 0)
	//{
	//	currentTime = (float)timeGetTime();
	//	delayTime = 60 - (currentTime - formerTime);
	//}


	// ���ִ�гɹ����ͷ��� true �����򷵻� FALSE

	return true;
}

void Game::checkPos() {
	if (x_mps <= 0) cameraPos.x -= 10;
	else if (x_mps >= 799) cameraPos.x += 10;
	if (y_mps <= 0) cameraPos.y -= 10;
	else if (y_mps >= 599) cameraPos.y += 10;
	checkEdge();
}

void Game::checkWhl() {
	const short n = mwhl > 0 ? 1 : -1;
	scalingLevel += n;
	if (scalingLevel > 2) scalingLevel = 2;
	else if (scalingLevel < 0) scalingLevel = 0;
	else {
		cameraPos.x += n * 400;
		cameraPos.y += n * 300;
		checkEdge();
	}
}