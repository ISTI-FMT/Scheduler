#pragma once
#include "tableLayoutPanelAllCDB.h"
#include "..\\EventQueue.h"

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
	public:
		FormStatoLineaATC(EventQueue ^ev)
		{
			InitializeComponent();
						eventiATC=ev;

			listbuttonCDB= gcnew Dictionary<int,Button^> ();
			genera();
			//
			//TODO: aggiungere qui il codice del costruttore.
			//
		}
		void genera();
		void aggiorna();
	
		void findandsetCDB(int id, int stato);
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
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1150, 378);
			this->Name = L"FormStatoLineaATC";
			this->Text = L"FormStatoLineaATC";
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
