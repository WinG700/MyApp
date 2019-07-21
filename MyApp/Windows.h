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

LRESULT OnCreateWindows(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); //�������ں���
LRESULT OnCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); //�¼���������
LRESULT OnCTLColorStatic(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); //���屳����ɫ������

BOOL CALLBACK lpEnumFunc(HWND hwnd, LPARAM lParam);
string TCHAR2STRING(TCHAR *STR);

BOOL OpenEXE();

static map<string, string>::iterator iter_configMap;
static map<string, string> m_mapConfigInfo;

void ConfigFileRead(map<string, string>& m_mapConfigInfo); //��ȡ�����ļ���洢����Map

static SHELLEXECUTEINFO ShExecInfo = { 0 }; //��exӦ�ó������Ϣ

static HBRUSH hBrush; //��ˢ

static TCHAR szTextBuf[20];
