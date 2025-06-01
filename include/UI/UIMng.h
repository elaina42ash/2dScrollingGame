#pragma once
// 体力ゲージ
#include <vector>
#include "GameDef.h"
#include "IUIElement.h"

// UIマネージャ

class UIMng {
public:
	void InitGlobalUI();

	void LoadSceneUI(SceneType type);

	void UnloadSceneUI();

	void Update();

	void Render();                      

	void SetHp(float _hp)
	{
		
	}
private:
	std::vector<IUIElement*> globalUIs_;
	std::vector<IUIElement*> sceneUIs_;
};