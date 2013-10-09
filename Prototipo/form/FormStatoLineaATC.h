#pragma once
#include "tableLayoutPanelAllCDB.h"
#include "..\\EventQueue.h"

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


	/// <summary>
	/// Riepilogo per FormStatoLineaATC
	/// </summary>
 ref class FormStatoLineaATC : public System::Windows::Forms::Form
	{
		Dictionary<int,Button^> ^listbuttonCDB;
		EventQueue ^eventiATC;
		System::Windows::Forms::ToolTip ^ToolTip1;
		tableLayoutPanelAllCDB ^tableCDB;

		delegate void GoCallback(int id, int stato , int nid_op, int nid_engine);
		GoCallback^ myDelegate;
	
	public:
		FormStatoLineaATC(EventQueue ^ev)
		{
			InitializeComponent();
						eventiATC=ev;

			listbuttonCDB= gcnew Dictionary<int,Button^> ();
			genera();
			ToolTip1 = gcnew System::Windows::Forms::ToolTip();

			myDelegate = gcnew GoCallback( this, &FormStatoLineaATC::findandsetCDB );
			//
			//TODO: aggiungere qui il codice del costruttore.
			//
		}
		void genera();
		void aggiorna();
	
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
			this->SuspendLayout();
			// 
			// FormStatoLineaATC
			// 
			this->ControlBox=false;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1240, 378);
			this->Name = L"FormStatoLineaATC";
			this->Text = L"FormStatoLineaATC";
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
