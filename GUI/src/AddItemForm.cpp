#include "headers/AddItemForm.h"
#include "headers/Item.h"

namespace GUI {
	void AddItemForm::itemSelection_SelectionChangeCommitted(Object^ sender, EventArgs^ e) {
		pictBox->Image = ItemSlot::images[(String^)itemSelection->SelectedItem];
	}
}