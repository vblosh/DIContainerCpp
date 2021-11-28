#pragma once
#include "../src/IComponent.h"
#include "../src/ComPtr.h"
#include "component1.h"

using namespace dicontainercpp;

const UID UIDComponent2 = 102;

struct  IComponent2 : IUnknown
{
	virtual int Calculate(int x) = 0;
};

class Component2 : public IComponent, public IComponent2
{
public:
	// IUnknown implementation
	virtual  unsigned int AddRef() override;

	virtual  unsigned int Release() override;

	virtual IUnknown* QueryInterface(UID id) override;

	// IComponent implementation
	virtual std::vector<UID>& GetDependencies() override;

	virtual void SetDependency(UID id, IUnknown* dependency) override;

	// Inherited via IComponent2
	virtual int Calculate(int x) override;
private:
	std::vector<UID> dependencies { UIDComponent1 };
	unsigned int m_Count = 0;

	ComPtr<IComponent1, UIDComponent1> m_Cmp1;
};
