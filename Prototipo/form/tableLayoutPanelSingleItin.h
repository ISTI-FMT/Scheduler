#pragma once
#include "..\\\Itinerari\\stazione.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
/*utilizzo questa classe per rappresentare graficamente una tabella contenete in ogni casella un bottone
che rappresenta graficamente lo stato degli itinerari*/
//rappresenta un controllo per la visualizzazione di un singolo itinerario
using namespace System::Diagnostics::CodeAnalysis;

[ExcludeFromCodeCoverage]
ref class tableLayoutPanelSingleItin : public System::Windows::Forms::UserControl
{
	System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	System::Windows::Forms::Label^  label0;
	System::ComponentModel::IContainer^ components;
	System::Windows::Forms::ErrorProvider^ errorProvider;
	Dictionary<int,Button^> ^listbutton;
	int rigae;
	int rigau;
public:
	tableLayoutPanelSingleItin(stazione ^station, Dictionary<int,Button^> ^listb);

	void init(String ^nome, int id);
	TableLayoutPanel ^getTableLayoutPanel(){return tableLayoutPanel1;};
	Button^ getButton(String ^textbutton, int id);
	void addbuttonEntrata(String ^namebutton, int id);
	void addbuttonUscita(String ^namebutton, int id);
	/*Void button_Click(System::Object^  sender, System::EventArgs^  e);*/
	void paint(stazione ^station);
};

