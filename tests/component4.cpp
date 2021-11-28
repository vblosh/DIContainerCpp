#include "component4.h"

int Component4::Calculate(int x)
{
	return m_Cmp1->Calculate(x) * 2;
}

unsigned int Component4::AddRef()
{
	return ComponentBase::AddRef();
}

unsigned int Component4::Release()
{
	return ComponentBase::Release();
}

IUnknown* Component4::QueryInterface(UID id)
{

	if (id == UIDComponent4) {
		AddRef();
		return static_cast<IComponent4*>(this);
	}

	return ComponentBase::QueryInterface(id);
}

std::vector<UID>& Component4::GetDependencies()
{
	return dependencies;
}

void Component4::SetDependency(UID id, IUnknown* dependency)
{
	AssignComPtr(m_Cmp1, id, dependency);
}

