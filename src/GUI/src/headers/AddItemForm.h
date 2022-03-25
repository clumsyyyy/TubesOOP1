#pragma once

namespace GUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for AddItemForm
	/// </summary>
	public ref class AddItemForm : public System::Windows::Forms::Form
	{
	public:
		AddItemForm();

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~AddItemForm();
	private: System::Windows::Forms::Label^ label1;
	public: System::Windows::Forms::ComboBox^ itemSelection;
	private:
	protected:

	private: System::Windows::Forms::PictureBox^ pictBox;
	private: System::Windows::Forms::Button^ okButton;

	private: System::Windows::Forms::Label^ label2;
	public: System::Windows::Forms::NumericUpDown^ itemQty;
	private:



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->itemSelection = (gcnew System::Windows::Forms::ComboBox());
			this->pictBox = (gcnew System::Windows::Forms::PictureBox());
			this->okButton = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->itemQty = (gcnew System::Windows::Forms::NumericUpDown());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictBox))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->itemQty))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(98, 12);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(162, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Which item did you want to add\?";
			// 
			// itemSelection
			// 
			this->itemSelection->FormattingEnabled = true;
			this->itemSelection->Items->AddRange(gcnew cli::array< System::Object^  >(34) {
				L"OAK_LOG", L"SPRUCE_LOG", L"BIRCH_LOG", L"OAK_PLANK",
					L"SPRUCE_PLANK", L"BIRCH_PLANK", L"STICK", L"COBBLESTONE", L"BLACKSTONE",
					L"IRON_INGOT", L"IRON_NUGGET", L"GOLD_INGOT", L"GOLD_NUGGET", L"DIAMOND",
					L"WOODEN_PICKAXE", L"STONE_PICKAXE", L"IRON_PICKAXE", L"GOLDEN_PICKAXE", L"DIAMOND_PICKAXE",
					L"WOODEN_AXE", L"STONE_AXE", L"IRON_AXE", L"GOLDEN_AXE", L"DIAMOND_AXE",
					L"WOODEN_SWORD", L"STONE_SWORD", L"IRON_SWORD", L"DIAMOND_SWORD", L"GOLDEN_SWORD",
					L"WOODEN_HOE", L"STONE_HOE", L"IRON_HOE", L"GOLDEN_HOE", L"DIAMOND_HOE"
			});
			this->itemSelection->Location = System::Drawing::Point(101, 37);
			this->itemSelection->Name = L"itemSelection";
			this->itemSelection->Size = System::Drawing::Size(197, 21);
			this->itemSelection->TabIndex = 2;
			this->itemSelection->SelectionChangeCommitted += gcnew System::EventHandler(this, &AddItemForm::itemSelection_SelectionChangeCommitted);
			// 
			// pictBox
			// 
			this->pictBox->Location = System::Drawing::Point(12, 12);
			this->pictBox->Name = L"pictBox";
			this->pictBox->Size = System::Drawing::Size(70, 70);
			this->pictBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictBox->TabIndex = 3;
			this->pictBox->TabStop = false;
			// 
			// okButton
			// 
			this->okButton->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->okButton->Location = System::Drawing::Point(223, 64);
			this->okButton->Name = L"okButton";
			this->okButton->Size = System::Drawing::Size(75, 23);
			this->okButton->TabIndex = 4;
			this->okButton->Text = L"OK";
			this->okButton->UseVisualStyleBackColor = true;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(101, 69);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(23, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Qty";
			// 
			// itemQty
			// 
			this->itemQty->Location = System::Drawing::Point(130, 65);
			this->itemQty->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->itemQty->Name = L"itemQty";
			this->itemQty->Size = System::Drawing::Size(87, 20);
			this->itemQty->TabIndex = 6;
			this->itemQty->Maximum = 2000;
			this->itemQty->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// AddItemForm
			// 
			this->AcceptButton = this->okButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(317, 99);
			this->Controls->Add(this->itemQty);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->okButton);
			this->Controls->Add(this->pictBox);
			this->Controls->Add(this->itemSelection);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"AddItemForm";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Add Item";
			this->TopMost = true;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictBox))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->itemQty))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: void itemSelection_SelectionChangeCommitted(Object^ sender, EventArgs^ e);
};
}
