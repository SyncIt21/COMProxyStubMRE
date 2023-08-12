#include "COMLibServer.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    if(FAILED(CoInitialize(NULL))){ return FALSE; }
   
    HRESULT hr;

    int testMode = 0;
    DWORD regNum;
    if (testMode == 0)
    {
      hr = CoRegisterClassObject(
        CLSID_CCOM,
        new ComputerFactory(),
        CLSCTX_LOCAL_SERVER,  //register factory for use out of process in same computer memory
        REGCLS_MULTIPLEUSE,    //allow this factory to be used multiple times
        &regNum
      );
      if (FAILED(hr)) {return FALSE;}

      /*
      * DWORD proxyNum
      //Register proxy/stub for marshalling IMouse & IKeyboard across processes
      hr = CoRegisterClassObject(
        CLSID_CPROXYSTUB,
        new ComputerPSFactory(),
        CLSCTX_INPROC_SERVER,  //register factory for use out of process in same computer memory
        REGCLS_MULTIPLEUSE,    //allow this factory to be used multiple times
        &proxyNum
      );
      if (FAILED(hr)) { return FALSE; }

      //Register this factory to allow creation of Proxy & stubs for IMouse interface
      hr = CoRegisterPSClsid(IID_IMOUSE, CLSID_CMARSHAL);
      if (FAILED(hr)) { return FALSE; }

      //Register this factory to allow creation of Proxy & stubs for IKeyboard interface
      hr = CoRegisterPSClsid(IID_IKEYBOARD, CLSID_CMARSHAL);
      if (FAILED(hr)) { return FALSE; }
      */
    }

    MSG msg = {};
    while (GetMessage(&msg, 0, 0, 0))
    {  
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }

    hr = CoRevokeClassObject(regNum);
    if (FAILED(hr)){return FALSE;}

    /*
    hr = CoRevokeClassObject(proxyNum);
    if (FAILED(hr)) { return FALSE; }
    */

    CoUninitialize();

    return (int) msg.wParam;
}