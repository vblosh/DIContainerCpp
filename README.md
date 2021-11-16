# About

*DIContainerCpp* is a simple but powerful dependency-injection container for C++.

# Usage

DIContainerCpp is inspired by Microsoft's COM object model.
Every interface managed by with library must implement `IUnknown`, and have a unique ID in additon to that.

## Writing components

```c++
using UID = long;

const UID IUnknown = 1;

struct IUnknown
{
	virtual unsigned int AddRef() = 0; // Increase the interface's RefCount
	virtual unsigned int Release() = 0; // Decrease the interface's RefCount. If zero, the component must be free itself.
	virtual IUnknown* QueryInterface(UID id) = 0; // Return the implementation of the interface known by `id`.
};
```

Every component is a collection of one-or-more interfaces and must implement `IComponent` (which in-turn derives from `IUnknown`):

```c++
struct IComponent : IUnknown
{
	// Return a list of interfaces that this component requires
	virtual std::vector<UID>& GetDependencies() = 0;
	// Inject the interface `dependency` with `id` into this component.
	// `id` will have been returned by `GetDependencies()`
	virtual void SetDependency(UID id, IUnknown* dependency) = 0;
};
```

## Using the container

The container itself, `DIContainer`, implements `IContainer`:

```c++
struct IContainer
{
	// Return the registered interface by `id`
	virtual IUnknown* GetInterface(UID id) = 0;
};

enum class CreationPolicy
{
	NewInstance, // New instance for every GetInterface() call
	SharedInstance // One instance per container
};

// E.g. []()->IComponent* { return new MyFancyCustomComponent(); }
typedef IComponent* (*CreateInstanceFunc)(void);

class DIContainer : IContainer {
public:
	// Register a component with the unique `id` to be lazily created using a `createFn` and a creation `policy`
	void RegisterInterface(UID id, CreateInstanceFunc createFn, CreationPolicy policy=CreationPolicy::NewInstance);
	virtual IUnknown* GetInterface(UID id) override;
}
```

Note that cyclic dependencies are detected automatically and raise a `DIContainerException`.

Example of using a DIContainer.

```c++
	// Container initialization
    DIContainer cont;
    // Register components in the container
    try {
        cont.RegisterInterface(UIDComponent3, []()->IComponent* { return new Component3; });
        cont.RegisterInterface(UIDComponent4, []()->IComponent* { return new Component4; });
    }
    catch (const DIContainerExeption& ex) {
    }

    // using components
    ComPtr<IComponent1, UIDComponent1> cmp1(cont.GetInterface(UIDComponent1));
    int res1 = cmp1->Calculate(val);

    ComPtr<IComponent2, UIDComponent2> cmp2 = (IComponent2*)cont.GetInterface(UIDComponent2);
    int res2 = cmp2->Calculate(val);
```

See [tests/](tests/) for more examples.

# Hacking

## Building

This project uses the CMake build-system. To build it, simply run the following commands:

```console
$ mkdir build
$ cd build/
$ cmake ..
$ make
```

## Running tests

This project uses *GoogleTest*.

1. Build the project
2. `cd build/ && ./runUnitTests`