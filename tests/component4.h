#pragma once
#include "../src/IComponent.h"
#include "../src/ComPtr.h"
#include "CyclicInterface.h"

class Component4 : public IComponent, public IComponent4
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
	unsigned int m_Count = 0;

	ComPtr<IComponent3, UIDComponent3> m_Cmp1;
};
