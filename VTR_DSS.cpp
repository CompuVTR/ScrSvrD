#include "VTR_DSS.h"
#include "VTR_rsrc.h"

#define MAX_LOADSTRING 100
#define	WM_USER_SHELLICON WM_USER + 1

// Global Variables:
HINSTANCE hInst;				                // current instance
NOTIFYICONDATA nidApp;
HMENU hPopMenu;
TCHAR szTitle[MAX_LOADSTRING];			        // The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];		    // the main window class name
TCHAR szApplicationToolTip[MAX_LOADSTRING];	    // the main window class name
BOOL  ScrSvrOFF = FALSE;			            // Screen Saver state


ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine,int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	
	MSG msg;
	
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_VTRDSS, szWindowClass, MAX_LOADSTRING);
	
	MyRegisterClass(hInstance);
	InitInstance(hInstance, nCmdShow);
	
	while (GetMessage(&msg, NULL, 0, 0))
	{
		
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		
	}

	return (int)msg.wParam;
}




ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LRG));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_VTRDSS);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SML));

	return RegisterClassEx(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND  hWnd;
   HICON hMainIcon;

   hInst = hInstance;

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   // Icon downloaded from "https://www.iconarchive.com/show/junior-icons-by-treetog/monitor-helix-icon.html"
   hMainIcon = LoadIcon(hInstance,(LPCTSTR)MAKEINTRESOURCE(IDI_LRG)); 

   nidApp.cbSize = sizeof(NOTIFYICONDATA);
   nidApp.hWnd = (HWND)hWnd;
   nidApp.uID = IDI_LRG;
   nidApp.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
   nidApp.hIcon = hMainIcon;
   nidApp.uCallbackMessage = WM_USER_SHELLICON; 
   LoadString(hInstance, IDS_APPTOOLTIP,nidApp.szTip,MAX_LOADSTRING);
   Shell_NotifyIcon(NIM_ADD, &nidApp); 

   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    POINT MouseLoc;
	switch (message)
	{
		case WM_USER_SHELLICON: 
			switch(LOWORD(lParam)) 
			{   
				case WM_RBUTTONDOWN: 
					GetCursorPos(&MouseLoc);
					hPopMenu = CreatePopupMenu();
			
					if ( ScrSvrOFF == TRUE )
					{
						InsertMenu(hPopMenu,1,MF_BYPOSITION|MF_STRING,IDM_ENABLE,_T("Enable Screen Saver"));									
					}
					else 
					{
						InsertMenu(hPopMenu,1,MF_BYPOSITION|MF_STRING,IDM_DISABLE,_T("Disable Screen Saver"));				
					}

					InsertMenu(hPopMenu, 2, MF_BYPOSITION | MF_STRING, IDM_ABOUT, _T("About"));

					InsertMenu(hPopMenu,3,MF_SEPARATOR,IDM_SPRT,_T("SPRT"));

					InsertMenu(hPopMenu,4,MF_BYPOSITION|MF_STRING,IDM_EXIT,_T("Exit"));
									
					SetForegroundWindow(hWnd);
					TrackPopupMenu(hPopMenu,TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_BOTTOMALIGN,MouseLoc.x, MouseLoc.y,0,hWnd,NULL);
					return TRUE; 
			}
			break;

		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case IDM_ABOUT:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
					break;
				case IDM_DISABLE:
					ScrSvrOFF = TRUE;
					DisableScreenSaver();
					break;
				case IDM_ENABLE:
					ScrSvrOFF = FALSE;
					EnableScreenSaver();
					break;
				case IDM_EXIT:
					Shell_NotifyIcon(NIM_DELETE,&nidApp);
					DestroyWindow(hWnd);
					break;
				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
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

// Message handler for about box.
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
