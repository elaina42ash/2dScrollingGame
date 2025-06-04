#include "Component/Goal/GoalCollisionComponent.h"

#include "Fwk/Framework.h"

GoalCollisionComponent::GoalCollisionComponent(bool _isActive, IMessenger* _messenger, IStaticObjectView* _staticObjectView) : CollisionComponent(_isActive, _messenger), staticObjectView_(_staticObjectView)
{

}

GoalCollisionComponent::GoalCollisionComponent(IMessenger* _messenger, IStaticObjectView* _staticObjectView) : CollisionComponent(_messenger), staticObjectView_(_staticObjectView)
{

}

void GoalCollisionComponent::Init()
{
	CollisionComponent::Init();

	// 自分はゴールグループのコリジョン
	SetGroup(CollisionGroup::GOAL);
	// コリジョンにタグを設定
	SetTag("Goal");
	// コリジョンのオーナーに自分を設定
	SetOwner(this);
	// コリジョンの形状を指定(矩形)
	SetRectCollider(16.0f, -32.0f, 32.0f, 64.0f);
	// コリジョンを活性状態にしておく
	EnableCollider();
	// コリジョンマネージャにコリジョンを登録
	CollisionManager_I->Register(&collider_);
}

void GoalCollisionComponent::Update()
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

void GoalCollisionComponent::Render()
{
	CollisionComponent::Render();
}

void GoalCollisionComponent::Term()
{
	CollisionComponent::Term();
}

void GoalCollisionComponent::HandleMessage(const IEventMessage& _msg)
{

}

void GoalCollisionComponent::Reset()
{
	CollisionComponent::Reset();
}
