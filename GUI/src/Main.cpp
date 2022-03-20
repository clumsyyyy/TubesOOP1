#include "headers/Main.h"
#include "headers/Item.h"
#include "headers/AddItemForm.h"
#include "headers/Helper.h"
#include "core/all_headers.hpp"

namespace GUI {
	Main::Main() {
		InitializeComponent();
		Lib::gm.Load();
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
	void Main::itemAdd_Click(Object^ sender, EventArgs^ e) {
		AddItemForm^ form = gcnew AddItemForm();
		if (form->ShowDialog(this) == System::Windows::Forms::DialogResult::OK
			&& form->itemSelection->SelectedItem != nullptr
		) {
			std::string item = to<std::string>((String^)(form->itemSelection->SelectedItem));
			//Lib::GiveHandler(item, to<int>(form->itemQty->Value));
		}
		delete form;
	}
}
