#include<Windows.h>
#include<stdio.h>

#pragma comment (lib, "gdi32.lib")
// #pragma comment (lib, "user32.lib")
#pragma comment (lib, "kernel32.lib")

typedef int (*lpfnMessageBox)(HWND, LPCSTR, LPCSTR, UINT);
void* xLoadLibrary(LPCSTR, LPCSTR);
void* xFreeLibrary(void*);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    lpfnMessageBox msgBox;
    msgBox = (lpfnMessageBox)xLoadLibrary("MessageBoxA", "user32.dll");
    // OutputDebugStringW(L"__DBG__1");
    msgBox(
        (HWND)NULL,
        TEXT("Hello message box!"),
        TEXT("First message box.. yey!"),
        MB_OK
    );
    xFreeLibrary(msgBox);
}

void* xLoadLibrary(LPCSTR funcName, LPCSTR libName)
{
    HMODULE hModule;
    lpfnMessageBox funcAddress;
    
    hModule = (HMODULE)LoadLibraryA(libName);
    if (hModule == NULL)
    {
        printf("ERROR\n");
        return(NULL);
    }
    
    funcAddress = (lpfnMessageBox) GetProcAddress(hModule, funcName);
    return funcAddress;
}

void* xFreeLibrary(void *ProcAddress)
{
    BOOL hResult;
    hResult = FreeLibrary((HMODULE)ProcAddress);
    if(hResult)
    {
        printf("Failed to free library!\n");
    }
}