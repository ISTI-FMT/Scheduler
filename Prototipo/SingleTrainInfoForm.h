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

ref class SingleTrainInfoForm : public System::Windows::Forms::Form,IComparable<SingleTrainInfoForm^>, IObservable<Event<List<Fermata^>^>^>
{
	Train ^train;
	
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
	ListTrainModel ^model;
	TabellaStazioni ^tabItineari;
	List<IObserver<Event<List<Fermata^>^>^>^> ^observers;
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
	
	virtual IDisposable ^Subscribe(IObserver<Event<List<Fermata^>^>^> ^observer);

	void setitinerary();
	void UpdateInfo();

};

