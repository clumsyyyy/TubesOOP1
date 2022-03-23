#include "headers/Item.h"
#include "core/all_headers.hpp"
#include "core/components/headers/crafting.hpp"

using namespace Lib;
namespace GUI {
	void ItemSlot::Craft(Object^ sender, MouseEventArgs^ e) {
		try {
			Lib::CraftingHandler();
			ItemSlot::UpdateAll();
		} catch (CraftingException* e) {
			MessageBox::Show(to<String^>(e->getException()));
		}
	}

	void ItemSlot::BeginDrag(Object^ sender, MouseEventArgs^ e) {
		if (e->Button == MouseButtons::Left)
			to<Control^>(sender)->DoDragDrop(this, DragDropEffects::Move);
	}

	void ItemSlot::DragEnter(Object^ sender, DragEventArgs^ e) {
		ItemSlot^ FromObj = FromDragEvent(e);
		ItemSlot^ ToObj = FromGenericPictureBox(sender);
		if (FromObj != nullptr && ToObj != nullptr && FromObj != ToObj)
			e->Effect = DragDropEffects::Move;
		else
			e->Effect = DragDropEffects::None;
	}

	void ItemSlot::DragDrop(Object^ sender, DragEventArgs^ e) {
		ItemSlot^ FromObj = FromDragEvent(e);
		ItemSlot^ ToObj = FromGenericPictureBox(sender);
		try {
			Lib::MoveHandler(
				to<std::string>(FromObj->ID),
				1,
				std::vector<std::string>{to<std::string>(ToObj->ID)}
			);
		} catch (MoveException* e) {
			MessageBox::Show(to<String^>(e->getException()));
		}
		UpdateAll();
	}

	ItemSlot^ ItemSlot::FromDragEvent(DragEventArgs^ e) {
		return to<ItemSlot^>(e->Data->GetData("GUI.ItemSlot"));
	}

	ItemSlot^ ItemSlot::FromGenericPictureBox(Object^ sender) {
		return to<ItemSlot^>(to<PictureBox^>(sender)->Tag);
	}

	ItemSlot^ ItemSlot::FromGenericContextMenu(Object^ sender) {
		System::Windows::Forms::ContextMenuStrip^
			c = to<System::Windows::Forms::ContextMenuStrip^>(sender);
		PictureBox^ p = to<PictureBox^>(c->SourceControl);
		return to<ItemSlot^>(p->Tag);
	}

	ItemSlot^ ItemSlot::FromGenericContextMenuItem(Object^ sender) {
		ToolStripMenuItem^ t = to<ToolStripMenuItem^>(sender);
		return FromGenericContextMenu(t->GetCurrentParent());
	}

	ItemSlot::ItemSlot(Control::ControlCollection^ controls, SlotType type) :
		ItemSlot(0, controls, nullptr, type) {}

	ItemSlot::ItemSlot(int index, Control::ControlCollection^ controls, SlotType type) :
		ItemSlot(index, controls, nullptr, type) {}

	ItemSlot::ItemSlot(int index, Control::ControlCollection^ controls, ContextMenuStrip^ contextItemMenu, SlotType type) {
		//
		// Create objects
		//
		this->index = index;
		this->pictBox = (gcnew PictureBox());
		this->damageBar = (gcnew ProgressBar());
		this->itemQuantity = (gcnew System::Windows::Forms::Label());
		this->container = (gcnew System::Windows::Forms::Panel());
		this->slotType = type;
		this->ID = (type == SlotType::INVENTORY ? "I" : (type == SlotType::CRAFTING ? "C" : "")) + to_str(index);
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
		if (type == SlotType::RESULT)
			this->pictBox->MouseDown += gcnew MouseEventHandler(this, &ItemSlot::Craft);
		else {
			this->pictBox->MouseDown += gcnew MouseEventHandler(this, &ItemSlot::BeginDrag);
			this->pictBox->DragEnter += gcnew DragEventHandler(this, &ItemSlot::DragEnter);
			this->pictBox->DragDrop += gcnew DragEventHandler(this, &ItemSlot::DragDrop);
		}
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

		// Tag this object to pictBox
		this->pictBox->Tag = this;
		controls->Add(this->container);
		if (type != SlotType::RESULT)
			itemsIns->Add(this);
		else
			itemRes = this;
	}

	Lib::Item* ItemSlot::GetItem() {
		return item;
	}

	String^ ItemSlot::GetID() {
		return ID;
	}

	int ItemSlot::GetIndex() {
		return index;
	}

	ItemSlot::SlotType ItemSlot::GetSlotType() {
		return slotType;
	}

	void ItemSlot::Update() {
		switch (slotType) {
		case SlotType::CRAFTING:
			item = gm.crftab[index];
			break;
		case SlotType::INVENTORY:
			item = gm.inv[index];
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
			s->Update();
		}
		Crafting craft;
		itemRes->item = craft.crafting_preview();
		itemRes->Update();
	}

	Image^ ItemSlot::GetImage(String^ key) {
		return images[key];
	}

	void ItemSlot::InitImages() {
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
			"GOLD_INGOT",
			"GOLD_NUGGET",
			"DIAMOND",
			"WOODEN_PICKAXE",
			"STONE_PICKAXE",
			"IRON_PICKAXE",
			"GOLDEN_PICKAXE",
			"DIAMOND_PICKAXE",
			"WOODEN_AXE",
			"STONE_AXE",
			"IRON_AXE",
			"GOLDEN_AXE",
			"DIAMOND_AXE",
			"WOODEN_SWORD",
			"STONE_SWORD",
			"IRON_SWORD",
			"GOLDEN_SWORD",
			"DIAMOND_SWORD",
			"WOODEN_HOE",
			"STONE_HOE",
			"IRON_HOE",
			"GOLDEN_HOE",
			"DIAMOND_HOE"
		};
		for (int i = 0; i < listImg->Length; i++) {
			images[listImg[i]] = LOAD_IMG(listImg[i] + ".png");
		}
	}
}