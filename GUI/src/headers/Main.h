#pragma once
#ifndef __MAIN_H
#define __MAIN_H
#include "Item.h"

namespace GUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Text;
	using namespace System::Web;
	using namespace std;
	/// <summary>
	/// Summary for Main
	/// </summary>
	public ref class Main : public System::Windows::Forms::Form
	{
	public:
		Main();

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Main();
	private: System::Windows::Forms::TableLayoutPanel^ craftingPanel;
	private: System::Windows::Forms::TableLayoutPanel^ inventoryPanel;
	private: System::Windows::Forms::MenuStrip^ menuBar;
	private: System::Windows::Forms::ToolStripMenuItem^ itemMenuBar;

	private: System::Windows::Forms::ToolStripMenuItem^ itemAdd;
	private: System::Windows::Forms::ToolStripMenuItem^ systemMenuBar;

	private: System::Windows::Forms::ToolStripMenuItem^ systemExport;






	private: System::Windows::Forms::ContextMenuStrip^ itemMenu;
	private: System::Windows::Forms::ToolStripMenuItem^ itemUse;

	private: System::Windows::Forms::ToolStripMenuItem^ itemDiscard;
	private: System::Windows::Forms::FlowLayoutPanel^ craftingResult;

	private: System::Windows::Forms::Label^ CraftingLabel;
	private: System::Windows::Forms::Label^ InventoryLabel;









	private: System::ComponentModel::IContainer^ components;




	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Main::typeid));
			this->craftingPanel = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->inventoryPanel = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->menuBar = (gcnew System::Windows::Forms::MenuStrip());
			this->itemMenuBar = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->itemAdd = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->systemMenuBar = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->systemExport = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->itemMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->itemUse = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->itemDiscard = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->craftingResult = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->CraftingLabel = (gcnew System::Windows::Forms::Label());
			this->InventoryLabel = (gcnew System::Windows::Forms::Label());
			this->menuBar->SuspendLayout();
			this->itemMenu->SuspendLayout();
			this->SuspendLayout();
			// 
			// craftingPanel
			// 
			this->craftingPanel->ColumnCount = 3;
			this->craftingPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				50)));
			this->craftingPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				50)));
			this->craftingPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				50)));
			this->craftingPanel->Location = System::Drawing::Point(151, 72);
			this->craftingPanel->Margin = System::Windows::Forms::Padding(0);
			this->craftingPanel->Name = L"craftingPanel";
			this->craftingPanel->RowCount = 3;
			this->craftingPanel->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 50)));
			this->craftingPanel->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 50)));
			this->craftingPanel->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 50)));
			this->craftingPanel->Size = System::Drawing::Size(150, 150);
			this->craftingPanel->TabIndex = 1;
			// 
			// inventoryPanel
			// 
			this->inventoryPanel->ColumnCount = 9;
			this->inventoryPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				50)));
			this->inventoryPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				50)));
			this->inventoryPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				50)));
			this->inventoryPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				50)));
			this->inventoryPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				50)));
			this->inventoryPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				50)));
			this->inventoryPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				50)));
			this->inventoryPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				50)));
			this->inventoryPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				50)));
			this->inventoryPanel->Location = System::Drawing::Point(90, 282);
			this->inventoryPanel->Margin = System::Windows::Forms::Padding(0);
			this->inventoryPanel->Name = L"inventoryPanel";
			this->inventoryPanel->RowCount = 3;
			this->inventoryPanel->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 50)));
			this->inventoryPanel->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 50)));
			this->inventoryPanel->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 50)));
			this->inventoryPanel->Size = System::Drawing::Size(450, 150);
			this->inventoryPanel->TabIndex = 2;
			// 
			// menuBar
			// 
			this->menuBar->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuBar->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->itemMenuBar, this->systemMenuBar });
			this->menuBar->Location = System::Drawing::Point(0, 0);
			this->menuBar->Name = L"menuBar";
			this->menuBar->Size = System::Drawing::Size(646, 24);
			this->menuBar->TabIndex = 3;
			this->menuBar->Text = L"menuStrip1";
			// 
			// itemMenuBar
			// 
			this->itemMenuBar->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->itemAdd });
			this->itemMenuBar->Name = L"itemMenuBar";
			this->itemMenuBar->Size = System::Drawing::Size(43, 20);
			this->itemMenuBar->Text = L"Item";
			// 
			// itemAdd
			// 
			this->itemAdd->Name = L"itemAdd";
			this->itemAdd->Size = System::Drawing::Size(96, 22);
			this->itemAdd->Text = L"Add";
			this->itemAdd->Click += gcnew System::EventHandler(this, &Main::itemAdd_Click);
			// 
			// systemMenuBar
			// 
			this->systemMenuBar->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->systemExport });
			this->systemMenuBar->Name = L"systemMenuBar";
			this->systemMenuBar->Size = System::Drawing::Size(57, 20);
			this->systemMenuBar->Text = L"System";
			// 
			// systemExport
			// 
			this->systemExport->Name = L"systemExport";
			this->systemExport->Size = System::Drawing::Size(108, 22);
			this->systemExport->Text = L"Export";
			this->systemExport->Click += gcnew System::EventHandler(this, &Main::systemExport_Click);
			// 
			// itemMenu
			// 
			this->itemMenu->ImageScalingSize = System::Drawing::Size(20, 20);
			this->itemMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->itemUse, this->itemDiscard });
			this->itemMenu->Name = L"contextMenuStrip1";
			this->itemMenu->Size = System::Drawing::Size(114, 48);
			this->itemMenu->Opening += gcnew System::ComponentModel::CancelEventHandler(this, &Main::itemMenu_Opening);
			// 
			// itemUse
			// 
			this->itemUse->Name = L"itemUse";
			this->itemUse->Size = System::Drawing::Size(113, 22);
			this->itemUse->Text = L"Use";
			this->itemUse->Click += gcnew System::EventHandler(this, &Main::itemUse_Click);
			// 
			// itemDiscard
			// 
			this->itemDiscard->Name = L"itemDiscard";
			this->itemDiscard->Size = System::Drawing::Size(113, 22);
			this->itemDiscard->Text = L"Discard";
			this->itemDiscard->Click += gcnew System::EventHandler(this, &Main::itemDiscard_Click);
			// 
			// craftingResult
			// 
			this->craftingResult->Location = System::Drawing::Point(429, 119);
			this->craftingResult->Name = L"craftingResult";
			this->craftingResult->Size = System::Drawing::Size(50, 50);
			this->craftingResult->TabIndex = 10;
			// 
			// CraftingLabel
			// 
			this->CraftingLabel->AutoSize = true;
			this->CraftingLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->CraftingLabel->ForeColor = System::Drawing::SystemColors::WindowText;
			this->CraftingLabel->Location = System::Drawing::Point(146, 47);
			this->CraftingLabel->Name = L"CraftingLabel";
			this->CraftingLabel->Size = System::Drawing::Size(73, 20);
			this->CraftingLabel->TabIndex = 12;
			this->CraftingLabel->Text = L"Crafting";
			// 
			// InventoryLabel
			// 
			this->InventoryLabel->AutoSize = true;
			this->InventoryLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->InventoryLabel->ForeColor = System::Drawing::SystemColors::WindowText;
			this->InventoryLabel->Location = System::Drawing::Point(85, 257);
			this->InventoryLabel->Name = L"InventoryLabel";
			this->InventoryLabel->Size = System::Drawing::Size(83, 20);
			this->InventoryLabel->TabIndex = 13;
			this->InventoryLabel->Text = L"Inventory";
			// 
			// Main
			// 
			this->BackColor = System::Drawing::SystemColors::MenuBar;
			this->ClientSize = System::Drawing::Size(646, 454);
			this->Controls->Add(this->InventoryLabel);
			this->Controls->Add(this->CraftingLabel);
			this->Controls->Add(this->craftingResult);
			this->Controls->Add(this->inventoryPanel);
			this->Controls->Add(this->craftingPanel);
			this->Controls->Add(this->menuBar);
			this->ForeColor = System::Drawing::SystemColors::ScrollBar;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuBar;
			this->MaximizeBox = false;
			this->Name = L"Main";
			this->Text = L"Minecraft Crafting Table";
			this->menuBar->ResumeLayout(false);
			this->menuBar->PerformLayout();
			this->itemMenu->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private: 
		void itemAdd_Click(Object^ sender, EventArgs^ e);
		void itemDiscard_Click(Object^ sender, EventArgs^ e);
		void itemUse_Click(Object^ sender, EventArgs^ e);
		void itemMenu_Opening(Object^ sender, CancelEventArgs^ e);
		void systemExport_Click(Object^ sender, EventArgs^ e);
};
}

#endif