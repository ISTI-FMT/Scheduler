#include "mapTrenoFisicoLogico.h"
#include "EditorMapTreni.h"
#include "FormDeleteElement.h"
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
map treni*/

//form per visualizzare sotto forma di tabella le informazioni contenute nel file maprteni xml
using namespace System::Diagnostics::CodeAnalysis;

[ExcludeFromCodeCoverage]
ref class FormVisualizzeMapTreni : public Form
{
	// System::Windows::Forms::Form ^  form;
	  System::Windows::Forms::DataGridView^  dataGridView1;
	  
	  Button ^NewTrain;
	  Button ^SaveXml;
	  Button^DeleteTrain;
	  mapTrenoFisicoLogico ^mapFisicoLogico;
	  void Form_Resize(System::Object^  sender, System::EventArgs^  e);
	  void NewTrain_Click(System::Object^  sender, System::EventArgs^  e);
	  void SaveXml_Click(System::Object^  sender, System::EventArgs^  e);
	  void Addtreno(System::Object^  sender, System::EventArgs^  e);
	  void DelTrain(System::Object^  sender, System::EventArgs^  e);
	  void DeleteTrain_Click(System::Object^  sender, System::EventArgs^  e);
	  void Aggiorna();
public:
	FormVisualizzeMapTreni(mapTrenoFisicoLogico ^m);
	void Inizialize();

};
