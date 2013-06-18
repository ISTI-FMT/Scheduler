#pragma once
#include "form\\tableLayoutPanelSingleItin.h"
#include "form\\tableLayoutPanelAllCDB.h"
#include "itinerari\\tabellaItinerari.h"
#include "messaggi\\StateItinerario.h"
#include "messaggi\\Messaggi.h"
#include "EventQueue.h"


namespace Prototipo {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Threading;
using namespace System::Threading::Tasks;

	/// <summary>
	/// Riepilogo per FormStatoItinerari
	/// </summary>
	 ref class FormStatoItinerari : public System::Windows::Forms::Form
	{
		tabellaItinerari ^tabItinerari;
		EventQueue ^eventiItinerario;
		Dictionary<int,Button^> ^listbutton;
		Dictionary<int,Button^> ^listbuttonCDB;
	public:

		FormStatoItinerari(EventQueue ^ev)
		{
			eventiItinerario=ev;
			listbutton= gcnew Dictionary<int,Button^> ();
			listbuttonCDB= gcnew Dictionary<int,Button^> ();
			InitializeComponent();

			tabItinerari = gcnew tabellaItinerari();
			tabItinerari->leggifileconfigurazioneItinerari("..\\FileConfigurazione\\ConfigurazioneItinerari.xml");
			genera();
			//aggiorna();
			//
			//TODO: aggiungere qui il codice del costruttore.
			//
		}
		void genera();
		void aggiorna();
		void findandset(int id, int stato);
		void findandsetCDB(int id, int stato);
	private: bool SendMessStatoIXL(List< StateItinerario^> ^listI, List<StateCDB^> ^listCItin);
			 List<StateCDB^> ^listCdBItin(int idstazione,int iditineraio);
			 void setCdBItin(List<StateCDB^> ^listCdB, int stato);

	protected:
		/// <summary>
		/// Liberare le risorse in uso.
		/// </summary>
		~FormStatoItinerari()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;

	protected: 

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
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 4;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel1->GrowStyle = System::Windows::Forms::TableLayoutPanelGrowStyle::AddColumns;
			this->tableLayoutPanel1->Location = System::Drawing::Point(12, 12);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->Size = System::Drawing::Size(1168, 444);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// FormStatoItinerari
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1192, 836);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Name = L"FormStatoItinerari";
			this->Text = L"FormStatoIXL";
			this->ResumeLayout(false);

		}
#pragma endregion
	/*private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 List< StateItinerario^> ^listI = gcnew List< StateItinerario^>();
				 List<StateCDB^> ^listCItin = gcnew  List<StateCDB^>();
				 for each ( tableLayoutPanelSingleItin ^c in tableLayoutPanel1->Controls )
				 {
					 int i=0;
					  int offset =0;
					 for each ( Object ^ssx in c->getTableLayoutPanel()->Controls )
					 {
						
						 if(i==0){
							 Label ^l  = (Label ^ )ssx;
							 offset = int::Parse(l->Name);

						 }
						 if(i>0){
							 Button ^s  = (Button ^ )ssx;
						 StateItinerario^ itin = gcnew StateItinerario();
						 int iditinerario = int::Parse(s->Name);

						 List<StateCDB^> ^listC = listCdBItin(offset,iditinerario);


						 itin->setNID_ITIN(iditinerario+offset);
						 if(s->BackColor== System::Drawing::Color::Red){
							 itin->setQ_STATOITIN(1);
							 setCdBItin(listC,2);
							  listCItin->AddRange(listC);
						 }else{

							 itin->setQ_STATOITIN(0);
							 if(s->BackColor== System::Drawing::Color::Green){
							 setCdBItin(listC,0);
							 listCItin->AddRange(listC);
							 }
						 }
						
						 listI->Add(itin);
						 Console::WriteLine(itin);
						 }

						 i++;
					 }


				 }

				 SendMessStatoIXL(listI, listCItin);

			 }*/
	};
	
	

}
