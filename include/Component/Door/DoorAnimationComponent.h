#pragma once
#include "Component/Common/ExecutorComponent/Class/AnimationComponent.h"
#include "GameObject/StaticObject/IStaticObjectView.h"

#pragma warning(push)
#pragma warning(disable:4250)
class DoorAnimationComponent : public AnimationComponent
{
private:
	Inject<IStaticObjectView> staticObjectView_;
public:
	DoorAnimationComponent(bool _isActive, IMessenger* _messenger, IStaticObjectView* _staticObjectView);

	DoorAnimationComponent(IMessenger* _messenger, IStaticObjectView* _staticObjectView);

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void HandleMessage(const IEventMessage& _msg) override;

protected:
	void Reset() override;
};
#pragma warning(pop)
