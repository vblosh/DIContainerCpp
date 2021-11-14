#pragma once
#include <vector>
#include "IUnknown.h"

const UID UIDIComponent = 1;

struct IComponent : IUnknown
{
	virtual std::vector<UID>& GetDependencies() = 0;
	virtual void SetDependency(UID id, IUnknown* dependency) = 0;
};
