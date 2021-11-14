#include <stdexcept>
#include "component1.h"

int Component1::Calculate(int x)
{
	return x*x;
}

 unsigned int Component1::AddRef()
{
	return ++m_Count;
}

 unsigned int Component1::Release()
{
	 auto ret = --m_Count;
	 if (m_Count == 0) {
		 delete this;
	 }
	 return ret;
 }

IUnknown* Component1::QueryInterface(UID id)
{
	if (id == UIDIUnknown) {
		return static_cast<IUnknown*>(static_cast<IComponent*>(this));
	}
	else if (id == UIDIComponent) {
		return static_cast<IComponent*>(this);
	}
	else if (id == UIDComponent1) {
		return (IUnknown*)static_cast<IComponent1*>(this);
	}

	throw std::runtime_error("Unknown interface id!");
}

std::vector<UID>& Component1::GetDependencies()
{
	return dependencies;
}

void Component1::SetDependency(UID id, IUnknown* dependency)
{
}
