#pragma once
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/*Utilizzo questa classe per rappresentare graficamente un controllo che visualizzi delle scritte che cambiano colore
in loop cosi da verificare se effettivamente l'applicazione è "viva"*/

//questo oggetto rappresenta un controllo che implementa un watch dog
ref class wdogcontrol : public System::Windows::Forms::UserControl
{
private: System::Windows::Forms::Label^  label0;
		 System::Windows::Forms::Label^  label1;
		 System::Windows::Forms::Label^  label2;
		 System::Windows::Forms::Label^  label3;
		 System::Windows::Forms::Label^  label4;
		 System::Windows::Forms::Label^  label5;
		 System::Windows::Forms::Label^  label6;
		 System::Windows::Forms::Label^  label7;


		 System::ComponentModel::IContainer^ components;
		 System::Windows::Forms::ErrorProvider^ errorProvider;
public:
	wdogcontrol(void);
	void InitializeComponent();
	void onNext();
	delegate void GoCallback();
	GoCallback^ myDelegate;
	void GoNext();
	void OverNext();
	delegate void GoCallbackOver();
	GoCallbackOver^ myDelegateOver;
	void OverMethodNext();
};

