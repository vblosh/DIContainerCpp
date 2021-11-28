#pragma once
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include "IUnknown.h"
#include "IComponent.h"
#include "IContainer.h"

namespace dicontainercpp {

enum class CreationPolicy
{
	NewInstance,
	SharedInstance
};

// E.g. []()->IComponent* { return new MyFancyCustomComponent(); }
typedef IComponent* (*CreateInstanceFunc)(void);

class DIContainerExeption : public std::runtime_error
{
public:
	explicit DIContainerExeption(const std::string& _Message) : std::runtime_error(_Message.c_str()) {}
	explicit DIContainerExeption(const char* _Message) : std::runtime_error(_Message) {}
	virtual ~DIContainerExeption() noexcept {}
};

class DIContainer : public IContainer
{
public:
	DIContainer();
	~DIContainer();
	
	// Register a component with the unique `id` to be lazily created using a `createFn` and a creation `policy`
	void RegisterInterface(UID id, CreateInstanceFunc createFn, CreationPolicy policy=CreationPolicy::NewInstance);
	
	// IContainer implementation
	virtual IUnknown* GetInterface(UID id) override;

private:
	IUnknown* GetInterfaceInternal(UID id);
	IUnknown* Resolve(UID id, CreateInstanceFunc createFunction);

	struct SharedData
	{
		CreateInstanceFunc CreateFunction;
		IUnknown* Instance;
	};

	std::unordered_map<UID, CreateInstanceFunc> m_NewInstances;
	std::unordered_map<UID, SharedData> m_SharedInstances;
	std::unordered_set<UID> m_alreadyVisited;

	friend std::ostream& operator << (std::ostream& os, DIContainer& cont);
};

std::ostream& operator << (std::ostream& os, DIContainer& cont);

}