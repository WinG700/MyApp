#pragma once
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <tchar.h>
#include <time.h>
using namespace std;

#if _Server
#endif //_Server

#if _Client
#endif //_Client

#define IDC_STATIC1  1001
#define IDC_BUTTON1  1002
#define IDC_EDIT1    1003
#define IDC_FRAME1   1004
#define IDC_MALE     2001
#define IDC_FEMALE   2002
#define IDC_LISTBOX1 1005
#define IDC_CB1      1006
#define IDC_CKBRED   1007
#define IDC_CKBGRN   1008
#define IDC_CKBBLU   1009

static TCHAR szAppName[] = TEXT("HelloWin32");
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

LRESULT OnCreateWindows(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); //创建窗口函数
LRESULT OnCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); //事件反馈函数
LRESULT OnCTLColorStatic(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); //字体背景颜色处理函数

BOOL CALLBACK lpEnumFunc(HWND hwnd, LPARAM lParam);
string TCHAR2STRING(TCHAR *STR);

BOOL OpenEXE();

static map<string, string>::iterator iter_configMap;
static map<string, string> m_mapConfigInfo;

void ConfigFileRead(map<string, string>& m_mapConfigInfo); //读取配置文件后存储到的Map

static SHELLEXECUTEINFO ShExecInfo = { 0 }; //打开ex应用程序的信息

static HBRUSH hBrush; //画刷

static TCHAR szTextBuf[20];
