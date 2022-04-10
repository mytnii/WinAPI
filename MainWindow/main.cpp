#define _CRT_SECURE_NO_WARNINGS

#include<winapifamily.h>
#include<Windows.h>
#include<stdio.h>
#include"resource.h"

constexpr INT STATIC = 104;

CONST CHAR g_szClassName[] = "My Window Class";

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = WndProc;
	wc.style = 0;
	//wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	//wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
	wc.hIconSm = (HICON)LoadImage(hInstance, "bonfire.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hIcon = (HICON)LoadImage(hInstance, "eclips.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hInstance = hInstance;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	INT screen_width = GetSystemMetrics(SM_CXSCREEN);
	INT screen_height = GetSystemMetrics(SM_CYSCREEN);
	INT window_width = screen_width - screen_width / 4;
	INT window_height = screen_height - screen_height / 4;
	INT window_start_x = screen_width / 8;
	INT window_start_y = screen_height / 8;
	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_szClassName,
		"Main Window",
		WS_OVERLAPPEDWINDOW,
		window_start_x, window_start_y,
		window_width, window_height,
		/*CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,*/
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hwnd)
	{
		MessageBox(NULL, "Window creation failed", "info", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		RECT rect;
		GetClientRect(hwnd, &rect);
		CreateWindowEx
		(
			NULL,
			"STATIC",
			"",
			WS_CHILD | WS_VISIBLE,
			rect.top, rect.left,
			1500, 150,
			hwnd,
			(HMENU)STATIC,
			GetModuleHandle(NULL),
			NULL
		);
		
	}
		break;
	case WM_COMMAND: break;
	case WM_SIZE:
	case WM_MOVE:
	{
		CONST INT SIZE = 256;
		CHAR buffer[SIZE]{};
		RECT rect;
		GetWindowRect(hwnd, &rect);
		sprintf(buffer, "%s  position: X %i Y %i, size: %ix%i", "Main Window", rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)buffer);
		SendMessage(GetDlgItem(hwnd, STATIC), WM_SETTEXT, 0, (LPARAM)buffer);
	}
		break;
	case WM_CLOSE: 
		if (MessageBox(hwnd, "Вы действительно хотите закрыть окно?", "Шо, внатуре?", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}