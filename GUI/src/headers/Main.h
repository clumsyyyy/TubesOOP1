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
			this->craftingPanel->Location = System::Drawing::Point(180, 45);
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
			this->inventoryPanel->Location = System::Drawing::Point(79, 217);
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
			this->itemAdd->Size = System::Drawing::Size(180, 22);
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
			this->systemExport->Size = System::Drawing::Size(180, 22);
			this->systemExport->Text = L"Export";
			// 
			// itemMenu
			// 
			this->itemMenu->ImageScalingSize = System::Drawing::Size(20, 20);
			this->itemMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->itemUse, this->itemDiscard });
			this->itemMenu->Name = L"contextMenuStrip1";
			this->itemMenu->Size = System::Drawing::Size(114, 48);
			// 
			// itemUse
			// 
			this->itemUse->Name = L"itemUse";
			this->itemUse->Size = System::Drawing::Size(113, 22);
			this->itemUse->Text = L"Use";
			// 
			// itemDiscard
			// 
			this->itemDiscard->Name = L"itemDiscard";
			this->itemDiscard->Size = System::Drawing::Size(113, 22);
			this->itemDiscard->Text = L"Discard";
			// 
			// craftingResult
			// 
			this->craftingResult->Location = System::Drawing::Point(429, 91);
			this->craftingResult->Name = L"craftingResult";
			this->craftingResult->Size = System::Drawing::Size(50, 50);
			this->craftingResult->TabIndex = 10;
			// 
			// Main
			// 
			this->ClientSize = System::Drawing::Size(646, 398);
			this->Controls->Add(this->craftingResult);
			this->Controls->Add(this->inventoryPanel);
			this->Controls->Add(this->craftingPanel);
			this->Controls->Add(this->menuBar);
			this->ForeColor = System::Drawing::SystemColors::ControlLight;
			this->MainMenuStrip = this->menuBar;
			this->Name = L"Main";
			this->Text = L"Minecraft Crafting Table";
			this->menuBar->ResumeLayout(false);
			this->menuBar->PerformLayout();
			this->itemMenu->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private: void itemAdd_Click(Object^ sender, EventArgs^ e);
};
}

#endif