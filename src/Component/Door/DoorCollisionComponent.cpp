#include "Component/Door/DoorCollisionComponent.h"

#include "Fwk/Framework.h"

DoorCollisionComponent::DoorCollisionComponent(bool _isActive, IMessenger* _messenger, IStaticObjectView* _staticObjectView) : CollisionComponent(_isActive, _messenger), staticObjectView_(_staticObjectView)
{

}

DoorCollisionComponent::DoorCollisionComponent(IMessenger* _messenger, IStaticObjectView* _staticObjectView) : CollisionComponent(_messenger), staticObjectView_(_staticObjectView)
{

}

void DoorCollisionComponent::Init()
{
	CollisionComponent::Init();

	// 自分はゴールグループのコリジョン
	SetGroup(CollisionGroup::IRON_SPIKE);
	// コリジョンにタグを設定
	SetTag("Door");
	// コリジョンのオーナーに自分を設定
	SetOwner(this);
	// コリジョンの形状を指定(矩形)
	SetRectCollider(32.0f, -16.0f, 64.0f, 32.0f);
	// コリジョンを活性状態にしておく
	EnableCollider();
	// コリジョンマネージャにコリジョンを登録
	CollisionManager_I->Register(&collider_);
}

void DoorCollisionComponent::Update()
{
	CollisionComponent::Update();

	if (staticObjectView_)
	{
		Vector2f newPos = { 0.0f,0.0f };
		newPos = staticObjectView_->GetPosition();
		SetPosition(newPos);
	}

	Reset();
}

void DoorCollisionComponent::Render()
{
	CollisionComponent::Render();
}

void DoorCollisionComponent::Term()
{
	CollisionComponent::Term();
}

void DoorCollisionComponent::HandleMessage(const IEventMessage& _msg)
{

}

void DoorCollisionComponent::Reset()
{
	CollisionComponent::Reset();
}
