// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

//{00000617-0000-0010-8000-00AA006D2EA4}

STDAPI DllRegisterServer(void)
{
	//=====================Begin Registering CLSID_CPROXYSTUB==============================================

	//Open HKEY_CLASSES_ROOT/CLSID
	HKEY clsidKey;
	if (RegOpenKeyA(HKEY_CLASSES_ROOT, "CLSID", &clsidKey) != ERROR_SUCCESS)
		return SELFREG_E_CLASS;

	//Create HKEY_CLASSES_ROOT/CLSID/{CLSID_CPROXYSTUB}
	char proxy_stub_buffer[100];
	GUID guid = CLSID_CPROXYSTUB;
	sprintf_s(proxy_stub_buffer, 100, "{%08lX-%04hX-%04hX-%02hX%02hX-%02hX%02hX%02hX%02hX%02hX%02hX}",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
	HKEY proxy_stub_key;
	if (RegCreateKeyA(clsidKey, proxy_stub_buffer, &proxy_stub_key) != ERROR_SUCCESS)
	{
	 RegCloseKey(clsidKey);
	 return SELFREG_E_CLASS;
	}
  /*
	* HKEY_CLASSES_ROOT/CLSID/{CLSID_CPROXYSTUB}
	*  -> (Default) = ComputerIPSFactoryBuffer
	*/
  std::string data = "ComputerIPSFactoryBuffer";
	if (RegSetValueA(proxy_stub_key, NULL, REG_SZ, data.c_str(), (DWORD)data.length()) != ERROR_SUCCESS)
	{
		RegCloseKey(proxy_stub_key);
		RegCloseKey(clsidKey);
		return SELFREG_E_CLASS;
	}
	

	//Create Key HKEY_CLASSES_ROOT/CLSID/{CLSID_CPROXYSTUB}/InprocServer32
	HKEY InprocServer32_key;
	if (RegCreateKeyA(proxy_stub_key, "InprocServer32", &InprocServer32_key) != ERROR_SUCCESS)
	{
		RegCloseKey(proxy_stub_key);
		RegCloseKey(clsidKey);
		return SELFREG_E_CLASS;
	}
	/*
 * HKEY_CLASSES_ROOT/CLSID/{CLSID_CPROXYSTUB}/InprocServer32
 *  -> (Default) = <Path to dll>
 */
	data = "F:\\Workspace\\Projects\\Visual Studio 2022\\COMBasics\\x64\\Debug\\COMProxyStubMemory.dll";
	if (RegSetValueA(InprocServer32_key, NULL, REG_SZ, data.c_str(), (DWORD)data.length()) != ERROR_SUCCESS)
	{
		RegCloseKey(InprocServer32_key);
		RegCloseKey(proxy_stub_key);
		RegCloseKey(clsidKey);
		return SELFREG_E_CLASS;
	}

	RegCloseKey(InprocServer32_key);
	RegCloseKey(proxy_stub_key);
	RegCloseKey(clsidKey);
  //==============================End Registering CLSID_CPROXYSTUB=============================================


  //==============================Begin Registering IIDS=================================================
	 //Open HKEY_CLASSES_ROOT/Interface
	 HKEY interfaceKey;
	 if(RegOpenKeyA(HKEY_CLASSES_ROOT, "Interface", &interfaceKey) != ERROR_SUCCESS)
	  	return SELFREG_E_CLASS;


	//==============================Begin Registering IID_IMOUSE=================================================
		//Create HKEY_CLASSES_ROOT/Interface/{IID_IMOUSE}
		char iid_buffer[100];
		guid = IID_IMOUSE;
		sprintf_s(iid_buffer, 100, "{%08lX-%04hX-%04hX-%02hX%02hX-%02hX%02hX%02hX%02hX%02hX%02hX}",
			guid.Data1, guid.Data2, guid.Data3,
			guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
			guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
		HKEY mouseKey;
		if (RegCreateKeyA(interfaceKey, iid_buffer, &mouseKey) != ERROR_SUCCESS)
		{
			RegCloseKey(interfaceKey);
			return SELFREG_E_CLASS;
		}
		/*
		* HKEY_CLASSES_ROOT/Interface/{IID_IMOUSE}
		*  -> (Default) = IMouse
		*/
		data = "IMouse";
		if (RegSetValueA(mouseKey, NULL, REG_SZ, data.c_str(), (DWORD)data.length()) != ERROR_SUCCESS)
		{
			RegCloseKey(mouseKey);
			RegCloseKey(interfaceKey);
			return SELFREG_E_CLASS;
		}

		//Create HKEY_CLASSES_ROOT/Interface/{IID_IMOUSE}/ProxyStubClsid32
		HKEY mouseKey_proxystub32;
		if (RegCreateKeyA(mouseKey, "ProxyStubClsid32", &mouseKey_proxystub32) != ERROR_SUCCESS)
		{
			RegCloseKey(mouseKey);
			RegCloseKey(interfaceKey);
			return SELFREG_E_CLASS;
		}
		/*
		* HKEY_CLASSES_ROOT/Interface/{IID_IMOUSE}/ProxyStubClsid32
		*  -> (Default) = {CLSID_CPROXYSTUB}
		*/
		data = std::string(proxy_stub_buffer, 100);
		if (RegSetValueA(mouseKey_proxystub32, NULL, REG_SZ, data.c_str(), (DWORD)data.length()) != ERROR_SUCCESS)
		{
			RegCloseKey(mouseKey_proxystub32);
			RegCloseKey(mouseKey);
			RegCloseKey(interfaceKey);
			return SELFREG_E_CLASS;
		}

		RegCloseKey(mouseKey_proxystub32);
		RegCloseKey(mouseKey);
	//==============================End Registering IID_IMOUSE=================================================

	//==============================Begin Registering IID_IKEYBOARD=================================================
		//Create HKEY_CLASSES_ROOT/Interface/{IID_IKEYBOARD}
		guid = IID_IKEYBOARD;
		sprintf_s(iid_buffer, 100, "{%08lX-%04hX-%04hX-%02hX%02hX-%02hX%02hX%02hX%02hX%02hX%02hX}",
			guid.Data1, guid.Data2, guid.Data3,
			guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
			guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
		HKEY keyboardKey;
		if (RegCreateKeyA(interfaceKey, iid_buffer, &keyboardKey) != ERROR_SUCCESS)
		{
			RegCloseKey(interfaceKey);
			return SELFREG_E_CLASS;
		}
		/*
		* HKEY_CLASSES_ROOT/Interface/{IID_IKEYBOARD}
		*  -> (Default) = IMouse
		*/
		data = "IKeyboard";
		if (RegSetValueA(keyboardKey, NULL, REG_SZ, data.c_str(), (DWORD)data.length()) != ERROR_SUCCESS)
		{
			RegCloseKey(keyboardKey);
			RegCloseKey(interfaceKey);
			return SELFREG_E_CLASS;
		}

		//Create HKEY_CLASSES_ROOT/Interface/{IID_IKEYBOARD}/ProxyStubClsid32
		HKEY keyboardKey_proxystub32;
		if (RegCreateKeyA(keyboardKey, "ProxyStubClsid32", &keyboardKey_proxystub32) != ERROR_SUCCESS)
		{
			RegCloseKey(keyboardKey);
			RegCloseKey(interfaceKey);
			return SELFREG_E_CLASS;
		}
		/*
		* HKEY_CLASSES_ROOT/Interface/{IID_IKEYBOARD}/ProxyStubClsid32
		*  -> (Default) = {CLSID_CPROXYSTUB}
		*/
		data = std::string(proxy_stub_buffer, 100);
		if (RegSetValueA(keyboardKey_proxystub32, NULL, REG_SZ, data.c_str(), (DWORD)data.length()) != ERROR_SUCCESS)
		{
			RegCloseKey(keyboardKey_proxystub32);
			RegCloseKey(keyboardKey);
			RegCloseKey(interfaceKey);
			return SELFREG_E_CLASS;
		}

		RegCloseKey(keyboardKey_proxystub32);
		RegCloseKey(keyboardKey);
	//==============================End Registering IID_IMOUSE=================================================

	RegCloseKey(interfaceKey);
 //==============================End Registering IIDS=================================================

 return S_OK;
}

_Use_decl_annotations_
STDAPI DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _Outptr_ LPVOID* ppv)
{
  *ppv = NULL;
  if (rclsid == CLSID_CPROXYSTUB)
  {
    ComputerIPSFactoryBuffer* factory = new ComputerIPSFactoryBuffer();

    return factory->QueryInterface(riid, (void**)ppv);
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

STDAPI DllUnregisterServer(void)
{
	//=====================Begin UnRegistering CLSID_CPROXYSTUB==============================================

	//Open HKEY_CLASSES_ROOT/CLSID
	HKEY clsidKey;
	if (RegOpenKeyA(HKEY_CLASSES_ROOT, "CLSID", &clsidKey) != ERROR_SUCCESS)
		return SELFREG_E_CLASS;

	
	//Open HKEY_CLASSES_ROOT/CLSID/{CLSID_CPROXYSTUB}
	char proxy_stub_buffer[100];
	GUID guid = CLSID_CPROXYSTUB;
	sprintf_s(proxy_stub_buffer, 100, "{%08lX-%04hX-%04hX-%02hX%02hX-%02hX%02hX%02hX%02hX%02hX%02hX}",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
	HKEY proxy_stub_key;
	if (RegOpenKeyA(clsidKey, proxy_stub_buffer, &proxy_stub_key) != ERROR_SUCCESS)
	{
		RegCloseKey(clsidKey);
		return SELFREG_E_CLASS;
	}

	//First delete HKEY_CLASSES_ROOT/CLSID/{CLSID_CPROXYSTUB}/InprocServer32
	if (RegDeleteKeyA(proxy_stub_key, "InprocServer32") != ERROR_SUCCESS)
	{
		RegCloseKey(clsidKey);
		return SELFREG_E_CLASS;
	}

	//Then Delete HKEY_CLASSES_ROOT/CLSID/{CLSID_CPROXYSTUB}
	if (RegDeleteKeyA(clsidKey, proxy_stub_buffer) != ERROR_SUCCESS)
	{
		RegCloseKey(clsidKey);
		return SELFREG_E_CLASS;
	}

	RegCloseKey(clsidKey);
  //=====================End UnRegistering CLSID_CPROXYSTUB==============================================


	//==============================Begin UnRegistering IIDS=================================================
	 //Open HKEY_CLASSES_ROOT/Interface
	 HKEY interfaceKey;
	 if (RegOpenKeyA(HKEY_CLASSES_ROOT, "Interface", &interfaceKey) != ERROR_SUCCESS)
	  	return SELFREG_E_CLASS;

 
  //==============================Begin UnRegistering IID_IMOUSE=================================================

	//Open HKEY_CLASSES_ROOT/Interface/{IID_IMOUSE}
	char iid_buffer[100];
	guid = IID_IMOUSE;
	sprintf_s(iid_buffer, 100, "{%08lX-%04hX-%04hX-%02hX%02hX-%02hX%02hX%02hX%02hX%02hX%02hX}",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
	HKEY mouse_key;
	if (RegOpenKeyA(interfaceKey, iid_buffer, &mouse_key) != ERROR_SUCCESS)
	{
		RegCloseKey(interfaceKey);
		return SELFREG_E_CLASS;
	}

	//First Delete HKEY_CLASSES_ROOT/Interface/{IID_IMOUSE}/ProxyStubClsid32
	if (RegDeleteKeyA(mouse_key, "ProxyStubClsid32") != ERROR_SUCCESS)
	{
		RegCloseKey(interfaceKey);
		return SELFREG_E_CLASS;
	}

	//Then Delete HKEY_CLASSES_ROOT/Interface/{IID_IMOUSE}
	if (RegDeleteKeyA(interfaceKey, iid_buffer) != ERROR_SUCCESS)
	{
		RegCloseKey(interfaceKey);
		return SELFREG_E_CLASS;
	}

	//==============================End Registering IID_IMOUSE=================================================

	 //==============================Begin UnRegistering IID_IKEYBOARD=================================================
	guid = IID_IKEYBOARD;
	sprintf_s(iid_buffer, 100, "{%08lX-%04hX-%04hX-%02hX%02hX-%02hX%02hX%02hX%02hX%02hX%02hX}",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
	HKEY keyboard_key;
	if (RegOpenKeyA(interfaceKey, iid_buffer, &keyboard_key) != ERROR_SUCCESS)
	{
		RegCloseKey(interfaceKey);
		return SELFREG_E_CLASS;
	}

	//First Delete HKEY_CLASSES_ROOT/Interface/{IID_IKEYBOARD}/ProxyStubClsid32
	if (RegDeleteKeyA(keyboard_key, "ProxyStubClsid32") != ERROR_SUCCESS)
	{
		RegCloseKey(interfaceKey);
		return SELFREG_E_CLASS;
	}

	//Then Delete HKEY_CLASSES_ROOT/Interface/{IID_IKEYBOARD}
	if (RegDeleteKeyA(interfaceKey, iid_buffer) != ERROR_SUCCESS)
	{
		RegCloseKey(interfaceKey);
		return SELFREG_E_CLASS;
	}
	//==============================End Registering IID_IKEYBOARD=================================================

	RegCloseKey(interfaceKey);
 //==============================End Registering IIDS=================================================

 return S_OK;
}
