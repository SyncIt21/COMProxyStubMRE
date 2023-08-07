#include "TestImplementation.h"

CPrintBuffer::CPrintBuffer(std::string str):refCount(0),buffer(NULL),length(0)
{
  length = (int)str.length();
  buffer = new char[length];
  strcpy_s(buffer, length, str.c_str());
}

HRESULT __stdcall CPrintBuffer::QueryInterface(REFIID riid, void** ppvObject)
{
  if (riid == IID_IUnknown)
    *ppvObject = this;
  else if (riid == IID_IPRINTBUFFER)
    *ppvObject = (IPrintBuffer*)this;
  else
  {
    *ppvObject = NULL;
    return E_NOINTERFACE;
  }

  ((IUnknown*)*ppvObject)->AddRef();
  return S_OK;
}
ULONG __stdcall CPrintBuffer::AddRef(void)
{
  refCount++;
  return refCount;
}

ULONG __stdcall CPrintBuffer::Release(void)
{
  refCount--;
  if (refCount > 0)
    return refCount;

  delete this;
  return 0;
}

HRESULT CPrintBuffer::getString(char** data)
{
  *data = buffer;
  return S_OK;
}

HRESULT CPrintBuffer::getLength(int* len)
{
  *len = length;
  return S_OK;
}

CPrintBuffer::~CPrintBuffer()
{
  delete buffer;
}

HRESULT Computer::Create(REFIID riid, void** ppv)
{
  Computer* computer = new Computer();
  if (computer == NULL)
    return E_OUTOFMEMORY;

  HRESULT hr = computer->QueryInterface(riid, ppv);
  if(FAILED(hr))
    delete computer;

  return hr;
}

Computer::Computer() :ref_count(0)
{
}

HRESULT __stdcall Computer::QueryInterface(REFIID riid, void** ppvObject)
{
  if (riid == IID_IUnknown)
    *ppvObject = (IUnknown*)this;
  else if (riid == IID_IMOUSE)
    *ppvObject = (IMouse*)new MouseImp();
  else if (riid == IID_IKEYBOARD)
    *ppvObject = (IKeyboard*)new KeyboardImp();
  else
  {
    *ppvObject = NULL;
    return ResultFromScode(E_NOINTERFACE);
  }
   
  ((IUnknown*)*ppvObject)->AddRef();
  return S_OK;
}

ULONG __stdcall Computer::AddRef(void)
{
  ref_count++;
  return ref_count;
}
ULONG __stdcall Computer::Release(void)
{
  ref_count--;
  if (ref_count > 0)
    return ref_count;

  delete this;
  return 0;
}

Computer::MouseImp::MouseImp() :buffer(NULL), ref_count(0)
{
}
HRESULT __stdcall Computer::MouseImp::click(int button)
{
  if (buffer != NULL)
    buffer->Release();

  buffer = new CPrintBuffer(std::string("Mouse Click ").append(std::to_string(button)));
  return S_OK;
}
HRESULT __stdcall Computer::MouseImp::scroll(int amount)
{
  if (buffer != NULL)
    buffer->Release();

  buffer = new CPrintBuffer(std::string("Mouse Scroll ").append(std::to_string(amount)));
  return S_OK;
}
HRESULT __stdcall Computer::MouseImp::QueryInterface(REFIID riid, void** ppvObject)
{
  if (riid == IID_IUnknown)
    *ppvObject = this;
  else if(riid == IID_IPRINTBUFFER)
    *ppvObject = (IPrintBuffer*)buffer;
  else
  {
    *ppvObject = NULL;
    return E_NOINTERFACE;
  }

  ((IUnknown*)*ppvObject)->AddRef();
  return E_NOTIMPL;
}
ULONG __stdcall Computer::MouseImp::AddRef(void)
{
  ref_count++;
  return ref_count;
}
ULONG __stdcall Computer::MouseImp::Release(void)
{
  ref_count--;
  if (ref_count > 0)
    return ref_count;

  delete this;
  return 0;
}
Computer::MouseImp::~MouseImp()
{
  if (buffer != NULL) {
    buffer->Release();
  }
}



Computer::KeyboardImp::KeyboardImp() :buffer(NULL), ref_count(0)
{
}
HRESULT __stdcall Computer::KeyboardImp::pressKey(int key)
{
  if (buffer != NULL)
    buffer->Release();

  buffer = new CPrintBuffer(std::string("Key Pressed ").append(std::to_string(key)));
  return S_OK;
}
HRESULT __stdcall Computer::KeyboardImp::releaseKey(int key)
{
  if (buffer != NULL)
    buffer->Release();

  buffer = new CPrintBuffer(std::string("Key Released ").append(std::to_string(key)));
  return S_OK;
}
Computer::KeyboardImp::~KeyboardImp()
{
  if (buffer != NULL) {
    buffer->Release();
  }
}
HRESULT __stdcall Computer::KeyboardImp::QueryInterface(REFIID riid, void** ppvObject)
{
  if (riid == IID_IUnknown)
    *ppvObject = this;
  else if (riid == IID_IPRINTBUFFER)
    *ppvObject = (IPrintBuffer*)buffer;
  else
  {
    *ppvObject = NULL;
    return E_NOINTERFACE;
  }

  ((IUnknown*)*ppvObject)->AddRef();
  return E_NOTIMPL;
}
ULONG __stdcall Computer::KeyboardImp::AddRef(void)
{
  ref_count++;
  return ref_count;
}
ULONG __stdcall Computer::KeyboardImp::Release(void)
{
  ref_count--;
  if (ref_count > 0)
    return ref_count;

  delete this;
  return 0;
}


HRESULT __stdcall ComputerFactory::QueryInterface(REFIID riid, void** ppvObject)
{
  if ((riid == IID_IClassFactory) || (riid == IID_IUnknown))
  {
    *ppvObject = this;
    AddRef();
    return S_OK;
  }

  return E_NOINTERFACE;
}
ULONG __stdcall ComputerFactory::AddRef(void)
{
  ref_count++;
  return ref_count;
}
ULONG __stdcall ComputerFactory::Release(void)
{
  ref_count--;
  if (ref_count > 0)
    return ref_count;

  delete this;
  return 0;
}

HRESULT __stdcall ComputerFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppvObject)
{
  if (pUnkOuter != NULL) {
    return CLASS_E_NOAGGREGATION;
  }

  return Computer::Create(riid, ppvObject);
}

HRESULT __stdcall ComputerFactory::LockServer(BOOL fLock)
{
  return S_OK;
}

