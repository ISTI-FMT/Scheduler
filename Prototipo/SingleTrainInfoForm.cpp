#include "SingleTrainInfoForm.h"


SingleTrainInfoForm::SingleTrainInfoForm(Train ^t,  ListTrainModel ^m, TabellaStazioni ^ti)
{

	Form::Form();
	tabItineari=ti;
	model=m;
	train=t;
	init();
	set();
	//this->Click += gcnew System::EventHandler(this, &SingleTrainInfoForm::B_Click);
	this->textboxPriorita->TextChanged += gcnew System::EventHandler(this, &SingleTrainInfoForm::textBox_TextChangedP);
	observers = gcnew List<IObserver<Event<List<Fermata^>^>^>^>();
}

void SingleTrainInfoForm::init(){
	this->components = gcnew System::ComponentModel::Container;
	//this->form = gcnew System::Windows::Forms::Form();
	this->errorProvider = gcnew System::Windows::Forms::ErrorProvider;
	this->tableLayoutPanelItinerari = (gcnew System::Windows::Forms::TableLayoutPanel());
	this->label5 = (gcnew System::Windows::Forms::Label());
	this->Labeltrn= (gcnew System::Windows::Forms::Label());
	this->Labelip= (gcnew System::Windows::Forms::Label());
	this->LabelEngineNumber= (gcnew System::Windows::Forms::Label());
	this->LabelPriorita= (gcnew System::Windows::Forms::Label());
	this->textboxPriorita = gcnew System::Windows::Forms::TextBox();
	this->bclose = (gcnew System::Windows::Forms::Button());
	this->bapply = (gcnew System::Windows::Forms::Button());

	//
	// label TRN
	//

	this->Labeltrn->AutoSize = true;
	this->Labeltrn->Location = System::Drawing::Point(13, 13);
	this->Labeltrn->Name = L"Labeltrn";
	this->Labeltrn->Size = System::Drawing::Size(35, 13);
	this->Labeltrn->TabIndex = 0;
	this->Labeltrn->Text = L"Train Running Number: ";

	// 
	// Labelip
	// 
	this->Labelip->AutoSize = true;
	this->Labelip->Location = System::Drawing::Point(240, 13);
	this->Labelip->Name = L"Labelip";
	this->Labelip->Size = System::Drawing::Size(35, 13);
	this->Labelip->TabIndex = 2;
	this->Labelip->Text = L"IP: ";

	// 
	// LabelEngineNumber
	// 
	this->LabelEngineNumber->AutoSize = true;
	this->LabelEngineNumber->Location = System::Drawing::Point(13, 40);
	this->LabelEngineNumber->Name = L"LabelEngineNumber";
	this->LabelEngineNumber->Size = System::Drawing::Size(35, 13);
	this->LabelEngineNumber->TabIndex = 1;
	this->LabelEngineNumber->Text = L"Engine Number: ";
	// 
	// textboxPriorita
	// 
	this->textboxPriorita->Location = System::Drawing::Point(370, 25);
	this->textboxPriorita->Name = L"textBox1";
	this->textboxPriorita->Size = System::Drawing::Size(100, 20);
	this->textboxPriorita->TabIndex = 3;
	
	// 
	// LabelPriorita
	// 
	this->LabelPriorita->AutoSize = true;
	this->LabelPriorita->Location = System::Drawing::Point(370, 6);
	this->LabelPriorita->Name = L"label4";
	this->LabelPriorita->Size = System::Drawing::Size(42, 13);
	this->LabelPriorita->TabIndex = 4;
	this->LabelPriorita->Text = L"Priorit�:";
	
	// 
	// button1
	// 
	this->bclose->Location = System::Drawing::Point(500, 451);
	this->bclose->Name = L"button1";
	this->bclose->Size = System::Drawing::Size(75, 23);
	this->bclose->TabIndex = 5;
	this->bclose->Text = L"Close";
	this->bclose->UseVisualStyleBackColor = true;
	this->bclose->Click += gcnew System::EventHandler(this, &SingleTrainInfoForm::ButtonClose_Click);
	// 
	// buttonAplly
	// 
	this->bapply->Location = System::Drawing::Point(500, 371);
	this->bapply->Name = L"button2";
	this->bapply->Size = System::Drawing::Size(75, 23);
	this->bapply->TabIndex = 7;
	this->bapply->Text = L"Apply";
	this->bapply->UseVisualStyleBackColor = true;
	this->bapply->Click += gcnew System::EventHandler(this, &SingleTrainInfoForm::ButtonApply_Click);
	// 
	// tableLayoutPanel1
	// 

	this->tableLayoutPanelItinerari->Location = System::Drawing::Point(16, 109);
	this->tableLayoutPanelItinerari->Name = L"tableLayoutPanel1";
	this->tableLayoutPanelItinerari->ColumnCount = 3;
	this->tableLayoutPanelItinerari->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->tableLayoutPanelItinerari->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->tableLayoutPanelItinerari->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	

	this->tableLayoutPanelItinerari->RowCount = 3;
	this->tableLayoutPanelItinerari->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->tableLayoutPanelItinerari->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->tableLayoutPanelItinerari->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->tableLayoutPanelItinerari->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->tableLayoutPanelItinerari->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->tableLayoutPanelItinerari->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->tableLayoutPanelItinerari->TabIndex = 12;
	this->tableLayoutPanelItinerari->Size = System::Drawing::Size(500, 326);

	// 
	// label5
	// 
	this->label5->AutoSize = true;
	this->label5->Location = System::Drawing::Point(16, 75);
	this->label5->Name = L"label5";
	this->label5->Size = System::Drawing::Size(35, 13);
	this->label5->TabIndex = 6;
	this->label5->Text = L"Lista Itinerari:";


	//this->tableLayoutPanelItinerari->Controls->Add(this->label0, 0, 0);

	//this->tableLayoutPanelItinerari->SetColumnSpan(this->label0, 2);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->ClientSize = System::Drawing::Size(551, 456);
	array<System::Windows::Forms::Control^>^temp0 = {label5,Labeltrn,Labelip,LabelEngineNumber,LabelPriorita,textboxPriorita,bclose,bapply,tableLayoutPanelItinerari};
	this->Controls->AddRange( temp0 );
	this->ControlBox=false;
	this->AutoSize = true;

	//this->Click += gcnew System::EventHandler(this, &SingleTrainInfoForm::Click);

	//this->ClientSize = System::Drawing::Size(112, 366);
	//Size = System::Drawing::Size( 150, 150 );
	//this->ForeColor=System::Drawing::Color::Yellow;
	this->ResumeLayout(false);
	this->PerformLayout();

	this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);






}


void SingleTrainInfoForm::set(){
	this->Name =  train->getPhysicalTrain()->getEngineNumber().ToString();
	this->Text =  train->getPhysicalTrain()->getEngineNumber().ToString();
	//this->form->Name =  train->getPhysicalTrain()->getEngineNumber().ToString();
	//this->form->Text =  train->getPhysicalTrain()->getEngineNumber().ToString();
	this->Labeltrn->Text += train->getTRN().ToString();
	this->LabelEngineNumber->Text += train->getPhysicalTrain()->getEngineNumber().ToString();
	this->Labelip->Text +=train->getPhysicalTrain()->getIpAddress();
	this->textboxPriorita->Text = train->getPriorita().ToString();
	setitinerary();
}

void SingleTrainInfoForm::setitinerary(){
	/*int riga=0;
	int colonna=0;*/
	for each (Fermata ^var in train->getListaFermate())
	{
		try{
		int id = var->getIdStazione();
		stazione ^s = tabItineari->getMap()[id];
		
		ItineraryBox ^itbox = gcnew ItineraryBox(var,s);
		itbox->CambioItineraioUscita += gcnew System::EventHandler(this, &SingleTrainInfoForm::ItBox_ItChangedU);
		itbox->CambioItineraioEntrata += gcnew System::EventHandler(this, &SingleTrainInfoForm::ItBox_ItChangedE);
		this->tableLayoutPanelItinerari->Controls->Add(itbox);
		}catch(Exception ^e){
			Console::WriteLine("Errore ",e->Message);
		}

	}
}






/*Void SingleTrainInfoForm::B_Click(System::Object^  sender, System::EventArgs^  e){

	//this->form->Visible==true;
	//Button::OnClick(e);
	Visible=true;
}*/

Void SingleTrainInfoForm::ItBox_ItChangedU(System::Object^  sender, System::EventArgs^  e){
	//ItineraryBox ^itbox =(ItineraryBox^) sender ;
	System::Windows::Forms::ComboBox ^combo =( System::Windows::Forms::ComboBox^) sender ;
	Itinerario ^itsel = (Itinerario^) combo->SelectedItem;
//	Console::WriteLine("hai provato a cambiare NID_IT:{0} di {1}",itbox->getIdIUscita(),itbox->getStationName());
	
}

Void SingleTrainInfoForm::ItBox_ItChangedE(System::Object^  sender, System::EventArgs^  e){
	//	ItineraryBox ^itbox =(ItineraryBox^) sender ;
	System::Windows::Forms::ComboBox ^combo =( System::Windows::Forms::ComboBox^) sender ;
	Itinerario ^itsel = (Itinerario^) combo->SelectedItem;
	//Console::WriteLine("hai provato a cambiare NID_IT:{0} di {1}",itbox->getIdIEntrata(),itbox->getStationName());

}

Void SingleTrainInfoForm::textBox_TextChangedP(System::Object^  sender, System::EventArgs^  e){
	TextBox ^textarea =(TextBox^) sender ;

	//[0-9]+(?:\.[0-9]*)?
	 System::Text::RegularExpressions::Match ^m = System::Text::RegularExpressions::Regex::Match(textarea->Text,"[0-9]+(?:\.[0-9]*)?");
	if (m->Success){
		
			try{
				model->changePrior(train,int::Parse(m->Value));
				//form->Close();
			}catch(Exception ^e){
				Console::WriteLine("Errore Form Single Train Information",e->Message);
			}
			if(m->Value->Length!=textarea->Text->Length){
				textarea->Text=m->Value;
		}

	}else{
		MessageBox::Show("Please enter only numbers.");

	}
	/*if (System::Text::RegularExpressions::Regex::IsMatch(textarea->Text,"[^0-9]"))
	{
		MessageBox::Show("Please enter only numbers.");
		textarea->Text=textarea->Text->Remove(textarea->Text->Length - 1);
	}else{
		if(textarea->Text->Length>0){
			try{
			controller->changePrior(key,int::Parse(textarea->Text));
			form->Close();
			}catch(Exception ^e){
				Console::WriteLine("Errore Form Single Train Information",e->Message);
			}
		}
	}*/

}
Void SingleTrainInfoForm::ButtonClose_Click(System::Object^  sender, System::EventArgs^  e){

	Visible=false;
}

void SingleTrainInfoForm::UpdateInfo(){
	init();
	set();
}

Void SingleTrainInfoForm::ButtonApply_Click(System::Object^  sender, System::EventArgs^  e){
	List<Fermata^> ^nuoviorari = gcnew List<Fermata^>();
	for each (ItineraryBox ^var in tableLayoutPanelItinerari->Controls)
	{
		
		nuoviorari->Add(var->getOrari());
	}

	// segnala evento!!!
	String ^source = "View "+train->getTRN();
	for each (IObserver<Event<List<Fermata^>^>^>^ observer in observers)
	{
		Event<List<Fermata^>^> ^evento = gcnew Event<List<Fermata^>^>(train,nuoviorari);
		observer->OnNext(evento);
	}
	//model->changeOrari(train,nuoviorari);
	//
}

Int32 SingleTrainInfoForm::CompareTo(SingleTrainInfoForm^otherKey){

	if (otherKey == nullptr) return 1;

	
	return train->CompareTo(otherKey->train);
}

IDisposable ^SingleTrainInfoForm::Subscribe(IObserver<Event<List<Fermata^>^>^> ^observer){
	if (! observers->Contains(observer)) 
		observers->Add(observer);
	
	return gcnew Unsubscriber<Event<List<Fermata^>^>^>(observers, observer);

}