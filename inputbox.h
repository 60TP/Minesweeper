#include<windows.h>
#include<time.h>
#ifdef __cplusplus
extern "C"{
#endif
HWND hInput;
int _ret;
LRESULT CALLBACK InputBoxWndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
    static HWND hStatic;
    switch(Message)
    {
        case WM_CREATE:
        {
            LOGFONTA lf;
            ZeroMemory(&lf,sizeof(lf));
            strcpy(lf.lfFaceName,"Î¢ÈíÑÅºÚ");
            lf.lfHeight=40;
            HFONT hf=CreateFontIndirectA(&lf);
            hStatic=CreateWindowA("static","Please enter the number of mines:",WS_CHILD|
                WS_VISIBLE,0,0,600,40,hwnd,NULL,GetModuleHandleA(NULL),NULL);
            hInput=CreateWindowA("edit",NULL,WS_CHILD|WS_VISIBLE|ES_MULTILINE|ES_WANTRETURN|
                ES_AUTOVSCROLL,0,40,600,40,hwnd,(HMENU)IDOK,
                GetModuleHandleA(NULL),NULL);
            SendMessageA(hStatic,WM_SETFONT,(WPARAM)hf,0);
            SendMessageA(hInput,WM_SETFONT,(WPARAM)hf,0);
            SetFocus(hInput);
            break;
        }
        case WM_COMMAND:
        {
            if(LOWORD(wParam)==IDOK)
            {
                if(SendMessageA(hInput,EM_GETLINECOUNT,0,0)>1)
                {
                    int sz=GetWindowTextLengthA(hInput);
                    char* txt=(char*)malloc(sz+1);
                    GetWindowTextA(hInput,txt,sz+1);
                    _ret=atoi(txt);
                    free(txt);
                    DestroyWindow(hwnd);
                }
            }
            break;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
        default:
            return DefWindowProcA(hwnd,Message,wParam,lParam);
    }
    return 0;
}
int inputbox()
{
    HICON hico=LoadIconA(NULL,IDI_APPLICATION);
    HCURSOR hcs=LoadCursorA(NULL,IDC_ARROW);
    HBRUSH hbr=(HBRUSH)(COLOR_WINDOW+1);
    WNDCLASSEXA wc=
        {sizeof(WNDCLASSEXA),0u,InputBoxWndProc,0,0,GetModuleHandleA(NULL),hico,hcs,hbr,NULL,
        "MinesweeperInputBox",hico};
    RegisterClassExA(&wc);
    HWND hInputBox=CreateWindowExA(WS_EX_CLIENTEDGE,"MinesweeperInputBox","Minesweeper v1.0",
        WS_VISIBLE|WS_OVERLAPPEDWINDOW,200,200,600,160,NULL,NULL,GetModuleHandleA(NULL),
        NULL);
    MSG msg;
    while(GetMessageA(&msg,NULL,0,0))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    return _ret;
}
#ifdef __cplusplus
}
#endif