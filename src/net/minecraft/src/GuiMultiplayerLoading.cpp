#include "GuiMultiplayerLoading.h"
#include "GuiMultiplayer.h"
#include "Minecraft.h"
#include "FontRenderer.h"

GuiMultiplayerLoading::GuiMultiplayerLoading(GuiScreen *parent)
	: parentScreen(parent)
	, frameCount(0)
	, triggered(false)
{
}

void GuiMultiplayerLoading::initGui()
{
	controlList.clear();
}

void GuiMultiplayerLoading::updateScreen()
{
	++frameCount;
	if (frameCount >= 2 && !triggered && mc != nullptr)
	{
		triggered = true;
		mc->displayGuiScreen(new GuiMultiplayer(parentScreen));
	}
}

void GuiMultiplayerLoading::drawScreen(int_t mouseX, int_t mouseY, float_t partialTick)
{
	(void)mouseX;
	(void)mouseY;
	(void)partialTick;

	drawDefaultBackground();

	const int_t modalWidth = 320;
	const int_t modalHeight = 90;
	const int_t x0 = (width - modalWidth) / 2;
	const int_t y0 = (height - modalHeight) / 2;
	const int_t x1 = x0 + modalWidth;
	const int_t y1 = y0 + modalHeight;

	// Panel modal oscuro translúcido con bordes contrastados
	drawGradientRect(x0, y0, x1, y1, 0xEE141414, 0xEE141414);
	drawGradientRect(x0, y0, x1, y0 + 1, 0xFF888888, 0xFF888888);
	drawGradientRect(x0, y1 - 1, x1, y1, 0xFF444444, 0xFF444444);
	drawGradientRect(x0, y0, x0 + 1, y1, 0xFF888888, 0xFF888888);
	drawGradientRect(x1 - 1, y0, x1, y1, 0xFF444444, 0xFF444444);

	FontRenderer *font = fontRenderer;
	if (font != nullptr)
	{
		drawCenteredString(font, "Modo Multijugador / Multiplayer", width / 2, y0 + 14, 0xFFFFAA);
		drawCenteredString(font, "Iniciando subsistemas y adaptadores de red...", width / 2, y0 + 36, 0xFFFFFF);
		drawCenteredString(font, "La carga puede demorar unos segundos. Sea paciente.", width / 2, y0 + 52, 0xCCCCCC);
		drawCenteredString(font, "Network initialization in progress. Please wait...", width / 2, y0 + 66, 0x888888);
	}
}
