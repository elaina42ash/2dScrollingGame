#pragma once
#include "Fwk/Audio/SoundSource.h"
#include "Fwk/Audio/WaveSound.h"
#include "Fwk/Collision/Collider.h"
#include "Fwk/Graphics/Sprite.h"
#include "Fwk/Graphics/Texture.h"
#include "GameObject/CharacterObject.h"

class GameObjectMng;
class Enemy : public CharacterObject
{
public:
	// 初期化
	void Init() override;
	// 終了
	void Term() override;
	// 更新
	void Update() override;
	// 描画
	void Render() override;


	// 現在位置を取得
	Lib::Math::Vector2f GetPosition();

	// 現在位置を設定
	void SetPosition(Lib::Math::Vector2f position);

	// ダメージを受ける
	virtual void OnDamaged(int damage);

	// 生成された時に呼び出す
	// 派生クラスで上書きして使う
	virtual void OnCreated();

	void EnableCollision();

	void DisableCollision();

protected:
	Enemy() = default;

private:
	// やられたときに呼びされる
	// 派生クラスで上書きして使う
	virtual void OnDefeated();

protected:
	Inject<GameObjectMng> gameObjectMng_;
	// 描画用テクスチャ
	Texture mTexture;
	// 描画用スプライト
	Sprite mSprite;
	// 現在の位置
	Vector2f mPosition;
	// コリジョン
	Fwk::Collision::Collider collision_;
	// 体力
	int mHP;
	// ダメージ時に加算する赤色の強さ（0.0~1.0）
	float mDamagedColor;
	// 効果音
	WaveSound mSound;
	// 音源
	SoundSource mSoundSource;
};
