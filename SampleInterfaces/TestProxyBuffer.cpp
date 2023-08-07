#include "TestProxyBuffer.h"

MouseProxyBuffer::MouseProxyBuffer(IUnknown* proxy):refCount(0),proxyBuffer(NULL),proxyManager(NULL)
{
	proxyManager = proxy;
	proxyManager->AddRef();
}
HRESULT __stdcall MouseProxyBuffer::QueryInterface(REFIID riid, void** ppvObject)
{
	if (riid == IID_IRpcProxyBuffer)
	{
		*ppvObject = (IRpcProxyBuffer*)this;
		((IUnknown*)*ppvObject)->AddRef();
		return S_OK;
	}
	else if (riid == IID_IMOUSE)
	{
		*ppvObject = (IMouse*)this;
		((IUnknown*)*ppvObject)->AddRef();
		return S_OK;
	}
	else
		return proxyManager->QueryInterface(riid, ppvObject);
}
ULONG __stdcall MouseProxyBuffer::AddRef(void)
{
	refCount++;
	return refCount;
}
ULONG __stdcall MouseProxyBuffer::Release(void)
{
	refCount--;
	if (refCount > 0)
		return refCount;

	delete this;
	return 0;
}
HRESULT __stdcall MouseProxyBuffer::Connect(IRpcChannelBuffer* pRpcChannelBuffer)
{
	proxyBuffer = pRpcChannelBuffer;
	proxyBuffer->AddRef();
	return S_OK;
}
void __stdcall MouseProxyBuffer::Disconnect(void)
{
	proxyBuffer->Release();
	proxyBuffer = NULL;
}
HRESULT MouseProxyBuffer::click(int button)
{
	RPCOLEMESSAGE message = {};
	ZeroMemory(&message, sizeof(RPCOLEMESSAGE));
	message.cbBuffer = sizeof(int);

	HRESULT hr = proxyBuffer->GetBuffer(&message, IID_IMOUSE);
	if (FAILED(hr)) {
		return E_UNEXPECTED;
	}

	message.iMethod = 3;
	((int*)message.Buffer)[0] = button;

	ULONG status = 0;
	hr = proxyBuffer->SendReceive(&message, &status);
	if (SUCCEEDED(hr)){
		std::cout << std::string((char*)message.Buffer);
	}
	
	proxyBuffer->FreeBuffer(&message);
	return S_OK;
}
HRESULT MouseProxyBuffer::scroll(int amount)
{
	RPCOLEMESSAGE message = {};
	ZeroMemory(&message, sizeof(RPCOLEMESSAGE));
	message.cbBuffer = sizeof(int);

	HRESULT hr = proxyBuffer->GetBuffer(&message, IID_IMOUSE);
	if (FAILED(hr)) {
		return E_UNEXPECTED;
	}

	message.iMethod = 4;
	((int*)message.Buffer)[0] = amount;

	ULONG status = 0;
	hr = proxyBuffer->SendReceive(&message, &status);
	if (SUCCEEDED(hr)) {
		std::cout << std::string((char*)message.Buffer);
	}

	proxyBuffer->FreeBuffer(&message);
	return S_OK;
}

KeyboardProxyBuffer::KeyboardProxyBuffer(IUnknown* proxy):refCount(0),proxyBuffer(NULL),proxyManager(NULL)
{
	proxyManager = proxy;
}
HRESULT __stdcall KeyboardProxyBuffer::QueryInterface(REFIID riid, void** ppvObject)
{
	if (riid == IID_IRpcProxyBuffer)
	{
		*ppvObject = (IRpcProxyBuffer*)this;
		((IUnknown*)*ppvObject)->AddRef();
		return S_OK;
	}
	else if (riid == IID_IKEYBOARD)
	{
		*ppvObject = (IKeyboard*)this;
		((IUnknown*)*ppvObject)->AddRef();
		return S_OK;
	}
	else
		return proxyManager->QueryInterface(riid, ppvObject);
}
ULONG __stdcall KeyboardProxyBuffer::AddRef(void)
{
	refCount++;
	return refCount;
}
ULONG __stdcall KeyboardProxyBuffer::Release(void)
{
	refCount--;
	if (refCount > 0)
		return refCount;

	delete this;
	return 0;
}
HRESULT __stdcall KeyboardProxyBuffer::Connect(IRpcChannelBuffer* pRpcChannelBuffer)
{
	proxyBuffer = pRpcChannelBuffer;
	proxyBuffer->AddRef();
	return S_OK;
}
void __stdcall KeyboardProxyBuffer::Disconnect(void)
{
	proxyBuffer->Release();
	proxyBuffer = NULL;
}
HRESULT KeyboardProxyBuffer::pressKey(int key)
{
	RPCOLEMESSAGE message = {};
	ZeroMemory(&message, sizeof(RPCOLEMESSAGE));
	message.cbBuffer = sizeof(int);

	HRESULT hr = proxyBuffer->GetBuffer(&message, IID_IKEYBOARD);
	if (FAILED(hr)) {
		return E_UNEXPECTED;
	}

	message.iMethod = 3;
	((int*)message.Buffer)[0] = key;

	ULONG status = 0;
	hr = proxyBuffer->SendReceive(&message, &status);
	if (SUCCEEDED(hr)) {
		std::cout << std::string((char*)message.Buffer);
	}

	proxyBuffer->FreeBuffer(&message);
	return S_OK;
}
HRESULT KeyboardProxyBuffer::releaseKey(int key)
{
	RPCOLEMESSAGE message = {};
	ZeroMemory(&message, sizeof(RPCOLEMESSAGE));
	message.cbBuffer = sizeof(int);

	HRESULT hr = proxyBuffer->GetBuffer(&message, IID_IKEYBOARD);
	if (FAILED(hr)) {
		return E_UNEXPECTED;
	}

	message.iMethod = 4;
	((int*)message.Buffer)[0] = key;

	ULONG status = 0;
	hr = proxyBuffer->SendReceive(&message, &status);
	if (SUCCEEDED(hr)) {
		std::cout << std::string((char*)message.Buffer);
	}

	proxyBuffer->FreeBuffer(&message);
	return S_OK;
}
