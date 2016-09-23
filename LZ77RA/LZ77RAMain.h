#include <string>
#pragma once

namespace LZ771 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class LZ77Main : public System::Windows::Forms::Form
	{
	public:
		LZ77Main(void)
		{
			InitializeComponent();

		}

		void doCompression();

	protected:

		~LZ77Main()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:



	public: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	public: System::Windows::Forms::Button^  loadFileButton;
	public: System::Windows::Forms::TextBox^  pathFile;
	private: System::Windows::Forms::Button^  compressButton;
	public:



	public:
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::TextBox^  numOfMistakesText;

	private: System::Windows::Forms::Label^  numOfMistakesLabel;
	private: System::Windows::Forms::CheckBox^  isLZWithMistakes;



	public:


	protected:

	protected:

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(LZ77Main::typeid));
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->loadFileButton = (gcnew System::Windows::Forms::Button());
			this->pathFile = (gcnew System::Windows::Forms::TextBox());
			this->compressButton = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->isLZWithMistakes = (gcnew System::Windows::Forms::CheckBox());
			this->numOfMistakesText = (gcnew System::Windows::Forms::TextBox());
			this->numOfMistakesLabel = (gcnew System::Windows::Forms::Label());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// openFileDialog
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// loadFileButton
			// 
			this->loadFileButton->Location = System::Drawing::Point(21, 36);
			this->loadFileButton->Name = L"loadFileButton";
			this->loadFileButton->Size = System::Drawing::Size(93, 23);
			this->loadFileButton->TabIndex = 1;
			this->loadFileButton->Text = L"Load File...";
			this->loadFileButton->UseVisualStyleBackColor = true;
			this->loadFileButton->Click += gcnew System::EventHandler(this, &LZ77Main::loadFileButton_Click);
			// 
			// pathFile
			// 
			this->pathFile->Location = System::Drawing::Point(120, 37);
			this->pathFile->Name = L"pathFile";
			this->pathFile->Size = System::Drawing::Size(318, 20);
			this->pathFile->TabIndex = 2;
			// 
			// compressButton
			// 
			this->compressButton->Location = System::Drawing::Point(134, 137);
			this->compressButton->Name = L"compressButton";
			this->compressButton->Size = System::Drawing::Size(172, 38);
			this->compressButton->TabIndex = 3;
			this->compressButton->Text = L"Compress now";
			this->compressButton->UseVisualStyleBackColor = true;
			this->compressButton->Click += gcnew System::EventHandler(this, &LZ77Main::button2_Click);
			// 
			// panel1
			// 
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Controls->Add(this->isLZWithMistakes);
			this->panel1->Controls->Add(this->numOfMistakesText);
			this->panel1->Controls->Add(this->numOfMistakesLabel);
			this->panel1->Controls->Add(this->compressButton);
			this->panel1->Controls->Add(this->pathFile);
			this->panel1->Controls->Add(this->loadFileButton);
			this->panel1->ImeMode = System::Windows::Forms::ImeMode::Hiragana;
			this->panel1->Location = System::Drawing::Point(12, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(453, 215);
			this->panel1->TabIndex = 0;
			// 
			// isLZWithMistakes
			// 
			this->isLZWithMistakes->AutoSize = true;
			this->isLZWithMistakes->Location = System::Drawing::Point(22, 102);
			this->isLZWithMistakes->Name = L"isLZWithMistakes";
			this->isLZWithMistakes->Size = System::Drawing::Size(117, 17);
			this->isLZWithMistakes->TabIndex = 6;
			this->isLZWithMistakes->Text = L"LZ77 with mistakes";
			this->isLZWithMistakes->UseMnemonic = false;
			this->isLZWithMistakes->UseVisualStyleBackColor = true;
			// 
			// numOfMistakesText
			// 
			this->numOfMistakesText->Location = System::Drawing::Point(120, 71);
			this->numOfMistakesText->Name = L"numOfMistakesText";
			this->numOfMistakesText->Size = System::Drawing::Size(66, 20);
			this->numOfMistakesText->TabIndex = 5;
			// 
			// numOfMistakesLabel
			// 
			this->numOfMistakesLabel->AutoSize = true;
			this->numOfMistakesLabel->Location = System::Drawing::Point(19, 73);
			this->numOfMistakesLabel->Name = L"numOfMistakesLabel";
			this->numOfMistakesLabel->Size = System::Drawing::Size(103, 13);
			this->numOfMistakesLabel->TabIndex = 4;
			this->numOfMistakesLabel->Text = L"Number of mistakes:";
			// 
			// LZ77Main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(477, 237);
			this->Controls->Add(this->panel1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"LZ77Main";
			this->Text = L"LZ77RA Project";
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
	}
private: System::Void loadFileButton_Click(System::Object^  sender, System::EventArgs^  e) {
	
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		System::IO::StreamReader ^ sr = gcnew
			System::IO::StreamReader(openFileDialog1->FileName);
		pathFile->Text = openFileDialog1->FileName;
		sr->Close();
	}

}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	if (pathFile->Text == "")
	{
		MessageBox::Show("Please insert a file", "LZ77RA Project", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	else
	{
		doCompression();
		MessageBox::Show("The file compressed successfully", "LZ77RA Project", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
}

};
}
