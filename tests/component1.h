#pragma once
#include "../src/ComponentBase.h"

using namespace dicontainercpp;

const UID UIDComponent1 = 101;
struct  IComponent1 : public IUnknown
{
	virtual int Calculate(int x) = 0;
};

class Component1 : public ComponentBase, public IComponent1
{
public:
	// IUnknown implementation
	virtual  unsigned int AddRef() override;

	virtual  unsigned int Release() override;

	virtual IUnknown* QueryInterface(UID id) override;

	// IComponent implementation
	virtual std::vector<UID>& GetDependencies() override;

	virtual void SetDependency(UID id, IUnknown* dependency) override;

	// Inherited via IComponent1
	virtual int Calculate(int x) override;

private:
	std::vector<UID> dependencies {};
};
