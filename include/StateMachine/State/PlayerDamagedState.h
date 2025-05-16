#pragma once
#include "PlayerState.h"
#include "Fwk/Framework.h"

class PlayerDamagedState :public PlayerState
{
private:
	enum class DamagedPhase
	{
		NONE = -1,
		FIRST = 0,
		KNOCKBACK = FIRST,
		END,
		COUNT
	};
public:
	PlayerDamagedState(IStateMachine* _parent, PlayerStateComponent* _playerStateComponent);

	void Enter() override
	{
		const Player* player = playerStateComponent_->GetPlayer();
		if (player->GetInvincibilityFrames()==0)
		{
			//TODO: 被ダメージ音を再生
			// タイマーをリセット
			mTimer = 0.0f;
			// ステップをリセット
			mStep = 0;
			// ノックバック中に敵に衝突しないようにコリジョンを無効にする
			mCollision.SetActive(false);
			// 速度をリセット
			mVelocity = { 0.0f,0.0f };
			// 自分の体力を減らす
			--mHp;
			// HPが0になったらやられ状態に遷移
			if (mHp == 0)
			{
				_die();
				return;
			}
			// 体力が負数にならないようにしておく
			if (mHp < 0)
			{
				mHp = 0;
			}
			// 残りの体力をデバッグ表示
			string debugStr = "HP=" + to_string(mHp);
			DebugLog(debugStr);
		}
	}

	void Update() override
	{

	}

	void Exit() override;
};
