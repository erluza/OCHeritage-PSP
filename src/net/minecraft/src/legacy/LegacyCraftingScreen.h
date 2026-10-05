#pragma once

#include "net/minecraft/src/GuiScreen.h"

class InventoryPlayer;
class World;
class EntityPlayer;
class RenderItem;
class ItemStack;

class LegacyCraftingScreen : public GuiScreen
{
public:
    static const int_t kCategoryCount = 5;

    LegacyCraftingScreen(InventoryPlayer *playerInventory, World *world, int_t x, int_t y, int_t z,
                         bool is2x2 = false, EntityPlayer *player = nullptr);
    virtual ~LegacyCraftingScreen();

    void initGui() override;
    void drawScreen(int_t mouseX, int_t mouseY, float_t partialTick) override;
    void updateScreen() override;
    void onGuiClosed() override;
    bool doesGuiPauseGame() override { return false; }
    int getOwnerPlayerIndex() const override;

protected:
    bool usesSpecializedMenuNavigation() const override { return true; }
    void keyTyped(char_t c, int_t key) override;
    void mouseClicked(int_t mouseX, int_t mouseY, int_t button) override;

private:
    void handleNavigation(int dirX, int dirY);
    void changeCategory(int dir);
    void changeVariant(int dir);
    void craftCurrentRecipe();
    bool canCraftCurrentRecipe() const;
    void ensureSelectionVisible();
    void drawSlotRect(int_t sx, int_t sy);
    void drawTooltip(ItemStack *stack, int_t mouseX, int_t mouseY);
    bool playerHasIngredient(int_t itemId, int_t itemDamage) const;
    void updateCraftingState();
    uint32_t computeInventoryHash() const;

    bool m_craftingStateDirty;
    bool m_cachedCanCraft;
    bool m_cachedSlotHasIngredient[9];
    uint32_t m_cachedInventoryHash;

    InventoryPlayer *inventory;
    World *world;
    int_t posX, posY, posZ;
    bool is2x2Mode;
    EntityPlayer *entityPlayer;

    int_t selectedCategory;
    int_t visibleCategoryIndices[kCategoryCount];
    int_t visibleCategoryCount;
    int_t selectedVisibleTab;
    int_t selectedGroup[kCategoryCount];
    int_t selectedVariant[kCategoryCount][32];
    int_t scrollOffset[kCategoryCount];

    int_t craftHoldTicks;
    bool ps2ActionReleaseLatch;
    int_t guiLeft;
    int_t guiTop;
    int_t xSize;
    int_t ySize;
    int ownerPlayerIndex;

    static RenderItem *itemRenderer;
};
