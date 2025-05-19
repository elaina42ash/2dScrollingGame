#pragma once
#include "Weapon.h"
#include "Event/Message/AnimationMsg/SwordAnimationBeginMsg.h"

#pragma warning(push)
#pragma warning(disable:4250)
class Katana : public Weapon
{
public:
	Katana();

	explicit Katana(IEquipOwnerView* _equipOwnerView);

	~Katana() override;

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
	void InitializeKatanaComponents();
};
#pragma warning(pop)


