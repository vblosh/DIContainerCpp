#pragma once
#include "IUnknown.h"

namespace dicontainercpp {

struct IContainer
{
	// Return the registered in the DIContainer interface by `id`
	virtual IUnknown* GetInterface(UID id) = 0;
};

}