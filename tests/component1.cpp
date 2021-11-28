#include <stdexcept>
#include "component1.h"

// IUnknown, IComponent implementation BEGIN
unsigned int Component1::AddRef()
{
	return ComponentBase::AddRef();
}

unsigned int Component1::Release()
{
	return ComponentBase::Release();
}

IUnknown* Component1::QueryInterface(UID id)
{

	if (id == UIDComponent1) {
		AddRef();
		return static_cast<IComponent1*>(this);
	}

	return ComponentBase::QueryInterface(id);
}

std::vector<UID>& Component1::GetDependencies()
{
	return dependencies;
}

void Component1::SetDependency(UID id, IUnknown* dependency)
{
}
//IUnknown, IComponent implementation END

// IComponent1 implementation BEGIN
int Component1::Calculate(int x)
{
	return x * x;
}
// IComponent1 implementation END
