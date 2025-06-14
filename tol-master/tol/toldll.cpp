// toldll.cpp : Defines the entry point for the DLL application.
//

#include <windows.h>
#include <stdio.h>

// http://stackoverflow.com/questions/6924195/get-dll-path-at-runtime

static char pathTolDll[MAX_PATH];

extern "C" const char *GetPathTolDll( )
{
  return pathTolDll;
}

extern "C" BOOL APIENTRY DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved )  // reserved
{
    // Perform actions based on the reason for calling.
    switch( fdwReason ) 
    { 
        case DLL_PROCESS_ATTACH:
         // Initialize once for each new process.
         // Return FALSE to fail DLL load.
          GetModuleFileNameA( hinstDLL, pathTolDll, sizeof( pathTolDll ) );
          // printf( "pathTolDll = %s\n", pathTolDll );
          break;

        case DLL_THREAD_ATTACH:
         // Do thread-specific initialization.
            break;

        case DLL_THREAD_DETACH:
         // Do thread-specific cleanup.
            break;

        case DLL_PROCESS_DETACH:
         // Perform any necessary cleanup.
            break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}
