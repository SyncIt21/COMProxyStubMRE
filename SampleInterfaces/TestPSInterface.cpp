#include "TestPSInterface.h"

HRESULT __stdcall ComputerPSFactory::QueryInterface(REFIID riid, void** ppvObject)
{
	if (riid == IID_IUnknown)
		*ppvObject = this;
	else if (riid == IID_IPSFactoryBuffer)
		*ppvObject = new ComputerIPSFactoryBuffer();
	else
	{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}

	((IUnknown*)*ppvObject)->AddRef();
	return S_OK;
}

ULONG __stdcall ComputerPSFactory::AddRef(void)
{
	refCount++;
	return refCount;
}
ULONG __stdcall ComputerPSFactory::Release(void)
{
	refCount--;
	if (refCount > 0)
		return refCount;

	delete this;
	return 0;
}

