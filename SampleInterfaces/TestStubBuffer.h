#pragma once

#include "TestInterfaces.h"
#include <objidl.h>

class MouseStubBuffer : public IRpcStubBuffer
{
	ULONG refCount, connections;
	IMouse* mouse_implementation;

	// Inherited via IUnknown
	virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
	virtual ULONG __stdcall AddRef(void) override;
	virtual ULONG __stdcall Release(void) override;

	// Inherited via IRpcStubBuffer
	virtual HRESULT __stdcall Connect(IUnknown* pUnkServer) override;
	virtual void __stdcall Disconnect(void) override;
	virtual HRESULT __stdcall Invoke(RPCOLEMESSAGE* _prpcmsg, IRpcChannelBuffer* _pRpcChannelBuffer) override;
	virtual IRpcStubBuffer* __stdcall IsIIDSupported(REFIID riid) override;
	virtual ULONG __stdcall CountRefs(void) override;
	// Not so important
	virtual HRESULT __stdcall DebugServerQueryInterface(void** ppv) override;
	virtual void __stdcall DebugServerRelease(void* pv) override;
};

class KeyboardStubBuffer : public IRpcStubBuffer
{
	ULONG refCount, connections;
	IKeyboard* keyboard_implementation;

	// Inherited via IUnknown
	virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
	virtual ULONG __stdcall AddRef(void) override;
	virtual ULONG __stdcall Release(void) override;

	// Inherited via IRpcStubBuffer
	virtual HRESULT __stdcall Connect(IUnknown* pUnkServer) override;
	virtual void __stdcall Disconnect(void) override;
	virtual HRESULT __stdcall Invoke(RPCOLEMESSAGE* _prpcmsg, IRpcChannelBuffer* _pRpcChannelBuffer) override;
	virtual IRpcStubBuffer* __stdcall IsIIDSupported(REFIID riid) override;
	virtual ULONG __stdcall CountRefs(void) override;
	// Not so important
	virtual HRESULT __stdcall DebugServerQueryInterface(void** ppv) override;
	virtual void __stdcall DebugServerRelease(void* pv) override;
};
