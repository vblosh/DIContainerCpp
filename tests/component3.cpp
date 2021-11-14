#include <stdexcept>
#include "component3.h"

int Component3::Calculate(int x)
{
	return m_Cmp1->Calculate(x) * 2;
}

unsigned int Component3::AddRef()
{
	return ++m_Count;
}

unsigned int Component3::Release()
{
	--m_Count;
	if (m_Count == 0) {
		delete this;
	}
	return m_Count;
}

IUnknown* Component3::QueryInterface(UID id)
{
	if (id == UIDIUnknown) {
		return static_cast<IUnknown*>(static_cast<IComponent*>(this));
	}
	else if (id == UIDIComponent) {
		return static_cast<IComponent*>(this);
	}
	else if (id == UIDComponent3) {
		return (IUnknown*)static_cast<IComponent3*>(this);
	}

	throw std::runtime_error("Unknown interface id!");
}

std::vector<UID>& Component3::GetDependencies()
{
	return dependencies;
}

void Component3::SetDependency(UID id, IUnknown* dependency)
{
	if (id == UIDComponent4) {
		m_Cmp1 = reinterpret_cast<IComponent4*>(dependency);
	}
}