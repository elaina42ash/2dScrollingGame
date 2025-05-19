#pragma once

// Sceneクラスを継承するので#include
#include "Scene.h"

// 音源クラスの定義を#include
#include "Fwk/Audio/SoundSource.h"
// MP3ファイルを扱うクラスの#include
#include "Fwk/Audio/MP3Sound.h"

// インゲームシーンクラス
class SceneInGame : public Scene {
public:
	// 初期化
	void Init() override;
	// 終了
	void Term() override;
	// 更新
	void Update() override;
	// 描画
	void Render() override;
private:
	// BGM読み込み用
	MP3Sound mSound;
	// 音源
	SoundSource mSoundSource;
	bool needResetScene = false;
private:
	// 現在のステージ番号
	int mSelectedIndex;
};