#pragma once
#include "stazione.h"
#include "tabellaItinerari.h"

	using namespace System::Diagnostics;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Net;
	using namespace System::Net::Sockets;
	//questa form visualizza sotto forma di tabella le informazioni contenute nel file di configurazione degli itinerari
ref class FormVisualizzeConfItine : public Form
{
	// System::Windows::Forms::Form ^  form;
	  System::Windows::Forms::DataGridView^  dataGridView1;
	  tabellaItinerari ^tabella;
	  void Form_Resize(System::Object^  sender, System::EventArgs^  e);
public:
	FormVisualizzeConfItine(tabellaItinerari ^tab);
	void Inizialize();

};

