#pragma once
#include "IStaticObjectView.h"
#include "Component/Common/ExecutorComponent/Interface/ITransformComponent.h"
#include "GameObject/StaticObject.h"

class IronSpike : public StaticObject , public IStaticObjectView
{
private:
	ITransformComponent* transformComponent_;
	IAnimationComponent* animationComponent_;
	ICollisionComponent* collisionComponent_;

public:
	IronSpike();

	~IronSpike();

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void HandleMessage(const IEventMessage& _msg) override;

	Lib::Math::Vector2f GetPosition() const override
	{
		if (!transformComponent_)
			return { 0.0f,0.0f };
		return transformComponent_->GetPosition();
	}
};
