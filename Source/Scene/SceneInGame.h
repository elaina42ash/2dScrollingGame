#pragma once
#include "Scene.h"
#include "Fwk/Audio/SoundSource.h"
#include "EnemyMng/EnemyMng.h"
#include "Fwk/Audio/MP3Sound.h"
#include "GameObject/StaticObject/IronSpike.h"
#include "Scene/ISceneContext.h"
#include "Scene/ISceneGameplayAPI.h"
#include "StaticObjectMng/StaticObjectMng.h"
#include "Tilemap/Tilemap.h"
#include "UI/UIMng.h"

// インゲームシーンクラス
class SceneInGame : public Scene, public ISceneContext, public ISceneGameplayAPI
{
public:
	SceneInGame() = default;

	explicit SceneInGame(int _sceneIndex);

	// 初期化
	void Init() override;
	// 終了
	void Term() override;
	// 更新
	void Update() override;
	// 描画
	void Render() override;

	float GetTileSize() override;

	bool IsInsideWallRect(Lib::Math::Vector2f _position, float _width, float _height) const override;

	bool IsInsideWallCircle(Lib::Math::Vector2f _position, float _radius) const override;

	void CreateEnemy(const char* _enemyName, Lib::Math::Vector2f _position) override;

private:
	// BGM読み込み用
	MP3Sound mSound;
	// 音源
	SoundSource mSoundSource;
	bool needResetScene = false;
private:

	StaticObjectMng staticObjectMng_;

	EnemyMng enemyMng_;

	Tilemap tilemap_;

	UIMng uiMng_;
};