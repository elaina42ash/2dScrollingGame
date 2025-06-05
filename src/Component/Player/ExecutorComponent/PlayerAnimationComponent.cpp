#include "Component/Player/ExecutorComponent/Class/PlayerAnimationComponent.h"

#include "Animation/AnimationDef.h"
#include "Component/Common/ExecutorComponent/Interface/IEquipmentComponent.h"
#include "Component/Common/ExecutorComponent/Interface/ITransformComponent.h"
#include "Event/Message/AnimationMsg/KatanaAnimationBeginMsg.h"
#include "Event/Message/AnimationMsg/KatanaAnimationCompletedMsg.h"
#include "Event/Message/AnimationMsg/KatanaAnimationKeyframeMsg.h"
#include "Event/Message/SemanticMsg/StartAttackSemMsg.h"
#include "Event/Message/SemanticMsg/StartIdleSemMsg.h"
#include "Event/Message/SemanticMsg/StartMoveSemMsg.h"
#include "GameObject/Equipment/Equipment.h"
#include "GameObject/Equipment/EquipmentDef.h"
#include "GameObject/Equipment/Weapon/Katana.h"
#include "GameObject/Equipment/Weapon/Sword.h"


PlayerAnimationComponent::PlayerAnimationComponent(bool _isActive, IMessenger* messenger_, IPlayerView* _playerView) : AnimationComponent(_isActive, messenger_),
playerView_(_playerView)
{
}

PlayerAnimationComponent::PlayerAnimationComponent(IMessenger* messenger_, IPlayerView* _playerView) : AnimationComponent(messenger_),
playerView_(_playerView)
{
}

void PlayerAnimationComponent::Init()
{
	AnimationComponent::Init();

	ITransformComponent* transformComponent = GetComponent<ITransformComponent>();

	Vector2f pos = { 0.0f,0.0f };
	if (transformComponent)
		pos = transformComponent->GetPosition();

	InitTexture(IDLE_ANIMATION_URL);

	SpriteParams params = {
		pos,
		48.0f,48.0f,
		true,
		0.0f
	};

	InitSprite(params, texture_);

	RegisterPlayerAnimation();

	// 初期のアニメ設定
	sprite_.PlayAnimation(ToAnimationName(static_cast<AnimationID>(PlayerAnimationType::IDLE)), AnimationPlayStyle::Continue);
}

void PlayerAnimationComponent::Update()
{
	Lib::Math::Vector2f _newPos = { 0.0f,0.0f };
	if (playerView_)
		_newPos = playerView_->GetPosition();

	// スプライトの位置を更新
	SetSpritePosition(_newPos);

	if (playerView_->GetRemainingInvincibleFrames() % 2 == 0)
	{
		SetAdditionalColor(0.0f, 0.0f, 0.0f);
	}
	else
	{
		SetAdditionalColor(0.5f, 0.5f, 0.5f);
	}

	AnimationComponent::Update();

	Reset();
}

void PlayerAnimationComponent::Render()
{
	AnimationComponent::Render();

	;
}

void PlayerAnimationComponent::Term()
{
	AnimationComponent::Term();
}

void PlayerAnimationComponent::Reset()
{
	AnimationComponent::Reset();
}

void PlayerAnimationComponent::InitAnimationFrames(float _uvWidth, float _uvHeight, int _frameCount, int _animationResourceRowIndex, vector<UVRect>& _idleAnimationFrames)
{
	for (size_t i = 0; i < _frameCount; ++i)
	{
		_idleAnimationFrames.push_back({ static_cast<float>(i) * _uvWidth,static_cast<float>(_animationResourceRowIndex) * _uvHeight,_uvWidth,_uvHeight });
	}

}

void PlayerAnimationComponent::RegisterPlayerAnimation()
{
	// UVの幅と高さ
	float uvWidth = 1.0f / static_cast<float>(MAX_ANIMATION_FRAMES);
	float uvHeight = 1.0f / static_cast<float>(MAX_ANIMATION_TYPE);

	vector<UVRect> idleAnimationFrames;

	int idleFrameCount = 10;
	int idleAnimationResourceRowIndex = 0;

	InitAnimationFrames(uvWidth, uvHeight, idleFrameCount, idleAnimationResourceRowIndex, idleAnimationFrames);

	vector<UVRect> runAnimationFrames;

	int runFrameCount = 8;
	int runAnimationResourceRowIndex = 1;
	InitAnimationFrames(uvWidth, uvHeight, runFrameCount, runAnimationResourceRowIndex, runAnimationFrames);

	vector<UVRect> swordAttackAnimationFrames;

	int swordAttackFrameCount = 6;
	int swordAttackAnimationResourceRowIndex = 2;
	InitAnimationFrames(uvWidth, uvHeight, swordAttackFrameCount, swordAttackAnimationResourceRowIndex, swordAttackAnimationFrames);

	vector<UVRect> katanaAttackAnimationFrames;

	int katanaAttackFrameCount = 9;
	int katanaAttackAnimationResourceRowIndex = 3;
	InitAnimationFrames(uvWidth, uvHeight, katanaAttackFrameCount, katanaAttackAnimationResourceRowIndex, katanaAttackAnimationFrames);

	vector<Animation> animations;
	animations.resize(4);
	CreateAnimationUV(animations[0], ToAnimationName(static_cast<int>(PlayerAnimationType::IDLE)), idleFrameCount, 1.0f / static_cast<float>(MAX_ANIMATION_FRAMES) * idleFrameCount, true, idleAnimationFrames.data());
	CreateAnimationUV(animations[1], ToAnimationName(static_cast<int>(PlayerAnimationType::RUN)), runFrameCount, 1.0f / static_cast<float>(MAX_ANIMATION_FRAMES) * runFrameCount, false, runAnimationFrames.data());
	CreateAnimationUV(animations[2], ToAnimationName(static_cast<int>(PlayerAnimationType::ATTACK_SWORD)), swordAttackFrameCount, 1.0f / static_cast<float>(MAX_ANIMATION_FRAMES) * swordAttackFrameCount, false, swordAttackAnimationFrames.data());
	CreateAnimationUV(animations[3], ToAnimationName(static_cast<int>(PlayerAnimationType::ATTACK_KATANA)), katanaAttackFrameCount, 1.0f / static_cast<float>(MAX_ANIMATION_FRAMES) * katanaAttackFrameCount, false, katanaAttackAnimationFrames.data());

	animations[2].SetEventCallback(CreateAnimationEventCallback(PlayerAnimationComponent::OnAnimationEvent));
	animations[3].SetEventCallback(CreateAnimationEventCallback(PlayerAnimationComponent::OnAnimationEvent));

	for (auto it = animations.begin(); it != animations.end(); ++it)
	{
		sprite_.AddAnimation(*it);
	}

}

void PlayerAnimationComponent::HandleMessage(const IEventMessage& _msg)
{
	const StartMoveSemMsg* startMoveSemMsg = TypeidSystem::SafeCast<StartMoveSemMsg>(&_msg);
	const StartIdleSemMsg* startIdleSemMsg = TypeidSystem::SafeCast<StartIdleSemMsg>(&_msg);
	const StartAttackSemMsg* startAttackSemMsg = TypeidSystem::SafeCast<StartAttackSemMsg>(&_msg);

	if (startMoveSemMsg)
	{
		AnimationRequest request = {
			static_cast<AnimationID>(PlayerAnimationType::NONE),
			AnimationPlayStyle::Continue,
			0,
			true,
			false
		};

		if (!playerView_->IsFacingRight())
			request.flip = true;

		request.animationID = static_cast<AnimationID>(PlayerAnimationType::RUN);


		AddAnimationTask(request);

	}

	if (startIdleSemMsg)
	{
		AnimationRequest request = {
	static_cast<AnimationID>(PlayerAnimationType::NONE),
	AnimationPlayStyle::Default,
	0,
	true,
	false
		};

		if (!playerView_->IsFacingRight())
			request.flip = true;

		request.animationID = static_cast<AnimationID>(PlayerAnimationType::IDLE);


		AddAnimationTask(request);
	}

	if (startAttackSemMsg)
	{
		AnimationRequest request = {
static_cast<AnimationID>(PlayerAnimationType::NONE),
AnimationPlayStyle::Default,
0,
true,
false
		};

		if (!playerView_->IsFacingRight())
			request.flip = true;

		IEquipmentComponent* equipmentComponent = GetComponent<IEquipmentComponent>();

		if (!equipmentComponent)
			return;

		const shared_ptr<const IWeapon> equipment = equipmentComponent->GetActiveWeapon();

		if (dynamic_pointer_cast<const Sword>(equipment))
			request.animationID = static_cast<AnimationID>(PlayerAnimationType::ATTACK_SWORD);
		else if (dynamic_pointer_cast<const Katana>(equipment))
			request.animationID = static_cast<AnimationID>(PlayerAnimationType::ATTACK_KATANA);

		AddAnimationTask(request);
	}
}

void PlayerAnimationComponent::OnSwordAnimationEvent(const AnimationEvent& _animEvent)
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

		if (_animEvent.KeyFrameIndex == 2 || _animEvent.KeyFrameIndex == 3)
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
	}
	break;
	default:
		break;
	}
}

void PlayerAnimationComponent::OnKatanaAnimationEvent(const AnimationEvent& _animEvent)
{

	switch (_animEvent.EventType)
	{
	case AnimationEventType::Begin:
	{
		KatanaAnimationBeginMsg katanaAnimationBeginMsg(currentAnimationID_);
		SendMsg(katanaAnimationBeginMsg);
	}
	break;

	case AnimationEventType::KeyframeProgressed:
	{

		if (_animEvent.KeyFrameIndex == 1 || _animEvent.KeyFrameIndex == 2 || _animEvent.KeyFrameIndex == 5)
		{
			KatanaAnimationKeyframeMsg katanaAnimationKeyframeMsg(currentAnimationID_, _animEvent.KeyFrameIndex);
			SendMsg(katanaAnimationKeyframeMsg);
		}
	}
	break;

	case AnimationEventType::Completed:
	{

		KatanaAnimationCompletedMsg katanaAnimationCompletedMsg(currentAnimationID_);
		SendMsg(katanaAnimationCompletedMsg);
	}
	break;
	default:
		break;
	}
}

void PlayerAnimationComponent::OnAnimationEvent(const AnimationEvent& _animEvent)
{
	if (strcmp(_animEvent.Name.c_str(), ToAnimationName(static_cast<AnimationID>(PlayerAnimationType::ATTACK_SWORD))) == 0)
		OnSwordAnimationEvent(_animEvent);
	if (strcmp(_animEvent.Name.c_str(), ToAnimationName(static_cast<AnimationID>(PlayerAnimationType::ATTACK_KATANA))) == 0)
		OnKatanaAnimationEvent(_animEvent);
}
