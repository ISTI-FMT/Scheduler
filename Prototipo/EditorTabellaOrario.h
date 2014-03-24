#pragma once
#include "ItineraryBox.h"
#include "Itinerari\\TabellaStazioni.h"
#include "tabellaOrario\\TabellaOrario.h"
namespace Prototipo {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Riepilogo per EditorTabellaOrario
	/// </summary>
	public ref class EditorTabellaOrario : public System::Windows::Forms::Form
	{
	public:
		event EventHandler ^Nuovotreno;
		EditorTabellaOrario(TabellaStazioni ^T)
		{
			InitializeComponent();
			//
			//TODO: aggiungere qui il codice del costruttore.
			//
			tabStazioni=T;
			this->Icon =  gcnew System::Drawing::Icon(System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream("app.ico"));
			comboBox1->SelectedIndex=0;
			this->tableLayoutPanelItinerari = (gcnew System::Windows::Forms::TableLayoutPanel());
			// 
			// tableLayoutPanel1
			// 

			this->tableLayoutPanelItinerari->Location = System::Drawing::Point(6, 109);
			this->tableLayoutPanelItinerari->Name = L"tableLayoutPanel1";
			this->tableLayoutPanelItinerari->ColumnCount = 3;
			this->tableLayoutPanelItinerari->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanelItinerari->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanelItinerari->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));


			this->tableLayoutPanelItinerari->RowCount = 3;
			this->tableLayoutPanelItinerari->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanelItinerari->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanelItinerari->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanelItinerari->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanelItinerari->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanelItinerari->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanelItinerari->TabIndex = 12;
			this->tableLayoutPanelItinerari->Size = System::Drawing::Size(550, 506);
			this->Controls->Add(tableLayoutPanelItinerari);
			setitinerary();
		}

	protected:
		/// <summary>
		/// Liberare le risorse in uso.
		/// </summary>
		~EditorTabellaOrario()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	protected: 
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  AddButton;

			 System::Windows::Forms::TableLayoutPanel^  tableLayoutPanelItinerari;
			 void setitinerary();
			 TabellaStazioni ^tabStazioni;
			 TabellaOrario ^tabOrario;
			 Void textBox_TextChangedP(System::Object^  sender, System::EventArgs^  e);
	private:
		/// <summary>
		/// Variabile di progettazione necessaria.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metodo necessario per il supporto della finestra di progettazione. Non modificare
		/// il contenuto del metodo con l'editor di codice.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->AddButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(23, 28);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 0;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &EditorTabellaOrario::textBox_TextChangedP);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(46, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(57, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"TRAIN ID:";
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"Sinistra", L"Destra"});
			this->comboBox1->Location = System::Drawing::Point(212, 28);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 21);
			this->comboBox1->TabIndex = 2;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(236, 8);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(51, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Direzione";
			// 
			// AddButton
			// 
			this->AddButton->Location = System::Drawing::Point(547, 587);
			this->AddButton->Name = L"AddButton";
			this->AddButton->Size = System::Drawing::Size(75, 23);
			this->AddButton->TabIndex = 4;
			this->AddButton->Text = L"Add";
			this->AddButton->UseVisualStyleBackColor = true;
			this->AddButton->Click += gcnew System::EventHandler(this, &EditorTabellaOrario::AddButton_Click);
			// 
			// EditorTabellaOrario
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(645, 622);
			this->Controls->Add(this->AddButton);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Name = L"EditorTabellaOrario";
			this->Text = L"EditorTabellaOrario";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void AddButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 try{
					 array<Fermata^>^ newfermatefortrain = gcnew array<Fermata^>(11);
					 for each (ItineraryBox ^var in tableLayoutPanelItinerari->Controls)
					 {
						 if(var->isChecked()){
							 KeyValuePair<DateTime, DateTime> ^orari = var->getOrari();
							 DateTime orarioSupporto3 = DateTime::ParseExact("00:00:00", "HH:mm:ss",  System::Globalization::CultureInfo::InvariantCulture);

							 TimeSpan sinceMidnighta = orari->Key - orarioSupporto3;
							 TimeSpan sinceMidnightp = orari->Value - orarioSupporto3;
							 double	darrivo = sinceMidnighta.TotalSeconds/30;
							 double	dpartenza = sinceMidnightp.TotalSeconds/30;
							 int indexCombo = comboBox1->SelectedIndex;
							 int identrata = 0;
							 String^ nomeentrata = "";
							 int iduscita =  0;
							 String^nomeuscita = ""; 
							 if(indexCombo==0){
								 identrata = var->getIdIEntrata();
								 nomeentrata = var->getNameIdEntrata();
								 iduscita =  var->getIdIUscita();
								 nomeuscita = var->getNomeIDUscita(); 
							 }else{
								 identrata = var->getIdIUscita();
								 nomeentrata = var->getNomeIDUscita(); 
								 iduscita =  var->getIdIEntrata();
								 nomeuscita = var->getNameIdEntrata();

							 }
							 Fermata^ newfermata = gcnew Fermata(var->getIdStation(),var->getStationName(),darrivo,dpartenza,10,1,FermataType::aperturaTrenoBanchinaDxSx, identrata,  nomeentrata,iduscita,  nomeuscita);
							 int i = var->getNumpos();
							 if((i>=0) & (i<13)){
								 newfermatefortrain[i] = newfermata;
								 //newfermatefortrain->Add(newfermata);
							 }

						 }
					 }
					 List<Fermata^>^ newfermate = gcnew List<Fermata^>();
					 for each (Fermata ^var in newfermatefortrain)
					 {
						 if(var){
							 newfermate->Add(var);
						 }
					 }



					 Console::WriteLine(newfermatefortrain);
					 Console::WriteLine(newfermate);
					 
					 int TRN = 0 ;
					 int::TryParse(textBox1->Text,TRN);
					 // segnala evento!!!
					if(TRN==0){

						MessageBox::Show("Inserisci un Train Running Number");
						return;
					}
					 Nuovotreno(gcnew  KeyValuePair<int,  List<Fermata^>^> (TRN,newfermate),e);
					
					 this->Close();
				 }catch(Exception ^e){
					 Console::WriteLine("Errore {0}", e->Message);
					 MessageBox::Show("Errore Tabella orario");
				 }

			 }

	};
}
