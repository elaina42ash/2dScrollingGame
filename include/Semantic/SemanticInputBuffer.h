#pragma once
#include <unordered_set>

#include "SemanticDef.h"

struct SemanticInputBuffer
{
private:
	std::unordered_set<GameSemantic::Semantic> buffer_;

public:
	void MarkSemanticInput(GameSemantic::Semantic _semantic)
	{
		buffer_.insert(_semantic);
	}

	bool IsSemanticInputTriggered(GameSemantic::Semantic _semantic) const
	{
		return buffer_.count(_semantic)>0;
	}

	void ClearAllSemanticInputs()
	{
		buffer_.clear();
	}
};
