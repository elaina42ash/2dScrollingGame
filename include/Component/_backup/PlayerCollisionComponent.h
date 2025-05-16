#pragma once
#include <unordered_map>

#include "Component.h"
#include "GameDef.h"
#include "Event/Messenger.h"
#include "Fwk/Collision/Collision.h"
using CollisionTagID = int;
class Player;
class PlayerCollisionComponent : public Component
{
private:
	Fwk::Collision::Collision collision_;
	unordered_map<CollisionTagID, string> tagNameTable_;
	Messenger* messenger_;
	Player* player_;
public:
	void Init() override;
	void Update() override;

	explicit PlayerCollisionComponent(Messenger* _messenger, Player* _player);

	PlayerCollisionComponent(bool _isActive, Messenger* _messenger, Player* _player);

private:
	void SetGroup(CollisionGroup _group);

	void AddHitGroup(CollisionGroup _group);

	const char* ToTagName(CollisionTagID _tagID);

	void SetTag(const string& _tag);

	void SetOwner(void* _pOwner);

	void SetPosition(const Vector2f& _position);


	void SetActive(bool _isActive);

	void SetCircle(float _x, float _y, float _r);

	void SetCallbackFunction(const function<void(const Fwk::Collision::Collision& colA, const Fwk::Collision::Collision& colB)>& _OnOverlapped);


	void OnCollision(const Fwk::Collision::Collision& _me, const Fwk::Collision::Collision& _other);
};



