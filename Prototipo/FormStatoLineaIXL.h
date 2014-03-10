#pragma once
#include "form\\tableLayoutPanelSingleItin.h"
#include "form\\tableLayoutPanelAllCDB.h"
#include "itinerari\\TabellaStazioni.h"
#include "messaggi\\StateItinerario.h"
#include "messaggi\\Messaggi.h"
#include "EventQueue.h"

/*Utilizzo questa classe per rappresentare graficamente una form che contiene le informazioni sullo stato degli itininerari
e sullo stato dei cdb dei messaggi stato della linea dell'IXL*/

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
	/// Riepilogo per FormStatoLineaIXL
	/// </summary>
	ref class FormStatoLineaIXL : public System::Windows::Forms::Form , IObserver<Event<StateCDB^>^>
	{
		TabellaStazioni ^tabItinerari;
		EventQueue<StateCDB^> ^eventiCDB;
		//Dictionary<int,Button^> ^listbutton;
		Dictionary<int,Button^> ^listbuttonCDB;
		bool _shouldStop;
		IDisposable ^unsubscriber;
	public:

		FormStatoLineaIXL()
		{
			//eventiCDB=ev;
			//	listbutton= gcnew Dictionary<int,Button^> ();
			listbuttonCDB= gcnew Dictionary<int,Button^> ();

			this->ControlBox=false;
			InitializeComponent();
			_shouldStop=false;
			//tabItinerari = gcnew TabellaStazioni();
			//tabItinerari->leggifileconfigurazioneItinerari();
			genera();
			//aggiorna();
			//
			//TODO: aggiungere qui il codice del costruttore.
			//
		}
		virtual void Subscribe(IObservable<Event<StateCDB^>^> ^provider){
			if (provider != nullptr) 
				unsubscriber = provider->Subscribe(this);	
		};

		virtual void OnCompleted(){

			Unsubscribe();

		};
		virtual void OnError(Exception ^e){

			Unsubscribe();

		};
		virtual void OnNext(Event<StateCDB^> ^value);
		virtual void Unsubscribe(){
			delete unsubscriber;
		};
		void genera();
		void aggiorna();
		//void findandset(int id, int stato);
		void findandsetCDB(int id, int stato);
		void RequestStop();
	private: 
		//List<StateCDB^> ^listCdBItin(int idstazione,int iditineraio);
		void setCdBItin(List<StateCDB^> ^listCdB, int stato);

	protected:
		/// <summary>
		/// Liberare le risorse in uso.
		/// </summary>
		~FormStatoLineaIXL()
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FormStatoLineaIXL::typeid));
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->Size = System::Drawing::Size(200, 100);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// FormStatoLineaIXL
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1240, 378);
			this->ControlBox = false;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"FormStatoLineaIXL";
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
