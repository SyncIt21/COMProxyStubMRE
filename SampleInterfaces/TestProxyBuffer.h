#pragma once

#include "TestInterfaces.h"
#include <objidl.h>

class MouseProxyBufferNonDelegate : public IRpcProxyBuffer
{
	ULONG refCount;
	IUnknown* outerObject;

	MouseProxyBufferNonDelegate(IUnknown*);

private:
	class MouseProxyBufferDelegate :  public IMouse
	{
		friend class MouseProxyBufferNonDelegate;
		IRpcChannelBuffer* proxyBuffer;
		IUnknown* outerObject;

	public:
		// Inherited via IUnknown
		virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
		virtual ULONG __stdcall AddRef(void) override;
		virtual ULONG __stdcall Release(void) override;

		// Inherited via IMouse
		virtual HRESULT click(int button) override;
		virtual HRESULT scroll(int amount) override;
	};
	MouseProxyBufferDelegate innerObject;

public:
	static HRESULT Create(IUnknown*, REFIID, void**);

	// Inherited via IUnknown
	virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
	virtual ULONG __stdcall AddRef(void) override;
	virtual ULONG __stdcall Release(void) override;

	// Inherited via IRpcProxyBuffer
	virtual HRESULT __stdcall Connect(IRpcChannelBuffer* pRpcChannelBuffer) override;
	virtual void __stdcall Disconnect(void) override;
};


class KeyboardProxyBufferNonDelegate : public IRpcProxyBuffer
{
	ULONG refCount;
	IUnknown* outerObject;

	KeyboardProxyBufferNonDelegate(IUnknown*);

	class KeyboardProxyBufferDelegate :  public IKeyboard
	{
		friend class KeyboardProxyBufferNonDelegate;
		IRpcChannelBuffer* proxyBuffer;
		IUnknown* outerObject;

	public:
		// Inherited via IUnknown
		virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
		virtual ULONG __stdcall AddRef(void) override;
		virtual ULONG __stdcall Release(void) override;

		// Inherited via IKeyboard
		virtual HRESULT pressKey(int key) override;
		virtual HRESULT releaseKey(int key) override;
	};
	KeyboardProxyBufferDelegate innerObject;

public:
	static HRESULT Create(IUnknown*, REFIID, void**);

	// Inherited via IRpcProxyBuffer
	virtual HRESULT __stdcall Connect(IRpcChannelBuffer* pRpcChannelBuffer) override;
	virtual void __stdcall Disconnect(void) override;

	// Inherited via IUnknown
	virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
	virtual ULONG __stdcall AddRef(void) override;
	virtual ULONG __stdcall Release(void) override;
};

