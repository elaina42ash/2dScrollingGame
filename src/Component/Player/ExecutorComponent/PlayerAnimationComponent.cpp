#include "Component/Player/ExecutorComponent/Class/PlayerAnimationComponent.h"

#include "Animation/AnimationDef.h"
#include "Component/Common/ExecutorComponent/Interface/ITransformComponent.h"
#include "Event/Message/SemanticMsg/StartAttackSemMsg.h"
#include "Event/Message/SemanticMsg/StartIdleSemMsg.h"
#include "Event/Message/SemanticMsg/StartMoveSemMsg.h"


PlayerAnimationComponent::PlayerAnimationComponent(bool _isActive, IMessenger* messenger_, IPlayerView* _playerView): AnimationComponent(_isActive, messenger_),
	playerView_(_playerView)
{
}

PlayerAnimationComponent::PlayerAnimationComponent(IMessenger* messenger_, IPlayerView* _playerView): AnimationComponent(messenger_),
	playerView_(_playerView)
{
}

void PlayerAnimationComponent::Init()
{
	AnimationComponent::Init();

	ITransformComponent* transformComponent = GetComponent<ITransformComponent>();

	Vector2f pos ={0.0f,0.0f};
	if (transformComponent)
		pos = transformComponent->GetPosition();

	InitTexture("Images/2dAction/player.png");

	SpriteParams params = {
		pos,
		64.0f,64.0f,
		true,
		0.0f
	};

	InitSprite(params, texture_);

	RegisterPlayerAnimation();

	// 初期のアニメ設定
	sprite_.PlayAnimation(ToAnimationName(static_cast<AnimationID>(PlayerAnimationType::IDLE_RIGHT)));
}

void PlayerAnimationComponent::Update()
{
	Lib::Math::Vector2f _newPos = { 0.0f,0.0f };
	if (playerView_)
		_newPos = playerView_->GetPosition();

	// スプライトの位置を更新
	SetSpritePosition(_newPos);

	if (playerView_->GetRemainingInvincibleFrames()%2==0)
	{
		SetAdditionalColor(0.0f, 0.0f, 0.0f);
	}
	else
	{
		SetAdditionalColor(0.5f, 0.5f, 0.5f);
	}

	AnimationComponent::Update();

	// スプライトの更新
	UpdateSprite();

	Reset();
}

void PlayerAnimationComponent::Render()
{
	AnimationComponent::Render();

	DrawSprite();
}

void PlayerAnimationComponent::Term()
{
	AnimationComponent::Term();
}

void PlayerAnimationComponent::Reset()
{
	AnimationComponent::Reset();
}

void PlayerAnimationComponent::RegisterPlayerAnimation()
{
	// UVの幅と高さ
	float uvW = 1.0f / 8.0f;
	float uvH = 1.0f / 1.0f;

	// スプライトセル構造体リスト（8パターン）
	UVRect uvs[] = {
		{uvW * 0.0f,0.0f,uvW,uvH}, // 前向き　パターン１
		{uvW * 1.0f,0.0f,uvW,uvH}, // 前向き　パターン２
		{uvW * 2.0f,0.0f,uvW,uvH}, // 右向き　パターン１
		{uvW * 3.0f,0.0f,uvW,uvH}, // 右向き　パターン２
		{uvW * 4.0f,0.0f,uvW,uvH}, // 後向き　パターン１
		{uvW * 5.0f,0.0f,uvW,uvH}, // 後向き　パターン２
		{uvW * 6.0f,0.0f,uvW,uvH}, // 左向き　パターン１
		{uvW * 7.0f,0.0f,uvW,uvH} // 左向き　パターン２
	};

	// プレイヤーのアイドル時のアニメ
	UVRect idle_front[] = { uvs[0] }; // 前
	UVRect idle_right[] = { uvs[2] }; // 右
	UVRect idle_back[] = { uvs[4] }; // 後
	UVRect idle_left[] = { uvs[6] }; // 左

	// プレイヤー移動時のアニメ
	// 前
	UVRect walk_front[] = { uvs[0],uvs[1],{} };

	// 右
	UVRect walk_right[] = { uvs[2],uvs[3],{} };

	// 後
	UVRect walk_back[] = { uvs[4],uvs[5],{} };

	// 左
	UVRect walk_left[] = { uvs[6],uvs[7],{} };

	// アニメションデータ
	Animation anim[8];

	// アニメションデータ作成：アイドル時のアニメ
	// 前向き
	::CreateAnimationUV(anim[0], ToAnimationName(static_cast<int>(PlayerAnimationType::IDLE_FRONT)), 1, 0.0f, false, idle_front);
	// 右向き
	::CreateAnimationUV(anim[1], ToAnimationName(static_cast<int>(PlayerAnimationType::IDLE_RIGHT)), 1, 0.0f, false, idle_right);
	// 後向き
	::CreateAnimationUV(anim[2], ToAnimationName(static_cast<int>(PlayerAnimationType::IDLE_BACK)), 1, 0.0f, false, idle_back);
	// 左向き
	::CreateAnimationUV(anim[3], ToAnimationName(static_cast<int>(PlayerAnimationType::IDLE_LEFT)), 1, 0.0f, false, idle_left);

	// アニメーションデータ作成：歩行時のアニメ
	// 前向き
	::CreateAnimationUV(anim[4], ToAnimationName(static_cast<int>(PlayerAnimationType::WALK_FRONT)), 3, 0.45f, true, walk_front);
	// 右向き
	::CreateAnimationUV(anim[5], ToAnimationName(static_cast<int>(PlayerAnimationType::WALK_RIGHT)), 3, 0.45f, true, walk_right);
	// 後向き
	::CreateAnimationUV(anim[6], ToAnimationName(static_cast<int>(PlayerAnimationType::WALK_BACK)), 3, 0.45f, true, walk_back);
	// 左向き
	::CreateAnimationUV(anim[7], ToAnimationName(static_cast<int>(PlayerAnimationType::WALK_LEFT)), 3, 0.45f, true, walk_left);

	// アニメーションをスプライトに登録
	for (int i = 0; i < 8; i++)
	{
		sprite_.AddAnimation(anim[i]);
	}

	// やられ時のアニメを追加
	{
		// 0度→360度の回転アニメーション
		float rotDeg[] = {
			0.0f,360.0f,
		};
		Animation animDying;
		// 回転アニメを生成、キーフレーム数は2。0.5秒で一回転、ループする
		::CreateAnimationRotation(animDying, ToAnimationName(static_cast<int>(PlayerAnimationType::DYING)), 2, 0.5, true, rotDeg);
		// 1で生成したアニメにUVアニメを追加。正面向きにします。
		::AddAnimationUV(animDying, 1, 0.5, idle_front);
		// Spriteにやられた時のアニメを追加
		sprite_.AddAnimation(animDying);
	}
}

void PlayerAnimationComponent::AddPlayerIdleAnimationTask()
{
	AnimationRequest animationRequest = {
		static_cast<AnimationID>(PlayerAnimationType::NONE),
		AnimationPlayStyle::Continue,
		20,
		true
	};

	switch (playerView_->GetDirection())
	{
	case Direction::RIGHT: animationRequest.animationID = static_cast<AnimationID>(PlayerAnimationType::IDLE_RIGHT); break;
	case Direction::LEFT: animationRequest.animationID = static_cast<AnimationID>(PlayerAnimationType::IDLE_LEFT); break;
	default: static_cast<AnimationID>(PlayerAnimationType::IDLE_RIGHT);
	}
	AddAnimationTask(animationRequest);
}

void PlayerAnimationComponent::HandleMessage(const IEventMessage& _msg)
{
	const StartMoveSemMsg* startMoveSemMsg = TypeidSystem::SafeCast<StartMoveSemMsg>(&_msg);
	const StartIdleSemMsg* startIdleSemMsg = TypeidSystem::SafeCast<StartIdleSemMsg>(&_msg);
	const StartAttackSemMsg* startAttackSemMsg = TypeidSystem::SafeCast<StartAttackSemMsg>(&_msg);

	if (startMoveSemMsg)
	{
		Vector2f moveInput = startMoveSemMsg->GetMoveInput();

		AnimationRequest request = {
			static_cast<AnimationID>(PlayerAnimationType::NONE),
			AnimationPlayStyle::Continue,
			0,
			true
		};

		if (moveInput.x > 0)
		{
			request.animationID = static_cast<AnimationID>(PlayerAnimationType::WALK_RIGHT);
		}
		else if (moveInput.x < 0)
		{
			request.animationID = static_cast<AnimationID>(PlayerAnimationType::WALK_LEFT);
		}

		AddAnimationTask(request);

	}

	if (startIdleSemMsg)
	{
		AddPlayerIdleAnimationTask();
	}

	if (startAttackSemMsg)
	{
		AddPlayerIdleAnimationTask();
	}
}
