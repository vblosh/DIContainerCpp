#include <stdexcept>
#include "component4.h"

int Component4::Calculate(int x)
{
	return m_Cmp1->Calculate(x) * 2;
}

unsigned int Component4::AddRef()
{
	return ++m_Count;
}

unsigned int Component4::Release()
{
	auto ret = --m_Count;
	if (m_Count == 0) {
		delete this;
	}
	return ret;
}

IUnknown* Component4::QueryInterface(UID id)
{
	if (id == UIDIUnknown) {
		return static_cast<IUnknown*>(static_cast<IComponent*>(this));
	}
	else if (id == UIDIComponent) {
		return static_cast<IComponent*>(this);
	}
	else if (id == UIDComponent4) {
		return (IUnknown*)static_cast<IComponent4*>(this);
	}

	throw std::runtime_error("Unknown interface id!");
}

std::vector<UID>& Component4::GetDependencies()
{
	return dependencies;
}

void Component4::SetDependency(UID id, IUnknown* dependency)
{
	if (id == UIDComponent3) {
		m_Cmp1 = reinterpret_cast<IComponent3*>(dependency);
	}
}
