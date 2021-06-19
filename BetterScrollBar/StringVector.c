#include<Windows.h>
#include "StringVector.h"

PSTRINGVECTOR CreateStringVector(void)
{
    PSTRINGVECTOR pStrVec = NULL;
    pStrVec = (PSTRINGVECTOR)Xcalloc(1, sizeof(STRINGVECTOR));
    return (pStrVec);
}

int PushBack(PSTRINGVECTOR pStrVec, CHAR* pNewString)
{
    pStrVec->iVectorSize += 1;
    pStrVec->ppStringVector = (CHAR**)realloc(
                                        pStrVec->ppStringVector,
                                        pStrVec->iVectorSize * sizeof(PCHAR)
                                        );
    pStrVec->ppStringVector[pStrVec->iVectorSize - 1] = pNewString;
    return(SUCCESS);
}

int DestroyVector(PSTRINGVECTOR pStrVec)
{
    int iCnt;
    for(iCnt=0; iCnt<pStrVec->iVectorSize; ++iCnt)
        free(pStrVec->ppStringVector[iCnt]);
    free(pStrVec->ppStringVector);
    free(pStrVec);
    return(SUCCESS);
}

LPVOID Xcalloc(size_t cbSize, size_t cbSizePerElement)
{
    LPVOID pNewObject = NULL;
    pNewObject = calloc(cbSize, cbSizePerElement);
    EXIT_IF_FAIL(pNewObject == NULL, "Out of virtual memory", "calloc");
    return(pNewObject);
}