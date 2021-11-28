#include <stdexcept>
#include "ComponentBase.h"

namespace dicontainercpp {


unsigned int ComponentBase::AddRef()
{
	return ++m_Count;
}

unsigned int ComponentBase::Release()
{
	auto ret = --m_Count;
	if (m_Count == 0) {
		delete this;
	}
	return ret;
}

IUnknown* ComponentBase::QueryInterface(UID id)
{
	if (id == UIDIUnknown) {
		AddRef();
		return static_cast<IUnknown*>(static_cast<IComponent*>(this));
	}
	else if (id == UIDIComponent) {
		AddRef();
		return static_cast<IComponent*>(this);
	}

	throw std::runtime_error("Unknown interface id!");
}

}