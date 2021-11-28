#pragma once
#include "../src/IComponent.h"

using namespace dicontainercpp;

const UID UIDTestComp = 201;
struct  ITestComp : public IUnknown
{
	virtual int Calculate(int x) = 0;
};

const UID UIDTestComp1 = 202;
struct  ITestComp1 : public IUnknown
{
	virtual int DoReturn(int x) = 0;
};

class TestComp : public IComponent, public ITestComp, public ITestComp1
{
public:
	// IUnknown implementation
	virtual  unsigned int AddRef() override;

	virtual  unsigned int Release() override;

	virtual IUnknown* QueryInterface(UID id) override;

	// IComponent implementation
	virtual std::vector<UID>& GetDependencies() override;

	virtual void SetDependency(UID id, IUnknown* dependency) override;

	// Inherited via ITestComp
	virtual int Calculate(int x) override;

	// Inherited via ITestComp1
	virtual int DoReturn(int x) override;

	static unsigned int GetCount() { return m_Count; }

private:
	std::vector<UID> dependencies {};
	static unsigned int m_Count;
};
