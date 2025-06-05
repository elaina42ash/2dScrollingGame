#pragma once
#include "SensorLogicalComponent.h"
#include "Collision/CollisionDef.h"
#include "Component/Common/SensorLogicalComponent/Interface/ICollisionComponent.h"
#include "Fwk/Collision/Collider.h"

#pragma warning(push)
#pragma warning(disable:4250)
class CollisionComponent : public SensorLogicalComponent, public ICollisionComponent
{
	using CollisionTagID = int;
	using SensorLogicalComponent::Enable;
	using SensorLogicalComponent::Disable;
private:
	unordered_map<CollisionTagID, std::string> tagNameTable_;

protected:
	Fwk::Collision::Collider collider_;

public:
	CollisionComponent(bool _isActive, IMessenger* _messenger);

	explicit CollisionComponent(IMessenger* _messenger);

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void Enable() override;

	void Disable() override;

	void SetPosition(const Vector2f& _position) override final;
protected:
	void Reset() override;

#pragma region Collision Function
	void SetGroup(CollisionGroup _group);

	void AddHitGroup(CollisionGroup _group);

	const char* ToTagName(CollisionTagID _tagID);

	void SetTag(const string& _tag);

	void SetOwner(void* _pOwner);

	void SetCircleCollider(float _x, float _y, float _r);

	void SetRectCollider(float _x, float _y, float _width,float _height);

	void SetRectCollider(const Fwk::Collision::Rect& _rect);

	Fwk::Collision::ShapeType GetShapeType() const override final;

	Fwk::Collision::Circle GetShapeCircle() const override final;

	Fwk::Collision::Rect GetShapeRect() const override final;

	void EnableCollider() override final;

	void DisableCollider() override final;

	void SetCallbackFunction();
	void SetCallbackFunctionEx();

	virtual void OnCollision(const Fwk::Collision::Collider& _me, const Fwk::Collision::Collider& _other);

	virtual void OnCollisionEx(const Fwk::Collision::CollisionEvent& _collisionEvent);


#pragma endregion
};
#pragma warning(pop)