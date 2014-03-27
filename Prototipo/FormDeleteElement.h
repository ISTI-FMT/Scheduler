#pragma once
#include "tabellaOrario\\TabellaOrario.h"
#include "mapTrenoFisicoLogico.h"
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
	public ref class FormDeleteElement : public System::Windows::Forms::Form
	{
	public:
		event EventHandler ^DeleteTreno;
		FormDeleteElement(TabellaOrario ^T)
		{
			TabOrario=T;
			Dictionary<int, List<Fermata^>^> ^taborario = T->get_TabellaOrario();
			Dictionary<int,  List<Fermata^>^>::KeyCollection ^keycoll = taborario->Keys;

			array<String^>^elementicombobox = gcnew array<String^>(keycoll->Count);
			int i=0;
			for each (int var in keycoll)
			{

				elementicombobox[i]=(var.ToString());
				i++;
			}
			InitializeComponent(elementicombobox);

		}
		FormDeleteElement(mapTrenoFisicoLogico ^T)
		{
			maptreni=T;

			Dictionary<int, TrenoFisicoLogico^> ^tabmaptreni = maptreni->get_Map();
			Dictionary<int,  TrenoFisicoLogico^>::KeyCollection ^keycoll = tabmaptreni->Keys;

			array<String^>^elementicombobox = gcnew array<String^>(keycoll->Count);
			int i=0;
			for each (int var in keycoll)
			{

				elementicombobox[i]=(var.ToString());
				i++;
			}
			InitializeComponent(elementicombobox);

		}

	protected:
		/// <summary>
		/// Liberare le risorse in uso.
		/// </summary>
		~FormDeleteElement()
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


	private: System::Windows::Forms::ComboBox^  comboBoxElement;

	private: System::Windows::Forms::Label^  label1;
			 System::Windows::Forms::Label ^label2;
	private: System::Windows::Forms::Label^  label3;
			 System::Windows::Forms::DataGridView^  dataGridView1;
	private: TabellaOrario ^TabOrario;
			 mapTrenoFisicoLogico ^maptreni;

			 System::ComponentModel::Container ^components;


			 void InitializeComponent(array<String^> ^ListElement)
			 {
				 this->buttonAnnulla = (gcnew System::Windows::Forms::Button());
				 this->buttonOk = (gcnew System::Windows::Forms::Button());

				 this->comboBoxElement = (gcnew System::Windows::Forms::ComboBox());


				 this->label1 = (gcnew System::Windows::Forms::Label());

				 this->label3 = (gcnew System::Windows::Forms::Label());
				 this->SuspendLayout();
				 // 
				 // buttonAnnulla
				 // 
				 this->buttonAnnulla->Location = System::Drawing::Point(280, 273);
				 this->buttonAnnulla->Name = L"buttonAnnulla";
				 this->buttonAnnulla->Size = System::Drawing::Size(75, 23);
				 this->buttonAnnulla->TabIndex = 0;
				 this->buttonAnnulla->Text = L"Annulla";
				 this->buttonAnnulla->UseVisualStyleBackColor = true;
				 this->buttonAnnulla->Click += gcnew System::EventHandler(this, &FormDeleteElement::buttonAnnulla_Click);
				 // 
				 // buttonOk
				 // 
				 this->buttonOk->Location = System::Drawing::Point(175, 273);
				 this->buttonOk->Name = L"buttonOk";
				 this->buttonOk->Size = System::Drawing::Size(75, 23);
				 this->buttonOk->TabIndex = 1;
				 this->buttonOk->Text = L"Ok";
				 this->buttonOk->UseVisualStyleBackColor = true;
				 this->buttonOk->Click += gcnew System::EventHandler(this, &FormDeleteElement::buttonOk_Click);

				 // 
				 // comboBoxElement
				 // 
				 this->comboBoxElement->FormattingEnabled = true;
				 this->comboBoxElement->Items->AddRange(ListElement);
				 this->comboBoxElement->Location =  System::Drawing::Point(141, 30);
				 this->comboBoxElement->Name = L"comboBoxElement";
				 this->comboBoxElement->Size = System::Drawing::Size(121, 21);
				 this->comboBoxElement->TabIndex = 3;
				 this->comboBoxElement->SelectedIndexChanged += gcnew System::EventHandler(this, &FormDeleteElement::comboBoxElement_SelectedIndexChanged);
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(17, 30);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(83, 13);
				 this->label1->TabIndex = 5;
				 this->label1->Text = L"Select Element:";



				 // 
				 // label2
				 // 
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->label2->AutoSize = true;
				 this->label2->Location = System::Drawing::Point(17, 60);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(70, 13);
				 this->label2->TabIndex = 6;
				 this->label2->Text = L"Info Element:";


				 dataGridView1 = gcnew System::Windows::Forms::DataGridView();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(dataGridView1))->BeginInit();
				 dataGridView1->AccessibleName = L"datagrid";
				 dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;
				 dataGridView1->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
				 dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
				 dataGridView1->Location =System::Drawing::Point(41, 90);
				 dataGridView1->Name = L"dataGridView1";
				 dataGridView1->Size =System::Drawing::Size(320, 175);
				 dataGridView1->TabIndex = 8;


				 // 
				 // EditorDeleteElement
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(384, 316);
				 this->Controls->Add(this->label3);

				 this->Controls->Add(this->label1);
				 this->Controls->Add(label2);
				 this->Controls->Add(this->comboBoxElement);
				 this->Controls->Add(this->dataGridView1);
				 this->Controls->Add(this->buttonOk);
				 this->Controls->Add(this->buttonAnnulla);

				 this->Name = L"EditorMapTreni";
				 this->Text = L"EditorMapTreni";
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }


	private: System::Void textBoxInfo_TextChanged(System::Object^  sender, System::EventArgs^  e) {
				 /*	 System::Windows::Forms::TextBox ^textarea =(System::Windows::Forms::TextBox^) sender ;

				 //[0-9]+(?:\.[0-9]*)?
				 System::Text::RegularExpressions::Match ^m = System::Text::RegularExpressions::Regex::Match(textarea->Text,"[0-9]+(?:\\.[0-9]*)?");
				 if (m->Success){
				 if(m->Value->Length!=textarea->Text->Length){
				 textarea->Text=m->Value;
				 }
				 }else{
				 System::Windows::Forms::MessageBox::Show("Please enter only numbers.");

				 }*/
			 }
	private: System::Void buttonOk_Click(System::Object^  sender, System::EventArgs^  e) {
				 try{


					 int elementodaeliminare = int::Parse(comboBoxElement->SelectedItem->ToString());
					 //segnala evento
					 DeleteTreno(elementodaeliminare,e);
					 this->Close();
				 }catch(Exception^e){
					 Console::WriteLine("Error {0}", e->Message) ;
					 System::Windows::Forms::MessageBox::Show("Please enter only numbers.");
				 }
			 }
	private: System::Void buttonAnnulla_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->Close();
			 }

	private: System::Void comboBoxElement_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 int elementoselezionato = int::Parse(comboBoxElement->SelectedItem->ToString());
				 if(TabOrario!=nullptr){
					 List<Fermata^>^ liatf= TabOrario->get_TabellaOrario()[elementoselezionato];
					 Aggiorna(elementoselezionato,liatf);
				 }else{
					 if(maptreni!=nullptr){
						 TrenoFisicoLogico ^trenosele = maptreni->get_Map()[elementoselezionato];
						 Aggiorna(elementoselezionato,trenosele);

					 }


				 }

			 }

	private: void Aggiorna(int treno , TrenoFisicoLogico^ trenofl){



				 dataGridView1->ColumnCount = 5;
				 dataGridView1->RowCount = trenofl->getIdTrenoListTreniLogici()->Count;
				 int colonna=0;
				 int riga=0;
				 dataGridView1->Columns[ 0 ]->Name = "Id_Engine_Treno";
				 dataGridView1->Columns[ 1 ]->Name = "";
				 dataGridView1->Columns[ 2 ]->Name = "TRN treno";
				 dataGridView1->Columns[ 3 ]->Name = " ";
				 dataGridView1->Columns[ 4 ]->Name = "Last Position";




				 String ^po=treno+"\n\r";
				 dataGridView1->Rows[riga]->Cells[0]->Value=po;
				 

				 for each (int dvar in trenofl->getIdTrenoListTreniLogici())
				 { 

					 dataGridView1->Rows[riga]->Cells[2]->Value=dvar;
					 dataGridView1->Rows[riga]->Cells[4]->Value=trenofl->getCDBLastPosition();
					 riga++;
				 }






			 }
			 void Aggiorna(int treno , List<Fermata^>^ liatf){



				 dataGridView1->ColumnCount = 10;
				 dataGridView1->RowCount = liatf->Count;
				 int colonna=0;
				 int riga=0;
				 dataGridView1->Columns[ 0 ]->Name = "Id_Treno";
				 dataGridView1->Columns[ 1 ]->Name = "Nome Stazione";
				 dataGridView1->Columns[ 2 ]->Name = "id Stazione";
				 dataGridView1->Columns[ 3 ]->Name = "Orario Arrivo";
				 dataGridView1->Columns[ 4 ]->Name = "Orario Partenza";
				 dataGridView1->Columns[ 5 ]->Name = "BinProg";
				 dataGridView1->Columns[ 6 ]->Name = "TempoMAPorte";
				 dataGridView1->Columns[ 7 ]->Name = "LatoAPorte";
				 dataGridView1->Columns[ 8 ]->Name = "It Entrata";
				 dataGridView1->Columns[ 9 ]->Name = "It Uscita";


				 String ^po=treno+"\n\r";
				 dataGridView1->Rows[riga]->Cells[0]->Value=po;


				 for each (Fermata ^dvar in liatf)
				 { 
					 dataGridView1->Rows[riga]->Cells[1]->Value=dvar->getnameStazione();
					 dataGridView1->Rows[riga]->Cells[2]->Value=dvar->getIdStazione();
					 TimeSpan Arrivo = TimeSpan::FromSeconds(dvar->getOrarioArrivo()*30);
					 dataGridView1->Rows[riga]->Cells[3]->Value= Arrivo.ToString();
					 TimeSpan Partenza = TimeSpan::FromSeconds(dvar->getOrarioPartenza()*30);
					 dataGridView1->Rows[riga]->Cells[4]->Value=Partenza.ToString();
					 dataGridView1->Rows[riga]->Cells[5]->Value=dvar->getBinarioProgrammato();
					 dataGridView1->Rows[riga]->Cells[6]->Value=dvar->gettempoMinimoAperturaPorte();
					 dataGridView1->Rows[riga]->Cells[7]->Value=(int) dvar->getLatoAperturaPorte();
					 dataGridView1->Rows[riga]->Cells[8]->Value=dvar->getnameitinerarioEntrata();
					 dataGridView1->Rows[riga]->Cells[9]->Value=dvar->getnameitinerarioUscita();
					 riga++;
				 }




			 }
	};
}
