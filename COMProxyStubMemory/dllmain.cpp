// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

STDAPI DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _Outptr_ LPVOID* ppv)
{
  ppv = NULL;
  if (rclsid == CLSID_CMARSHAL)
  {
    ComputerIPSFactoryBuffer* factory = new ComputerIPSFactoryBuffer();

    return factory->QueryInterface(riid, (void**)&ppv);
  }
  return E_NOTIMPL;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
      break;

    case DLL_THREAD_ATTACH:
      break;

    case DLL_THREAD_DETACH:
      break;

    case DLL_PROCESS_DETACH:
      break;
    }
    return TRUE;
}

