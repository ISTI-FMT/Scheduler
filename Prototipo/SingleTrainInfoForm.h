#pragma once
#include "ControllerListTrain.h"
#include "ItineraryBox.h"
#include "Itinerari\\TabellaStazioni.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;

ref class SingleTrainInfoForm : public System::Windows::Forms::Form,IComparable<SingleTrainInfoForm^>
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
	void setitinerary();
	void UpdateInfo();

};

