#pragma once
#include "../src/IComponent.h"
#include "../src/ComPtr.h"
#include "CyclicInterface.h"

class Component3 : public IComponent, public IComponent3
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
	unsigned int m_Count = 0;

	ComPtr<IComponent4, UIDComponent4> m_Cmp1;
};