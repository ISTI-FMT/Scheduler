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
	void initCombo();
	//static void CambioItineraioUscita();
	Void comboBoxE_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
	Void comboBoxU_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
};

