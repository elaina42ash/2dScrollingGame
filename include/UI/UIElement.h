#pragma once
#include "IUIElement.h"

class UIElement : public IUIElement
{
public:
	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;
};
