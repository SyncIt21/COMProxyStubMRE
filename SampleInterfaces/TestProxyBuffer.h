#pragma once

#include "TestInterfaces.h"
#include <objidl.h>

class MouseProxyBuffer : public IRpcProxyBuffer, public IMouse
{
	ULONG refCount;
	IRpcChannelBuffer* proxyBuffer;
	IUnknown* proxyManager;

public:
	MouseProxyBuffer(IUnknown*);

	// Inherited via IUnknown
	virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
	virtual ULONG __stdcall AddRef(void) override;
	virtual ULONG __stdcall Release(void) override;

	// Inherited via IRpcProxyBuffer
	virtual HRESULT __stdcall Connect(IRpcChannelBuffer* pRpcChannelBuffer) override;
	virtual void __stdcall Disconnect(void) override;

	// Inherited via IMouse
	virtual HRESULT click(int button) override;
	virtual HRESULT scroll(int amount) override;
};

class KeyboardProxyBuffer : public IRpcProxyBuffer, public IKeyboard
{
	ULONG refCount;
	IRpcChannelBuffer* proxyBuffer;
	IUnknown* proxyManager;

public:
	KeyboardProxyBuffer(IUnknown*);

	// Inherited via IUnknown
	virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
	virtual ULONG __stdcall AddRef(void) override;
	virtual ULONG __stdcall Release(void) override;

	// Inherited via IRpcProxyBuffer
	virtual HRESULT __stdcall Connect(IRpcChannelBuffer* pRpcChannelBuffer) override;
	virtual void __stdcall Disconnect(void) override;

	// Inherited via IKeyboard
	virtual HRESULT pressKey(int key) override;
	virtual HRESULT releaseKey(int key) override;
};

