#pragma once
#include "../src/ComponentBase.h"
#include "../src/ComPtr.h"
#include "CyclicInterface.h"

using namespace dicontainercpp;

class Component4 : public ComponentBase, public IComponent4
{
public:
	// IUnknown implementation
	virtual  unsigned int AddRef() override;

	virtual  unsigned int Release() override;

	virtual IUnknown* QueryInterface(UID id) override;

	// IComponent implementation
	virtual std::vector<UID>& GetDependencies() override;

	virtual void SetDependency(UID id, IUnknown* dependency) override;

	// Inherited via IComponent4
	virtual int Calculate(int x) override;

private:
	std::vector<UID> dependencies { UIDComponent3 };

	ComPtr<IComponent3, UIDComponent3> m_Cmp1;
};
