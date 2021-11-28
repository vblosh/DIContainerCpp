#pragma once

namespace dicontainercpp {

using UID = long;

const UID UIDIUnknown = 1;

// `IUnknown` is the base for all interfaces managed with this library
struct IUnknown
{
	virtual unsigned int AddRef() = 0; // Increase the interface's RefCount
	virtual unsigned int Release() = 0; // Decrease the interface's RefCount. If zero, the component must be free itself.
	virtual IUnknown* QueryInterface(UID id) = 0; // Return the implementation of the interface known by `id`.
};

}