#pragma once
#include "IUnknown.h"

struct IContainer
{
	// Return the registered in the DIContainer interface by `id`
	virtual IUnknown* GetInterface(UID id) = 0;
};