#pragma once
#include <queue>
#include <unordered_map>

#include "Component.h"
#include "Event/Messenger.h"
#include "Event/Listener/IMessageListener.h"
#include "Fwk/Graphics/Sprite.h"
#include "Fwk/Graphics/Texture.h"
#include "Lib/Math/TVector2.h"

enum class AnimationType
{
	NONE = -1,
	IDLE_FRONT = 1000,
	IDLE_RIGHT,
	IDLE_BACK,
	IDLE_LEFT,
	WALK_FRONT,
	WALK_RIGHT,
	WALK_BACK,
	WALK_LEFT,
	DYING
};

using AnimationID = int;

class Player;
class PlayerAnimationComponent : public Component, public IMessageListener
{
private:
	struct SpriteParams
	{
		Lib::Math::Vector2f position;
		float sizeX;
		float sizeY;
		bool visible;
		float rotDeg;
	};
	struct AnimationRequest
	{
		AnimationID animationID=static_cast<AnimationID>(AnimationType::NONE);
		AnimationPlayStyle animationPlayStyle = AnimationPlayStyle::Default;
		int priority = 0;
		bool force = false;
	};
	Player* player_;
	// 表示用スプライト
	Sprite sprite_;
	// テクスチャ
	Texture texture_;
	unordered_map<AnimationID, string> animationNameTable_;
	Messenger* messenger_;
	std::vector<AnimationRequest> frameAnimationRequests_;
	bool isPlaying_ = false;
	AnimationID currentAnimation_; 
public:
	PlayerAnimationComponent(Player* _player,Messenger* _messenger,bool _isActive);

	explicit PlayerAnimationComponent(Player* _player, Messenger* _messenger);

	void Init() override;
	void UpdateCurrentAnimation();
	void Update() override;
	void Render() override;
	void Term() override;
	void HandleMessage(const IEventMessage& _msg) override;

private:
	void InitTexture(const char* _relativeAddress);
	void InitSprite(const SpriteParams& _params, Texture& _texture);
	void RegisterPlayerAnimation();
	const char* ToAnimationName(AnimationID _animationID);
	const char* ToAnimationName(AnimationType _animationType);
	void AddAnimationRequest(const AnimationRequest& _animationRequest);

protected:
	void Reset() override;
};
