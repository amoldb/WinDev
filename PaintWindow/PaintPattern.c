#include<Windows.h>

#pragma comment (lib, "gdi32.lib")
#pragma comment (lib, "user32.lib")
#pragma comment (lib, "kernel32.lib")

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    static TCHAR szClassName[]   = TEXT("The first paint windows.");
    static TCHAR szWindowCapton[]   = TEXT("All group names.");

    WNDCLASSEX  wndEx;
    MSG         msg;
    ZeroMemory(&wndEx, sizeof(WNDCLASSEX));
    ZeroMemory(&msg, sizeof(MSG));

    HBRUSH      hBrush  = NULL;
    HICON       hIcon   = NULL;
    HICON       hIconSm = NULL;
    HCURSOR     hCursor = NULL;
    HWND        hWnd    = NULL;

    hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
    if(hBrush == NULL)
    {
        MessageBox(
            (HWND)NULL,
            TEXT("Could not obtain brush."),
            TEXT("GetStockObject"),
            MB_ICONERROR
        );
        return(EXIT_FAILURE);
    }

    hIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
    if(hIcon == NULL)
    {
        MessageBox(
            (HWND)NULL,
            TEXT("Could not get icon."),
            TEXT("LoadIcon"),
            MB_ICONERROR
        );
        return(EXIT_FAILURE);
    }

    hIconSm = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
    if(hIconSm == NULL)
    {
        MessageBox(
            (HWND)NULL,
            TEXT("Could not get small icon"),
            TEXT("LoadIcon"),
            MB_ICONERROR
        );
        return(EXIT_FAILURE);
    }

    hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);
    if(hCursor == NULL)
    {
        MessageBox(
            (HWND)NULL,
            TEXT("Could not get cursor."),
            TEXT("LoadCursor"),
            MB_ICONERROR
        );
        return(EXIT_FAILURE);
    }

    wndEx.cbSize        = sizeof(WNDCLASSEX);
    wndEx.cbClsExtra    = 0;
    wndEx.cbWndExtra    = 0;
    wndEx.hbrBackground = hBrush;
    wndEx.hInstance     = hInstance;
    wndEx.hIcon         = hIcon;
    wndEx.hIconSm       = hIconSm;
    wndEx.hCursor       = hCursor;
    wndEx.lpszClassName = szClassName;
    wndEx.lpszMenuName  = NULL;
    wndEx.lpfnWndProc   = WndProc;
    wndEx.style         = CS_HREDRAW | CS_VREDRAW;

    if(!RegisterClassEx(&wndEx))
    {
        MessageBox(
            (HWND)NULL,
            TEXT("Could not register window class."),
            TEXT("RegisterClassEx"),
            MB_ICONERROR
        );
        return(EXIT_FAILURE);
    }

    hWnd = CreateWindowEx(
        WS_EX_APPWINDOW,
        szClassName,
        szWindowCapton,
        WS_OVERLAPPED,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        (HWND)NULL,
        (HMENU)NULL,
        hInstance,
        NULL
    );

    if(hWnd == NULL)
    {
        MessageBox(
            (HWND)NULL,
            TEXT("Could not start application window."),
            TEXT("CreateWindowEx"),
            MB_ICONERROR
        );
        return(EXIT_FAILURE);
    }

    ShowWindow(hWnd, nShowCmd);
    UpdateWindow(hWnd);

    while(GetMessage(&msg, (HWND)NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static int cxSize, cySize;
    PAINTSTRUCT ps;
    HDC hdc;
    int i,j;

    switch(uMsg)
    {
        case WM_SIZE:
            cxSize = LOWORD(lParam);
            cySize = HIWORD(lParam);
            break;
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);

            for(i=1; i<=358; i+=6)
            {
                // Upper Horizontal Line
                MoveToEx(hdc, i, i, NULL);
                LineTo(hdc, (cxSize-i), i);
                // Lower Horizontal Line
                MoveToEx(hdc, i, (cySize-i), NULL);
                LineTo(hdc, (cxSize-i), (cySize-i));
                // Right hand side vertical Horizontal Line
                MoveToEx(hdc, (cxSize-i), i, NULL);
                LineTo(hdc, (cxSize-i), (cySize-i));
                // Left hand side vertical Horizontal Line
                MoveToEx(hdc, i, i, NULL);
                LineTo(hdc, i, (cySize-i));
            }
        
            EndPaint(hWnd, &ps);
            break;
        case WM_DESTROY:
            PostQuitMessage(EXIT_SUCCESS);
            break;
    }
    return(DefWindowProc(hWnd, uMsg, wParam, lParam));
}