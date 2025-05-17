#pragma once
#include "CharacterObject.h"
#include "GameObject.h"
#include "IDetachableObject.h"
#include "Inject.h"
#include "GameObject/GameObjectDef.h"

#pragma warning(push)
#pragma warning(disable:4250)
class DetachableObject : public GameObject,public IDetachableObject
{
private:
	DetachableObjectState objectState_ = DetachableObjectState::NONE;
	Inject<CharacterObject> owner_;

public:
	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	DetachableObjectState GetState() const override final;

	void SetOwner(CharacterObject* _owner);

protected:

	explicit DetachableObject(DetachableObjectState _objectState);

	DetachableObject() = default;
};
#pragma warning(pop)