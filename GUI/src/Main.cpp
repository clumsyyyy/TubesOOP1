#include "headers/Main.h"
#include "headers/Item.h"
#include "headers/AddItemForm.h"
#include "headers/DiscardItemForm.h"
#include "headers/Helper.h"
#include "core/all_headers.hpp"

using namespace Lib;

namespace GUI {
	Main::Main() {
		InitializeComponent();
		//Lib::gm.Load();
		ItemSlot::InitImages();
		this->inventoryPanel->SuspendLayout();
		this->craftingPanel->SuspendLayout();
		this->craftingResult->SuspendLayout();
		
		for (int i = 0; i < 27; i++)
			gcnew ItemSlot(i, this->inventoryPanel->Controls, this->itemMenu, ItemSlot::SlotType::INVENTORY);
		for (int i = 0; i < 9; i++)
			gcnew ItemSlot(i, this->craftingPanel->Controls, ItemSlot::SlotType::CRAFTING);
		gcnew ItemSlot(this->craftingResult->Controls, ItemSlot::SlotType::RESULT);
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
			Lib::GiveHandler(item, to<int>(form->itemQty->Value));
			ItemSlot::UpdateAll();
		}
		delete form;
	}

	void Main::itemMenu_Opening(Object^ sender, CancelEventArgs^ e) {
		ItemSlot^ it = ItemSlot::FromGenericContextMenu(sender);
		if (it == nullptr)
			e->Cancel = true;
		else {
			Lib::Item* item = it->GetItem();
			if (item != nullptr && !item->isUndef()) {
				itemMenu->Items[0]->Visible = item->isTool();
			} else
				e->Cancel = true;
		}
	}

	void Main::itemDiscard_Click(Object^ sender, EventArgs^ e) {
		ItemSlot^ it = ItemSlot::FromGenericContextMenuItem(sender);
		if (it != nullptr) {
			Lib::Item* item = it->GetItem();
			if (item != nullptr && !item->isUndef()) {
				int qty = 1;
				if (item->isNonTool()) {
					DiscardItemForm^ form = gcnew DiscardItemForm(it);
					if (form->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
						qty = to<int>(form->itemQty->Value);
					else
						return;
				}
				Lib::DiscardHandler(it->GetIndex(), qty);
				ItemSlot::UpdateAll();
			}
		}
	}

	void Main::itemUse_Click(Object^ sender, EventArgs^ e) {
		ItemSlot^ it = ItemSlot::FromGenericContextMenuItem(sender);
		if (it != nullptr) {
			try {
				Lib::UseHandler(to<std::string>(it->GetID()));
				ItemSlot::UpdateAll();
			}
			catch (UseException* e) {
				MessageBox::Show(to<String^>(e->getException()));
			}
		}
	}
}
