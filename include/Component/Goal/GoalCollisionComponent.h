#pragma once
#include "Component/Common/SensorLogicalComponent/Class/CollisionComponent.h"
#include "GameObject/StaticObject/IStaticObjectView.h"

#pragma warning(push)
#pragma warning(disable:4250)
class GoalCollisionComponent : public CollisionComponent
{
private:
	Inject<IStaticObjectView> staticObjectView_;
public:
	GoalCollisionComponent(bool _isActive, IMessenger* _messenger, IStaticObjectView* _staticObjectView);

	GoalCollisionComponent(IMessenger* _messenger, IStaticObjectView* _staticObjectView);

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void HandleMessage(const IEventMessage& _msg) override;

protected:
	void Reset() override;
};
#pragma warning(pop)
