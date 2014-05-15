#pragma once
#include "SingleTrainInfoForm.h"
#include "Itinerari\\TabellaStazioni.h"
#include "EventQueue.h"
/*questa classe rappresenta la vista nel modello mvc e viene utilizzata per visualizzare i treni presenti in lista pronti*/
namespace Prototipo {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Diagnostics::CodeAnalysis;


	/// <summary>
	/// Riepilogo per ListTrainView
	/// </summary>
	[ExcludeFromCodeCoverage]
	public ref class ListTrainView : public System::Windows::Forms::Form,IObserver<List<Train^>^>
	{

		IDisposable ^unsubscriber;
		ListTrainModel ^model;
		delegate void GoCallback(List<Train^>^ trains);
		delegate void DeleteListCallback();
		delegate void PaintCallback();
		DeleteListCallback ^myDelegateDeleteList;
		GoCallback ^myDelegateNewTrain;
		PaintCallback^ myDelegatePaint;
		TabellaStazioni ^tabItinerari;
		Dictionary<String^,SingleTrainInfoForm^> ^dictionaryTrainsInfoForm;
		EventQueue<List<Fermata^>^> ^EQueueCambioOrario;
		bool _shouldStop;
	public:
		ListTrainView(TabellaStazioni ^ti,EventQueue<List<Fermata^>^> ^ECambioOrario)
		{
			myDelegateNewTrain = gcnew GoCallback( this, &ListTrainView::setNewTrain );
			tabItinerari=ti;
			_shouldStop=false;
			InitializeComponent();
			myDelegateDeleteList = gcnew DeleteListCallback(this, &ListTrainView::DeleteList);
			myDelegatePaint = gcnew PaintCallback(this, &ListTrainView::RePaintList);
			dictionaryTrainsInfoForm = gcnew Dictionary<String^,SingleTrainInfoForm^>();
			EQueueCambioOrario =ECambioOrario;
			//
			//TODO: aggiungere qui il codice del costruttore.
			//
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Location = System::Drawing::Point(900, 400);
		}
		void AddModel(ListTrainModel ^c );
		void ViewNewTrain(List<Train^>^ trains);
		void setNewTrain(List<Train^>^ trains);
		void DeleteList();
		void RePaintList();
		void PaintTrain();
		void ViewDeleteList();
		void RequestStop(){_shouldStop=true;};
		Void B_Click(System::Object^  sender, System::EventArgs^  e);

		virtual void OnCompleted();
		virtual void OnError(Exception ^e);
		virtual void OnNext(List<Train^> ^value);

		virtual void Subscribe(IObservable<List<Train^>^> ^provider);
		virtual void Unsubscribe();

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ListTrainView::typeid));
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
			this->ControlBox = false;
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->label1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"Lista Treni";
			this->Text = L"Lista Treni";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &ListTrainView::ListTrainView_FormClosing);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void ListTrainView_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
				 if(_shouldStop){

					 for each (SingleTrainInfoForm ^var in dictionaryTrainsInfoForm->Values)
					 {
						 var->Close();
					 }
					 e->Cancel=false;
				 }else{
					 e->Cancel=true;
				 }
			 }
	};
}
