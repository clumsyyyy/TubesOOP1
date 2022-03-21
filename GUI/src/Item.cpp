#include "headers/Item.h"
#include "core/all_headers.hpp"

using namespace Lib;
namespace GUI {
	void ItemSlot::BeginDrag(Object^ sender, MouseEventArgs^ e) {
		if (e->Button == MouseButtons::Left)
			to<Control^>(sender)->DoDragDrop(pictBox, DragDropEffects::Move);
	}

	void ItemSlot::DragEnter(Object^ sender, DragEventArgs^ e) {
		PictureBox^ FromObj = getItemData(e);
		PictureBox^ ToObj = (PictureBox^)sender;
		if (FromObj != nullptr && ToObj != nullptr && FromObj->Tag != ToObj->Tag)
			e->Effect = DragDropEffects::Move;
		else
			e->Effect = DragDropEffects::None;
	}

	void ItemSlot::DragDrop(Object^ sender, DragEventArgs^ e) {
		PictureBox^ FromObj = getItemData(e);
		PictureBox^ ToObj = (PictureBox^)sender;
		try {
			Lib::MoveHandler(
				to<std::string>(FromObj->Tag),
				1,
				std::vector<std::string>{to<std::string>(ToObj->Tag)}
			);
		} catch (...) {
			MessageBox::Show("Error when handling move.");
		}
		UpdateAll();
	}

	PictureBox^ ItemSlot::getItemData(DragEventArgs^ e) {
		return to<PictureBox^>(e->Data->GetData("System.Windows.Forms.PictureBox"));
	}

	ItemSlot::ItemSlot(Control::ControlCollection^ controls, SlotType type) :
		ItemSlot(0, controls, nullptr, type) {}

	ItemSlot::ItemSlot(int idx, Control::ControlCollection^ controls, SlotType type) :
		ItemSlot(idx, controls, nullptr, type) {}

	ItemSlot::ItemSlot(int idx, Control::ControlCollection^ controls, ContextMenuStrip^ contextItemMenu, SlotType type) {
		//
		// Create objects
		//
		this->idx = idx;
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
		this->itemQuantity->Location = Point(29, 0);
		this->itemQuantity->Name = L"itemQuantity";
		this->itemQuantity->Size = Size(21, 14);
		this->itemQuantity->Text = L"64";
		this->itemQuantity->Visible = false;
		this->pictBox->Tag = (slotType == SlotType::INVENTORY ? "I" : (slotType == SlotType::CRAFTING ? "C" : "")) + to_str(idx);
		controls->Add(this->container);
		itemsIns->Add(this);
	}

	Lib::Item* ItemSlot::get_item() {
		return item;
	}

	void ItemSlot::set_item(Lib::Item* item) {
		this->item = item;
		update();
	}

	void ItemSlot::update() {
		switch (slotType) {
		case SlotType::CRAFTING:
			item = gm.crftab[idx];
			break;
		case SlotType::INVENTORY:
			item = gm.inv[idx];
			break;
		}
		if (item != nullptr && item->getID() != UNDEFINED_ID) {
			this->pictBox->Image = images[to<String^>(item->getName())];
			this->itemQuantity->Text = to_str(item->getQuantity());
			this->itemQuantity->Visible = item->getBType() == "NONTOOL" && item->getQuantity() > 1;
			this->damageBar->Value = item->getDurability();
			this->damageBar->Visible = item->getBType() == "TOOL" && item->getDurability() < 10;
		}
		else {
			this->pictBox->Image = nullptr;
			this->itemQuantity->Visible = false;
			this->damageBar->Visible = false;
		}
	}

	void ItemSlot::UpdateAll() {
		for each(ItemSlot ^ s in itemsIns) {
			s->update();
		}
	}

	void ItemSlot::init_images() {
		cli::array<String^>^ listImg = {
			"OAK_LOG",
			"SPRUCE_LOG",
			"BIRCH_LOG",
			"OAK_PLANK",
			"SPRUCE_PLANK",
			"BIRCH_PLANK",
			"STICK",
			"COBBLESTONE",
			"BLACKSTONE",
			"IRON_INGOT",
			"IRON_NUGGET",
			"DIAMOND",
			"WOODEN_PICKAXE",
			"STONE_PICKAXE",
			"IRON_PICKAXE",
			"DIAMOND_PICKAXE",
			"WOODEN_AXE",
			"STONE_AXE",
			"IRON_AXE",
			"DIAMOND_AXE",
			"WOODEN_SWORD",
			"STONE_SWORD",
			"IRON_SWORD",
			"DIAMOND_SWORD"
		};
		for (int i = 0; i < listImg->Length; i++) {
			images[listImg[i]] = LOAD_IMG(listImg[i] + ".png");
		}
	}
}