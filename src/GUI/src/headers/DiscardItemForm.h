#pragma once
#include "Item.h"

namespace GUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for DiscardItemForm
	/// </summary>
	public ref class DiscardItemForm : public System::Windows::Forms::Form
	{
	public:
		DiscardItemForm(ItemSlot^ item);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DiscardItemForm();
	private: System::Windows::Forms::Label^ lblSlot;
	protected:

	private: System::Windows::Forms::PictureBox^ pictBox;
	public: System::Windows::Forms::NumericUpDown^ itemQty;
	private: System::Windows::Forms::Label^ lblQty;
	public:

	private: System::Windows::Forms::Button^ okButton;
	public:
	private:
	protected:

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
			this->lblSlot = (gcnew System::Windows::Forms::Label());
			this->pictBox = (gcnew System::Windows::Forms::PictureBox());
			this->itemQty = (gcnew System::Windows::Forms::NumericUpDown());
			this->lblQty = (gcnew System::Windows::Forms::Label());
			this->okButton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictBox))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->itemQty))->BeginInit();
			this->SuspendLayout();
			// 
			// lblSlot
			// 
			this->lblSlot->AutoSize = true;
			this->lblSlot->Location = System::Drawing::Point(88, 12);
			this->lblSlot->Name = L"lblSlot";
			this->lblSlot->Size = System::Drawing::Size(187, 13);
			this->lblSlot->TabIndex = 1;
			this->lblSlot->Text = L"How much to delete the item in slot ()\?";
			// 
			// pictBox
			// 
			this->pictBox->Location = System::Drawing::Point(12, 12);
			this->pictBox->Name = L"pictBox";
			this->pictBox->Size = System::Drawing::Size(70, 70);
			this->pictBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictBox->TabIndex = 4;
			this->pictBox->TabStop = false;
			// 
			// itemQty
			// 
			this->itemQty->Location = System::Drawing::Point(91, 31);
			this->itemQty->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->itemQty->Name = L"itemQty";
			this->itemQty->Size = System::Drawing::Size(135, 20);
			this->itemQty->TabIndex = 7;
			this->itemQty->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// lblQty
			// 
			this->lblQty->AutoSize = true;
			this->lblQty->Location = System::Drawing::Point(232, 33);
			this->lblQty->Name = L"lblQty";
			this->lblQty->Size = System::Drawing::Size(43, 13);
			this->lblQty->TabIndex = 8;
			this->lblQty->Text = L"out of ()";
			// 
			// okButton
			// 
			this->okButton->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->okButton->Location = System::Drawing::Point(91, 56);
			this->okButton->Name = L"okButton";
			this->okButton->Size = System::Drawing::Size(186, 23);
			this->okButton->TabIndex = 9;
			this->okButton->Text = L"OK";
			this->okButton->UseVisualStyleBackColor = true;
			// 
			// DiscardItemForm
			// 
			this->AcceptButton = this->okButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(289, 91);
			this->Controls->Add(this->okButton);
			this->Controls->Add(this->lblQty);
			this->Controls->Add(this->itemQty);
			this->Controls->Add(this->pictBox);
			this->Controls->Add(this->lblSlot);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"DiscardItemForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Discard item";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictBox))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->itemQty))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	};
}
