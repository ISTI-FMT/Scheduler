#pragma once
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class wdogcontrol : public System::Windows::Forms::UserControl
{
private: System::Windows::Forms::Label^  label0;
		 System::Windows::Forms::Label^  label1;
		 System::Windows::Forms::Label^  label2;
		 System::Windows::Forms::Label^  label3;
		 System::ComponentModel::IContainer^ components;
		 System::Windows::Forms::ErrorProvider^ errorProvider;
public:
	wdogcontrol(void);
	void InitializeComponent();
	void onNext();
	delegate void GoCallback();
	GoCallback^ myDelegate;
	void GoNext();
};

