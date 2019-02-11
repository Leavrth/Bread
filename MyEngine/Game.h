#pragma once
#include <windows.h>
#include "D3DGraphic.h"
#include "Object.h"

class Game
{
public:
	Game(HINSTANCE g_hInst, HWND g_hWnd, int g_width, int g_height) :hInst(g_hInst), 
		hWnd(g_hWnd), width(g_width), height(g_height), ntex(0){};
	bool DoInit();
	bool DoShutdown();
	bool DoPreFrame();
	bool DoFrame();
	bool DoPostFrame();

	
	void sendMouPos(float x, float y) { x_mps = x; y_mps = y; };
private:
	void checkPos();

	HINSTANCE hInst;
	int width, height;
	HWND hWnd;
	D3DGraphic *D3DGph;
	float x_mps, y_mps; // 鼠标坐标



	//人
	short face;//3w,0s,1a,2d
	short ntex;
	bool  move;
	short mancoord[2] = {300,300};

	// 地图
	struct _cameraPos { // 摄像机坐标
		float x = 0;
		float y = 0;
	}cameraPos;
	float mapSize[2];

};