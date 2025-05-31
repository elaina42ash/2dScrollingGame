#include "Component/IronSpike/IronSpikeCollisionComponent.h"

#include "Fwk/Framework.h"

IronSpikeCollisionComponent::IronSpikeCollisionComponent(bool _isActive, IMessenger* _messenger, IStaticObjectView* _staticObjectView): CollisionComponent(_isActive, _messenger),staticObjectView_(_staticObjectView)
{

}

IronSpikeCollisionComponent::IronSpikeCollisionComponent(IMessenger* _messenger, IStaticObjectView* _staticObjectView): CollisionComponent(_messenger), staticObjectView_(_staticObjectView)
{

}

void IronSpikeCollisionComponent::Init()
{
	CollisionComponent::Init();

	// 自分はゴールグループのコリジョン
	SetGroup(CollisionGroup::IronSpike);
	// コリジョンにタグを設定
	SetTag("IronSpike");
	// コリジョンのオーナーに自分を設定
	SetOwner(this);
	// コリジョンの形状を指定(矩形)
	SetRectCollider(32.0f, -16.0f, 64.0f, 32.0f);
	// コリジョンを活性状態にしておく
	EnableCollider();
	// コリジョンマネージャにコリジョンを登録
	CollisionManager_I->Register(&collider_);
}

void IronSpikeCollisionComponent::Update()
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

void IronSpikeCollisionComponent::Render()
{
	CollisionComponent::Render();
}

void IronSpikeCollisionComponent::Term()
{
	CollisionComponent::Term();
}

void IronSpikeCollisionComponent::HandleMessage(const IEventMessage& _msg)
{
		
}

void IronSpikeCollisionComponent::Reset()
{
	CollisionComponent::Reset();
}
