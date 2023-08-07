#pragma once

#include "TestInterfaces.h"
#include "TestProxyBuffer.h"
#include "TestStubBuffer.h"
#include <objidl.h>

class ComputerIPSFactoryBuffer : public IPSFactoryBuffer
{
	ULONG refCount = 0;

public:
	// Inherited via IUnknown
	virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
	virtual ULONG __stdcall AddRef(void) override;
	virtual ULONG __stdcall Release(void) override;

	// Inherited via IPSFactoryBuffer
	virtual HRESULT __stdcall CreateProxy(IUnknown* pUnkOuter, REFIID riid, IRpcProxyBuffer** ppProxy, void** ppv) override;
	virtual HRESULT __stdcall CreateStub(REFIID riid, IUnknown* pUnkServer, IRpcStubBuffer** ppStub) override;
};

