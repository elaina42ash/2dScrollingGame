#pragma once
#include "Component/Common/IComponent.h"
#include "Event/Listener/IMessageListener.h"
#include "Semantic/SemanticDef.h"
#include "StateMachine/IStateMachine.h"

class IStateComponent : virtual public IComponent , public IMessageListener
{
protected:
	using StateID = int;

public:
	virtual ~IStateComponent() override = default;

	virtual bool IsSemanticInputTriggered(GameSemantic::Semantic _semantic) const = 0;

	virtual StateID GetCurrentStateID(IStateMachine* _stateMachine) const = 0;

};
