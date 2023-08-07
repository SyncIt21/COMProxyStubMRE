#include "TestStubBuffer.h"

HRESULT __stdcall MouseStubBuffer::QueryInterface(REFIID riid, void** ppvObject)
{
  if (riid == IID_IUnknown)
    *ppvObject = (IUnknown*)this;
  else if (riid == IID_IRpcStubBuffer)
    *ppvObject = (IRpcStubBuffer*)this;
  else
  {
    *ppvObject = NULL;
    return E_NOTIMPL;
  }

  ((IUnknown*)*ppvObject)->AddRef();
  return S_OK;
}
ULONG __stdcall MouseStubBuffer::AddRef(void)
{
  refCount++;
  return refCount;
}
ULONG __stdcall MouseStubBuffer::Release(void)
{
  refCount--;
  if (refCount > 0)
    return refCount;

  delete this;
  return 0;
}
HRESULT __stdcall MouseStubBuffer::Connect(IUnknown* pUnkServer)
{
  connections++;

  return pUnkServer->QueryInterface(IID_IMOUSE, (void**)&mouse_implementation);
}
void __stdcall MouseStubBuffer::Disconnect(void)
{
  connections--;
  mouse_implementation->Release();
}
HRESULT __stdcall MouseStubBuffer::Invoke(RPCOLEMESSAGE* _prpcmsg, IRpcChannelBuffer* _pRpcChannelBuffer)
{
  IPrintBuffer* printBuffer = NULL;
  char* buffer = NULL;
  int length = 0;


  if (FAILED(mouse_implementation->QueryInterface(IID_IPRINTBUFFER, (void**)&printBuffer)))
    return E_UNEXPECTED;

  switch (_prpcmsg->iMethod)
  {
  case 3:
    if (FAILED(mouse_implementation->click(((int*)_prpcmsg->Buffer)[0])))
      return E_UNEXPECTED;

    break;
  case 4:
    if (FAILED(mouse_implementation->scroll(((int*)_prpcmsg->Buffer)[0])))
      return E_UNEXPECTED;
 
    break;

  default:
    return E_NOTIMPL;
  }

  printBuffer->getString(&buffer);
  printBuffer->getLength(&length);

  _prpcmsg->cbBuffer = sizeof(char) * length;
  _pRpcChannelBuffer->GetBuffer(_prpcmsg, IID_IMOUSE);
  strcpy_s((char*)_prpcmsg->Buffer, length, buffer);
  delete buffer;

  return NO_ERROR;
}
IRpcStubBuffer* __stdcall MouseStubBuffer::IsIIDSupported(REFIID riid)
{
  if (riid == IID_IMOUSE)
    return this;
  return NULL;
}
ULONG __stdcall MouseStubBuffer::CountRefs(void)
{
  return connections;
}
HRESULT __stdcall MouseStubBuffer::DebugServerQueryInterface(void** ppv){return E_NOTIMPL;}
void __stdcall MouseStubBuffer::DebugServerRelease(void* pv){}


HRESULT __stdcall KeyboardStubBuffer::QueryInterface(REFIID riid, void** ppvObject)
{
  if (riid == IID_IUnknown)
    *ppvObject = (IUnknown*)this;
  else if(riid == IID_IRpcStubBuffer)
    *ppvObject = (IRpcStubBuffer*)this;
  else
  {
    *ppvObject = NULL;
    return E_NOTIMPL;
  }

  ((IUnknown*)*ppvObject)->AddRef();
  return S_OK;
}
ULONG __stdcall KeyboardStubBuffer::AddRef(void)
{
  refCount++;
  return refCount;
}
ULONG __stdcall KeyboardStubBuffer::Release(void)
{
  refCount--;
  if (refCount > 0)
    return refCount;

  delete this;
  return 0;
}
HRESULT __stdcall KeyboardStubBuffer::Connect(IUnknown* pUnkServer)
{
  connections++;

  return pUnkServer->QueryInterface(IID_IKEYBOARD, (void**)&keyboard_implementation);
}
void __stdcall KeyboardStubBuffer::Disconnect(void)
{
  connections--;
  keyboard_implementation->Release();
}
HRESULT __stdcall KeyboardStubBuffer::Invoke(RPCOLEMESSAGE* _prpcmsg, IRpcChannelBuffer* _pRpcChannelBuffer)
{
  IPrintBuffer* printBuffer = NULL;
  char* buffer = NULL;
  int length = 0;

  if (FAILED(keyboard_implementation->QueryInterface(IID_IPRINTBUFFER, (void**)&printBuffer)))
    return E_UNEXPECTED;

  switch (_prpcmsg->iMethod)
  {
  case 3:
    if (FAILED(keyboard_implementation->pressKey(((int*)_prpcmsg->Buffer)[0])))
      return E_UNEXPECTED;

    break;
  case 4:
    if (FAILED(keyboard_implementation->releaseKey(((int*)_prpcmsg->Buffer)[0])))
      return E_UNEXPECTED;

    break;

  default:
    return E_NOTIMPL;
  }

  printBuffer->getString(&buffer);
  printBuffer->getLength(&length);

  _prpcmsg->cbBuffer = sizeof(char) * length;
  _pRpcChannelBuffer->GetBuffer(_prpcmsg, IID_IKEYBOARD);
  strcpy_s((char*)_prpcmsg->Buffer, length, buffer);
  delete buffer;

  return NO_ERROR;
}
IRpcStubBuffer* __stdcall KeyboardStubBuffer::IsIIDSupported(REFIID riid)
{
  if (riid == IID_IKEYBOARD)
    return this;
  return NULL;
}
ULONG __stdcall KeyboardStubBuffer::CountRefs(void)
{
  return connections;
}
HRESULT __stdcall KeyboardStubBuffer::DebugServerQueryInterface(void** ppv) { return E_NOTIMPL; }
void __stdcall KeyboardStubBuffer::DebugServerRelease(void* pv) {}