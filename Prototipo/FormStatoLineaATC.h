#pragma once
#include "form\\tableLayoutPanelAllCDB.h"
#include "EventQueue.h"

/*Utilizzo questa classe per rappresentare graficamente una form che contiene le informazioni sullo stato  dei cdb 
dei messaggi stato della linea dell'ATC*/


namespace Prototipo {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Net::Sockets;
	using namespace System::Threading;
	using namespace System::Threading::Tasks;
	using namespace System::Diagnostics::CodeAnalysis;



	/// <summary>
	/// Riepilogo per FormStatoLineaATC
	/// </summary>
	[ExcludeFromCodeCoverage]
	ref class FormStatoLineaATC : public System::Windows::Forms::Form , IObserver<Event<StateCDB^>^>
	{
		Dictionary<int,Button^> ^listbuttonCDB;
		/*EventQueue<StateCDB^> ^eventiATC;*/
		System::Windows::Forms::ToolTip ^ToolTip1;
		tableLayoutPanelAllCDB ^tableCDB;
		IDisposable ^unsubscriber;
		delegate void GoCallback(int id, int stato , int nid_op, int nid_engine);
		GoCallback^ myDelegate;
		bool _shouldStop;
	public:
		FormStatoLineaATC(/*EventQueue<StateCDB^> ^ev*/)
		{
			InitializeComponent();
			/*eventiATC=ev;*/
			_shouldStop=false;
			listbuttonCDB= gcnew Dictionary<int,Button^> ();
			genera();
			ToolTip1 = gcnew System::Windows::Forms::ToolTip();

			myDelegate = gcnew GoCallback( this, &FormStatoLineaATC::findandsetCDB );
			//
			//TODO: aggiungere qui il codice del costruttore.
			//
		}
		void genera();
		/*void aggiorna();*/
		void RequestStop();
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
		void findandsetCDB(int id, int stato , int nid_op, int nid_engine);
	protected:
		/// <summary>
		/// Liberare le risorse in uso.
		/// </summary>
		~FormStatoLineaATC()
		{
			if (components)
			{
				delete components;
			}
		}

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FormStatoLineaATC::typeid));
			this->SuspendLayout();
			// 
			// FormStatoLineaATC
			//
			
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Location = System::Drawing::Point(1, 370);
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1500, 420);
			this->ControlBox = false;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"FormStatoLineaATC";
			this->Text = L"FormStatoLineaATC";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &FormStatoLineaATC::FormStatoLineaATC_FormClosing);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void FormStatoLineaATC_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
				if(_shouldStop){
				 e->Cancel=false;
				}else{
					e->Cancel=true;
				}
			 }
	};
}
