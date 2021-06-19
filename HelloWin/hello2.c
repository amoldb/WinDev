#include<Windows.h>

#pragma comment (lib, "gdi32.lib")
#pragma comment (lib, "user32.lib")
#pragma comment (lib, "kernel32.lib")

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    static TCHAR szClassName[]      = TEXT("The first window");
    static TCHAR szWindowCaption[]  = TEXT("AAICHYA GAAVAT!");

    WNDCLASSEX  wndEx;
    MSG         msg;
    ZeroMemory(&wndEx, sizeof(WNDCLASSEX));
    ZeroMemory(&msg, sizeof(MSG));

    HBRUSH      hBrush      = NULL;
    HICON       hIcon       = NULL;
    HWND        hWnd        = NULL;
    HICON       hIconSm     = NULL;
    HCURSOR     hCursor     = NULL;

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
    if(hIcon == NULL)
    {
        MessageBox(
            (HWND)NULL,
            TEXT("Could not get small icon."),
            TEXT("LoadIcon"),
            MB_ICONERROR
        );
        return(EXIT_FAILURE);
    }

    wndEx.cbSize        = sizeof(WNDCLASSEX);
    wndEx.cbClsExtra    = 0;
    wndEx.cbWndExtra    = 0;
    wndEx.hInstance     = hInstance;
    wndEx.hCursor       = hCursor;
    wndEx.hIcon         = hIcon;
    wndEx.hIconSm       = hIconSm;
    wndEx.hbrBackground = hBrush;
    wndEx.lpszMenuName  = NULL;
    wndEx.lpszClassName = szClassName;
    wndEx.lpfnWndProc   = WndProc;
    wndEx.style         = CS_HREDRAW | CS_VREDRAW;

    if(!RegisterClassEx(&wndEx))
    {
        MessageBox(
            (HWND)NULL,
            TEXT("Could not create window class"),
            TEXT("RegisterClassEx"),
            MB_ICONERROR
        );
        return(EXIT_FAILURE);
    }

    hWnd = CreateWindowEx(
        WS_EX_APPWINDOW,
        szClassName,
        szWindowCaption,
        WS_OVERLAPPEDWINDOW,
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
            TEXT("Could not create appplication window."),
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
    switch(uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(EXIT_SUCCESS);
            break;
    }
    return(DefWindowProc(hWnd, uMsg, wParam, lParam));  
}