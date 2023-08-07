#include "TestIPCFactoryBuffer.h"

HRESULT __stdcall ComputerIPSFactoryBuffer::QueryInterface(REFIID riid, void** ppvObject)
{
	if (riid == IID_IUnknown)
		*ppvObject = (IUnknown*)this;
	else if(riid == IID_IPSFactoryBuffer)
		*ppvObject = (IPSFactoryBuffer*)this;
	else
	{
		*ppvObject = NULL;
		return E_NOTIMPL;
	}

	((IUnknown*)*ppvObject)->AddRef();
	return S_OK;
}

ULONG __stdcall ComputerIPSFactoryBuffer::AddRef(void)
{
	refCount++;
	return refCount;
}
ULONG __stdcall ComputerIPSFactoryBuffer::Release(void)
{
	refCount--;
	if (refCount > 0)
		return refCount;

	delete this;
	return 0;
}


//Client side
HRESULT __stdcall ComputerIPSFactoryBuffer::CreateProxy(
	IUnknown* pUnkOuter,       //the aggregate if specified by the user in CreateInstance
	REFIID riid,               //the IID of the object we are trying to create a proxy for
	IRpcProxyBuffer** ppProxy, //We must give this a value. The buffer which the Proxy will use to communicate with the stub
	void** ppv                 //We must give this a value. the actual interface specified by IID returned to the client
)
{
	if (riid == IID_IMOUSE)
		*ppProxy = new MouseProxyBuffer(pUnkOuter);
	else if (riid == IID_IKEYBOARD)
		*ppProxy = new KeyboardProxyBuffer(pUnkOuter);
	else
	{
		*ppv = NULL;
		*ppProxy = NULL;
		return E_NOINTERFACE;
	}

	((IUnknown*)*ppProxy)->QueryInterface(riid, (void**)ppv);

	return 	((IUnknown*)*ppProxy)->QueryInterface(IID_IRpcProxyBuffer, (void**)ppProxy);
}

//Server side
HRESULT __stdcall ComputerIPSFactoryBuffer::CreateStub(
	REFIID riid,                    //IID for the interface we are trying to create a stub for
	IUnknown* pUnkServer,           //The object(in this example Mouse,Keyboard objects) we are trying to create a stub for
	IRpcStubBuffer** ppStub         //We must give this a value. The buffer which the Proxy will use to communicate with the proxy
)
{
	if (riid == IID_IMOUSE)
		*ppStub = new MouseStubBuffer();
	else if (riid == IID_IKEYBOARD)
		*ppStub = new KeyboardStubBuffer();
	else
	{
		*ppStub = NULL;
		return E_NOINTERFACE;
	}
	
	((IRpcStubBuffer*)*ppStub)->Connect(pUnkServer);

	return ((IRpcStubBuffer*)*ppStub)->QueryInterface(IID_IRpcStubBuffer, (void**)ppStub);
}
