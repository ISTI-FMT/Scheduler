#pragma once
#include "tabellaOrario\\Fermata.h"
#include "Itinerari\\stazione.h"
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
	Fermata ^fermata;
	stazione ^station;
public:
	//delegate void EventHandler(Object ^ sender,   EventArgs ^ e);
	event EventHandler ^CambioItineraioUscita;
	event EventHandler ^CambioItineraioEntrata;
	ItineraryBox(Fermata ^f, stazione ^s);
	void init();
	void setNameStation(System::String ^s);
	void setInitUscita(int id);
	void setInitEntrata(int id);
	void setOrarioP(double id);
	void setOrarioA(double id);
	int getStationId(){
		return fermata->getIdStazione();
	}
	int getIdIUscita(){
		
		return ((Itinerario^)comboBoxU->SelectedItem)->getId();
	}
	int getIdIEntrata(){
		
		return ((Itinerario^)comboBoxE->SelectedItem)->getId();
	}
	String ^getStationName(){
		return fermata->getnameStazione();
	}
	int getIdStation(){
		return fermata->getIdStazione();
	}
	KeyValuePair<DateTime, DateTime> getOrari(){
DateTime arr =  DateTime(orarioA->Value);
DateTime parr = DateTime(orarioP->Value);
 KeyValuePair<DateTime, DateTime> result = KeyValuePair<DateTime, DateTime>(arr,parr);
		return result;
	}
	void initCombo(String^ direzione);
	//static void CambioItineraioUscita();
	Void comboBoxE_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
	Void comboBoxU_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
};

