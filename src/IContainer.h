#pragma once
#include "IUnknown.h"

struct IContainer
{
	virtual IUnknown* GetInterface(UID id) = 0;
};