// �����ļ�
#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include "Game.h"

// ����һ��Game���ʵ��
Game* game;

// ��ҪӦ�ó���ʵ��
HINSTANCE g_hInst;          // ȫ��ʵ�����
HWND g_hWnd;            // ȫ�ִ��ھ��

						// Ӧ�ó��򴰿ڵĴ�С�������Լ���ʹ��ڵ�����
#define WNDWIDTH 800
#define WNDHEIGHT 600
#define WNDTYPE WS_OVERLAPPEDWINDOW
#define WNDCAPTION  "FrameClass"
#define WNDTITLE "FrameCaption"

						// ��ҪӦ�ó���ԭ��

						// ��ڵ�
int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hPrev, \
	LPSTR szCmdLine, int nCmdShow);

// ��Ϣ������
long FAR PASCAL WindowProc(HWND hWnd, UINT uMsg, \
	WPARAM wParam, LPARAM lParam);

// ����ע�ᴰ�����Լ�ȡ��ע�ᴰ����ĺ���
BOOL RegisterWindowClasses(HINSTANCE hInst);
BOOL UnregisterWindowClasses(HINSTANCE hInst);

// ���ڴ���Ӧ�ó��򴰿ڵĺ���
HWND CreateMainWindow(HINSTANCE hInst);


int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hPrev, \
	LPSTR szCmdLine, int nCmdShow)
{
	MSG Msg;

	// ����Ӧ�ó���ʵ��
	g_hInst = hInst;

	// ע�ᴰ���ࡪ��ʹ�� FALSE ���з���
	if (RegisterWindowClasses(hInst) == FALSE)
		return FALSE;

	// �������ڡ���ʹ�� FALSE ���з���
	if ((g_hWnd = CreateMainWindow(hInst)) == NULL)
		return FALSE;

	game = new Game(g_hInst, g_hWnd, WNDWIDTH, WNDHEIGHT);
	// ����Ӧ�ó���ĳ�ʼ������ʹ�� FALSE ���з���
	if (game->DoInit()) {

		// ������Ϣ��
		ZeroMemory(&Msg, sizeof(MSG));
		while (Msg.message != WM_QUIT) {
			// ���� Windows ��Ϣ������еĻ���
			if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE)) {
				TranslateMessage(&Msg);
				DispatchMessage(&Msg);
			}
			else {
				// ���� pre-frame ����������� FALSE ����ֹ����
				if (!game->DoPreFrame())
					break;

				// ���� pre-frame ����������� FALSE ����ֹ����
				if (!game->DoFrame())
					break;

				// ���� post-frame ����������� FALSE ����ֹ����
				if (!game->DoPostFrame())
					break;
			}
		}
	}

	// ִ�йرպ���
	game->DoShutdown();
	delete game;

	// ȡ��ע�ᴰ��
	UnregisterWindowClasses(hInst);

	return TRUE;
}

BOOL RegisterWindowClasses(HINSTANCE hInst)
{
	WNDCLASSEX wcex;

	// ���ﴴ�������ಢע����
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
	// ȡ��ע�ᴰ��
	UnregisterClass(WNDTITLE, hInst);
	return TRUE;
}

HWND CreateMainWindow(HINSTANCE hInst)
{
	HWND hWnd;

	// ���������� (Main Window)
	hWnd = CreateWindow(WNDTITLE, WNDCAPTION, WNDTYPE, 200, 200, WNDWIDTH, WNDHEIGHT, NULL, NULL, hInst, NULL);
	if (!hWnd)
		return NULL;

	// ��ʾ�����´���
	ShowWindow(hWnd, SW_NORMAL);
	UpdateWindow(hWnd);

	// ���ش��ھ��
	return hWnd;
}



// ��Ϣ������
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

