#pragma once
#include "stazione.h"
#include "TabellaStazioni.h"

	using namespace System::Diagnostics;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Net;
	using namespace System::Net::Sockets;
	using namespace System::Diagnostics::CodeAnalysis;
	
	/*utilizzo questa classe per visualizzare graficamente sotto forma di tabella le informazioni contenute 
	nel file di configurazione degli Itinerari ConfigurazioneItinerari.xml*/
	//questa form visualizza sotto forma di tabella le informazioni contenute nel file di configurazione degli itinerari
[ExcludeFromCodeCoverage]
ref class FormVisualizzeConfItine : public Form
{
	// System::Windows::Forms::Form ^  form;
	  System::Windows::Forms::DataGridView^  dataGridView1;
	  TabellaStazioni ^tabella;
	  void Form_Resize(System::Object^  sender, System::EventArgs^  e);
public:
	FormVisualizzeConfItine(TabellaStazioni ^tab);
	void Inizialize();

};

