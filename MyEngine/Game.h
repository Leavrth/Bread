#pragma once
#include <windows.h>
#include "D3DGraphic.h"
#include "keyInput.h"

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
	void actMouDown();
private:
	void checkPos();
	void checkWhl(); //滚轮事件
	void inline checkEdge() {
		if (cameraPos.x < 0) cameraPos.x = 0;
		else if (cameraPos.x + width > mapSize[scalingLevel][0]) cameraPos.x = mapSize[scalingLevel][0] - width;
		if (cameraPos.y < 0) cameraPos.y = 0;
		else if (cameraPos.y + height > mapSize[scalingLevel][1]) cameraPos.y = mapSize[scalingLevel][1] - height;
	}

	HINSTANCE hInst;
	int width, height;
	HWND hWnd;
	D3DGraphic* D3DGph;
	keyInput* keyInpt;
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
	}cameraPos;
	float mapSize[3][2] = { 
		{640.0f + 512.0f, 480.0f + 384.0f}, 
		{1280.0f + 512.0f, 960.0f + 384.0f}, 
		{2560.0f + 512.0f, 1920.0f + 384.f} 
	};
	short mapID[60][80] = {0}; // (r,c)
	short scalingLevel = 2; // 缩放级别 0-2
	_checkMsg checkMsg;
	short nn = 0; // 0-47;

};