#pragma once
#include "ControllerListTrain.h"
#include "ItineraryBox.h"
#include "Itinerari\\tabellaItinerari.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;

ref class SingleTrainInfoForm : public System::Windows::Forms::Button
{
	Train ^train;
	KeyListTrain ^key;
	System::Windows::Forms::Form ^form;
	System::Windows::Forms::TableLayoutPanel^  tableLayoutPanelItinerari;
	System::Windows::Forms::Label^  label5;
	System::Windows::Forms::Label^  Labeltrn;
	System::Windows::Forms::Label^  Labelip;
	System::Windows::Forms::Label^  LabelEngineNumber;
	System::Windows::Forms::Label^  LabelPriorita;
	System::Windows::Forms::TextBox ^textboxPriorita;
	System::Windows::Forms::Button ^ bclose;
	System::ComponentModel::IContainer^ components;
	System::Windows::Forms::ErrorProvider^ errorProvider;
	IControllerListTrain ^controller;
	tabellaItinerari ^tabItineari;
public:
	SingleTrainInfoForm(Train ^t, KeyListTrain ^ k, IControllerListTrain ^c,tabellaItinerari ^ti);
	void init();
	void set();
	
	Void ItBox_ItChangedU(System::Object^  sender, System::EventArgs^  e);
	Void ItBox_ItChangedE(System::Object^  sender, System::EventArgs^  e);
	Void textBox_TextChangedP(System::Object^  sender, System::EventArgs^  e);
	Void B_Click(System::Object^  sender, System::EventArgs^  e);
	Void ButtonClose_Click(System::Object^  sender, System::EventArgs^  e);
	void setitinerary();

};

