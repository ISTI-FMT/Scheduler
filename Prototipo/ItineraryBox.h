#pragma once
#include "tabellaOrario\\Fermata.h"
ref class ItineraryBox :
public System::Windows::Forms::UserControl
{
	System::Windows::Forms::Label^  label;
	System::Windows::Forms::TextBox ^textboxE;
	System::Windows::Forms::TextBox ^textboxU;
	System::ComponentModel::IContainer^ components;
	System::Windows::Forms::ErrorProvider^ errorProvider;
	System::Windows::Forms::TableLayoutPanel ^ tableLayoutPanel;
	Fermata ^fermata;
public:
	ItineraryBox(Fermata ^f);
	void init();
	void setNameStation(System::String ^s);
	void setInitUscita(System::String ^s);
	void setInitEntrata(System::String ^s);
	Void textBox_TextChangedE(System::Object^  sender, System::EventArgs^  e);
	Void textBox_TextChangedU(System::Object^  sender, System::EventArgs^  e);
};

