#include "Windows.h"

#if _Server
#include "server.h"
#endif

#if _Client
#include "client.h"
#endif

//LARGE_INTEGER* getTime()
//{
//	time_t timep;
//	time(&timep);
//	char tmp[64];
//	tm tmm;
//	localtime_s(&tmm, &timep);
//	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", /*localtime(&timep))*/	&tmm);
//	LARGE_INTEGER* lpFrequency = new LARGE_INTEGER;
//	if (!QueryPerformanceFrequency(lpFrequency))
//	{
//		printf("Get Time false\n");
//	}
//	return lpFrequency;
//}

int main()
{
	HWND     hWnd;
	MSG      msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = GetModuleHandle(0);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	ConfigFileRead(m_mapConfigInfo);


	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
		return 0;
	}

	hWnd = CreateWindow(szAppName,                  // window class name
		szAppName,                 // window caption
		WS_OVERLAPPEDWINDOW,        // window style
		CW_USEDEFAULT,              // initial x position
		CW_USEDEFAULT,              // initial y position
		800,              // initial x size
		600,              // initial y size
		NULL,                       // parent window handle
		NULL,                       // window menu handle
		GetModuleHandle(0),                // program instance handle
		NULL);                     // creation parameters

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	//OpenEXE();

#if _Server
//初始化服务器
	if (!initSever())
	{
		exitServer();
		return SERVER_SETUP_FAIL;
	}

	//启动服务
	if (!startService())
	{
		showServerStartMsg(FALSE);
		exitServer();
		return SERVER_SETUP_FAIL;
	}

	//处理数据
	//inputAndOutput();

	//退出主线程，清理资源
	exitServer();
#endif

#if _Client
	//初始化
	if (!InitClient())
	{
		ExitClient();
	}

	//连接服务器
	if (ConnectServer())
	{
		ShowConnectMsg(TRUE);
	}
	else
	{
		ShowConnectMsg(FALSE);
		ExitClient();
	}

	//创建发送和接收数据线程
	if (!CreateSendAndRecvThread())
	{
		ExitClient();

	}

	//用户输入数据和显示结果
	//InputAndOutput();
#endif

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		return OnCreateWindows(hWnd, message, wParam, lParam);

	case WM_COMMAND:
		return OnCommand(hWnd, message, wParam, lParam);

	case WM_CTLCOLORSTATIC:
		return OnCTLColorStatic(hWnd, message, wParam, lParam);

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

