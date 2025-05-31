
#include "Component/Katana/SensorLogicalComponent/Class/KatanaCollisionComponent.h"
#include "Enemy/Enemy.h"
#include "Event/Message/AnimationMsg/KatanaAnimationBeginMsg.h"
#include "Event/Message/AnimationMsg/KatanaAnimationCompletedMsg.h"
#include "Event/Message/AnimationMsg/KatanaAnimationKeyframeMsg.h"
#include "Fwk/Framework.h"
#include "GameObject/Equipment/Weapon/IWeaponView.h"

KatanaCollisionComponent::KatanaCollisionComponent(bool _isActive, IMessenger* _messenger, IWeaponView* _weaponView) : CollisionComponent(_isActive, _messenger), weaponView_(_weaponView)
{
}

KatanaCollisionComponent::KatanaCollisionComponent(IMessenger* _messenger, IWeaponView* _weaponView) : CollisionComponent(_messenger), weaponView_(_weaponView)
{
}

void KatanaCollisionComponent::Init()
{
	CollisionComponent::Init();

	// 自分はプレイヤーグループのコリジョン
	SetGroup(CollisionGroup::WEAPON);

	// 衝突対象に敵グループのコリジョンを追加
	AddHitGroup(CollisionGroup::ENEMY);

	SetCircleCollider(0, 0, 8.0f);

	// コリジョンにタグを設定
	SetTag(ToTagName(static_cast<int>(CollisionTag::KATANA)));

	// コリジョンのオーナーに自分を設定
	SetOwner(this);

	// コリジョンを非活性にしておく
	DisableCollider();

	// コリジョン衝突時のコールバック関数を設定
	SetCallbackFunctionEx();
}

void KatanaCollisionComponent::Update()
{
	CollisionComponent::Update();
	
	if (weaponView_->IsAttacking())
	{
		Vector2f newPos = { 0.0f,0.0f };
		if (weaponView_->GetDirection()==Direction::RIGHT)
			newPos={ weaponView_->GetPosition().x + 16.0f ,weaponView_->GetPosition().y };
		else
			newPos={ weaponView_->GetPosition().x - 16.0f ,weaponView_->GetPosition().y };
		SetPosition(newPos);
	}

	Reset();
}

void KatanaCollisionComponent::Render()
{
	CollisionComponent::Render();
}

void KatanaCollisionComponent::Term()
{
	CollisionComponent::Term();
}

void KatanaCollisionComponent::HandleMessage(const IEventMessage& _msg)
{
	const KatanaAnimationBeginMsg* katanaAnimationBeginMsg = TypeidSystem::SafeCast<KatanaAnimationBeginMsg>(&_msg);
	const KatanaAnimationKeyframeMsg* katanaAnimationKeyframeMsg = TypeidSystem::SafeCast<KatanaAnimationKeyframeMsg>(&_msg);
	const KatanaAnimationCompletedMsg* katanaAnimationCompletedMsg = TypeidSystem::SafeCast<KatanaAnimationCompletedMsg>(&_msg);

	if (katanaAnimationBeginMsg)
	{
		
	}

	if (katanaAnimationKeyframeMsg)
	{
		EnableCollider();
	}

	if (katanaAnimationCompletedMsg)
	{

		DisableCollider();

	}
}

void KatanaCollisionComponent::Reset()
{
	CollisionComponent::Reset();
}

void KatanaCollisionComponent::OnCollisionEx(const Fwk::Collision::CollisionEvent& _collisionEvent)
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


