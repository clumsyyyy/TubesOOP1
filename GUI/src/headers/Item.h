#ifndef __ITEM_H
#define __ITEM_H
#define LOAD_IMG(X) gcnew Bitmap("resources/icons/" + X)

#include "core/components/headers/item.hpp"
#include <map>
#include "Helper.h"

namespace GUI {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections::Generic;
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
		int idx;
		static Image^ bgSlot = LOAD_IMG("slot.png");
		static List<ItemSlot^>^ itemsIns = gcnew List<ItemSlot^>();

		void BeginDrag(Object^ sender, MouseEventArgs^ e);
		void DragEnter(Object^ sender, DragEventArgs^ e);
		void DragDrop(Object^ sender, DragEventArgs^ e);
		static PictureBox^ getItemData(DragEventArgs^ e);
	public:
		enum class SlotType {
			INVENTORY,
			CRAFTING,
			RESULT
		};
		SlotType slotType;
		ItemSlot(Control::ControlCollection^ controls, SlotType type);
		ItemSlot(int idx, Control::ControlCollection^ controls, SlotType type);
		ItemSlot(int idx, Control::ControlCollection^ controls, ContextMenuStrip^ contextItemMenu, SlotType type);
		Lib::Item* get_item();
		void set_item(Lib::Item* item);
		void update();
		static void init_images();
		static void UpdateAll();
		static Dictionary<String^, Image^>^ images = gcnew Dictionary<String^, Image^>();
	};
}

#endif