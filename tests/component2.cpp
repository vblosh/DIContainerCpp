#include "component2.h"

int Component2::Calculate(int x)
{
	return m_Cmp1->Calculate(x) * 2;
}

unsigned int Component2::AddRef()
{
	return ComponentBase::AddRef();
}

unsigned int Component2::Release()
{
	return ComponentBase::Release();
}

IUnknown* Component2::QueryInterface(UID id)
{
	if (id == UIDComponent2) {
		AddRef();
		return static_cast<IComponent2*>(this);
	}

	return ComponentBase::QueryInterface(id);
}

std::vector<UID>& Component2::GetDependencies()
{
	return m_Dependencies;
}

void Component2::SetDependency(UID id, IUnknown* dependency)
{
	AssignComPtr(m_Cmp1, id, dependency);
}
