#pragma once
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::IO;
/*utilizzo questa classe per rappresentare graficamente una tabella contenete in ogni casella un bottone
che rappresenta graficamente lo stato dei cdb della linea*/
//rapressenta un controllo usato per visualizzare lo stato di tutti di i cdb della linea
ref class tableLayoutPanelAllCDB : public System::Windows::Forms::UserControl
{
	System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	System::Windows::Forms::Label^  label0;
	System::ComponentModel::IContainer^ components;
	System::Windows::Forms::ErrorProvider^ errorProvider;
	Dictionary<int,Button^> ^lbuttonCDB;

public:
	tableLayoutPanelAllCDB( Dictionary<int,Button^> ^lbCDB);

	void init();
	TableLayoutPanel ^getTableLayoutPanel(){return tableLayoutPanel1;};
	Button^ getButton(String ^textbutton);
	void addbutton(String ^namebutton, int riga, int colonna);
	//void addbuttonUscita(String ^namebutton, int id);
	/*Void button_Click(System::Object^  sender, System::EventArgs^  e);*/
	void read(String ^file);
};

