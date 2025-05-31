#pragma once

// 使う効果音の種類
enum class PlayerSoundType {
	NONE = -1,
	FIRST = 0,
	JUMP = FIRST,
	KNOCK_BACK,

	COUNT
};

enum class SwordSoundType {
	NONE = -1,
	FIRST = 0,
	ATTACK = FIRST,

	COUNT
};

enum class KatanaSoundType {
	NONE = -1,
	FIRST = 0,
	ATTACK = FIRST,

	COUNT
};