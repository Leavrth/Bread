#pragma once
#include <windows.h>
#include "D3DGraphic.h"

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

	void sendMouWhl(const short whl) { mwhl = whl; checkWhl(); mwhl = 0; }
	void sendMouPos(float x, float y) { x_mps = x; y_mps = y; };
private:
	void checkPos();
	void checkWhl(); //滚轮事件

	HINSTANCE hInst;
	int width, height;
	HWND hWnd;
	D3DGraphic *D3DGph;
	float x_mps, y_mps; // 鼠标坐标
	short mwhl = 0; // 鼠标滚轮信息


	//人
	short face;//3w,0s,1a,2d
	short ntex;
	bool  move;
	short mancoord[2] = {300,300};

	// 地图
	struct _cameraPos { // 摄像机坐标
		float x = 0;
		float y = 0;
		float w = 800.0f;
		float h = 600.0f;
	}cameraPos;
	float mapSize[2] = {2560.0f, 1920.0f};
	short mapID[60][80] = {0}; // (r,c)


};