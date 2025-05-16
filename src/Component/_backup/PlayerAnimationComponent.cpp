#include "Component/PlayerAnimationComponent.h"

#include "Player.h"
#include "Event/MessageUtils.h"
#include "Event/Message/AnimationMessage.h"

void PlayerAnimationComponent::InitTexture(const char* _relativeAddress)
{
	// テクスチャを読み込み
	texture_.Load(_relativeAddress);
}

void PlayerAnimationComponent::InitSprite(const SpriteParams& _params, Texture& _texture)
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
	::CreateAnimationUV(anim[0], ToAnimationName(static_cast<int>(AnimationType::IDLE_FRONT)), 1, 0.0f, false, idle_front);
	// 右向き
	::CreateAnimationUV(anim[1], ToAnimationName(static_cast<int>(AnimationType::IDLE_RIGHT)), 1, 0.0f, false, idle_right);
	// 後向き
	::CreateAnimationUV(anim[2], ToAnimationName(static_cast<int>(AnimationType::IDLE_BACK)), 1, 0.0f, false, idle_back);
	// 左向き
	::CreateAnimationUV(anim[3], ToAnimationName(static_cast<int>(AnimationType::IDLE_LEFT)), 1, 0.0f, false, idle_left);

	// アニメーションデータ作成：歩行時のアニメ
	// 前向き
	::CreateAnimationUV(anim[4], ToAnimationName(static_cast<int>(AnimationType::WALK_FRONT)), 3, 0.45f, true, walk_front);
	// 右向き
	::CreateAnimationUV(anim[5], ToAnimationName(static_cast<int>(AnimationType::WALK_RIGHT)), 3, 0.45f, true, walk_right);
	// 後向き
	::CreateAnimationUV(anim[6], ToAnimationName(static_cast<int>(AnimationType::WALK_BACK)), 3, 0.45f, true, walk_back);
	// 左向き
	::CreateAnimationUV(anim[7], ToAnimationName(static_cast<int>(AnimationType::WALK_LEFT)), 3, 0.45f, true, walk_left);

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
		::CreateAnimationRotation(animDying, ToAnimationName(static_cast<int>(AnimationType::DYING)), 2, 0.5, true, rotDeg);
		// 1で生成したアニメにUVアニメを追加。正面向きにします。
		::AddAnimationUV(animDying, 1, 0.5, idle_front);
		// Spriteにやられた時のアニメを追加
		sprite_.AddAnimation(animDying);
	}
}

const char* PlayerAnimationComponent::ToAnimationName(AnimationID _animationID)
{
	auto it = animationNameTable_.find(_animationID);
	if (it == animationNameTable_.end())
	{
		auto pair = animationNameTable_.insert({ _animationID ,std::to_string(_animationID) });
		return pair.first->second.c_str();
	}
	return it->second.c_str();
}

const char* PlayerAnimationComponent::ToAnimationName(AnimationType _animationType)
{
	return ToAnimationName(static_cast<AnimationID>(_animationType));
}

void PlayerAnimationComponent::AddAnimationRequest(const AnimationRequest& _animationRequest)
{
	frameAnimationRequests_.push_back(_animationRequest);
}

void PlayerAnimationComponent::Reset()
{
	frameAnimationRequests_.clear();
}

PlayerAnimationComponent::PlayerAnimationComponent(Player* _player, Messenger* _messenger, bool _isActive) : Component(_isActive), messenger_(_messenger),player_(_player)
{
}

PlayerAnimationComponent::PlayerAnimationComponent(Player* _player, Messenger* _messenger) : player_(_player), messenger_(_messenger)
{
}

void PlayerAnimationComponent::Init()
{
	Component::Init();
	const Vector2f& mPosition = player_->GetPosition();

	InitTexture("Images/2dAction/player.png");

	SpriteParams params = {
		player_->GetPosition(),
		64.0f,64.0f,
		true,
		0.0f
	};
	InitSprite(params, texture_);

	RegisterPlayerAnimation();

	// 初期のアニメ設定
	sprite_.PlayAnimation(ToAnimationName(AnimationType::IDLE_FRONT));
}

void PlayerAnimationComponent::UpdateCurrentAnimation()
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
		sprite_.PlayAnimation(ToAnimationName(best.animationID), best.animationPlayStyle);
		currentAnimation_ = best.animationID;
		isPlaying_ = true;
	}
}

void PlayerAnimationComponent::Update()
{
	Component::Update();
	const Vector2f& mPosition = player_->GetPosition();
	// スプライトの位置を更新
	sprite_.SetPosition(mPosition);

	UpdateCurrentAnimation();

	// スプライトの更新
	sprite_.Update();

	Reset();
}

void PlayerAnimationComponent::Render()
{
	Component::Render();
	sprite_.Draw();
}

void PlayerAnimationComponent::Term()
{
	Component::Term();
	sprite_.Term();
	texture_.Unload();
}

void PlayerAnimationComponent::HandleMessage(const IEventMessage& _msg)
{
	if (_msg.GetMessageType() == IEventMessage::MessageType::ANIMATION)
	{
		const AnimationMessage* animationMsg = TypeidSystem::SafeCast<AnimationMessage>(&_msg);

		if (!animationMsg)
			return;

		AnimationMessage::AnimationMessageParams params = animationMsg->GetParams();

		AnimationRequest request = {
			params.animationID_,
			params.animationPlayStyle,

		};
		AddAnimationRequest(request);

	}
}
