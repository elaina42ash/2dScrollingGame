#include "Component/Sword/ExecutorComponent/Class/SwordAnimationComponent.h"

#include "Animation/AnimationDef.h"
#include "Component/Common/ExecutorComponent/Interface/ITransformComponent.h"
#include "Event/Message/AnimationMsg/SwordAnimationBeginMsg.h"
#include "Event/Message/AnimationMsg/SwordAnimationCompletedMsg.h"
#include "Event/Message/AnimationMsg/SwordAnimationKeyframeMsg.h"
#include "Fwk/Framework.h"

SwordAnimationComponent::SwordAnimationComponent(bool _isActive, IMessenger* messenger_, IWeaponView* _swordView) : AnimationComponent(_isActive, messenger_),
swordView_(_swordView)
{
}

SwordAnimationComponent::SwordAnimationComponent(IMessenger* messenger_, IWeaponView* _swordView) : AnimationComponent(messenger_),
swordView_(_swordView)
{
}

void SwordAnimationComponent::Init()
{
	AnimationComponent::Init();

	ITransformComponent* transformComponent = GetComponent<ITransformComponent>();

	Vector2f pos = { 0.0f,0.0f };
	if (transformComponent)
		pos = transformComponent->GetPosition();

	InitTexture("Images/2dAction/sword.png");

	SpriteParams params = {
	pos,
	128.0f,64.0f,
	false,
	0.0f
	};

	InitSprite(params, texture_);

	RegisterSwordAnimation();
}

void SwordAnimationComponent::HandleSwordSwingAnimation()
{
	AnimationRequest animationRequest = {
		static_cast<int>(SwordAnimationType::NONE),
		AnimationPlayStyle::Default,
		10,
		true,
	};

	switch (swordView_->GetDirection())
	{
	case Direction::RIGHT:animationRequest.animationID = static_cast<int>(SwordAnimationType::SWING_RIGHT);
		break;
	case Direction::LEFT:animationRequest.animationID = static_cast<int>(SwordAnimationType::SWING_LEFT);
		break;
	default:
		break;
	}

	AddAnimationTask(animationRequest);
}

void SwordAnimationComponent::Update()
{
	Lib::Math::Vector2f _newPos = { 0.0f,0.0f };
	if (swordView_)
		_newPos = swordView_->GetPosition();

	// スプライトの位置を更新
	SetSpritePosition(_newPos);

	if (swordView_->IsAttacking() && !hasTriggeredAttack_)
	{
		HandleSwordSwingAnimation();
		SetVisible(true);
		hasTriggeredAttack_ = true;
	}

	AnimationComponent::Update();

	// スプライトの更新
	UpdateSprite();

	Reset();
}

void SwordAnimationComponent::Render()
{
	AnimationComponent::Render();

	DrawSprite();
}

void SwordAnimationComponent::Term()
{
	AnimationComponent::Term();
}

void SwordAnimationComponent::HandleMessage(const IEventMessage& _msg)
{

}

void SwordAnimationComponent::Reset()
{
	AnimationComponent::Reset();
}

void SwordAnimationComponent::OnAnimationEvent(const AnimationEvent& _animEvent)
{
	switch (_animEvent.EventType)
	{
	case AnimationEventType::Begin:
	{
		SwordAnimationBeginMsg swordAnimationBegin(currentAnimationID_);
		SendMsg(swordAnimationBegin);
	}
	break;

	case AnimationEventType::KeyframeProgressed:
	{

		if (_animEvent.KeyFrameIndex == 1 || _animEvent.KeyFrameIndex == 2)
		{
				SwordAnimationKeyframeMsg swordAnimationKeyframeMsg(currentAnimationID_, _animEvent.KeyFrameIndex);
				SendMsg(swordAnimationKeyframeMsg);
		}
	}
	break;

	case AnimationEventType::Completed:
	{
		
		SwordAnimationCompletedMsg swordAnimationFinishedMsg(currentAnimationID_);
		SendMsg(swordAnimationFinishedMsg);
		hasTriggeredAttack_ = false;
	}
	break;
	default:
		break;
	}
}

void SwordAnimationComponent::RegisterSwordAnimation()
{
	// パターン１つ分のUV座標上の幅と高さ
	float uvW = 1.0f / 4.0f;
	float uvH = 1.0f / 2.0f;

	// 8パターン分のUV座標とPivot
	SpriteCell cells[8] = {
		{{uvW * 0.0f,0.0f,uvW,uvH},{0.5f,-0.5f}}, // 0 上
		{{uvW * 1.0f,0.0f,uvW,uvH},{0.0f,0.0f}}, // 1 右上
		{{uvW * 2.0f,0.0f,uvW,uvH},{0.0f,0.5f}}, // 2 右
		{{uvW * 3.0f,0.0f,uvW,uvH},{0.0f,1.0f}}, // 3 右下

		{{uvW * 0.0f,0.5f,uvW,uvH},{0.5f,1.5f}}, // 4 下
		{{uvW * 1.0f,0.5f,uvW,uvH},{1.0f,1.0f}}, // 5 左下
		{{uvW * 2.0f,0.5f,uvW,uvH},{1.0f,0.5f}}, // 6 左
		{{uvW * 3.0f,0.5f,uvW,uvH},{1.0f,0.0f}}, // 7 左上
	};

	// UV・Pivot設定リスト　右に剣を振る
	SpriteCell swing_right[]{
		cells[0], // 0 上
		cells[1], // 1 右上
		cells[2], // 2 右
		{}
	};

	// UV・Pivot設定リスト　左に剣を振る
	SpriteCell swing_left[]{
		cells[0], // 0 上
		cells[7], // 7 左上
		cells[6], // 6 左
		{}
	};

	// キーフレームの時刻
	float keyTimes[] = {
		0.0f,
		0.05f,
		0.10f,
		0.25f
	};


	// アニメーションデータ
	Animation anim[2];
	CreateAnimationSpriteCell(anim[0], ToAnimationName(static_cast<int>(SwordAnimationType::SWING_LEFT)), 4, keyTimes, false, swing_left);
	CreateAnimationSpriteCell(anim[1], ToAnimationName(static_cast<int>(SwordAnimationType::SWING_RIGHT)), 4, keyTimes, false, swing_right);


	for (int i = 0; i < 2; i++)
	{
		// 各アニメーションにイベントのコールバック関数を登録する
		anim[i].SetEventCallback(CreateAnimationEventCallback(SwordAnimationComponent::OnAnimationEvent));
		// アニメーションをスプライト
		sprite_.AddAnimation(anim[i]);
	}

	// 描画プライオリティ上げておく
	sprite_.SetPriority(10);
}
