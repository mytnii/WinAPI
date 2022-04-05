
#define _CRT_SECURE_NO_WARNINGS

#include<Windows.h>
#include<winapifamily.h>
#include<cstdio>
#include "resource.h"

CONST CHAR* str[] =
{
	"This", "is", "my", "first", "List", "Box"
};

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hComboBox = GetDlgItem(hwnd, IDC_COMBO2);
		for (int i = 0; i < sizeof(str) / sizeof(str[0]); ++i)
		{
			SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)str[i]);
		}
	}
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			CHAR sz_message[SIZE] = {};
			HWND hComboBox = GetDlgItem(hwnd, IDC_COMBO2);
			INT index = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);
			if (!index)
			{
				SendMessage(hComboBox, CB_GETLBTEXT, index, (LPARAM)sz_message);
				sprintf(sz_buffer, "Вы выбрали элемент: № %d со значением \"%s\".", index, sz_message);
				MessageBox(hwnd, sz_buffer, "Info", MB_OK | MB_ICONINFORMATION);
			}
			else
			{
				sprintf(sz_buffer, "Элемент не выбран");
				MessageBox(hwnd, sz_buffer, "Info", MB_OK | MB_ICONINFORMATION);
			}
		}
		break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
	}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return FALSE;
}