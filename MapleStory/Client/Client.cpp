// Client.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Client.h"
#include "Maingame.h"

#define MAX_LOADSTRING 100

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

// 전역 변수
HWND		g_hWnd;
wchar_t		g_ipbuf[50];		// ip 입력 받는 버퍼
wchar_t		g_nicknamebuf[50];	// 닉네임 입력
bool		g_bIsProgramEnd = false;

HINSTANCE hInst;						// 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];			// 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];	// 기본 창 클래스 이름입니다.

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow){
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
        return FALSE;

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;
	msg.message = WM_NULL;

	// 메인게임 클래스 생성.
	CMaingame mainGame;
	mainGame.Initialize();

	// GetTickCount : 운영체제가 시작됐을 때부터 흘러온 시간을 1/1000초 단위의
	// 정수형으로 반환
	DWORD dwOldTime = GetTickCount();
	DWORD dwCurTime = 0;

	TCHAR szFPS[32] = __T("");
	DWORD dwFPSOldTime = GetTickCount();
	DWORD dwFPSCurTime = 0;
	int   iFps = 0;

	while (WM_QUIT != msg.message)
	{
		dwFPSCurTime = GetTickCount();

		if (dwFPSOldTime + 1000 < dwFPSCurTime)
		{
			dwFPSOldTime = dwFPSCurTime;
			swprintf_s(szFPS, __T("FPS: %d"), iFps);
			SetWindowText(g_hWnd, szFPS);
			iFps = 0;
		}

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurTime = GetTickCount();
			if (dwOldTime + 15 < dwCurTime)
			{
				dwOldTime = dwCurTime;

				mainGame.Update();
				mainGame.Render();

				iFps++;
			}
		}

		if (g_bIsProgramEnd == true)
			break;
	}

    return (int) msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize			= sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL; /*MAKEINTRESOURCEW(IDC_CLIENT);*/
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석: 이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//         주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	// 윈도우 크기 정보 담는 렉트.
	RECT rc = { 0, 0, WINCX, WINCY };

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
		return FALSE;

	// 생성한 hWnd를 글로벌 변수 g_hWnd에 넣어 준다.
	g_hWnd = hWnd;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int count{ 0 };
	static int count_id{ 0 };
	switch (message)
	{
	case WM_CHAR:
	{
		SCENE_TYPE type = CSceneMgr::GetInstance()->GetSceneType();
		switch (type) {
		case SCENE_LOGO:
			g_ipbuf[count++] = wParam;
			g_ipbuf[count] = '\0';
			break;
		case SCENE_MAKINGPLAYER:
			g_nicknamebuf[count_id++] = wParam;
			g_nicknamebuf[count_id] = '\0';
			break;
		}
	}
	break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
