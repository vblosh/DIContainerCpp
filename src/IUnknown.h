#pragma once


using UID = long;

const UID UIDIUnknown = 1;

struct IUnknown
{
	virtual unsigned int AddRef() = 0;
	virtual unsigned int Release() = 0;
	virtual IUnknown* QueryInterface(UID id) = 0;
};
