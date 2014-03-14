#pragma once
#include "ControllerListTrain.h"
#include "ItineraryBox.h"
#include "Itinerari\\TabellaStazioni.h"
#include "Event.h"
#include "Unsubscriber.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;

/*questa classe rappresenta la form con le informazioni del treno*/

using namespace System::Diagnostics::CodeAnalysis;
[ExcludeFromCodeCoverage]
ref class SingleTrainInfoForm : public System::Windows::Forms::Form,IComparable<SingleTrainInfoForm^>, IObservable<Event<List<Fermata^>^>^>,IObserver<Train^>
{
	Train ^train;
	IDisposable ^unsubscriber;
	System::Windows::Forms::TableLayoutPanel^  tableLayoutPanelItinerari;
	System::Windows::Forms::Label^  label5;
	System::Windows::Forms::Label^  Labeltrn;
	System::Windows::Forms::Label^  Labelip;
	System::Windows::Forms::Label^  LabelEngineNumber;
	System::Windows::Forms::Label^  LabelPriorita;
	System::Windows::Forms::TextBox ^textboxPriorita;
	System::Windows::Forms::Button ^ bclose;
	System::Windows::Forms::Button ^ bapply;
	System::ComponentModel::IContainer^ components;
	System::Windows::Forms::ErrorProvider^ errorProvider;
	System::Windows::Forms::RichTextBox^  richTextBox1;
	System::Windows::Forms::Label^  LabelStateTrain;
	System::Windows::Forms::ComboBox^  comboBoxCambiaStatoTreno;
	System::IO::Stream^ stream;
	System::Drawing::Image ^Imagegreen;
	System::Drawing::Image ^Imagered;
	System::Drawing::Icon ^Icongreen;
	System::Drawing::Icon ^Iconred;
	StateTrain tempStateTrain;
	ListTrainModel ^model;
	TabellaStazioni ^tabItineari;
	List<IObserver<Event<List<Fermata^>^>^>^> ^observers;
	delegate void GoCallback(Train^ t);
	GoCallback ^DelegateCTrain;
public:
	SingleTrainInfoForm(Train ^t,  ListTrainModel ^m,TabellaStazioni ^ti);
	void init();
	void set();
	virtual Int32 CompareTo(SingleTrainInfoForm^ otherKey);
	Void ItBox_ItChangedU(System::Object^  sender, System::EventArgs^  e);
	Void ItBox_ItChangedE(System::Object^  sender, System::EventArgs^  e);
	Void textBox_TextChangedP(System::Object^  sender, System::EventArgs^  e);
	//Void B_Click(System::Object^  sender, System::EventArgs^  e);
	Void ButtonClose_Click(System::Object^  sender, System::EventArgs^  e);
	Void ButtonApply_Click(System::Object^  sender, System::EventArgs^  e);
	void setinfoTrain(Train^ train);
	virtual IDisposable ^Subscribe(IObserver<Event<List<Fermata^>^>^> ^observer);
	System::Void comboBoxCambiaStatoTreno_SelectionChangeCommitted(System::Object^  sender, System::EventArgs^  e);
	System::Void SingleTrainInfoForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
	void setitinerary();
	void UpdateInfo();
	void aggiornaiconstate(StateTrain t);
	String ^fromStateTreno(StateTrain t);
	String ^forwardItinerario(int index,List<Fermata^> ^Listafermate);
	virtual void Subscribe(IObservable<Train^> ^provider){
		if (provider != nullptr) 
			unsubscriber = provider->Subscribe(this);	
	};

	virtual void OnCompleted(){
		Console::WriteLine("The Location Tracker has completed transmitting data to");
		Unsubscribe();

	};
	virtual void OnError(Exception ^e){
		Console::WriteLine("The Location Tracker has Error");
		Unsubscribe();

	};
	virtual void OnNext(Train ^t){
		this->Invoke(DelegateCTrain,t);
	};
	virtual void Unsubscribe(){
		delete unsubscriber;
	};
};

