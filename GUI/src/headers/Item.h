#ifndef __ITEM_H
#define __ITEM_H
#define LOAD_IMG(X) gcnew Bitmap("resources/" + X)

#include "core/components/headers/item.hpp"
#include <map>
#include "Helper.h"

namespace GUI {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	public ref class ItemSlot {
	private:
		Panel^ container;
		PictureBox^ pictBox;
		ProgressBar^ damageBar;
		Label^ itemQuantity;
		Lib::Item* item = nullptr;
		static Image^ bgSlot = LOAD_IMG("slot.png");

		void BeginDrag(Object^ sender, MouseEventArgs^ e);
		void DragEnter(Object^ sender, DragEventArgs^ e);
		void DragDrop(Object^ sender, DragEventArgs^ e);
		static ItemSlot^ getItemData(DragEventArgs^ e);
	public:
		enum class SlotType {
			INVENTORY,
			CRAFTING,
			RESULT
		};
		SlotType slotType;
		ItemSlot(Control::ControlCollection^ controls, ContextMenuStrip^ contextItemMenu, SlotType type);
		Lib::Item* get_item();
		void set_item(Lib::Item* item);
		void update();
	};
}

#endif