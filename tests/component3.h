#pragma once
#include "../src/ComponentBase.h"
#include "../src/ComPtr.h"
#include "CyclicInterface.h"

using namespace dicontainercpp;

class Component3 : public ComponentBase, public IComponent3
{
public:
	// IUnknown implementation
	virtual  unsigned int AddRef() override;

	virtual  unsigned int Release() override;

	virtual IUnknown* QueryInterface(UID id) override;

	// IComponent implementation
	virtual std::vector<UID>& GetDependencies() override;

	virtual void SetDependency(UID id, IUnknown* dependency) override;

	// Inherited via IComponent3
	virtual int Calculate(int x) override;

private:
	std::vector<UID> dependencies { UIDComponent4 };

	ComPtr<IComponent4, UIDComponent4> m_Cmp1;
};
