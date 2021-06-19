#include<Windows.h>

#pragma once

#define SUCCESS 1

#ifndef EXIT_IF_FAIL
#define EXIT_IF_FAIL(COND, MESG, CAPTION)                                       \
                        do                                                      \
                        {                                                       \
                                if((COND) == TRUE)                              \
                                {                                               \
                                        MessageBox(                             \
                                                NULL,                           \
                                                TEXT(MESG),                     \
                                                TEXT(CAPTION),                  \
                                                MB_ICONERROR);                  \
                                                ReleaseAll();                   \
                                                ExitProcess(EXIT_FAILURE);      \
                                }                                               \
                        }while(0)
#endif

typedef struct tagVectorString
{
        CHAR** ppStringVector;
        int iVectorSize;
}STRINGVECTOR, *PSTRINGVECTOR, *NPSTRINGVECTOR, *LPSTRINGVECTOR;

PSTRINGVECTOR CreateStringVector(void);
int PushBack(PSTRINGVECTOR pStrVec, CHAR* pNewString);
int DestroyVector(PSTRINGVECTOR pStrVec);
LPVOID Xcalloc(size_t cbSize, size_t cbSizePerElement);