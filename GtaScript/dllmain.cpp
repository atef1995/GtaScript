// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <windows.h>
#include "main.h"
#include "natives.h"

void ScriptMain() {
    while (true) {
        HUD::BEGIN_TEXT_COMMAND_PRINT("STRING");
        HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("my mod loaded");
        HUD::END_TEXT_COMMAND_PRINT(2000, true);

        scriptWait(0);
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        scriptRegister(hModule, ScriptMain);
        break;
    case DLL_PROCESS_DETACH:
        scriptUnregister(hModule);
        break;
    }
    return TRUE;
}

