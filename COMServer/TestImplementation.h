#pragma once

#include "TestInterfaces.h"
#include <oleauto.h>
#include <atlstr.h>
#include <string>

class CPrintBuffer : public IPrintBuffer
{
	char* buffer;
	int length;
	ULONG refCount;
	

public:
	CPrintBuffer(std::string);
	// Inherited via IUnknown
	virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
	virtual ULONG __stdcall AddRef(void) override;
	virtual ULONG __stdcall Release(void) override;

	// Inherited via IPrintBuffer
	virtual HRESULT getString(char**) override;
	virtual HRESULT getLength(int*) override;
	~CPrintBuffer();
};

class Computer : public IUnknown
{
	ULONG ref_count = 0;
	

	// Static member function for creating new instances (don't use 
	// new directly). Protects against outer objects asking for 
	// interfaces other than Iunknown. 
public:
	static HRESULT Create(REFIID riid, void** ppv);

	Computer();

	//IUnknown
	virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
	virtual ULONG __stdcall AddRef(void) override;
	virtual ULONG __stdcall Release(void) override;

private:
	class MouseImp : public IMouse
	{
	private:
		ULONG ref_count = 0;
		CPrintBuffer* buffer;

	public:
		MouseImp();
		virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
		virtual ULONG __stdcall AddRef(void) override;
		virtual ULONG __stdcall Release(void) override;
		HRESULT __stdcall click(int button) override;
		HRESULT __stdcall scroll(int amount) override;
		~MouseImp();
	};

	class KeyboardImp : public IKeyboard
	{
	private:
		ULONG ref_count = 0;
		CPrintBuffer* buffer;

	public:
		KeyboardImp();
		virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
		virtual ULONG __stdcall AddRef(void) override;
		virtual ULONG __stdcall Release(void) override;
		HRESULT __stdcall pressKey(int key) override;
		HRESULT __stdcall releaseKey(int key) override;
		~KeyboardImp();
	};
};

class ComputerFactory : public IClassFactory
{
	ULONG ref_count = 0;

	virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
	virtual ULONG __stdcall AddRef(void) override;
	virtual ULONG __stdcall Release(void) override;
	virtual HRESULT __stdcall CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppvObject) override;
	virtual HRESULT __stdcall LockServer(BOOL fLock) override;
};
