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

		void BeginDrag(
			Object^ sender,
			MouseEventArgs^ e
		) {
			if (e->Button == MouseButtons::Left)
				safe_cast<Control^>(sender)->DoDragDrop(this, DragDropEffects::Move);
		}

		void DragEnter(
			Object^ sender,
			DragEventArgs^ e
		) {
			if (getItemData(e))
				e->Effect = DragDropEffects::Move;
			else
				e->Effect = DragDropEffects::None;
		}

		void DragDrop(
			Object^ sender,
			DragEventArgs^ e
		) {
			ItemSlot^ slot = getItemData(e);
		}

		static ItemSlot^ getItemData(DragEventArgs^ e) {
			return static_cast<ItemSlot^>(e->Data->GetData("GUI.ItemSlot"));
		}
	public:
		enum class SlotType {
			INVENTORY,
			CRAFTING,
			RESULT
		};
		SlotType slotType;
		ItemSlot(
			Control::ControlCollection^ controls,
			ContextMenuStrip^ contextItemMenu,
			SlotType type
		) {
			//
			// Create objects
			//
			this->pictBox = (gcnew PictureBox());
			this->damageBar = (gcnew ProgressBar());
			this->itemQuantity = (gcnew System::Windows::Forms::Label());
			this->container = (gcnew System::Windows::Forms::Panel());
			this->slotType = type;
			// 
			// container
			// 
			this->container->Controls->Add(this->itemQuantity);
			this->container->Controls->Add(this->damageBar);
			this->container->Controls->Add(this->pictBox);
			this->container->Location = Point(417, 90);
			this->container->Margin = Padding(0);
			this->container->Name = L"container";
			this->container->Size = Size(50, 50);
			this->container->TabIndex = 9;
			// 
			// pictBox
			// 
			this->pictBox->BackgroundImage = bgSlot;
			this->pictBox->BackgroundImageLayout = ImageLayout::Stretch;
			this->pictBox->ContextMenuStrip = contextItemMenu;
			this->pictBox->Name = L"pictBox";
			this->pictBox->Padding = Padding(10);
			this->pictBox->Location = System::Drawing::Point(0, 0);
			this->pictBox->Size = Size(50, 50);
			this->pictBox->SizeMode = PictureBoxSizeMode::StretchImage;
			this->pictBox->TabIndex = 6;
			this->pictBox->TabStop = false;
			this->pictBox->AllowDrop = true;
			this->pictBox->MouseDown += gcnew MouseEventHandler(this, &ItemSlot::BeginDrag);
			this->pictBox->DragEnter += gcnew DragEventHandler(this, &ItemSlot::DragEnter);
			this->pictBox->DragDrop += gcnew DragEventHandler(this, &ItemSlot::DragDrop);
			// 
			// itemDamage
			// 
			this->damageBar->Anchor = static_cast<AnchorStyles>((AnchorStyles::Left | AnchorStyles::Right));
			this->damageBar->Location = Point(13, 37);
			this->damageBar->Name = L"damageBar";
			this->damageBar->Size = Size(27, 3);
			this->damageBar->TabIndex = 7;
			this->damageBar->Maximum = 10;
			this->damageBar->Value = 10;
			this->damageBar->Minimum = 0;
			this->damageBar->Visible = false;
			// 
			// itemQuantity
			// 
			this->itemQuantity->Anchor = static_cast<AnchorStyles>((AnchorStyles::Top | AnchorStyles::Right));
			this->itemQuantity->AutoSize = true;
			this->itemQuantity->BackColor = Color::Black;
			this->itemQuantity->Font = (gcnew Font(L"Courier New", 8.25F, FontStyle::Bold, GraphicsUnit::Point,
				static_cast<Byte>(0)));
			this->itemQuantity->ForeColor = Color::White;
			this->itemQuantity->Location = Point(26, 0);
			this->itemQuantity->Name = L"itemQuantity";
			this->itemQuantity->Size = Size(21, 14);
			this->itemQuantity->Text = L"64";
			this->itemQuantity->Visible = false;
			controls->Add(this->container);
		}

		Lib::Item* get_item() {
			return item;
		}
		void set_item(Lib::Item* item) {
			this->item = item;
			update();
		}
		void update() {
			this->itemQuantity->Text = to_cs_str<int>(item->getQuantity());
			this->itemQuantity->Visible = item->getQuantity() > 1;
			this->damageBar->Value = item->getDurability();
			this->damageBar->Visible = item->getDurability() < 10;
		}
	};
}

#endif