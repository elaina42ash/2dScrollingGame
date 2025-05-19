#pragma once
#include <unordered_map>
#include "ExecutorComponent.h"
#include "Inject.h"
#include "Fwk/Graphics.h"
#include "Component/Common/ExecutorComponent/Interface/IAnimationComponent.h"
#include "Lib/Math/TVector2.h"

#pragma warning(push)
#pragma warning(disable:4250)
class AnimationComponent : public ExecutorComponent , public IAnimationComponent
{
	using AnimationID = int;
protected:
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
		AnimationID animationID = -1;
		AnimationPlayStyle animationPlayStyle = AnimationPlayStyle::Default;
		int priority = 0;
		bool force = false;
		bool flip = false;
	};
private:
	unordered_map<AnimationID, string> animationNameTable_;

	std::vector<AnimationRequest> frameAnimationRequests_;

	bool isPlaying_ = false;



protected:
	// 表示用スプライト
	Sprite sprite_;
	// テクスチャ
	Texture texture_;

	AnimationID currentAnimationID_ = -1;

	Inject<IMessenger> messenger_;
public:
	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

protected:
	explicit AnimationComponent(bool _isActive, IMessenger* messenger_);

	AnimationComponent(IMessenger* messenger_);

	void Reset() override;

	void InitTexture(const char* _relativeAddress);

	void InitSprite(const SpriteParams& _params, Texture& _texture);

	void SetVisible(bool _isVisible);

	const char* ToAnimationName(AnimationID _animationID);

	void SetSpritePosition(const Vector2f& _newPos);

	void UpdateSprite();

	void DrawSprite();

	void AddAnimationTask(const AnimationRequest& _animationRequest);

	bool IsAnimationPlaying();

	virtual void OnAnimationEvent(const AnimationEvent& _animEvent);

	void SetAdditionalColor(float _r,float _g,float _b);

private:
	void TermSprite();

	void TermTexture();

	void UpdateCurrentAnimation();

	void AddAnimationRequest(const AnimationRequest& _animationRequest);
};
#pragma warning(pop)