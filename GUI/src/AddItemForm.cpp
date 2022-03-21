#include "headers/AddItemForm.h"
#include "headers/Item.h"

namespace GUI {
	AddItemForm::AddItemForm()
	{
		InitializeComponent();
	}

	AddItemForm::~AddItemForm()
	{
		if (components)
			delete components;
	}

	void AddItemForm::itemSelection_SelectionChangeCommitted(Object^ sender, EventArgs^ e) {
		pictBox->Image = ItemSlot::GetImage((String^)itemSelection->SelectedItem);
	}
}