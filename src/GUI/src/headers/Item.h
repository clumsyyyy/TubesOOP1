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
	public:
		enum class SlotType {
			INVENTORY,
			CRAFTING,
			RESULT
		};
	private:
		SlotType slotType;
		String^ ID;
		Panel^ container;
		PictureBox^ pictBox;
		ProgressBar^ damageBar;
		Label^ itemQuantity;
		Lib::Item* item = nullptr;
		int index;

		static List<ItemSlot^>^ itemsIns = gcnew List<ItemSlot^>();
		static ItemSlot^ itemRes;
		static Image^ bgSlot = LOAD_IMG("slot.png");
		static Dictionary<String^, Image^>^ images = gcnew Dictionary<String^, Image^>();

		void Craft(Object^ sender, MouseEventArgs^ e);
		void BeginDrag(Object^ sender, MouseEventArgs^ e);
		void DragEnter(Object^ sender, DragEventArgs^ e);
		void DragDrop(Object^ sender, DragEventArgs^ e);
		static ItemSlot^ FromDragEvent(DragEventArgs^ e);
	public:
		ItemSlot(Control::ControlCollection^ controls, SlotType type);
		ItemSlot(int index, Control::ControlCollection^ controls, SlotType type);
		ItemSlot(int index, Control::ControlCollection^ controls, ContextMenuStrip^ contextItemMenu, SlotType type);
		Lib::Item* GetItem();
		String^ GetID();
		int GetIndex();
		SlotType GetSlotType();
		void Update();
		static void InitImages();
		static void UpdateAll();
		static Image^ GetImage(String^ key);
		static ItemSlot^ FromGenericPictureBox(Object^ o);
		static ItemSlot^ FromGenericContextMenuItem(Object^ o);
		static ItemSlot^ FromGenericContextMenu(Object^ o);
	};
}

#endif