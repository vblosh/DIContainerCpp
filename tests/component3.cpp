#include "component3.h"

int Component3::Calculate(int x)
{
	return m_Cmp1->Calculate(x) * 2;
}

unsigned int Component3::AddRef()
{
	return ComponentBase::AddRef();
}

unsigned int Component3::Release()
{
	return ComponentBase::Release();
}

IUnknown* Component3::QueryInterface(UID id)
{

	if (id == UIDComponent3) {
		AddRef();
		return static_cast<IComponent3*>(this);
	}

	return ComponentBase::QueryInterface(id);
}

std::vector<UID>& Component3::GetDependencies()
{
	return dependencies;
}

void Component3::SetDependency(UID id, IUnknown* dependency)
{
	AssignComPtr(m_Cmp1, id, dependency);
}
