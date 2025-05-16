#include  "Component/PlayerCollisionComponent.h"

#include "GameDef.h"
#include "Player.h"
#include "Fwk/Framework.h"

void PlayerCollisionComponent::Init()
{
	Component::Init();

	// コリジョンマネージャにコリジョンを登録
	CollisionManager_I->Register(&collision_);
}

void PlayerCollisionComponent::Update()
{
	Component::Update();

	// コリジョンの位置更新
	SetPosition(player_->GetPosition());
}

PlayerCollisionComponent::PlayerCollisionComponent(Messenger* _messenger, Player* _player) : messenger_(_messenger), player_(_player)
{
}

PlayerCollisionComponent::PlayerCollisionComponent(bool _isActive, Messenger* _messenger, Player* _player) : Component(_isActive), messenger_(_messenger), player_(_player)
{
}


void PlayerCollisionComponent::SetGroup(CollisionGroup _group)
{
	collision_.SetGroup(static_cast<int>(_group));
}

void PlayerCollisionComponent::AddHitGroup(CollisionGroup _group)
{
	collision_.AddHitGroup(static_cast<int>(_group));
}

const char* PlayerCollisionComponent::ToTagName(CollisionTagID _tagID)
{
	auto it = tagNameTable_.find(_tagID);
	if (it == tagNameTable_.end())
	{
		auto pair = tagNameTable_.insert({ _tagID ,std::to_string(_tagID) });
		return pair.first->second.c_str();
	}
	return it->second.c_str();
}

void PlayerCollisionComponent::SetTag(const string& _tag)
{
	collision_.SetTag(_tag);
}

void PlayerCollisionComponent::SetOwner(void* _pOwner)
{
	collision_.SetOwner(_pOwner);
}

void PlayerCollisionComponent::SetPosition(const Vector2f& _position)
{
	collision_.SetPosition(_position);
}

void PlayerCollisionComponent::SetActive(bool _isActive)
{
	collision_.SetActive(_isActive);
}

void PlayerCollisionComponent::SetCircle(float _x, float _y, float _r)
{
	collision_.SetCircle(_x, _y, _r);
}

void PlayerCollisionComponent::SetCallbackFunction(
	const function<void(const Fwk::Collision::Collision& colA, const Fwk::Collision::Collision& colB)>& _OnOverlapped)
{
	collision_.SetCallbackFunction(_OnOverlapped);
}

void PlayerCollisionComponent::OnCollision(const Fwk::Collision::Collision& _me,
                                           const Fwk::Collision::Collision& _other)
{
	if (_other.GetGroup() == (int)CollisionGroup::Enemy)
	{
		ChangeBoolConditionMessageInternal::ChangeBoolConditionMessageParams params = {
			PlayerStateComponent::PlayerConditionID::IS_DAMAGED,
			true
		};
		ChangeBoolConditionMessage changeBoolConditionMsg(params);
		messenger_->SendMSG(changeBoolConditionMsg);
	}
}
