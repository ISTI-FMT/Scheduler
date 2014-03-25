#pragma once
#include "TrenoFisicoLogico.h"
namespace Prototipo {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Diagnostics::CodeAnalysis;



	/// <summary>
	/// Riepilogo per EditorMapTreni
	/// </summary>
	[ExcludeFromCodeCoverage]
	public ref class EditorMapTreni : public System::Windows::Forms::Form
	{
	public:
		event EventHandler ^Nuovotreno;
		EditorMapTreni(void)
		{
			InitializeComponent();
			//
			//TODO: aggiungere qui il codice del costruttore.
			//
		}

	protected:
		/// <summary>
		/// Liberare le risorse in uso.
		/// </summary>
		~EditorMapTreni()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  buttonAnnulla;
	protected: 

	private: System::Windows::Forms::Button^  buttonOk;
	protected: 

	private: System::Windows::Forms::TextBox^  textBoxEngine;
	private: System::Windows::Forms::ComboBox^  comboBoxLastPos;
	private: System::Windows::Forms::TextBox^  listBoxTRN;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;

	private:

		System::ComponentModel::Container ^components;


		void InitializeComponent(void)
		{
			this->buttonAnnulla = (gcnew System::Windows::Forms::Button());
			this->buttonOk = (gcnew System::Windows::Forms::Button());
			this->textBoxEngine = (gcnew System::Windows::Forms::TextBox());
			this->comboBoxLastPos = (gcnew System::Windows::Forms::ComboBox());
			this->listBoxTRN = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// buttonAnnulla
			// 
			this->buttonAnnulla->Location = System::Drawing::Point(280, 213);
			this->buttonAnnulla->Name = L"buttonAnnulla";
			this->buttonAnnulla->Size = System::Drawing::Size(75, 23);
			this->buttonAnnulla->TabIndex = 0;
			this->buttonAnnulla->Text = L"Annulla";
			this->buttonAnnulla->UseVisualStyleBackColor = true;
			this->buttonAnnulla->Click += gcnew System::EventHandler(this, &EditorMapTreni::buttonAnnulla_Click);
			// 
			// buttonOk
			// 
			this->buttonOk->Location = System::Drawing::Point(175, 213);
			this->buttonOk->Name = L"buttonOk";
			this->buttonOk->Size = System::Drawing::Size(75, 23);
			this->buttonOk->TabIndex = 1;
			this->buttonOk->Text = L"Ok";
			this->buttonOk->UseVisualStyleBackColor = true;
			this->buttonOk->Click += gcnew System::EventHandler(this, &EditorMapTreni::buttonOk_Click);
			// 
			// textBoxEngine
			// 
			this->textBoxEngine->Location = System::Drawing::Point(41, 56);
			this->textBoxEngine->Name = L"textBoxEngine";
			this->textBoxEngine->Size = System::Drawing::Size(120, 20);
			this->textBoxEngine->TabIndex = 2;
			this->textBoxEngine->TextChanged += gcnew System::EventHandler(this, &EditorMapTreni::textBoxEngine_TextChanged);
			// 
			// comboBoxLastPos
			// 
			this->comboBoxLastPos->FormattingEnabled = true;
			this->comboBoxLastPos->Items->AddRange(gcnew cli::array< System::Object^  >(24) {L"13301", L"13302", L"14301", L"14302", L"15301", 
				L"15302", L"11301", L"11302", L"12301", L"12302", L"12303", L"10301", L"10302", L"406", L"407", L"418", L"419", L"16301", L"16302", 
				L"16303", L"17301", L"17302", L"17303", L"17304"});
			this->comboBoxLastPos->Location = System::Drawing::Point(42, 141);
			this->comboBoxLastPos->Name = L"comboBoxLastPos";
			this->comboBoxLastPos->Size = System::Drawing::Size(121, 21);
			this->comboBoxLastPos->TabIndex = 3;
			// 
			// listBoxTRN
			// 
			this->listBoxTRN->Multiline = true;
			this->listBoxTRN->Location = System::Drawing::Point(222, 59);
			this->listBoxTRN->Name = L"listBoxTRN";
			this->listBoxTRN->Size = System::Drawing::Size(120, 95);
			this->listBoxTRN->TabIndex = 4;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 35);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(83, 13);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Engine Number:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(17, 115);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(70, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Last Position:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(193, 35);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(133, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"List Train Running Number";
			// 
			// EditorMapTreni
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(384, 256);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->listBoxTRN);
			this->Controls->Add(this->comboBoxLastPos);
			this->Controls->Add(this->textBoxEngine);
			this->Controls->Add(this->buttonOk);
			this->Controls->Add(this->buttonAnnulla);
			this->Name = L"EditorMapTreni";
			this->Text = L"EditorMapTreni";
			this->ResumeLayout(false);
			this->PerformLayout();

		}


	private: System::Void textBoxEngine_TextChanged(System::Object^  sender, System::EventArgs^  e) {
				 System::Windows::Forms::TextBox ^textarea =(System::Windows::Forms::TextBox^) sender ;

				 //[0-9]+(?:\.[0-9]*)?
				 System::Text::RegularExpressions::Match ^m = System::Text::RegularExpressions::Regex::Match(textarea->Text,"[0-9]+(?:\\.[0-9]*)?");
				 if (m->Success){
					 if(m->Value->Length!=textarea->Text->Length){
						 textarea->Text=m->Value;
					 }
				 }else{
					 System::Windows::Forms::MessageBox::Show("Please enter only numbers.");

				 }
			 }
	private: System::Void buttonOk_Click(System::Object^  sender, System::EventArgs^  e) {
				 try{
					 List<int> ^list = gcnew List<int>();
					 array<String^> ^listtrn = listBoxTRN->Lines;
					 for each (  String ^var in  listtrn)
					 {
						 list->Add(int::Parse(var));
					 }
					 int lastpos = int::Parse(comboBoxLastPos->SelectedItem->ToString());
					 TrenoFisicoLogico^ newtreno = gcnew TrenoFisicoLogico(int::Parse(textBoxEngine->Text),list,lastpos);

					 //segnala evento
					 Nuovotreno(newtreno,e);
					 this->Close();
				 }catch(Exception^e){

					 System::Windows::Forms::MessageBox::Show("Please enter only numbers.");
				 }
			 }
	private: System::Void buttonAnnulla_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->Close();
			 }
	};
}
