#pragma once
static const char* BGM_URL = "Sound/bgm.mp3";

// 方向を示す定数
enum class Direction {
	NONE=-1,

	FIRST = 0,
	RIGHT = FIRST,
	LEFT,

	COUNT
};

// シーン種別
enum class SceneType {
	None = -1,
	Title,
	InGame,
	GameOver,
	GameClear,
	StageSelect,
	Introduction,
};
