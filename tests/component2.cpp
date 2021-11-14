#include <stdexcept>
#include "component2.h"

int Component2::Calculate(int x)
{
	return m_Cmp1->Calculate(x) * 2;
}

 unsigned int Component2::AddRef()
{
	return ++m_Count;
}

 unsigned int Component2::Release()
{
	auto ret = --m_Count;
	if (m_Count == 0) {
		delete this;
	}
	return ret;
}

IUnknown* Component2::QueryInterface(UID id)
{
	if (id == UIDIUnknown) {
		return static_cast<IUnknown*>(static_cast<IComponent*>(this));
	}
	else if (id == UIDIComponent) {
		return static_cast<IComponent*>(this);
	}
	else if (id == UIDComponent2) {
		return (IUnknown*)static_cast<IComponent2*>(this);
	}

	throw std::runtime_error("Unknown interface id!");
}

std::vector<UID>& Component2::GetDependencies()
{
	return dependencies;
}

void Component2::SetDependency(UID id, IUnknown* dependency)
{
	if (id == UIDComponent1) {
		m_Cmp1 = reinterpret_cast<IComponent1*>(dependency);
	}
}
