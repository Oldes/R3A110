#include <stdlib.h>
#include <windows.h>

char* rebser_to_utf8(REBSER* series) {
    char *uf8str = 0;
    REBCHR* str;
    REBCHR** pstr = &str;
    REBINT result = RL_GET_STRING(series, 0 , (void**)pstr);

    if (result > 0){
        //unicode string
        int iLen = wcslen(str);
        int oLen = iLen *  sizeof(REBCHR);
        uf8str = malloc(oLen);
        int result = WideCharToMultiByte(CP_UTF8, 0, str, iLen, uf8str, oLen, 0, 0);
        if (result == 0) {
            int err = GetLastError();
            RL->print("err: %d\n", err);
        }
    } else if (result < 0) {
        //bytes string (ascii or latin-1)
        uf8str = malloc(strlen((char *)str));
        strcpy(uf8str, (char *)str);
    }
    return uf8str;
}

REBSER* MultiByteToRebser(char* mbStr) {
    int len = MultiByteToWideChar( CP_UTF8, 0, mbStr, -1, NULL, 0);
    REBSER *ser = RL_MAKE_STRING(len-1,TRUE);
    REBUNI *dst;
    REBUNI **pdst = &dst;
    REBINT *s = (REBINT*)ser;

    //the len is length of the string + null terminator
    wchar_t *wcStr = malloc(len * sizeof(wchar_t));
    int result = MultiByteToWideChar(CP_UTF8, 0, mbStr, strlen(mbStr), wcStr, len);
    if (result == 0) {
        int err = GetLastError();
        RL->print("ERROR: MultiByteToWideChar -> %d\n", err);
        exit(-1); //how to throw ERROR on REBOL side?
    }

    //hack! - will set the tail to len
    s[1] = len-1;

    RL_GET_STRING(ser,0,(void**)pdst);
    wcscpy(dst, wcStr);

    free(wcStr);
    wcStr = NULL;
    return ser;
}
