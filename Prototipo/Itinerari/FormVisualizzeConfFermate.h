#pragma once
#include "..\\Itinerari\\tabellaFermate.h"

	using namespace System::Diagnostics;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Net;
	using namespace System::Net::Sockets;

	/*utilizzo questa classe per visualizzare graficamente sotto forma di tabella le informazioni contenute 
	nel file di configurazione della fermate ConfigurazioneFermate.xml*/
ref class FormVisualizzeConfFermate : public Form
{
	// System::Windows::Forms::Form ^  form;
	  System::Windows::Forms::DataGridView^  dataGridView1;
	  tabellaFermate ^tabella;
	  void Form_Resize(System::Object^  sender, System::EventArgs^  e);
public:
	FormVisualizzeConfFermate(tabellaFermate ^tab);
	void Inizialize();

};

