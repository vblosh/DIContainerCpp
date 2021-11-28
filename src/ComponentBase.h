#pragma once
#include "IComponent.h"
#include "ComPtr.h"

namespace dicontainercpp {

class ComponentBase : public IComponent
{
public:
	ComponentBase() : m_Count(0) {}

	virtual ~ComponentBase() {}

	// IUnknown implementation
	virtual  unsigned int AddRef() override;

	virtual  unsigned int Release() override;

	virtual IUnknown* QueryInterface(UID id) override;

	template<class T, UID uid>
	void AssignComPtr(ComPtr<T, uid>& comPtr, UID id, IUnknown* dependency) {
		if (id == uid) {
			comPtr = reinterpret_cast<T*>(dependency);
		}
	}

private:
	unsigned int m_Count;
};

}