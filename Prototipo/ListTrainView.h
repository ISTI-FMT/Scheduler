#pragma once
#include "IListTrainView.h"
#include "SingleTrainInfoForm.h"
#include "Itinerari\\tabellaItinerari.h"

namespace Prototipo {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Riepilogo per ListTrainView
	/// </summary>
	public ref class ListTrainView : public System::Windows::Forms::Form,IListTrainView
	{
		IControllerListTrain ^controller;
		delegate void GoCallback(KeyListTrain ^key,Train^ train);
		GoCallback^ myDelegateNewTrain;
		tabellaItinerari ^tabItinerari;
	public:
		ListTrainView(tabellaItinerari ^ti)
		{
			myDelegateNewTrain = gcnew GoCallback( this, &ListTrainView::setNewTrain );
			tabItinerari=ti;
			InitializeComponent();
			
			
			//
			//TODO: aggiungere qui il codice del costruttore.
			//
		}
		virtual void AddListener(IControllerListTrain ^c );
		virtual void ViewNewTrain(KeyListTrain ^key,Train^ train);
		 void setNewTrain(KeyListTrain ^key,Train^ train);
		virtual void ViewChangeTrain(KeyListTrain ^key,StateTrain state);
		virtual void ViewChangeTrain(KeyListTrain ^key,List<Fermata^>^ train);
		Void B_Click(System::Object^  sender, System::EventArgs^  e);
	protected:
		/// <summary>
		/// Liberare le risorse in uso.
		/// </summary>
		~ListTrainView()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected: 
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;

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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(59, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Lista Treni:";
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 4;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel1->Location = System::Drawing::Point(13, 43);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 4;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->Size = System::Drawing::Size(414, 387);
			this->tableLayoutPanel1->TabIndex = 1;
			// 
			// ListTrainView
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(439, 472);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->label1);
			this->Name = L"ListTrainView";
			this->Text = L"ListTrainView";
			this->ControlBox=false;
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		
	};
}
