// 包含文件
#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include "Game.h"

// 声明一个Game类的实例
Game* game;

// 主要应用程序实例
HINSTANCE g_hInst;          // 全局实例句柄
HWND g_hWnd;            // 全局窗口句柄

						// 应用程序窗口的大小、类型以及类和窗口的名称
#define WNDWIDTH 800
#define WNDHEIGHT 600
#define WNDTYPE WS_OVERLAPPEDWINDOW
#define WNDCAPTION  "FrameClass"
#define WNDTITLE "FrameCaption"

						// 主要应用程序原型

						// 入口点
int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hPrev, \
	LPSTR szCmdLine, int nCmdShow);

// 消息处理函数
long FAR PASCAL WindowProc(HWND hWnd, UINT uMsg, \
	WPARAM wParam, LPARAM lParam);

// 用于注册窗口类以及取消注册窗口类的函数
BOOL RegisterWindowClasses(HINSTANCE hInst);
BOOL UnregisterWindowClasses(HINSTANCE hInst);

// 用于创建应用程序窗口的函数
HWND CreateMainWindow(HINSTANCE hInst);


int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hPrev, \
	LPSTR szCmdLine, int nCmdShow)
{
	MSG Msg;

	// 保存应用程序实例
	g_hInst = hInst;

	// 注册窗口类——使用 FALSE 进行返回
	if (RegisterWindowClasses(hInst) == FALSE)
		return FALSE;

	// 创建窗口——使用 FALSE 进行返回
	if ((g_hWnd = CreateMainWindow(hInst)) == NULL)
		return FALSE;

	game = new Game(g_hInst, g_hWnd, WNDWIDTH, WNDHEIGHT);
	// 进行应用程序的初始化——使用 FALSE 进行返回
	if (game->DoInit()) {

		// 进入消息泵
		ZeroMemory(&Msg, sizeof(MSG));
		while (Msg.message != WM_QUIT) {
			// 处理 Windows 消息（如果有的话）
			if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE)) {
				TranslateMessage(&Msg);
				DispatchMessage(&Msg);
			}
			else {
				// 进行 pre-frame 处理，如果返回 FALSE 就终止处理
				if (!game->DoPreFrame())
					break;

				// 进行 pre-frame 处理，如果返回 FALSE 就终止处理
				if (!game->DoFrame())
					break;

				// 进行 post-frame 处理，如果返回 FALSE 就终止处理
				if (!game->DoPostFrame())
					break;
			}
		}
	}

	// 执行关闭函数
	game->DoShutdown();
	delete game;

	// 取消注册窗口
	UnregisterWindowClasses(hInst);

	return TRUE;
}

BOOL RegisterWindowClasses(HINSTANCE hInst)
{
	WNDCLASSEX wcex;

	// 这里创建窗口类并注册它
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_CLASSDC;
	wcex.lpfnWndProc = WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInst;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = WNDTITLE;
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
		return FALSE;

	return TRUE;
}

BOOL UnregisterWindowClasses(HINSTANCE hInst)
{
	// 取消注册窗口
	UnregisterClass(WNDTITLE, hInst);
	return TRUE;
}

HWND CreateMainWindow(HINSTANCE hInst)
{
	HWND hWnd;

	// 创建主窗口 (Main Window)
	hWnd = CreateWindow(WNDTITLE, WNDCAPTION, WNDTYPE, 200, 200, WNDWIDTH, WNDHEIGHT, NULL, NULL, hInst, NULL);
	if (!hWnd)
		return NULL;

	// 显示并更新窗口
	ShowWindow(hWnd, SW_NORMAL);
	UpdateWindow(hWnd);

	// 返回窗口句柄
	return hWnd;
}



// 消息处理函数
long FAR PASCAL WindowProc(HWND hWnd, UINT uMsg, \
	WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_MOUSEMOVE:
		game->sendMouPos(LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_MOUSEWHEEL:
		game->sendMouWhl(HIWORD(wParam));
		return 0;
	case WM_LBUTTONDOWN:
		game->actMouDown();
		return 0;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

