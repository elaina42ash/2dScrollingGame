#include "Enemy.h"
#include "Collision/CollisionDef.h"
#include "Fwk/Framework.h"
#include "GameObjectMng/GameObjectMng.h"

// 初期化
void Enemy::Init()
{
	CharacterObject::Init();
	// 状態をアクティブに
	mIsActive = true;

	// 被ダメージ音を読み込む
	mSound.Load("Sound/damageE.wav");

	// 音源の初期化
	mSoundSource.Init(mSound, 1);

	// コリジョンの設定(共通の項目のみ)
	{
		// 自分は敵グループのコリジョン
		collision_.SetGroup((int)CollisionGroup::ENEMY);
		// 衝突対象にプレイヤーグループのコリジョンを追加
		collision_.AddHitGroup((int)CollisionGroup::PLAYER);
		// コリジョンのオーナーに自分を設定
		collision_.SetOwner(this);
		// コリジョンを活性状態にしておく
		collision_.SetActive(true);
		// コリジョンマネージャにコリジョンを登録
		CollisionManager_I->Register(&collision_);
	}

	// ダメージ時に付ける赤色
	mDamagedColor = 0.0f;
}

// 後片付け
void Enemy::Term()
{
	CharacterObject::Term();
	// コリジョンマネージから登録解除
	CollisionManager_I->Unregister(&collision_);

	mSprite.Term();
	mTexture.Unload();

	// サウンドの破棄
	mSound.Unload();
	// 音源の解放
	mSoundSource.Term();
}

// 更新
void Enemy::Update()
{
	CharacterObject::Update();
	// スプライトを更新
	mSprite.Update();
	// スプライトの位置を更新
	mSprite.SetPosition(mPosition);
	// コリジョンの位置を更新
	collision_.SetPosition(mPosition);

	// ダメージ時に加算する色（赤）の強さが0でなければ
	if (mDamagedColor > 0.0f)
	{
		// 0.25秒くらいで０に戻るように減算
		mDamagedColor -= Time_I->GetDeltaTime() * 4.0f;
		// マイナスの値にならないように調整
		if (mDamagedColor < 0.0f)
		{
			mDamagedColor = 0.0f;
		}
		// 加算する赤色の強さを指定
		mSprite.SetAdditionalColor(mDamagedColor, 0.0f, 0.0f);
	}
}

// 描画
void Enemy::Render()
{
	CharacterObject::Render();
	// アクティブでなければ描画処理は行わない
	if (!IsActive())
	{
		return;
	}

	mSprite.Draw();
}

// アクティブか？
bool Enemy::IsActive()
{
	return mIsActive;
}

// 現在位置を取得
Vector2f Enemy::GetPosition()
{
	return mPosition;
}


// 現在位置を設定
void Enemy::SetPosition(Vector2f position)
{
	mPosition = position;
	mSprite.SetPosition(mPosition);
	// コリジョンの位置も更新
	collision_.SetPosition(mPosition);
}

// ダメージを受ける
void Enemy::OnDamaged(int damage)
{
	mHP -= damage;
	if (mHP < 0)
	{
		Disable();
		collision_.SetActive(false);
		// やられたときに呼びされる
		// （派生クラスでOnDefeated上書きしていた場合にその関数が呼ばれる）
		OnDefeated();
	}
	// ダメージ時に加算する赤色の強さを最大値（1,0）に設定
	mDamagedColor = 1.0f;
	mSprite.SetAdditionalColor(mDamagedColor, 0.0f, 0.0f);
	// ダメージ音の再生
	mSoundSource.Play();
}

// 生成された時に呼び出す
// 派生クラスで上書きして使う
void Enemy::OnCreated()
{
}

void Enemy::EnableCollision()
{
	collision_.SetActive(true);
}

void Enemy::DisableCollision()
{
	collision_.SetActive(false);
}

void Enemy::InjectGameObjectMng(GameObjectMng* _gameObjectMng)
{
	gameObjectMng_.Bind(_gameObjectMng);
}

// やられたときに呼びされる
// 派生クラスで上書きして使う
void Enemy::OnDefeated()
{
}




