#include "Windows.h"

BOOL CALLBACK lpEnumFunc(HWND hwnd, LPARAM lParam)
{
	string str;
	TCHAR kTextBuf[20] = { 0 };
	GetClassName(hwnd, kTextBuf, 20);
	str = TCHAR2STRING(kTextBuf);
	if (str.find("Unreal") != string::npos)
	{
		printf("%s\n", str.c_str());
		PostMessage(hwnd, WM_KEYDOWN, 84, 1);
	}
	//for (int i=0; i<20 ;i++)
	//{
	//	printf("%c", kTextBuf[i]);
	//}
	//printf("\n");
	//SendMessage(hwnd, WM_KEYDOWN, VK_F5, 1);

	return 1;
}

string TCHAR2STRING(TCHAR *STR)
{

	int iLen = WideCharToMultiByte(CP_ACP, 0, STR, -1, NULL, 0, NULL, NULL);

	char* chRtn = new char[iLen * sizeof(char)];

	WideCharToMultiByte(CP_ACP, 0, STR, -1, chRtn, iLen, NULL, NULL);

	std::string str(chRtn);

	return str;

}

BOOL OpenEXE()
{
	//打开外部exe应用程序
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = L"E:/SecurityRoom/SecurityRoom201805281342/RVR/Binaries/Win64/RVR.exe";
	ShExecInfo.lpParameters = L"";
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_SHOW;
	ShExecInfo.hInstApp = NULL;

	return ShellExecuteEx(&ShExecInfo);
}

LRESULT OnCreateWindows(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hCtrl;

	CreateWindow(TEXT("STATIC"), L"Test String", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | SS_CENTERIMAGE, 10, 10, 80, 20, hWnd, (HMENU)IDC_STATIC1, NULL, NULL);
	CreateWindow(TEXT("BUTTON"), TEXT("Click Me"), WS_CHILD | WS_VISIBLE, 10, 40, 80, 20, hWnd, (HMENU)IDC_BUTTON1, NULL, NULL);
	//CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 70, 80, 20, hWnd, (HMENU)IDC_EDIT1, NULL, NULL);

	CreateWindow(TEXT("BUTTON"), TEXT("性别"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 120, 10, 130, 50, hWnd, (HMENU)IDC_FRAME1, NULL, NULL);
	CreateWindow(TEXT("BUTTON"), TEXT("男"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 134, 30, 40, 20, hWnd, (HMENU)IDC_MALE, NULL, NULL);
	CreateWindow(TEXT("BUTTON"), TEXT("女"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 194, 30, 40, 20, hWnd, (HMENU)IDC_FEMALE, NULL, NULL);

	CreateWindow(TEXT("BUTTON"), TEXT("红色"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_AUTOCHECKBOX, 120, 70, 54, 20, hWnd, (HMENU)IDC_CKBRED, NULL, NULL);
	CreateWindow(TEXT("BUTTON"), TEXT("绿色"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_AUTOCHECKBOX, 180, 70, 54, 20, hWnd, (HMENU)IDC_CKBGRN, NULL, NULL);
	CreateWindow(TEXT("BUTTON"), TEXT("蓝色"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_AUTOCHECKBOX, 240, 70, 54, 20, hWnd, (HMENU)IDC_CKBBLU, NULL, NULL);

	hCtrl = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("LISTBOX"), NULL, WS_CHILD | WS_VISIBLE | LBS_STANDARD, 10, 100, 80, 90, hWnd, (HMENU)IDC_LISTBOX1, NULL, NULL);
	SendMessage(hCtrl, LB_ADDSTRING, 0, (LPARAM)TEXT("list str1"));
	SendMessage(hCtrl, LB_ADDSTRING, 0, (LPARAM)TEXT("list str2"));
	SendMessage(hCtrl, LB_ADDSTRING, 0, (LPARAM)TEXT("list str3"));
	SendMessage(hCtrl, LB_ADDSTRING, 0, (LPARAM)TEXT("list str4"));

	hCtrl = CreateWindow(TEXT("COMBOBOX"), NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_AUTOHSCROLL | CBS_DROPDOWNLIST, 120, 100, 100, 90, hWnd, (HMENU)IDC_CB1, NULL, NULL);
	SendMessage(hCtrl, CB_ADDSTRING, 0, (LPARAM)TEXT("comb str1"));
	SendMessage(hCtrl, CB_ADDSTRING, 0, (LPARAM)TEXT("comb str2"));
	SendMessage(hCtrl, CB_ADDSTRING, 0, (LPARAM)TEXT("comb str3"));
	SendMessage(hCtrl, CB_ADDSTRING, 0, (LPARAM)TEXT("comb str4"));
	SendMessage(hCtrl, CB_SETCURSEL, 1, 0);

	return 0;
}

LRESULT OnCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hwndTmp;
	int wmId = LOWORD(wParam);
	switch (wmId)
	{
	case IDC_BUTTON1:
		hwndTmp = GetDlgItem(hWnd, IDC_STATIC1);
		HWND h1 = GetDlgItem(hWnd, IDC_MALE);
		HWND h2 = GetDlgItem(hWnd, IDC_FEMALE);
		RECT* rect = new RECT;
		if (SendMessage(h1, BM_GETCHECK, 0, 0))
		{
			RECT rect;
			GetClientRect(hwndTmp, &rect);
			MapWindowPoints(hwndTmp, hWnd, (POINT *)&rect, 2);
			InvalidateRect(hWnd, &rect, TRUE);
			//RedrawWindow(hWnd, &rect, NULL, RDW_ERASE | RDW_INVALIDATE);
			wsprintf(szTextBuf, L"男");
			SetWindowText(hwndTmp, szTextBuf);
		}
		else if (SendMessage(h2, BM_GETCHECK, 0, 0))
		{
			RECT rect;
			GetClientRect(hwndTmp, &rect);
			MapWindowPoints(hwndTmp, hWnd, (POINT *)&rect, 2);
			InvalidateRect(hWnd, &rect, TRUE);
			wsprintf(szTextBuf, L"女");
			SetWindowText(hwndTmp, szTextBuf);
		}
		//EnumWindows(lpEnumFunc, NULL);
		/*	bool b = TerminateProcess(ShExecInfo.hProcess, NULL);
			printf("Shutdown exe success : %s", b ? "true" : "false");*/
		MessageBox(hWnd, TEXT("Text Changed!"), TEXT("info"), MB_OK);
		break;
	}
	return 0;
}

LRESULT OnCTLColorStatic(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc = (HDC)wParam;
	SetTextColor(hdc, RGB(0xFF, 0x00, 0x00));
	SetBkMode(hdc, TRANSPARENT);

	HWND hwndTmp = GetDlgItem(hWnd, IDC_STATIC1);
	if ((int)hwndTmp == (int)lParam)
	{
		hBrush = CreateSolidBrush(RGB(0x41, 0x96, 0x4F));
		return (INT_PTR)hBrush;
	}

	return (BOOL)((HBRUSH)GetStockObject(NULL_BRUSH));
}

void ConfigFileRead(map<string, string>& m_mapConfigInfo)
{
	ifstream configFile;
	string path = "conf/Setting.ini";
	configFile.open(path.c_str());
	string str_line;
	if (configFile.is_open())
	{
		while (!configFile.eof())
		{
			getline(configFile, str_line);
			if (str_line.compare(0, 1, "[") == 0)
			{
				continue;
			}
			size_t pos = str_line.find('=');
			string str_key = str_line.substr(0, pos);
			string str_value = str_line.substr(pos + 1);
			m_mapConfigInfo.insert(pair<string, string>(str_key, str_value));
		}
		/*cout << "open config file Setting.ini success" << endl;*/
		printf("open config file Setting.ini success \n");
	}
	else
	{
		printf("Cannot open config file Setting.ini, path: %s\n", path.c_str());
		/*cout << "Cannot open config file Setting.ini, path:" << endl;*/
		/*exit(-1);*/
	}
}
