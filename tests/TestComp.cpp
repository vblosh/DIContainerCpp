#include <stdexcept>
#include "TestComp.h"

unsigned int TestComp::m_Count = 0;

int TestComp::Calculate(int x)
{
	return x*x;
}

int TestComp::DoReturn(int x)
{
	return x;
}

unsigned int TestComp::AddRef()
{
	return ++m_Count;
}

 unsigned int TestComp::Release()
{
	 auto ret = --m_Count;
	 if (m_Count == 0) {
		 delete this;
	 }
	 return ret;
 }

IUnknown* TestComp::QueryInterface(UID id)
{
	if (id == UIDIUnknown) {
		AddRef();
		return static_cast<IUnknown*>(static_cast<IComponent*>(this));
	}
	else if (id == UIDIComponent) {
		AddRef();
		return static_cast<IComponent*>(this);
	}
	else if (id == UIDTestComp) {
		AddRef();
		return (IUnknown*)static_cast<ITestComp*>(this);
	}
	else if (id == UIDTestComp1) {
		AddRef();
		return (IUnknown*)static_cast<ITestComp1*>(this);
	}

	throw std::runtime_error("Unknown interface id!");
}

std::vector<UID>& TestComp::GetDependencies()
{
	return dependencies;
}

void TestComp::SetDependency(UID id, IUnknown* dependency)
{
}
