#pragma once
#include "Component/Common/ExecutorComponent/Class/MovementComponent.h"
#include "GameObject/DroppedObject/IDroppedObjectView.h"

#pragma warning(push)
#pragma warning(disable:4250)
class DroppedSwordMovementComponent : public MovementComponent
{
private:
	Inject<IDroppedObjectView> droppedObjectView_;

public:
	DroppedSwordMovementComponent(bool _isActive, IMessenger* _messenger,
		IDroppedObjectView* _droppedObjectView);

	DroppedSwordMovementComponent(IMessenger* _messenger, IDroppedObjectView* _droppedObjectView);

private:
	void Move(const Lib::Math::Vector2f& _velocity) override;

public:
	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void HandleMessage(const IEventMessage& _msg) override;

protected:
	void Reset() override;
};
#pragma warning(pop)
