#include "Component/Common/ExecutorComponent/Class/AnimationComponent.h"

AnimationComponent::AnimationComponent(bool _isActive, IMessenger* messenger_) : ExecutorComponent(_isActive, messenger_)
{
}

AnimationComponent::AnimationComponent(IMessenger* messenger_) :ExecutorComponent(messenger_)
{

}

void AnimationComponent::Init()
{
	ExecutorComponent::Init();
}

void AnimationComponent::Update()
{
	ExecutorComponent::Update();
}

void AnimationComponent::Render()
{
	ExecutorComponent::Render();
}

void AnimationComponent::Term()
{
	ExecutorComponent::Term();

	TermSprite();

	TermTexture();
}

void AnimationComponent::Reset()
{
	ExecutorComponent::Reset();
	frameAnimationRequests_.clear();
}

void AnimationComponent::AddAnimationRequest(const AnimationRequest& _animationRequest)
{
	frameAnimationRequests_.push_back(_animationRequest);
}

void AnimationComponent::UpdateCurrentAnimation()
{
	if (!frameAnimationRequests_.empty())
	{
		std::sort(frameAnimationRequests_.begin(),
			frameAnimationRequests_.end(),
			[](const AnimationRequest& _a, const AnimationRequest& _b)
			{
				return _a.priority > _b.priority;
			}
		);

		const AnimationRequest& best = frameAnimationRequests_.front();
		if (best.force || best.animationID != currentAnimationID_)
		{
			sprite_.PlayAnimation(ToAnimationName(best.animationID), best.animationPlayStyle);
			currentAnimationID_ = best.animationID;
			isPlaying_ = true;
		}
	}
}

void AnimationComponent::InitTexture(const char* _relativeAddress)
{
	// テクスチャを読み込み
	texture_.Load(_relativeAddress);
}

void AnimationComponent::InitSprite(const SpriteParams& _params, Texture& _texture)
{
	// スプライトの初期化
	sprite_.Init();
	sprite_.SetTexture(_texture);
	sprite_.SetSize(_params.sizeX, _params.sizeY);
	sprite_.SetPosition(_params.position);

	// ※追加　やられ状態から復帰してくたときに再表示する必要があるか
	sprite_.SetVisible(_params.visible);
	// ※追加　やられ状態から復帰してくたときに回転をリセットする必要がある
	sprite_.SetRotation(_params.rotDeg);
}

void AnimationComponent::SetVisible(bool _isVisible)
{
	sprite_.SetVisible(_isVisible);
}

void AnimationComponent::SetSpritePosition(const Vector2f& _newPos)
{
	sprite_.SetPosition(_newPos);
}

void AnimationComponent::UpdateSprite()
{
	sprite_.Update();
}

void AnimationComponent::DrawSprite()
{
	sprite_.Draw();
}

void AnimationComponent::AddAnimationTask(const AnimationRequest& _animationRequest)
{
	AddAnimationRequest(_animationRequest);

	if (TaskQueueIsEmpty())
	{
		AddTask([=]()->void
			{
				this->UpdateCurrentAnimation();
			});
	}
}

bool AnimationComponent::IsAnimationPlaying()
{
	return sprite_.IsAnimationPlaying();
}

void AnimationComponent::OnAnimationEvent(const AnimationEvent& _animEvent)
{

}

void AnimationComponent::SetAdditionalColor(float _r, float _g, float _b)
{
	sprite_.SetAdditionalColor(_r, _g, _b);
}


void AnimationComponent::TermSprite()
{
	sprite_.Term();
}

void AnimationComponent::TermTexture()
{
	texture_.Unload();
}

const char* AnimationComponent::ToAnimationName(AnimationID _animationID)
{
	auto it = animationNameTable_.find(_animationID);
	if (it == animationNameTable_.end())
	{
		auto pair = animationNameTable_.insert({ _animationID ,std::to_string(_animationID) });
		return pair.first->second.c_str();
	}
	return it->second.c_str();
}


