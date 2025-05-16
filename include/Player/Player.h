#pragma once
#include "IEquipOwnerView.h"
#include "IPlayerView.h"
#include "Component/Common/DecisionLogicalComponent/Interface/IStateComponent.h"
#include "Component/Common/ExecutorComponent/Interface/IAnimationComponent.h"
#include "Component/Common/ExecutorComponent/Interface/ICombatStatusComponent.h"
#include "Component/Common/ExecutorComponent/Interface/IEquipmentComponent.h"
#include "Component/Common/ExecutorComponent/Interface/IHealthComponent.h"
#include "Component/Common/ExecutorComponent/Interface/IMovementComponent.h"
#include "Component/Common/ExecutorComponent/Interface/IPhysicsComponent.h"
#include "Component/Common/ExecutorComponent/Interface/ISoundComponent.h"
#include "Component/Common/ExecutorComponent/Interface/ITransformComponent.h"
#include "Component/Common/InputLogicalComponent/Interface/IInputComponent.h"
#include "Component/Common/SensorLogicalComponent/Interface/ICollisionComponent.h"
#include "Component/Common/SensorLogicalComponent/Interface/IGroundSensorComponent.h"
#include "Component/Common/SensorLogicalComponent/Interface/ITileMapSensorComponent.h"
#include "GameObject/GameObject.h"

// コリジョンクラスの名前空間を使う
using namespace Fwk::Collision;


// 向きの定数を使うのでinclude
#include "GameDef.h"

class Player : public GameObject , public IPlayerView,public IEquipOwnerView
{
private:
	IInputComponent* inputComponent_ = nullptr;

	ITileMapSensorComponent* tileMapSensorComponent_ = nullptr;

	IGroundSensorComponent* groundSensorComponent_ = nullptr;

	IStateComponent* stateComponent_ = nullptr;

	IEquipmentComponent* equipmentComponent_ = nullptr;

	IHealthComponent* healthComponent_ = nullptr;

	ITransformComponent* transformComponent_ = nullptr;

	IPhysicsComponent* physicsComponent_ = nullptr;

	IMovementComponent* movementComponent_ = nullptr;

	ICombatStatusComponent* combatStatusComponent_ = nullptr;

	ICollisionComponent* collisionComponent_ = nullptr;

	IAnimationComponent* animationComponent_ = nullptr;

	ISoundComponent* soundComponent_ = nullptr;

public:
	Player();

	virtual ~Player() override;
	void StateComponentSubscribeMsg();

	// プレイヤーの初期化
	void Init() override;

	// プレイヤーの更新
	void Update() override;

	// プレイヤーの描画
	void Render() override;

	// プレイヤーの後片付け
	void Term() override;

	Direction GetDirection() const override;

	Lib::Math::Vector2f GetVelocity() const override;

	float GetVelocityX() const override;

	float GetVelocityY() const override;

	Lib::Math::Vector2f GetPosition() const override;

	float GetPositionX() const override;

	float GetPositionY() const override;

	bool IsAlive() const override;

	bool IsDead() const override;

	bool IsReachedGoal() const override;

	int GetHp() const override;

	float GetNormalizedHp() const override;

	bool Grounded() const override;

	int IsInVincible() const override;

	bool IsAttacking() const override;

	bool IsStageCleared() const override;

	void ResetState();

	int GetRemainingInvincibleFrames() const override;

	void ResetPlayer();
};