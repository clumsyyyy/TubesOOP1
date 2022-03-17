#include "headers/Main.h"
#include "headers/Item.h"

namespace GUI {
	Main::Main() {
		InitializeComponent();
		this->inventoryPanel->SuspendLayout();
		this->craftingPanel->SuspendLayout();
		this->craftingResult->SuspendLayout();
		for (int i = 0; i < 27; i++)
			gcnew ItemSlot(this->inventoryPanel->Controls, this->itemMenu, ItemSlot::SlotType::INVENTORY);
		for (int i = 0; i < 9; i++)
			gcnew ItemSlot(this->craftingPanel->Controls, nullptr, ItemSlot::SlotType::CRAFTING);
		gcnew ItemSlot(this->craftingResult->Controls, nullptr, ItemSlot::SlotType::RESULT);
		this->inventoryPanel->ResumeLayout();
		this->craftingPanel->ResumeLayout();
		this->craftingResult->ResumeLayout();
	}
	Main::~Main() {
		if (components)
		{
			delete components;
		}
	}
}
