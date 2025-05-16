#pragma once
#include <algorithm>
#include <stdexcept>
#include <typeindex>
#include <unordered_map>
#include "IGameObject.h"
#include "Component/Common/IComponent.h"
#include "Event/Messenger.h"
class GameObject : virtual public IGameObject
{
private:
	MessageBus messageBus_;

	std::unordered_map<std::type_index, IComponent*> components_;

	std::vector<IComponent*> sortedComponents_;

protected:
	Messenger messenger_;
public:
	GameObject();

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	template<typename T>
	void AddComponent(T* _comp);

	template<typename T>
	T* GetComponent();

	template <typename T>
	void RemoveComponent();

	template <typename T>
	void SetComponent(T* _new);

	template <typename T>
	void SetComponentPriority(int p);

	void ResortComponents();
private:
	void ApplyActiveChanges();
};

template <typename T>
void GameObject::AddComponent(T* _comp)
{
	static_assert(std::is_base_of<IComponent, T>::value, "AddComponent must be a Component");

	if (components_.count(typeid(T)) > 0)
	{
		throw std::logic_error("Component already exists. Use SetComponent to replace.");
	}

	_comp->SetOwner(this);
	components_[typeid(T)] = _comp;
	sortedComponents_.push_back(_comp);

	ResortComponents();
}

template <typename T>
T* GameObject::GetComponent()
{
	auto it = components_.find(typeid(T));
	if (it != components_.end())
		return dynamic_cast<T*>(it->second);
	return nullptr;
}

template <typename T>
void GameObject::RemoveComponent()
{
	static_assert(std::is_base_of<IComponent, T>::value, "RemoveComponent must be a Component");

	auto it = components_.find(typeid(T));
	if (it != components_.end()) {
		IComponent* comp = it->second;
		components_.erase(it);

		auto vecIt = std::find(sortedComponents_.begin(), sortedComponents_.end(), comp);
		if (vecIt != sortedComponents_.end()) {
			sortedComponents_.erase(vecIt);
		}

		if (comp)
		{
			delete comp;
			comp = nullptr;
		}
			
	}

	ResortComponents();
}

template <typename T>
void GameObject::SetComponent(T* _new)
{
	static_assert(std::is_base_of<IComponent, T>::value, "SetComponent must be a Component");

	if (!_new)
		return;

	RemoveComponent<T>(); 
	AddComponent<T>(_new);   
}

template <typename T>
void GameObject::SetComponentPriority(int p)
{
	auto* comp = GetComponent<T>();
	if (comp) {
		comp->SetPriority(p);
		ResortComponents();
	}
}

inline void GameObject::ResortComponents()
{
	std::sort(sortedComponents_.begin(), sortedComponents_.end(),
		[](IComponent* _a, IComponent* _b) {
			return _a->GetPriority() < _b->GetPriority();
		});
}
