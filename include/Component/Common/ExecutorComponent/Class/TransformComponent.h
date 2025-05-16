#pragma once
#include "ExecutorComponent.h"
#include "Component/Common/ExecutorComponent/Interface/ITransformComponent.h"
#pragma warning(push)
#pragma warning(disable:4250)


class TransformComponent : public ExecutorComponent, public ITransformComponent
{
private:
	Lib::Math::Vector2f position_ = { 0.0f,0.0f };

	Direction direction_ = Direction::NONE;

	void SetPosition(const Lib::Math::Vector2f& _new);

	void SetDirection(const Direction& _new);

public:

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	const Lib::Math::Vector2f& GetPosition() const override final;

	float GetPositionY() const override final;

	float GetPositionX()const override final;

	void Translate(const Lib::Math::Vector2f& _offset) override final;

	void MoveTo(const Lib::Math::Vector2f& _target) override final;

	void ChangeDirection(const Direction& _new) override final;

	void ReverseDirection() override final;

	Direction GetDirection() const override final;
protected:
	void Reset() override;

	TransformComponent(bool _isActive, IMessenger* _messenger);

	explicit TransformComponent(IMessenger* _messenger);
};
#pragma warning(pop)