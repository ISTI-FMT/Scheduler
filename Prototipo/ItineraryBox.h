#pragma once
#include "tabellaOrario\\Fermata.h"
#include "Itinerari\\stazione.h"

/*Utilizzo questa classe per rappresentare graficamente un controllo che visualizzi le informazioni sugli itinerari*/
using namespace System::Diagnostics::CodeAnalysis;

[ExcludeFromCodeCoverage]
ref class ItineraryBox :
public System::Windows::Forms::UserControl
{
	System::Windows::Forms::Label^  label;
	System::ComponentModel::IContainer^ components;
	System::Windows::Forms::ErrorProvider^ errorProvider;
	System::Windows::Forms::TableLayoutPanel ^ tableLayoutPanel;
	System::Windows::Forms::ComboBox^  comboBoxE;
	System::Windows::Forms::ComboBox^  comboBoxU;
	System::Windows::Forms::DateTimePicker^  orarioP;
	System::Windows::Forms::DateTimePicker^  orarioA;
	System::Windows::Forms::TextBox^  textBoxN;
	System::Windows::Forms::CheckBox^  CheckBoxC;
	Fermata ^fermata;
	stazione ^station;
public:
	//delegate void EventHandler(Object ^ sender,   EventArgs ^ e);
	event EventHandler ^CambioItineraioUscita;
	event EventHandler ^CambioItineraioEntrata;
	ItineraryBox(Fermata ^f, stazione ^s);
	ItineraryBox(stazione ^s, int i);
	void init();
	void setNameStation(System::String ^s);
	void setInitUscita(int id);
	void setInitEntrata(int id);
	void setOrarioP(double id);
	void setOrarioA(double id);
	
	int getIdIUscita(){
		//'System.NullReferenceException' 
		 Itinerario^ it = ((Itinerario^)comboBoxU->SelectedItem);
		 if(it!=nullptr){
			return it->getId();
		 }
		 return 0;
		
	}
	String^ getNomeIDUscita(){
		//'System.NullReferenceException' 
		 Itinerario^ it = ((Itinerario^)comboBoxU->SelectedItem);
		 if(it!=nullptr){
			return it->getName();
		 }
		 return "";
		
	}
	int getIdIEntrata(){
		 Itinerario^ it = ((Itinerario^)comboBoxE->SelectedItem);
		 if(it!=nullptr){
			return it->getId();
		 }
		 return 0;
	}
	String^ getNameIdEntrata(){
		 Itinerario^ it = ((Itinerario^)comboBoxE->SelectedItem);
		 if(it!=nullptr){
			 return it->getName();
		 }
		 return "";
	}
	String ^getStationName(){
		return station->get_NomeStazione();
	}
	int getIdStation(){
		return station->get_idStazione();
	}
	KeyValuePair<DateTime, DateTime> ^getOrari(){
		DateTime arr =  DateTime(orarioA->Value);
		DateTime parr = DateTime(orarioP->Value);

		return KeyValuePair<DateTime, DateTime>(arr,parr);
	}
	Fermata ^getFermataAggiornataOrari(){
		DateTime arr =  DateTime(orarioA->Value);
		DateTime parr = DateTime(orarioP->Value);

		Fermata ^result = fermata->Clone();
		result->setOrarioArrivo(arr);
		result->setOrarioPartenza(parr);
		return result;
	}
	void initCombo(String^ direzione);
	void initCombo();
	//static void CambioItineraioUscita();
	Void comboBoxE_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
	Void comboBoxU_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
	Void textBox_TextChangedP(System::Object^  sender, System::EventArgs^  e);
};

