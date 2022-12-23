#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("DesktopApp");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Таблиця");

// Stored instance handle for use in Win32 API calls such as FindResource
HINSTANCE hInst;

// Flag to be switched
BOOL bFlag = TRUE;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // Store instance handle in our global variable
    hInst = hInstance;

    // The parameters to CreateWindowEx explained:
    // WS_EX_OVERLAPPEDWINDOW : An optional extended window style.
    // szWindowClass: the name of the application
    // szTitle: the text that appears in the title bar
    // WS_OVERLAPPEDWINDOW: the type of window to create
    // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
    // 500, 100: initial size (width, length)
    // NULL: the parent of this window
    // NULL: this application does not have a menu bar
    // hInstance: the first parameter from WinMain
    // NULL: not used in this application
    HWND hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        500, 150,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // The parameters to ShowWindow explained:
    // hWnd: the value returned from CreateWindow
    // nCmdShow: the fourth parameter from WinMain
    ShowWindow(hWnd,
        nCmdShow);
    UpdateWindow(hWnd);

    UINT_PTR TimerID = SetTimer(hWnd, 101, 20000, NULL);

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR line1[] = _T("  1,   2,   3");
    TCHAR line2[] = _T("  4,   5,   6");
    TCHAR line3[] = _T("  7,   8,   9");
    TCHAR line4[] = _T("10, 11, 12");
    TCHAR line5[] = _T("Почекайте 20 секунд, поки таблиця зникне.");
    TCHAR line6[] = _T("Вона знову з'явиться через 20 секунд.");
    TCHAR line7[] = _T("                    ");


    switch (message)
    {
    case WM_PAINT:

        hdc = BeginPaint(hWnd, &ps);

        if (bFlag == TRUE)
        {
            TextOut(hdc, 5, 5, line1, _tcslen(line1));
            TextOut(hdc, 5, 20, line2, _tcslen(line2));
            TextOut(hdc, 5, 35, line3, _tcslen(line3));
            TextOut(hdc, 5, 50, line4, _tcslen(line4));
            TextOut(hdc, 5, 65, line5, _tcslen(line5));
            TextOut(hdc, 5, 80, line6, _tcslen(line6));

        }
        else
        {
            TextOut(hdc, 5, 5, line7, _tcslen(line7));
            TextOut(hdc, 5, 20, line7, _tcslen(line7));
            TextOut(hdc, 5, 35, line7, _tcslen(line7));
            TextOut(hdc, 5, 50, line7, _tcslen(line7));

        }
        EndPaint(hWnd, &ps);
        break;
    case WM_TIMER:
        bFlag = !bFlag;
        InvalidateRect(hWnd, NULL, NULL);
        break;
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;

}