#include "Component/Sword/SensorLogicalComponent/Class/SwordCollisionComponent.h"
#include "Animation/AnimationDef.h"
#include "Enemy/Enemy.h"
#include "Event/Message/AnimationMsg/SwordAnimationCompletedMsg.h"
#include "Event/Message/AnimationMsg/SwordAnimationKeyframeMsg.h"
#include "Fwk/Framework.h"

SwordCollisionComponent::SwordCollisionComponent(bool _isActive, IMessenger* _messenger, IWeaponView* _swordView) : CollisionComponent(_isActive, _messenger), swordView_(_swordView)
{
}

SwordCollisionComponent::SwordCollisionComponent(IMessenger* _messenger, IWeaponView* _swordView) : CollisionComponent(_messenger), swordView_(_swordView)
{
}

void SwordCollisionComponent::Init()
{
	CollisionComponent::Init();

	// 自分はプレイヤーグループのコリジョン
	SetGroup(CollisionGroup::WEAPON);

	// 衝突対象に敵グループのコリジョンを追加
	AddHitGroup(CollisionGroup::ENEMY);

	// コリジョンにタグを設定
	SetTag(ToTagName(static_cast<int>(CollisionTag::SWORD)));

	// コリジョンのオーナーに自分を設定
	SetOwner(this);

	// コリジョンを非活性にしておく
	DisableCollider();

	// コリジョン衝突時のコールバック関数を設定
	SetCallbackFunctionEx();
}

void SwordCollisionComponent::Update()
{
	CollisionComponent::Update();

	if (swordView_->IsAttacking())
	{
		SetPosition(swordView_->GetPosition());
	}

	Reset();
}

void SwordCollisionComponent::Render()
{
	CollisionComponent::Render();
}

void SwordCollisionComponent::Term()
{
	CollisionComponent::Term();
}

void SwordCollisionComponent::HandleMessage(const IEventMessage& _msg)
{
	const SwordAnimationKeyframeMsg* swordAnimationKeyframeMsg = TypeidSystem::SafeCast<SwordAnimationKeyframeMsg>(&_msg);
	const SwordAnimationCompletedMsg* swordAnimationFinishedMsg = TypeidSystem::SafeCast<SwordAnimationCompletedMsg>(&_msg);

	if (swordAnimationKeyframeMsg)
	{
		int animationID = swordAnimationKeyframeMsg->GetAnimationID();
		SwordAnimationType swordAnimation = static_cast<SwordAnimationType>(animationID);

		int keyFrameIndex = swordAnimationKeyframeMsg->GetKeyFrameIndex();



		switch (keyFrameIndex)
		{
		case 1:
		{
			SetRectCollider(hitRects2[static_cast<int>(swordView_->GetDirection())]);

		}
		break;
		case 2:
		{
			SetRectCollider(hitRects[static_cast<int>(swordView_->GetDirection())]);

		}
		break;
		default:
			break;
		}
		SetPosition(swordView_->GetPosition());
		EnableCollider();
	}

	if (swordAnimationFinishedMsg)
	{
		int animationID = swordAnimationFinishedMsg->GetAnimationID();
		SwordAnimationType swordAnimation = static_cast<SwordAnimationType>(animationID);

		switch (swordAnimation)
		{
		case SwordAnimationType::SWING_RIGHT:
		case SwordAnimationType::SWING_LEFT:
		{
			DisableCollider();
		}
		break;
		default:
			break;
		}
	}
}

void SwordCollisionComponent::Reset()
{
	CollisionComponent::Reset();
}

void SwordCollisionComponent::OnCollisionEx(const Fwk::Collision::CollisionEvent& _collisionEvent)
{
	// 衝突した瞬間のイベントのみ処理をさせる
	if (_collisionEvent.EventType == Fwk::Collision::CollisionEventType::Enter)
	{
		// 相手が敵である場合
		if (_collisionEvent.ColliderB->GetGroup() == (int)CollisionGroup::ENEMY)
		{
			Enemy* pEnemy = (Enemy*)(_collisionEvent.ColliderB->GetOwner());
			DebugLog("Enemy take damage 1");
			pEnemy->OnDamaged(1);
		}
	}
}


