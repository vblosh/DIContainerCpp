#pragma once
#include <vector>
#include "IUnknown.h"

namespace dicontainercpp {

const UID UIDIComponent = 1;

struct IComponent : IUnknown
{
	// Return a list of interfaces that this component requires
	virtual std::vector<UID>& GetDependencies() = 0;
	// Inject the interface `dependency` with `id` into this component.
	// `id` will have been returned by `GetDependencies()`
	virtual void SetDependency(UID id, IUnknown* dependency) = 0;
};

}