#include "ItineraryBox.h"


ItineraryBox::ItineraryBox(Fermata ^f, stazione ^s)
{
	fermata=f;
	station=s;
	init();

	this->setNameStation(f->getnameStazione());
	this->setInitEntrata(f->getIditinerarioEntrata());
	this->setInitUscita(f->getIditinerarioUscita());
	this->comboBoxU->SelectedIndexChanged += gcnew System::EventHandler(this, &ItineraryBox::comboBoxU_SelectedIndexChanged);
	this->comboBoxE->SelectedIndexChanged += gcnew System::EventHandler(this, &ItineraryBox::comboBoxE_SelectedIndexChanged);
}

void ItineraryBox::init()
{
	this->components = gcnew System::ComponentModel::Container;

	this->errorProvider = gcnew System::Windows::Forms::ErrorProvider;

	this->label = (gcnew System::Windows::Forms::Label());
	this->tableLayoutPanel = (gcnew System::Windows::Forms::TableLayoutPanel());
	this->comboBoxE = (gcnew System::Windows::Forms::ComboBox());
	this->comboBoxU = (gcnew System::Windows::Forms::ComboBox());
	//this->textboxE = gcnew System::Windows::Forms::TextBox();
	//this->textboxU = gcnew System::Windows::Forms::TextBox();

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
	// comboBoxE
	// 
	this->comboBoxE->FormattingEnabled = true;

	this->comboBoxE->Name = L"comboBoxe";
	this->comboBoxE->Size = System::Drawing::Size(60, 23);
	this->comboBoxE->TabIndex = 8;
	this->comboBoxE->DisplayMember = "ShortDescName";
	this->comboBoxE->ValueMember = "ShortName";
	this->SuspendLayout();


	// 
	// comboBoxU
	// 
	this->comboBoxU->FormattingEnabled = true;

	this->comboBoxU->Name = L"comboBoxu";
	this->comboBoxU->Size = System::Drawing::Size(60, 23);
	this->comboBoxU->TabIndex = 9;
	this->comboBoxU->DisplayMember = "ShortDescName";
	this->comboBoxU->ValueMember = "ShortName";
	this->SuspendLayout();


	this->tableLayoutPanel->Location = System::Drawing::Point(16, 39);
	this->tableLayoutPanel->Name = L"tableLayoutPanel1";
	this->tableLayoutPanel->ColumnCount = 2;
	this->tableLayoutPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->tableLayoutPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));


	this->tableLayoutPanel->RowCount = 1;
	this->tableLayoutPanel->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));

	this->tableLayoutPanel->TabIndex = 12;
	this->tableLayoutPanel->Size = System::Drawing::Size(127, 44);

	tableLayoutPanel->Controls->Add(comboBoxE,0,0);
	tableLayoutPanel->Controls->Add(comboBoxU,2,0);
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

void ItineraryBox::initCombo(String ^direzione){
	Dictionary<int,Itinerario^ > ^itinerari =  station->getItinerariid();
	Dictionary<int,Itinerario^ >::ValueCollection ^valueColl =   station->getItinerariid()->Values;
	if(comboBoxE->Items->Count==0){
		for each (Itinerario ^itin in valueColl)
		{
			if(itin->getDirezione()==direzione){
				if(itin->getTipiItinerario()==typeItini::Entrata){
					comboBoxE->Items->Add(itin);
				}else{
					if(itin->getTipiItinerario()==typeItini::Uscita){
						comboBoxU->Items->Add(itin);
					}


				}
			}

		}
	}


}


void ItineraryBox::setNameStation(System::String ^s){

	this->label->Text=s;

}

void ItineraryBox::setInitEntrata(int id){
	if(id>0){
		Itinerario ^i = station->getItinerariid()[id];
		initCombo(i->getDirezione());
		int index = comboBoxE->FindString(i->getName());
		comboBoxE->SelectedIndex = index;
	}else{
		//comboBoxE->Visible=false;
	}

}


void ItineraryBox::setInitUscita(int id){
	if(id>0){
		Itinerario ^i = station->getItinerariid()[id];
		initCombo(i->getDirezione());
		int index = comboBoxU->FindString(i->getName());
		comboBoxU->SelectedIndex = index;
	}else{
		//comboBoxU->Visible=false;
	}
}

Void ItineraryBox::comboBoxE_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e){
	/*System::Windows::Forms::ComboBox ^combo =( System::Windows::Forms::ComboBox^) sender ;
	Itinerario ^itsel = (Itinerario^) combo->SelectedItem;
	fermata->setIditinerarioEntrata(itsel->getId());*/
	CambioItineraioEntrata(sender,e);
}

Void ItineraryBox::comboBoxU_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e){
	/*System::Windows::Forms::ComboBox ^combo =( System::Windows::Forms::ComboBox^) sender ;
	Itinerario ^itsel = (Itinerario^) combo->SelectedItem;
	fermata->setIditinerarioUscita(itsel->getId());*/
	CambioItineraioUscita(sender,e);
}