#pragma once
#include "..\\Itinerari\\TabellaStazioni.h"

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
	nel file di configurazione della fermate ConfigurazioneFermate.xml*/
[ExcludeFromCodeCoverage]
ref class FormVisualizzeConfFermate : public Form
{
	// System::Windows::Forms::Form ^  form;
	  System::Windows::Forms::DataGridView^  dataGridView1;
	  TabellaStazioni ^tabella;
	  void Form_Resize(System::Object^  sender, System::EventArgs^  e);
public:
	FormVisualizzeConfFermate(TabellaStazioni ^tab);
	void Inizialize();

};

