#include "Component/Sword/SensorLogicalComponent/Class/SwordCollisionComponent.h"
#include "Enemy/Enemy.h"
#include "Event/Message/AnimationMsg/SwordAnimationBeginMsg.h"
#include "Event/Message/AnimationMsg/SwordAnimationCompletedMsg.h"
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

	SetCircleCollider(0, 0, 8.0f);

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
		
		if (swordView_->GetDirection()==Direction::RIGHT)
		{
			SetPosition({ swordView_->GetPosition().x + 16.0f ,swordView_->GetPosition().y });
		}
		else
		{
			SetPosition({ swordView_->GetPosition().x - 16.0f ,swordView_->GetPosition().y });
		}
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
	const SwordAnimationCompletedMsg* swordAnimationFinishedMsg = TypeidSystem::SafeCast<SwordAnimationCompletedMsg>(&_msg);
	const SwordAnimationBeginMsg* swordAnimationBegin = TypeidSystem::SafeCast<SwordAnimationBeginMsg>(&_msg);

	if (swordAnimationBegin)
	{
		EnableCollider();
	}

	if (swordAnimationFinishedMsg)
	{

		DisableCollider();

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


