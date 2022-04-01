#include<Windows.h>
#include <winapifamily.h>
#include"resource.h"

CHAR sz_login_invitation[] = "Введите логин";
CHAR sz_password_invitation[] = "Введите пароль";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMgs, WPARAM wParam, LPARAM lPARAM);

INT WINAPI WinMain(HINSTANCE hInstanse, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	/*MessageBox
	(
		NULL, "HelloWorld", "Info", MB_YESNOCANCEL |
		MB_ICONERROR | MB_HELP | MB_DEFBUTTON4 | 
		MB_SYSTEMMODAL | MB_SETFOREGROUND
	);*/

	DialogBoxParam(hInstanse, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMgs, WPARAM wParam, LPARAM lPARAM)
{
	switch (uMgs)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		SendMessage(GetDlgItem(hwnd,IDC_EDIT_LOGIN), WM_SETTEXT, 0, (LPARAM)sz_login_invitation);
		SendMessage(GetDlgItem(hwnd,IDC_EDIT_PASSWORD), WM_SETTEXT, 0, (LPARAM)sz_password_invitation);
	}
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN:
		{
			switch (HIWORD(wParam))
			{
			case EN_SETFOCUS:
				SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_SETTEXT, 0, (LPARAM)"");
				break;
			case EN_KILLFOCUS:
				SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_SETTEXT, 0, (LPARAM)sz_login_invitation);
				break;
			}
		}
		break;
		case IDC_BUTTON_COPY:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			SendMessage(hLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			HWND hPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			SendMessage(hPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
			break;
		case IDC_BUTTON_SET_TITLE:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			//SendMessage(FindWindow(NULL, "WinAPI -"), WM_SETTEXT, 0, (LPARAM)sz_buffer);
			
		}
		break;
		case IDOK:MessageBox(NULL, "Была нажата кнопка ОК", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
	}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}