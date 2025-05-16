#include "Component/Common/SensorLogicalComponent/Class/CollisionComponent.h"
#include "Collision/CollisionDef.h"
#include "Fwk/Framework.h"

CollisionComponent::CollisionComponent(bool _isActive, IMessenger* _messenger) : SensorLogicalComponent(_isActive, _messenger)
{
}

CollisionComponent::CollisionComponent(IMessenger* _messenger) : SensorLogicalComponent(_messenger)
{
}

void CollisionComponent::Init()
{
	SensorLogicalComponent::Init();

	// コリジョンマネージャにコリジョンを登録
	CollisionManager_I->Register(&collider_);
}

void CollisionComponent::Update()
{
	SensorLogicalComponent::Update();
}

void CollisionComponent::Render()
{
	SensorLogicalComponent::Render();
}

void CollisionComponent::Term()
{
	SensorLogicalComponent::Term();
}

void CollisionComponent::Enable()
{
	SensorLogicalComponent::Enable();
}

void CollisionComponent::Disable()
{
	SensorLogicalComponent::Disable();
}

void CollisionComponent::Reset()
{
	SensorLogicalComponent::Reset();
}

#pragma region Collision Function
void CollisionComponent::SetGroup(CollisionGroup _group)
{
	collider_.SetGroup(static_cast<int>(_group));
}

void CollisionComponent::AddHitGroup(CollisionGroup _group)
{
	collider_.AddHitGroup(static_cast<int>(_group));
}

const char* CollisionComponent::ToTagName(CollisionTagID _tagID)
{
	auto it = tagNameTable_.find(_tagID);
	if (it == tagNameTable_.end())
	{
		auto pair = tagNameTable_.insert({ _tagID ,std::to_string(_tagID) });
		return pair.first->second.c_str();
	}
	return it->second.c_str();
}

void CollisionComponent::SetTag(const string& _tag)
{
	collider_.SetTag(_tag);
}

void CollisionComponent::SetOwner(void* _pOwner)
{
	collider_.SetOwner(_pOwner);
}

void CollisionComponent::SetPosition(const Vector2f& _position)
{
	collider_.SetPosition(_position);
}

void CollisionComponent::SetCircleCollider(float _x, float _y, float _r)
{
	collider_.SetCircle(_x, _y, _r);
}

void CollisionComponent::SetRectCollider(float _x, float _y, float _width, float _height)
{
	collider_.SetRect(_x, _y, _width, _height);
}

void CollisionComponent::SetRectCollider(const Fwk::Collision::Rect& _rect)
{

	collider_.SetRect(_rect);
	EnableCollider();
}

Fwk::Collision::ShapeType CollisionComponent::GetShapeType() const
{
	return collider_.GetShapeType();
}

Fwk::Collision::Circle CollisionComponent::GetShapeCircle() const
{
	return collider_.GetShapeCircle();
}

Fwk::Collision::Rect CollisionComponent::GetShapeRect() const
{
	return  collider_.GetShapeRect();
}

void CollisionComponent::EnableCollider()
{
	collider_.SetActive(true);
}

void CollisionComponent::DisableCollider()
{
	collider_.SetActive(false);
}

void CollisionComponent::SetCallbackFunction()
{
	collider_.SetCallbackFunction(bind(&CollisionComponent::OnCollision, this, std::placeholders::_1, std::placeholders::_2));
}

void CollisionComponent::SetCallbackFunctionEx()
{
	collider_.SetCallbackFunctionEx(std::bind(&CollisionComponent::OnCollisionEx, this, std::placeholders::_1));
}

void CollisionComponent::OnCollision(const Fwk::Collision::Collider& _me, const Fwk::Collision::Collider& _other)
{
		
}

void CollisionComponent::OnCollisionEx(const Fwk::Collision::CollisionEvent& _collisionEvent)
{
		
}
#pragma endregion
