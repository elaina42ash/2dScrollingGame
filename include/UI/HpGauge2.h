#pragma once

#include "UIElement.h"
#include "Component/Player/ExecutorComponent/Class/PlayerHealthComponent.h"
#include "Fwk//Graphics.h"
#include "Player/Player.h"

class HpGauge2 : public UIElement
{
public:
	// 初期化
	void Init();
	// 後片付け
	void Term();
	// 更新
	void Update();
	// 描画
	void Render();

	void BindToPlayer(Player* _player);

	// 体力設定（0~1.0の範囲で指定）
	void SetHp(float hp);
private:
	Texture mTexture;
	Sprite mSprite;
};
