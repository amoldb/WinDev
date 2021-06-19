#include<Windows.h>
#include<stdio.h>
#include "StringVector.h"

#pragma comment (lib, "user32.lib")
#pragma comment (lib, "kernel32.lib")
#pragma comment (lib, "gdi32.lib")

#define 	bSize		256
#define		xOffSet		4
#define		xStart		0

LRESULT CALLBACK WndProc(
                        HWND hWnd,
                        UINT uMsg,
                        WPARAM wParam,
                        LPARAM lParam
                );

PSTRINGVECTOR ReadFileInMemory(LPSTR lpFileName);
void ReleaseAll(void);
// Global handles
LPSTR glpCmdLine = NULL;
PSTRINGVECTOR gpStrVec = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	static TCHAR szClassName[]      = TEXT("File reader.");
	static TCHAR szWindowCaption[]  = TEXT("First file reader.");
	
        WNDCLASSEX	wndEx;
        MSG		msg;

        glpCmdLine = lpCmdLine;

        ZeroMemory(&wndEx, sizeof(WNDCLASSEX));	
        ZeroMemory(&msg, sizeof(&msg));

        HICON		hIcon	= NULL;
        HICON		hIconSm	= NULL;
        HCURSOR		hCursor	= NULL;
        HBRUSH		hBrush	= NULL;
        HWND 		hWnd	= NULL;
        ATOM 		bIsWindowClassRegistered = 0;

        hBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);
        if(hBrush == NULL)
        {
                MessageBox(
                        (HWND)NULL,
                        TEXT("Failed to obtain brush."),
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
                        TEXT("Failed to get cursor."),
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
                        TEXT("Failed to get icon."),
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
                        TEXT("Failed to get small icon."),
                        TEXT("LoadIcon"),
                        MB_ICONERROR
                );
                return(EXIT_FAILURE);
        }

        wndEx.cbSize		= sizeof(WNDCLASSEX);
        wndEx.cbClsExtra	= 0;
        wndEx.cbWndExtra	= 0;
        wndEx.hIcon			= hIcon;
        wndEx.hIconSm		= hIconSm;
        wndEx.hInstance		= hInstance;
        wndEx.hbrBackground	= hBrush;
        wndEx.hCursor		= hCursor;
        wndEx.lpszClassName	= szClassName;
        wndEx.lpszMenuName	= NULL;
        wndEx.lpfnWndProc	= WndProc;
        wndEx.style			= CS_HREDRAW | CS_VREDRAW;

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
                        szWindowCaption,
                        WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | 
                        WS_MAXIMIZEBOX | WS_SYSMENU | WS_THICKFRAME | WS_VSCROLL,
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

        while(GetMessage(&msg, (HWND)NULL,0, 0))
        {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
        }

        ReleaseAll();
        return(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
        static int  cxChar, cyChar, cxCaps;
        static int  cxClient, cyClient, iVscollPos = 0;
	int         iVerPos, iPaintBeg, iPaintEnd;
        HDC         hdc = NULL;
        FILE*       fp = NULL;
        int         iCnt=0;
        char        chBuffer[bSize];
        char        chLineNumberBuffer[xOffSet];
        char*       pchBuffer = NULL;
        TEXTMETRIC  tm;
        PAINTSTRUCT ps;

        switch(uMsg)
        {
                case WM_CREATE:
                        SCROLLINFO si;
                        hdc = GetDC(hWnd);

                        GetTextMetrics(hdc, &tm);
                        cxChar = tm.tmAveCharWidth;
                        cyChar = tm.tmHeight + tm.tmExternalLeading;
                        cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar/2;
                        ReleaseDC(hWnd, hdc);
                        hdc = NULL;

                        gpStrVec    = ReadFileInMemory(glpCmdLine);

                        SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
                        SetScrollPos(hWnd, SB_VERT, iVscollPos, TRUE);
                        break;

                case WM_SIZE:
                        cxClient    = LOWORD(lParam);
                        cyClient    = HIWORD(lParam);
                        si.cbSize   = sizeof (si);
                        si.fMask    = SIF_RANGE | SIF_PAGE;
                        si.nMin     = 0;
                        si.nMax     = gpStrVec->iVectorSize - 1;
                        si.nPage    = cyClient / cyChar;
                        SetScrollInfo (hWnd, SB_VERT, &si, TRUE);
                        break;

                case WM_VSCROLL:
                        si.cbSize   = sizeof(SCROLLINFO);
                        si.fMask    = SIF_ALL;
                        GetScrollInfo (hWnd, SB_VERT, &si);
                        iVerPos     = si.nPos;
                        switch(LOWORD(wParam))
                        {
                                case SB_TOP:
                                        si.nPos = si.nMin;
                                        break;
                                case SB_BOTTOM:
                                        si.nPos = si.nMax;
                                        break;
                                case SB_LINEUP:
                                        si.nPos -= 1;
                                        break;
                                case SB_LINEDOWN:
                                        si.nPos += 1;
                                        break;
                                case SB_PAGEUP:
                                        si.nPos -= si.nPage;
                                        break;
                                case SB_PAGEDOWN:
                                        si.nPos += si.nPage;
                                        break;
                                case SB_THUMBTRACK:
                                        si.nPos = si.nTrackPos;
                                        break;
                                default:
                                        break;
                        }

                        si.fMask = SIF_POS;
                        SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
                        GetScrollInfo(hWnd, SB_VERT, &si);

                        if(si.nPos != iVerPos)
                        {
                                ScrollWindow(
                                        hWnd,
                                        0,
                                        cyChar*(iVerPos-si.nPos),
                                        NULL,
                                        NULL
                                );
                                UpdateWindow(hWnd);
                        }

                        break;

                case WM_PAINT:
                        hdc = BeginPaint(hWnd, &ps);
                        si.cbSize   = sizeof(si);
                        si.fMask    = SIF_POS;

                        GetScrollInfo(hWnd, SB_VERT, &si);
                        iVerPos     = si.nPos;

                        iPaintBeg = max(0, iVerPos + ps.rcPaint.top / cyChar);
                        iPaintEnd = min(gpStrVec->iVectorSize,
                        iVerPos + ps.rcPaint.bottom / cyChar);

			SetBkMode(hdc, TRANSPARENT);
			for(iCnt=iPaintBeg; iCnt<gpStrVec->iVectorSize; ++iCnt)
			{
                                pchBuffer = itoa(iCnt+1, chLineNumberBuffer, 10);
				TextOutA(
                                        hdc,
                                        xStart,
                                        ((iCnt - iVerPos) * cyChar),
                                        pchBuffer, strlen(pchBuffer)
                                );
                		TextOutA(
                                        hdc,
					(xOffSet * cxCaps),
					cyChar * (iCnt - iVerPos),
					gpStrVec->ppStringVector[iCnt],
					strlen(gpStrVec->ppStringVector[iCnt])
				);
			}
                        EndPaint(hWnd, &ps);
                        hdc = NULL;
                        break;

                case WM_DESTROY:
                        PostQuitMessage(0);
                        break;
        }
        return(DefWindowProc(hWnd, uMsg, wParam, lParam));
}

PSTRINGVECTOR ReadFileInMemory(LPSTR lpFileName)
{
        #define BUFFER_SIZE 128
        FILE* fp = NULL;
        CHAR chBuffer[BUFFER_SIZE];
        PCHAR pStr = NULL;
        int iStrLen;

        fp = fopen(lpFileName, "r");
        EXIT_IF_FAIL(
                fp == NULL,
                "Could not open file.",
                "fopen"
        );

        gpStrVec = CreateStringVector();
        memset(chBuffer, 0, BUFFER_SIZE);

        while(fgets(chBuffer, BUFFER_SIZE, fp) != NULL)
        {
                iStrLen = strnlen_s(chBuffer, BUFFER_SIZE);
                pStr = (PCHAR)Xcalloc(1, iStrLen+1);
                strncpy(pStr, chBuffer,iStrLen);
                PushBack(gpStrVec, pStr);
                memset(chBuffer, 0, BUFFER_SIZE);
        }

        fclose(fp);
        fp = NULL;

        return(gpStrVec);
}

void ReleaseAll(void)
{
        if(gpStrVec != NULL)
        {
                DestroyVector(gpStrVec);
                gpStrVec = NULL;
        }
}