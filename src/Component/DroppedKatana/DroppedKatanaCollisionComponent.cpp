#include "Component/DroppedKatana/DroppedKatanaCollisionComponent.h"

#include "Fwk/Framework.h"

DroppedKatanaCollisionComponent::DroppedKatanaCollisionComponent(bool _isActive, IMessenger* _messenger,
	IDroppedObjectView* _droppedObjectView) : CollisionComponent(_isActive, _messenger),
	droppedObjectView_(_droppedObjectView)
{
}

DroppedKatanaCollisionComponent::DroppedKatanaCollisionComponent(IMessenger* _messenger,
	IDroppedObjectView* _droppedObjectView) : CollisionComponent(_messenger),
	droppedObjectView_(_droppedObjectView)
{
}

void DroppedKatanaCollisionComponent::Init()
{
	CollisionComponent::Init();

	// 自分はゴールグループのコリジョン
	SetGroup(CollisionGroup::DROPPED_ITEM);
	// コリジョンにタグを設定
	SetTag("Katana");
	// コリジョンのオーナーに自分を設定
	SetOwner(this);
	// コリジョンの形状を指定(矩形)
	SetRectCollider(0.0f, 0.0f, 32.0f, 32.0f);
	// コリジョンを活性状態にしておく
	EnableCollider();
	// コリジョンマネージャにコリジョンを登録
	CollisionManager_I->Register(&collider_);
}

void DroppedKatanaCollisionComponent::Update()
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

void DroppedKatanaCollisionComponent::Render()
{
	CollisionComponent::Render();
}

void DroppedKatanaCollisionComponent::Term()
{
	CollisionComponent::Term();
}

void DroppedKatanaCollisionComponent::HandleMessage(const IEventMessage& _msg)
{

}

void DroppedKatanaCollisionComponent::Reset()
{
	CollisionComponent::Reset();
}
