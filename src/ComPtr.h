#pragma once
#include "IUnknown.h"

template<class _T, UID _id>
class ComPtr
{
public:
	ComPtr() : ptr(nullptr) {}
	
	explicit ComPtr(IUnknown* p) : ptr(reinterpret_cast<_T*>(p)) {}
	
	ComPtr(_T* p) : ptr(p) {}

	ComPtr(const ComPtr<_T, _id>& other)
	{
		this->operator=(other);
	}

	template<class _U, UID _uid>
	ComPtr(const ComPtr<_U, _uid>& other)
	{
		this->operator=(other);
	}

	ComPtr(ComPtr<_T, _id>&& other) : ptr(other.ptr) {}

	ComPtr& operator=(const ComPtr<_T, _id>& other)
	{
		if (&other != this) {
			ptr = other.ptr;
			static_cast<IUnknown*>(other.ptr)->AddRef();
		}
		return *this;
	}

	template<class _U, UID _uid>
	ComPtr& operator=(const ComPtr<_U, _uid>& other)
	{
		ptr = reinterpret_cast<_T*>(static_cast<IUnknown*>(other.ptr)->QueryInterface(_id));
		return *this;
	}

	ComPtr& operator=(_T* p)
	{
		ptr = p;
		return *this;
	}

	~ComPtr()
	{
		if (ptr != nullptr) {
			static_cast<IUnknown*>(ptr)->Release();
		}
	}

	_T& operator*()
	{
		return *ptr;
	}

	_T* operator->()
	{
		return ptr;
	}

	explicit operator bool() const
	{
		return ptr != nullptr;
	}

	_T* get() const
	{
		return ptr;
	}

private:
	_T* ptr;
};