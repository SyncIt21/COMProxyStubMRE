#pragma once

#include "TestIPCFactoryBuffer.h"
#include <objidl.h>

class ComputerPSFactory : public IUnknown
{
	ULONG refCount;

	// Inherited via IUnknown
	virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
	virtual ULONG __stdcall AddRef(void) override;
	virtual ULONG __stdcall Release(void) override;
};

