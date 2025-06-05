#include "Component/Apple/AppleCollisionComponent.h"

#include "Fwk/Framework.h"

AppleCollisionComponent::AppleCollisionComponent(bool _isActive, IMessenger* _messenger,
	IDroppedObjectView* _droppedObjectView) : CollisionComponent(_isActive, _messenger),
	droppedObjectView_(_droppedObjectView)
{
}

AppleCollisionComponent::AppleCollisionComponent(IMessenger* _messenger,
	IDroppedObjectView* _droppedObjectView) : CollisionComponent(_messenger),
	droppedObjectView_(_droppedObjectView)
{
}

void AppleCollisionComponent::Init()
{
	CollisionComponent::Init();

	// 自分はゴールグループのコリジョン
	SetGroup(CollisionGroup::DROPPED_ITEM);
	// コリジョンにタグを設定
	SetTag("Apple");
	// コリジョンのオーナーに自分を設定
	SetOwner(this);
	// コリジョンの形状を指定(矩形)
	SetRectCollider(0.0f, 0.0f, 32.0f, 32.0f);
	// コリジョンを活性状態にしておく
	EnableCollider();
	// コリジョンマネージャにコリジョンを登録
	CollisionManager_I->Register(&collider_);
}

void AppleCollisionComponent::Update()
{
	CollisionComponent::Update();

	if (droppedObjectView_)
	{
		Vector2f newPos = { 0.0f,0.0f };
		newPos = droppedObjectView_->GetPosition();
		SetPosition(newPos);
	}

	Reset();
}

void AppleCollisionComponent::Render()
{
	CollisionComponent::Render();
}

void AppleCollisionComponent::Term()
{
	CollisionComponent::Term();
}

void AppleCollisionComponent::HandleMessage(const IEventMessage& _msg)
{

}

void AppleCollisionComponent::Reset()
{
	CollisionComponent::Reset();
}
