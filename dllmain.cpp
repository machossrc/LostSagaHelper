#include "StdAfx.h"
#include "GameProcess.h"
#include "Utils.h"

using namespace std;

void OnHook()
{

}

void OnHelper()
{

    if (!g_GameMgr.MemoryInit())
    {
        cout << "Game Memory Initialize ... Error" << endl;
        return;
    }

    cout << "Game Memory Initialize ... Successed" << endl;

    g_GameMgr.GameProcess();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        g_Utils.OnConsole();
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OnHelper, NULL, NULL, NULL);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}