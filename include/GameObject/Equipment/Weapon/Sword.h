#pragma once
#include "Weapon.h"
#include "Event/Message/AnimationMsg/SwordAnimationBeginMsg.h"
#include "Event/Message/AnimationMsg/SwordAnimationCompletedMsg.h"

#pragma warning(push)
#pragma warning(disable:4250)
class Sword : public Weapon
{
public:
	Sword();

	explicit Sword(IEquipOwnerView* _equipOwnerView);

	~Sword() override;

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void Attack() override;

	void EndAttack() override;

	void HandleMessage(const IEventMessage& _msg) override;

	void OnAttackPhaseStarted(int _animationID) override;

	void OnAttackKeyframe(int _animationID, int frameIndex) override;

	void OnAttackCompleted(int _animationID) override;

private:
	void InitializeSwordComponents();
};
#pragma warning(pop)


