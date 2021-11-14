#include "DIcontainer.h"
#include <sstream>   

// Utility functions
template<class _Val>
void CheckIfAlreadyRegistered(std::unordered_map<UID, _Val>& map, UID id)
{
	auto itNew =map.find(id);
	if (itNew != map.end()) {
		std::stringstream message;
		message << "component with id=" << id << " is already registered in the container!";
		throw DIContainerExeption(message.str());
	}
}

std::ostream& operator << (std::ostream& os, std::unordered_set<UID>& container)
{
	for (auto id : container) {
		os << id << std::endl;
	}
	return os;
}

std::ostream& operator << (std::ostream& os, DIContainer& cont)
{
	os << "Registered ids with SharedInstance policy:\n";
	for (auto& item : cont.m_SharedInstances) {
		os << item.first << " instance at " << (void*)(item.second.Instance) << std::endl;
	}
	os << "Registered ids with NewInstance policy:\n";
	for (auto& item : cont.m_NewInstances) {
		os << item.first << std::endl;
	}
	return os;
}

// DIContainer implementation
DIContainer::DIContainer()
{
}

DIContainer::~DIContainer()
{
}

void DIContainer::RegisterInterface(UID id, CreateInstanceFunc createFn, CreationPolicy policy)
{
	if (policy == CreationPolicy::NewInstance) {
		CheckIfAlreadyRegistered(m_NewInstances, id);
		m_NewInstances[id] = createFn;
	}
	else if (policy == CreationPolicy::SharedInstance) {
		CheckIfAlreadyRegistered(m_SharedInstances, id);
		m_SharedInstances[id] = SharedData{ createFn, nullptr };
	}
}

IUnknown* DIContainer::GetInterface(UID id)
{
	m_alreadyVisited.clear();
	return GetInterfaceInternal(id);
}

IUnknown* DIContainer::GetInterfaceInternal(UID id)
{
	// check new instances registry
	auto itNew = m_NewInstances.find(id);
	if (itNew != m_NewInstances.end()) {
		return Resolve(id, itNew->second);
	}

	// check shared instances registry
	auto itShared = m_SharedInstances.find(id);
	if (itShared != m_SharedInstances.end()) {
		if (itShared->second.Instance == nullptr) {
			itShared->second.Instance = Resolve(id, itShared->second.CreateFunction);
		}
		itShared->second.Instance->AddRef();
		return itShared->second.Instance;
	}

	std::stringstream message;
	message << "component with id=" << id << " is not registered in the container!";
	throw DIContainerExeption(message.str());
}

IUnknown* DIContainer::Resolve(UID id, CreateInstanceFunc createFunction)
{
	// check cyclic dependencies
	if (m_alreadyVisited.find(id) != m_alreadyVisited.end()) {
		std::stringstream message;
		message << "Cyclic dependencies detected! "
			"Component graph consists of uids:\n" << m_alreadyVisited;
		throw DIContainerExeption(message.str());
	}
	else
		m_alreadyVisited.insert(id);

	// set component dependencies
	IComponent* component = createFunction();
	component->AddRef();

	std::vector<UID>& depIds = component->GetDependencies();
	for (auto id : depIds) {
		IUnknown* idep = GetInterfaceInternal(id);
		component->SetDependency(id, idep);
	}

	return component->QueryInterface(id);
}
