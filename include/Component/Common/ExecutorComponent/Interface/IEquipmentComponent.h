#pragma once
#include <memory>
#include "Component/Common/IComponent.h"
#include "Event/Listener/IMessageListener.h"
#include "GameObject/DroppedObject/DroppedObject.h"
#include "GameObject/Equipment/Weapon/IWeapon.h"

class IEquipmentComponent : virtual public IComponent, public IMessageListener
{
public:
	virtual  ~IEquipmentComponent() override = default;
	virtual bool IsAttacking() = 0;
	virtual bool GetActiveWeaponID_() const = 0;
	virtual void TakeDroppedWeapon(const char* _name, DroppedObject* _droppedObject) = 0;
	virtual const std::shared_ptr<const IWeapon> GetActiveWeapon() const = 0;
};
