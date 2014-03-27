#include "ItineraryBox.h"


ItineraryBox::ItineraryBox(Fermata ^f, stazione ^s)
{
	fermata=f;
	station=s;
	init();

	this->setNameStation(f->getnameStazione()+" "+s->get_idStazione());
	this->setInitEntrata(f->getIditinerarioEntrata());
	this->setInitUscita(f->getIditinerarioUscita());
	this->setOrarioA(f->getOrarioArrivo());
	this->setOrarioP(f->getOrarioPartenza());
	this->comboBoxU->SelectedIndexChanged += gcnew System::EventHandler(this, &ItineraryBox::comboBoxU_SelectedIndexChanged);
	this->comboBoxE->SelectedIndexChanged += gcnew System::EventHandler(this, &ItineraryBox::comboBoxE_SelectedIndexChanged);
}

ItineraryBox::ItineraryBox(stazione ^s, int i)
{

	station=s;
	init();

	this->setNameStation(s->get_NomeStazione()+" "+s->get_idStazione().ToString());
	initCombo();

	// textBoxN
	// 
	this->textBoxN = gcnew System::Windows::Forms::TextBox();
	this->textBoxN->Location = System::Drawing::Point(140, 13);
	this->textBoxN->Name = L"textBoxN";
	this->textBoxN->Size = System::Drawing::Size(18, 20);
	this->textBoxN->TabIndex = 0;
	this->textBoxN->Text=i.ToString();
	// 
	// CheckBoxC
	// 
	this->CheckBoxC = gcnew System::Windows::Forms::CheckBox();
	this->CheckBoxC->AutoSize = true;
	this->CheckBoxC->Location = System::Drawing::Point(160, 13);
	this->CheckBoxC->Name = L"CheckBoxC";
	this->CheckBoxC->Size = System::Drawing::Size(15, 14);
	this->CheckBoxC->TabIndex = 5;
	this->CheckBoxC->Checked =true;
	this->CheckBoxC->UseVisualStyleBackColor = true;
	this->label->Location = System::Drawing::Point(5, 13);
	array<System::Windows::Forms::Control^>^temp0 = {textBoxN,CheckBoxC};
	this->Controls->AddRange( temp0 );
	//this->comboBoxU->SelectedIndex=0;
	//this->comboBoxE->SelectedIndex=0;
	this->comboBoxU->SelectedIndexChanged += gcnew System::EventHandler(this, &ItineraryBox::comboBoxU_SelectedIndexChanged);
	this->comboBoxE->SelectedIndexChanged += gcnew System::EventHandler(this, &ItineraryBox::comboBoxE_SelectedIndexChanged);
}

void ItineraryBox::init()
{
	this->components = gcnew System::ComponentModel::Container;

	this->errorProvider = gcnew System::Windows::Forms::ErrorProvider;
	this->orarioA = (gcnew System::Windows::Forms::DateTimePicker());
	this->orarioP = (gcnew System::Windows::Forms::DateTimePicker());

	this->label = (gcnew System::Windows::Forms::Label());
	this->tableLayoutPanel = (gcnew System::Windows::Forms::TableLayoutPanel());
	this->comboBoxE = (gcnew System::Windows::Forms::ComboBox());
	this->comboBoxU = (gcnew System::Windows::Forms::ComboBox());
	//this->textboxE = gcnew System::Windows::Forms::TextBox();
	//this->textboxU = gcnew System::Windows::Forms::TextBox();


	// 
	// orarioP
	// 
	this->orarioP->Format = System::Windows::Forms::DateTimePickerFormat::Time;
	this->orarioP->ShowUpDown = true;
	//this->orarioP->Location = System::Drawing::Point(243, 247);
	this->orarioP->Name = L"orarioP";
	this->orarioP->Size = System::Drawing::Size(67, 20);
	this->orarioP->TabIndex = 9;
	this->orarioP->Value =  DateTime::ParseExact("00:00:00", "HH:mm:ss",  System::Globalization::CultureInfo::InvariantCulture);

	// 
	// orarioA
	// 
	this->orarioA->Format = System::Windows::Forms::DateTimePickerFormat::Time;
	this->orarioA->ShowUpDown = true;
	//this->orarioA->Location = System::Drawing::Point(243, 247);
	this->orarioA->Name = L"orarioP";
	this->orarioA->Size = System::Drawing::Size(67, 20);
	this->orarioA->TabIndex = 19;
	this->orarioA->Value = DateTime::ParseExact("00:00:00", "HH:mm:ss",  System::Globalization::CultureInfo::InvariantCulture);

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


	this->tableLayoutPanel->RowCount = 2;
	this->tableLayoutPanel->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->tableLayoutPanel->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));

	this->tableLayoutPanel->TabIndex = 12;
	this->tableLayoutPanel->Size = System::Drawing::Size(142, 70);

	tableLayoutPanel->Controls->Add(orarioA,0,0);
	tableLayoutPanel->Controls->Add(orarioP,2,0);


	tableLayoutPanel->Controls->Add(comboBoxE,0,1);
	tableLayoutPanel->Controls->Add(comboBoxU,2,1);
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
				if(itin->getTipoItinerario()==typeItini::Entrata){
					comboBoxE->Items->Add(itin);
				}else{
					if(itin->getTipoItinerario()==typeItini::Uscita){
						comboBoxU->Items->Add(itin);
					}


				}
			}

		}
	}


}

void ItineraryBox::initCombo(){
	Dictionary<int,Itinerario^ > ^itinerari =  station->getItinerariid();
	Dictionary<int,Itinerario^ >::ValueCollection ^valueColl =   station->getItinerariid()->Values;

	for each (Itinerario ^itin in valueColl)
	{

		if(itin->getTipoItinerario()==typeItini::Entrata){
			comboBoxE->Items->Add(itin);
		}else{
			if(itin->getTipoItinerario()==typeItini::Uscita){
				comboBoxU->Items->Add(itin);
			}


		}


	}
	if(comboBoxE->Items->Count==0){
		comboBoxE->Visible=false;
	}
	if(comboBoxU->Items->Count==0){
		comboBoxU->Visible=false;
	}

}


void ItineraryBox::setNameStation(System::String ^s){

	this->label->Text=s;

}

void ItineraryBox::setOrarioA(double o){
	if(o>0){
		Double times = o*30;
		TimeSpan sinceMidnight = TimeSpan::FromSeconds(times);
		DateTime orarioSupporto = DateTime::ParseExact("00:00:00", "HH:mm:ss", System::Globalization::CultureInfo::InvariantCulture);
		DateTime TimeStampNextEvent= orarioSupporto+sinceMidnight;
		this->orarioA->Value=TimeStampNextEvent;
	}
}
void ItineraryBox::setOrarioP(double o){
	if(o>0){
		Double times = o*30;
		TimeSpan sinceMidnight = TimeSpan::FromSeconds(times);
		DateTime orarioSupporto = DateTime::ParseExact("00:00:00", "HH:mm:ss",  System::Globalization::CultureInfo::InvariantCulture);
		DateTime 	TimeStampNextEvent= orarioSupporto+sinceMidnight;
		this->orarioP->Value=TimeStampNextEvent;
	}
}

void ItineraryBox::setInitEntrata(int id){
	if(id>0){
		Itinerario ^i = station->getItinerariid()[id];
		initCombo(i->getDirezione());
		int index = comboBoxE->FindString(i->ShortName);
		comboBoxE->SelectedIndex = index;
	}else{
		comboBoxE->Visible=false;
	}

}


void ItineraryBox::setInitUscita(int id){
	if(id>0){
		Itinerario ^i = station->getItinerariid()[id];
		initCombo(i->getDirezione());
		int index = comboBoxU->FindString(i->ShortName);
		comboBoxU->SelectedIndex = index;
	}else{
		comboBoxU->Visible=false;
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

Void ItineraryBox::textBox_TextChangedP(System::Object^  sender, System::EventArgs^  e){
	System::Windows::Forms::TextBox ^textarea =(System::Windows::Forms::TextBox^) sender ;

	//[0-9]+(?:\.[0-9]*)?
	System::Text::RegularExpressions::Match ^m = System::Text::RegularExpressions::Regex::Match(textarea->Text,"[0-9]+(?:\\.[0-9]*)?");
	if (m->Success){
		if(m->Value->Length!=textarea->Text->Length){
			textarea->Text=m->Value;
		}
	}else{
		System::Windows::Forms::MessageBox::Show("Please enter only numbers.");

	}
}