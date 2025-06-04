#include "Component/Player/SensorLogicalComponent/Class/PlayerCollisionComponent.h"
#include "Component/Common/SensorLogicalComponent/Class/CollisionComponent.h"
#include "Event/IMessenger.h"
#include "Event/Message/SemanticMsg/EndKnockBackSemMsg.h"
#include "Event/Message/SemanticMsg/StartGameVectorySemMsg.h"
#include "Event/Message/SemanticMsg/StartInteractSemMsg.h"
#include "Event/Message/SemanticMsg/StartKnockBackSemMsg.h"
#include "Event/Message/StateMsg/SetIsClearConditionMsg.h"
#include "Event/Message/StateMsg/SetIsDamagedConditionMsg.h"
#include "Fwk/Framework.h"
#include "Player/IPlayerView.h"

PlayerCollisionComponent::PlayerCollisionComponent(bool _isActive, IMessenger* _messenger, IPlayerView* _playerView) : ::CollisionComponent(_isActive, _messenger), playerView_(_playerView)
{
}

PlayerCollisionComponent::PlayerCollisionComponent(IMessenger* _messenger, IPlayerView* _playerView) : CollisionComponent(_messenger), playerView_(_playerView)
{
}

void PlayerCollisionComponent::Init()
{
	CollisionComponent::Init();

	// 自分はプレイヤーグループのコリジョン
	SetGroup(CollisionGroup::PLAYER);

	// 衝突対象に敵グループのコリジョンを追加
	AddHitGroup(CollisionGroup::ENEMY);

	// 衝突対象にゴールグループのコリジョンを追加
	AddHitGroup(CollisionGroup::IRON_SPIKE);

	AddHitGroup(CollisionGroup::DROPPED_ITEM);

	AddHitGroup(CollisionGroup::DOOR);

	AddHitGroup(CollisionGroup::GOAL);

	// コリジョンにタグを設定
	SetTag(ToTagName(static_cast<int>(CollisionTag::PLAYER)));

	// コリジョンのオーナーに自分を設定
	SetOwner(this);

	// コリジョンの形状を指定（円）
	EnableCollider();

	// コリジョン衝突時のコールバック関数を設定
	SetRectCollider(0.0f, 0.0f, 16.0f, 27.0f);

	// コリジョン衝突時のコールバック関数を設定
	SetCallbackFunction();

	SetCallbackFunctionEx();
}

void PlayerCollisionComponent::Update()
{
	if (playerView_)
		// コリジョンの位置更新
		SetPosition(playerView_->GetPosition());

	CollisionComponent::Update();

	Reset();
}

void PlayerCollisionComponent::Render()
{
	CollisionComponent::Render();
}

void PlayerCollisionComponent::Term()
{
	CollisionComponent::Term();
}

void PlayerCollisionComponent::Reset()
{
	CollisionComponent::Reset();
}

void PlayerCollisionComponent::OnCollision(const Fwk::Collision::Collider& _me,
	const Fwk::Collision::Collider& _other)
{
	if (_other.GetGroup() == static_cast<int>(CollisionGroup::ENEMY))
	{
		SetIsDamagedConditionMsg msg(true);
		SendMsg(msg);
	}

	if (_other.GetTag() == "IronSpike")
	{
		SetIsDamagedConditionMsg msg(true);
		SendMsg(msg);
	}


	if (_other.GetTag() == "Goal")
	{
		StartGameVectorySemMsg msg;
		SendMsg(msg);
	}

}

void PlayerCollisionComponent::OnCollisionEx(const Fwk::Collision::CollisionEvent& _collisionEvent)
{
	if (_collisionEvent.EventType == Fwk::Collision::CollisionEventType::Enter)
	{
		if (_collisionEvent.ColliderB->GetGroup() == (int)CollisionGroup::DOOR)
		{
			isDoorTrigger = true;
		}

		if (_collisionEvent.ColliderB->GetGroup() == (int)CollisionGroup::DROPPED_ITEM)
		{
		
		}
	}

	if (_collisionEvent.EventType == Fwk::Collision::CollisionEventType::Exit)
	{
		if (_collisionEvent.ColliderB->GetGroup() == (int)CollisionGroup::DOOR)
		{
			isDoorTrigger = false;
		}
	}
}

void PlayerCollisionComponent::HandleMessage(const IEventMessage& _msg)
{
	const StartKnockBackSemMsg* startKnockBackSemMsg = TypeidSystem::SafeCast<StartKnockBackSemMsg>(&_msg);
	const EndKnockBackSemMsg* endKnockBackSemMsg = TypeidSystem::SafeCast<EndKnockBackSemMsg>(&_msg);
	const StartInteractSemMsg* startInteractSem = TypeidSystem::SafeCast<StartInteractSemMsg>(&_msg);

	if (startKnockBackSemMsg)
	{
		DisableCollider();
	}

	if (endKnockBackSemMsg)
	{
		EnableCollider();
	}

	if (startInteractSem)
	{
		if (isDoorTrigger)
		{
			SetIsClearConditionMsg setIsClearConditionMsg(true);
			SendMsg(setIsClearConditionMsg);
		}
	}
}
