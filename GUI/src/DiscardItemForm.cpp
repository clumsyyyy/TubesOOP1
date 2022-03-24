#include "headers/DiscardItemForm.h"

namespace GUI {
	DiscardItemForm::DiscardItemForm(ItemSlot^ item)
	{
		InitializeComponent();
		lblSlot->Text = "How much to delete the item in slot " + item->GetID() + "?";
		Lib::NonTool& it = Lib::NonTool::FromItem(item->GetItem());
		pictBox->Image = item->GetImage(to<String^>(it.getName()));
		int max = it.getQuantity();
		itemQty->Maximum = max;
		lblQty->Text = "out of " + max;
	}

	DiscardItemForm::~DiscardItemForm()
	{
		if (components)
		{
			delete components;
		}
	}
}