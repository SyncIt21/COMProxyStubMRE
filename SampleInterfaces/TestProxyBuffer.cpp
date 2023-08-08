#include "TestProxyBuffer.h"

MouseProxyBufferNonDelegate::MouseProxyBufferNonDelegate(IUnknown* ptr_outer):refCount(0)
{
	outerObject = ptr_outer;
	innerObject.outerObject = ptr_outer;
}

HRESULT MouseProxyBufferNonDelegate::Create(IUnknown* outer, REFIID riid, void** ppvObject)
{
	if (outer != NULL && riid != IID_IUnknown)
		return CLASS_E_NOAGGREGATION;
	
	MouseProxyBufferNonDelegate* mainObject = new MouseProxyBufferNonDelegate(outer);
	if(mainObject == NULL)
		return E_OUTOFMEMORY;

	if (mainObject->outerObject == NULL)
	{
		mainObject->outerObject = mainObject;
		mainObject->innerObject.outerObject = mainObject;
	}

	HRESULT hr = mainObject->QueryInterface(riid, (void**)ppvObject);
	if (FAILED(hr))
		delete mainObject;
	return hr;
}
HRESULT __stdcall MouseProxyBufferNonDelegate::QueryInterface(REFIID riid, void** ppvObject)
{
	if (riid == IID_IUnknown)
		*ppvObject = (IUnknown*)this;
	else if (riid == IID_IMOUSE)
		*ppvObject = (IMouse*)&innerObject;
	else if (riid == IID_IRpcProxyBuffer)
		*ppvObject = (IRpcProxyBuffer*)this;
	else
	{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}

	((IUnknown*)*ppvObject)->AddRef();
	return S_OK;
}
ULONG __stdcall MouseProxyBufferNonDelegate::AddRef(void)
{
	refCount++;
	return refCount;
}
ULONG __stdcall MouseProxyBufferNonDelegate::Release(void)
{
	refCount--;
	if (refCount > 0)
		return refCount;

	delete this;
	return 0;
}
HRESULT __stdcall MouseProxyBufferNonDelegate::MouseProxyBufferDelegate::QueryInterface(REFIID riid, void** ppvObject) { return outerObject->QueryInterface(riid, ppvObject); }
ULONG __stdcall MouseProxyBufferNonDelegate::MouseProxyBufferDelegate::AddRef(void) { return outerObject->AddRef(); }
ULONG __stdcall MouseProxyBufferNonDelegate::MouseProxyBufferDelegate::Release(void) { return outerObject->Release(); }
HRESULT __stdcall  MouseProxyBufferNonDelegate::Connect(IRpcChannelBuffer* pRpcChannelBuffer)
{
	innerObject.proxyBuffer = pRpcChannelBuffer;
	innerObject.proxyBuffer->AddRef();
	return S_OK;
}
void __stdcall  MouseProxyBufferNonDelegate::Disconnect(void)
{
	innerObject.proxyBuffer->Release();
	innerObject.proxyBuffer = NULL;
}
HRESULT  MouseProxyBufferNonDelegate::MouseProxyBufferDelegate::click(int button)
{
	RPCOLEMESSAGE message = {};
	ZeroMemory(&message, sizeof(RPCOLEMESSAGE));
	message.cbBuffer = sizeof(int);

	HRESULT hr = proxyBuffer->GetBuffer(&message, IID_IMOUSE);
	if (FAILED(hr)) 
	{
		std::string errorMsg;
		switch (hr)
		{
		case E_INVALIDARG:errorMsg = "Invalid Arguments";
			break;
		case E_OUTOFMEMORY:errorMsg = "No Memory";
			break;
		case E_UNEXPECTED:errorMsg = "Catostrophic Failure";
			break;
		case E_FAIL:errorMsg = "Fail";
		}
		std::cout << errorMsg << std::endl;
		return E_UNEXPECTED;
	}

	message.iMethod = 3;
	((int*)message.Buffer)[0] = button;

	ULONG status = 0;
	hr = proxyBuffer->SendReceive(&message, &status);
	if (SUCCEEDED(hr)){std::cout << std::string((char*)message.Buffer);}
	else
	{
		std::string errorMsg;
		switch (hr)
		{
		case E_INVALIDARG:errorMsg = "Invalid Arguments";
			break;
		case E_OUTOFMEMORY:errorMsg = "No Memory";
			break;
		case E_UNEXPECTED:errorMsg = "Catostrophic Failure";
			break;
		case E_FAIL:errorMsg = "Fail";
		}
		std::cout << errorMsg << std::endl;
	}
	
	proxyBuffer->FreeBuffer(&message);
	return S_OK;
}
HRESULT  MouseProxyBufferNonDelegate::MouseProxyBufferDelegate::scroll(int amount)
{
	RPCOLEMESSAGE message = {};
	ZeroMemory(&message, sizeof(RPCOLEMESSAGE));
	message.cbBuffer = sizeof(int);

	HRESULT hr = proxyBuffer->GetBuffer(&message, IID_IMOUSE);
	if (FAILED(hr)) 
	{
		std::string errorMsg;
		switch (hr)
		{
		case E_INVALIDARG:errorMsg = "Invalid Arguments";
			break;
		case E_OUTOFMEMORY:errorMsg = "No Memory";
			break;
		case E_UNEXPECTED:errorMsg = "Catostrophic Failure";
			break;
		case E_FAIL:errorMsg = "Fail";
		}
		std::cout << errorMsg << std::endl;
		return E_UNEXPECTED;
	}

	message.iMethod = 4;
	((int*)message.Buffer)[0] = amount;

	ULONG status = 0;
	hr = proxyBuffer->SendReceive(&message, &status);
	if (SUCCEEDED(hr)) {std::cout << std::string((char*)message.Buffer);}
	else
	{
		std::string errorMsg;
		switch (hr)
		{
		case E_INVALIDARG:errorMsg = "Invalid Arguments";
			break;
		case E_OUTOFMEMORY:errorMsg = "No Memory";
			break;
		case E_UNEXPECTED:errorMsg = "Catostrophic Failure";
			break;
		case E_FAIL:errorMsg = "Fail";
		}
		std::cout << errorMsg << std::endl;
	}

	proxyBuffer->FreeBuffer(&message);
	return S_OK;
}





KeyboardProxyBufferNonDelegate::KeyboardProxyBufferNonDelegate(IUnknown* ptr_outer):refCount(0)
{
	outerObject = ptr_outer;
	innerObject.outerObject = outerObject;
}
HRESULT __stdcall KeyboardProxyBufferNonDelegate::QueryInterface(REFIID riid, void** ppvObject)
{
	if (riid == IID_IUnknown)
		*ppvObject = (IUnknown*)this;
	else if (riid == IID_IKEYBOARD)
		*ppvObject = (IKeyboard*)&innerObject;
	else if (riid == IID_IRpcProxyBuffer)
		*ppvObject = (IRpcProxyBuffer*)this;
	else
	{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}

	((IUnknown*)*ppvObject)->AddRef();
	return S_OK;
}
ULONG __stdcall KeyboardProxyBufferNonDelegate::AddRef(void)
{
	refCount++;
	return refCount;
}
ULONG __stdcall KeyboardProxyBufferNonDelegate::Release(void)
{
	refCount--;
	if (refCount > 0)
		return refCount;

	delete this;
	return 0;
}
HRESULT KeyboardProxyBufferNonDelegate::Create(IUnknown* outer, REFIID riid, void** ppvObject)
{
	if (outer != NULL && riid != IID_IUnknown)
		return CLASS_E_NOAGGREGATION;

	KeyboardProxyBufferNonDelegate* mainObject = new KeyboardProxyBufferNonDelegate(outer);
	if (mainObject == NULL)
		return E_OUTOFMEMORY;

	if (mainObject->outerObject == NULL)
	{
		mainObject->outerObject = mainObject;
		mainObject->innerObject.outerObject = mainObject;
	}

	HRESULT hr = mainObject->QueryInterface(riid, (void**)ppvObject);
	if (FAILED(hr))
		delete mainObject;
	return hr;
}
HRESULT __stdcall KeyboardProxyBufferNonDelegate::KeyboardProxyBufferDelegate::QueryInterface(REFIID riid, void** ppvObject) { return outerObject->QueryInterface(riid, ppvObject); }
ULONG __stdcall KeyboardProxyBufferNonDelegate::KeyboardProxyBufferDelegate::AddRef(void) { return outerObject->AddRef(); }
ULONG __stdcall KeyboardProxyBufferNonDelegate::KeyboardProxyBufferDelegate::Release(void) { return outerObject->Release(); }
HRESULT __stdcall KeyboardProxyBufferNonDelegate::Connect(IRpcChannelBuffer* pRpcChannelBuffer)
{
	innerObject.proxyBuffer = pRpcChannelBuffer;
	innerObject.proxyBuffer->AddRef();
	return S_OK;
}
void __stdcall KeyboardProxyBufferNonDelegate::Disconnect(void)
{
	innerObject.proxyBuffer->Release();
	innerObject.proxyBuffer = NULL;
}
HRESULT KeyboardProxyBufferNonDelegate::KeyboardProxyBufferDelegate::pressKey(int key)
{
	RPCOLEMESSAGE message = {};
	ZeroMemory(&message, sizeof(RPCOLEMESSAGE));
	message.cbBuffer = sizeof(int);

	HRESULT hr = proxyBuffer->GetBuffer(&message, IID_IKEYBOARD);
	if (FAILED(hr)) 
	{
		std::string errorMsg;
		switch (hr)
		{
		case E_INVALIDARG:errorMsg = "Invalid Arguments";
			break;
		case E_OUTOFMEMORY:errorMsg = "No Memory";
			break;
		case E_UNEXPECTED:errorMsg = "Catostrophic Failure";
			break;
		case E_FAIL:errorMsg = "Fail";
		}
		std::cout << errorMsg << std::endl;
		return E_UNEXPECTED;
	}

	message.iMethod = 3;
	((int*)message.Buffer)[0] = key;

	ULONG status = 0;
	hr = proxyBuffer->SendReceive(&message, &status);
	if (SUCCEEDED(hr)) {std::cout << std::string((char*)message.Buffer);}
	else
	{
		std::string errorMsg;
		switch (hr)
		{
		case E_INVALIDARG:errorMsg = "Invalid Arguments";
			break;
		case E_OUTOFMEMORY:errorMsg = "No Memory";
			break;
		case E_UNEXPECTED:errorMsg = "Catostrophic Failure";
			break;
		case E_FAIL:errorMsg = "Fail";
		}
		std::cout << errorMsg << std::endl;
	}

	proxyBuffer->FreeBuffer(&message);
	return S_OK;
}
HRESULT KeyboardProxyBufferNonDelegate::KeyboardProxyBufferDelegate::releaseKey(int key)
{
	RPCOLEMESSAGE message = {};
	ZeroMemory(&message, sizeof(RPCOLEMESSAGE));
	message.cbBuffer = sizeof(int);

	HRESULT hr = proxyBuffer->GetBuffer(&message, IID_IKEYBOARD);
	if (FAILED(hr)) 
	{
		std::string errorMsg;
		switch (hr)
		{
		case E_INVALIDARG:errorMsg = "Invalid Arguments";
			break;
		case E_OUTOFMEMORY:errorMsg = "No Memory";
			break;
		case E_UNEXPECTED:errorMsg = "Catostrophic Failure";
			break;
		case E_FAIL:errorMsg = "Fail";
		}
		std::cout << errorMsg << std::endl;
		return E_UNEXPECTED;
	}

	message.iMethod = 4;
	((int*)message.Buffer)[0] = key;

	ULONG status = 0;
	hr = proxyBuffer->SendReceive(&message, &status);
	if (SUCCEEDED(hr)) {std::cout << std::string((char*)message.Buffer);}
	else
	{
		std::string errorMsg;
		switch (hr)
		{
		case E_INVALIDARG:errorMsg = "Invalid Arguments";
			break;
		case E_OUTOFMEMORY:errorMsg = "No Memory";
			break;
		case E_UNEXPECTED:errorMsg = "Catostrophic Failure";
			break;
		case E_FAIL:errorMsg = "Fail";
		}
		std::cout << errorMsg << std::endl;
	}

	proxyBuffer->FreeBuffer(&message);
	return S_OK;
}
