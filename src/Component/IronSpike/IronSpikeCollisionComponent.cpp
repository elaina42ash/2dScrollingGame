#include "Component/IronSpike/IronSpikeCollisionComponent.h"

#include "Fwk/Framework.h"

IronSpikeCollisionComponent::IronSpikeCollisionComponent(bool _isActive, IMessenger* _messenger): CollisionComponent(_isActive, _messenger)
{
}

IronSpikeCollisionComponent::IronSpikeCollisionComponent(IMessenger* _messenger): CollisionComponent(_messenger)
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
	SetRectCollider(-32.0f, -64.0f, 64.0f, 128.0f);
	// コリジョンを活性状態にしておく
	EnableCollider();
	// コリジョンマネージャにコリジョンを登録
	CollisionManager_I->Register(&collider_);
}

void IronSpikeCollisionComponent::Update()
{
	CollisionComponent::Update();

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
