#pragma once
#include "TabellaOrario.h"
#include "..\\EditorTabellaOrario.h"

	using namespace System::Diagnostics;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Net;
	using namespace System::Net::Sockets;
	
/*Utilizzo questa classe per visualizzare graficamente le informazioni presenti nel file di configurazione della
tabella orario*/

//form per visualizzare sotto forma di tabella le informazioni contenute nel file della tabella orario
using namespace System::Diagnostics::CodeAnalysis;

[ExcludeFromCodeCoverage]
ref class FormVisualizzeTabOrario : public Form
{
	// System::Windows::Forms::Form ^  form;
	  System::Windows::Forms::DataGridView^  dataGridView1;
	  TabellaOrario ^tabella;
	  Button ^NewTrain;
	  TabellaStazioni ^Tabellastazioni;
	  void Form_Resize(System::Object^  sender, System::EventArgs^  e);
	  void NewTrain_Click(System::Object^  sender, System::EventArgs^  e);
public:
	FormVisualizzeTabOrario(TabellaOrario ^tab, TabellaStazioni ^t);
	void Inizialize();

};

