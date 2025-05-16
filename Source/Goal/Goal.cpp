#include "Goal.h"

// CollisionManagerを使うために必要なのでinclude
#include "Fwk/Framework.h"

// CollisionGroupを使うために必要
#include "GameDef.h"
#include "Collision/CollisionDef.h"

// 初期化
void Goal::Init()
{
	// テキスチャの読み込み
	mTexture.Load("Images/2dAction/Goal.png");
	
	// Spriteの初期化と各種設定
	mSprite.Init();
	mSprite.SetTexture(mTexture);
	mSprite.SetSize(64.0f,128.0f);

	// コリジョンの設定
	{
		// 自分はゴールグループのコリジョン
		mCollision.SetGroup((int)CollisionGroup::GOAL);
		// コリジョンにタグを設定
		mCollision.SetTag("Goal");
		// コリジョンのオーナーに自分を設定
		mCollision.SetOwner(this);
		// コリジョンの形状を指定(矩形)
		mCollision.SetRect(-32.0f,-64.0f,64.0f,128.0f);
		// コリジョンを活性状態にしておく
		mCollision.SetActive(true);
		// コリジョンマネージャにコリジョンを登録
		CollisionManager_I->Register(&mCollision);
	}
}

// 終了
void Goal::Term()
{
	// コリジョンマネージャから登録解除
	CollisionManager_I->Unregister(&mCollision);
	mSprite.Term();
	mTexture.Unload();
}

// 更新
void Goal::Update()
{
	// スプライトの更新
	mSprite.Update();
}

// 描画
void Goal::Render()
{
	mSprite.Draw();
}


// 位置設定
void Goal::SetPosition(Vector2f position)
{
	// スプライトの位置を更新
	mSprite.SetPosition(position);
	// コリジョンの位置も更新
	mCollision.SetPosition(position);
}