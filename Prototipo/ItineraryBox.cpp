#include "ItineraryBox.h"


ItineraryBox::ItineraryBox(Fermata ^f)
{
	init();
	fermata=f;
	this->setNameStation(f->getnameStazione());
	this->setInitEntrata(f->getIditinerarioEntrata().ToString());
	this->setInitUscita(f->getIditinerarioUscita().ToString());
}

void ItineraryBox::init()
{
	this->components = gcnew System::ComponentModel::Container;

	this->errorProvider = gcnew System::Windows::Forms::ErrorProvider;

	this->label = (gcnew System::Windows::Forms::Label());
	this->tableLayoutPanel = (gcnew System::Windows::Forms::TableLayoutPanel());
	this->textboxE = gcnew System::Windows::Forms::TextBox();
	this->textboxU = gcnew System::Windows::Forms::TextBox();

	//
	// label 
	//

	this->label->AutoSize = true;
	this->label->Location = System::Drawing::Point(13, 13);
	this->label->Name = L"StationName";
	this->label->Size = System::Drawing::Size(35, 13);
	this->label->TabIndex = 0;
	this->label->Text = L"";

	// 
	// textbox
	// 

	this->textboxE->Name = L"textBoxE";
	this->textboxE->Size = System::Drawing::Size(60, 23);
	this->textboxE->TabIndex = 3;
	this->textboxE->TextChanged += gcnew System::EventHandler(this, &ItineraryBox::textBox_TextChangedE);
	// 
	// textbox
	// 
	this->textboxU->Name = L"textBoxU";
	this->textboxU->Size = System::Drawing::Size(60, 23);
	this->textboxU->TabIndex = 4;
	this->textboxU->TextChanged += gcnew System::EventHandler(this, &ItineraryBox::textBox_TextChangedU);

	this->tableLayoutPanel->Location = System::Drawing::Point(16, 39);
	this->tableLayoutPanel->Name = L"tableLayoutPanel1";
	this->tableLayoutPanel->ColumnCount = 2;
	this->tableLayoutPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->tableLayoutPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));


	this->tableLayoutPanel->RowCount = 1;
	this->tableLayoutPanel->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));

	this->tableLayoutPanel->TabIndex = 12;
	this->tableLayoutPanel->Size = System::Drawing::Size(127, 44);

	tableLayoutPanel->Controls->Add(textboxE,0,0);
	tableLayoutPanel->Controls->Add(textboxU,2,0);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	//this->ClientSize = System::Drawing::Size(511, 416);
	array<System::Windows::Forms::Control^>^temp0 = {label,tableLayoutPanel};
	this->Controls->AddRange( temp0 );

	this->AutoSize = true;

	//this->Click += gcnew System::EventHandler(this, &SingleTrainInfoForm::Click);

	//this->ClientSize = System::Drawing::Size(112, 366);
	//Size = System::Drawing::Size( 150, 150 );
	//this->ForeColor=System::Drawing::Color::Yellow;
	this->ResumeLayout(false);
	this->PerformLayout();
}

void ItineraryBox::setNameStation(System::String ^s){

	this->label->Text=s;

}

void ItineraryBox::setInitEntrata(System::String ^s){

	this->textboxE->Text=s;

}


void ItineraryBox::setInitUscita(System::String ^s){

	this->textboxU->Text=s;

}

Void ItineraryBox::textBox_TextChangedE(System::Object^  sender, System::EventArgs^  e){
	 System::Windows::Forms::TextBox ^textarea =( System::Windows::Forms::TextBox^) sender ;
	if (System::Text::RegularExpressions::Regex::IsMatch(textarea->Text,"[^0-9]"))
	{
		 System::Windows::Forms::MessageBox::Show("Please enter only numbers.");
		textarea->Text=textarea->Text->Remove(textarea->Text->Length - 1);
	}

}

Void ItineraryBox::textBox_TextChangedU(System::Object^  sender, System::EventArgs^  e){
	 System::Windows::Forms::TextBox ^textarea =( System::Windows::Forms::TextBox^) sender ;
	if (System::Text::RegularExpressions::Regex::IsMatch(textarea->Text,"[^0-9]"))
	{
		 System::Windows::Forms::MessageBox::Show("Please enter only numbers.");
		textarea->Text=textarea->Text->Remove(textarea->Text->Length - 1);
	}

}