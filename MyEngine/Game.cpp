#include "Game.h"
bool Game::DoInit()
{
	// 这里执行应用程序初始化函数，比如设置图形、声音、网络，等等
	D3DGph = new D3DGraphic(hWnd, width, height);
	if (FAILED(D3DGph->D3D_Init(mapSize[0], mapSize[1])))
		return false;
	// 如果执行成功，就返回 true ，否则返回 FALSE
	return true;
}

bool Game::DoShutdown()
{
	// 这里执行应用程序关闭函数，比如关闭图形、声音，等等
	D3DGph->D3D_Clean();
	SAFE_DELETE(D3DGph);
	//PoolManager::purge();
	// 如果执行成功，就返回 true ，否则返回 FALSE
	return true;
}

bool Game::DoPreFrame()
{
	// 执行 pre-frame 处理过程，比如设置计时器
	// 如果执行成功，就返回 true ，否则返回 FALSE
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
	// 上96 下408 左84 右636
	if (!move) ntex = face*(face-1)*(face-2)/3;
	return true;
}

bool Game::DoFrame()
{
	// 执行 per-frame 处理过程，比如渲染
	D3DGph->g_pd3dDevice->BeginScene();
	D3DGph->g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0L);
	//-渲染部分--------------------------------
	D3DGph->D3D_bgdDraw(cameraPos.x, cameraPos.y, mapID);
	D3DGph->D3D_booDraw(mancoord[0]+21, mancoord[1]+50);
	D3DGph->D3D_infoDraw(x_mps, y_mps, mwhl);  // 第三个参数用于传递临时数据
	//D3DGph->D3D_manDraw(mancoord[0], mancoord[1], ntex, face);
	//------------------------------------------
	D3DGph->g_pd3dDevice->EndScene();
	D3DGph->g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
	// 如果执行成功，就返回 true ，否则返回 FALSE
	return true;
}

bool Game::DoPostFrame()
{
	// 执行 post-frame 处理过程，比如时间同步等
	static float currentTime = 0.0f;
	static float formerTime = 0.0f;
	static float delayTime = 0.0f;
	formerTime = currentTime;
	currentTime = (float)timeGetTime();
 	delayTime = 16.66667 - (currentTime - formerTime)/1000; // 1000毫秒除以60帧
	if(delayTime > 0)
		Sleep(delayTime);
	//while (delayTime > 0)
	//{
	//	currentTime = (float)timeGetTime();
	//	delayTime = 60 - (currentTime - formerTime);
	//}


	// 如果执行成功，就返回 true ，否则返回 FALSE

	return true;
}

void Game::checkPos() {
	if (x_mps <= 0) cameraPos.x -= 15;
	else if (x_mps >= 799) cameraPos.x += 15;
	if (y_mps <= 0) cameraPos.y -= 15;
	else if (y_mps >= 599) cameraPos.y += 15;
	if (cameraPos.x < 0) cameraPos.x = 0;
	else if (cameraPos.x + cameraPos.w > mapSize[0]) cameraPos.x = mapSize[0] - cameraPos.w;
	if (cameraPos.y < 0) cameraPos.y = 0;
	else if (cameraPos.y + cameraPos.h > mapSize[1]) cameraPos.y = mapSize[1] - cameraPos.h;
}

void Game::checkWhl() {
	const short n = mwhl / 120;
	cameraPos.w += n * 220;
	cameraPos.h += n * 165;
	if (cameraPos.w > mapSize[0]) { cameraPos.w = mapSize[0]; cameraPos.h = mapSize[1]; }
	else if (cameraPos.w < width) { cameraPos.w = width; cameraPos.h = height; }
}