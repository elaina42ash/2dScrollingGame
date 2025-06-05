#pragma once
#include "Component/Common/SensorLogicalComponent/Class/CollisionComponent.h"
#include "GameObject/DroppedObject/IDroppedObjectView.h"

#pragma warning(push)
#pragma warning(disable:4250)
class AppleCollisionComponent : public CollisionComponent
{
private:
	Inject<IDroppedObjectView> droppedObjectView_;
public:
	AppleCollisionComponent(bool _isActive, IMessenger* _messenger,
		IDroppedObjectView* _droppedObjectView);

	AppleCollisionComponent(IMessenger* _messenger, IDroppedObjectView* _droppedObjectView);

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void HandleMessage(const IEventMessage& _msg) override;

protected:
	void Reset() override;
};
#pragma warning(pop)
