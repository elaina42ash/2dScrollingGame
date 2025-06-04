#include "Component/DroppedSword/DroppedSwordCollisionComponent.h"

#include "Fwk/Framework.h"

DroppedSwordCollisionComponent::DroppedSwordCollisionComponent(bool _isActive, IMessenger* _messenger,
	IDroppedObjectView* _droppedObjectView) : CollisionComponent(_isActive, _messenger),
	droppedObjectView_(_droppedObjectView)
{
}

DroppedSwordCollisionComponent::DroppedSwordCollisionComponent(IMessenger* _messenger,
	IDroppedObjectView* _droppedObjectView) : CollisionComponent(_messenger),
	droppedObjectView_(_droppedObjectView)
{
}

void DroppedSwordCollisionComponent::Init()
{
	CollisionComponent::Init();

	// 自分はゴールグループのコリジョン
	SetGroup(CollisionGroup::DROPPED_ITEM);
	// コリジョンにタグを設定
	SetTag("Sword");
	// コリジョンのオーナーに自分を設定
	SetOwner(this);
	// コリジョンの形状を指定(矩形)
	SetRectCollider(16.0f, -16.0f, 32.0f, 32.0f);
	// コリジョンを活性状態にしておく
	EnableCollider();
	// コリジョンマネージャにコリジョンを登録
	CollisionManager_I->Register(&collider_);
}

void DroppedSwordCollisionComponent::Update()
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

void DroppedSwordCollisionComponent::Render()
{
	CollisionComponent::Render();
}

void DroppedSwordCollisionComponent::Term()
{
	CollisionComponent::Term();
}

void DroppedSwordCollisionComponent::HandleMessage(const IEventMessage& _msg)
{

}

void DroppedSwordCollisionComponent::Reset()
{
	CollisionComponent::Reset();
}
