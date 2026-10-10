#pragma once

#include "GuiScreen.h"

class GuiMultiplayerLoading : public GuiScreen
{
public:
	explicit GuiMultiplayerLoading(GuiScreen *parent);
	virtual ~GuiMultiplayerLoading() = default;

	void initGui() override;
	void updateScreen() override;
	void drawScreen(int_t mouseX, int_t mouseY, float_t partialTick) override;

private:
	GuiScreen *parentScreen;
	int_t frameCount;
	bool triggered;
};
