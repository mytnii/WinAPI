#define _CRT_SECURE_NO_WARNINGS

#include<Windows.h>
#include<winapifamily.h>
#include<cstdio>
#include"resource.h"

CONST CHAR* string[] =
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
		HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
		for (int i = 0; i < sizeof(string) / sizeof(string[0]); ++i)
		{
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)string[i]);
		}
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			CHAR sz_message[SIZE] = {};

			HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
			int index = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			SendMessage(hListBox, LB_GETTEXT, index, (LPARAM)sz_buffer);
			sprintf(sz_message, "Вы выбрали элемент: № %d со значением \"%s\".", index, sz_buffer);
			MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
		}
			break;
		case IDCANCEL:EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return FALSE;
}