// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.
#include "pch.h"
// #include <winsock.h>
// #include <stdexcept>
// 
// 
// BOOL APIENTRY DllMain( HMODULE hModule,
//                        DWORD  ul_reason_for_call,
//                        LPVOID lpReserved
//                      )
// {
//     static int ResultWSAStartup = -1;
//     static WSADATA WSAData;
// 
//     switch (ul_reason_for_call)
//     {
//     case DLL_PROCESS_ATTACH:
//         if (ResultWSAStartup = WSAStartup(MAKEWORD(2, 2), &WSAData))
//         {
//             throw std::runtime_error("WSAStartup failed");
//         }
//         break;
//     case DLL_THREAD_ATTACH:
//         break;
//     case DLL_THREAD_DETACH:
//         break;
//     case DLL_PROCESS_DETACH:
//         break;
//     }
// 
//     return TRUE;
// }
// 
// 