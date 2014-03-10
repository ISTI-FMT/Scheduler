#include "SingleTrainInfoForm.h"


SingleTrainInfoForm::SingleTrainInfoForm(Train ^t,  ListTrainModel ^m, TabellaStazioni ^ti)
{

	Form::Form();
	tabItineari=ti;
	model=m;
	train=t;
	stream = System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream("green.ico");
	Imagegreen = System::Drawing::Image::FromStream(stream);

	Icongreen  =  gcnew System::Drawing::Icon(System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream("green.ico"));
	stream = System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream("red.ico");
	Imagered = System::Drawing::Image::FromStream(stream);
	
	Iconred =  gcnew System::Drawing::Icon(System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream("red.ico"));
	init();
	set();
	DelegateCTrain = gcnew GoCallback( this, &SingleTrainInfoForm::setinfoTrain );
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
	this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
	this->LabelStateTrain = (gcnew System::Windows::Forms::Label());
	this->comboBoxCambiaStatoTreno = (gcnew System::Windows::Forms::ComboBox());
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
	this->textboxPriorita->Size = System::Drawing::Size(42, 20);
	this->textboxPriorita->TabIndex = 3;

	// 
	// LabelPriorita
	// 
	this->LabelPriorita->AutoSize = true;
	this->LabelPriorita->Location = System::Drawing::Point(370, 6);
	this->LabelPriorita->Name = L"label4";
	this->LabelPriorita->Size = System::Drawing::Size(42, 13);
	this->LabelPriorita->TabIndex = 4;
	this->LabelPriorita->Text = L"Priorità:";

	// 
	// button1
	// 
	this->bclose->Location = System::Drawing::Point(500, 500);
	this->bclose->Name = L"button1";
	this->bclose->Size = System::Drawing::Size(75, 23);
	this->bclose->TabIndex = 5;
	this->bclose->Text = L"Close";
	this->bclose->UseVisualStyleBackColor = true;
	this->bclose->Click += gcnew System::EventHandler(this, &SingleTrainInfoForm::ButtonClose_Click);
	// 
	// buttonAplly
	// 
	this->bapply->Location = System::Drawing::Point(500, 470);
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
	// 
	// richTextBox1
	// 
	this->richTextBox1->BackColor = System::Drawing::Color::DimGray;
	this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Arial", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->richTextBox1->ForeColor = System::Drawing::Color::White;
	this->richTextBox1->Location = System::Drawing::Point(16, 428);
	this->richTextBox1->Name = L"richTextBox1";
	this->richTextBox1->Size = System::Drawing::Size(359, 102);
	this->richTextBox1->TabIndex = 10;
	this->richTextBox1->Text = L"";
	// 
	// LabelStateTrain
	// 
	
	this->LabelStateTrain->TextAlign =System::Drawing::ContentAlignment::MiddleRight;
	//this->LabelStateTrain->Location = System::Drawing::Point(192, 59); System::Drawing::Point(370, 25);
	this->LabelStateTrain->Location = System::Drawing::Point(420, 21);
	this->LabelStateTrain->Name = L"LabelStateTrain";
	this->LabelStateTrain->Size = System::Drawing::Size(150, 30);
	this->LabelStateTrain->Text = L"Pronto";
	this->LabelStateTrain->TabIndex = 8;
	this->LabelStateTrain->Image =Imagegreen ;
	this->LabelStateTrain->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;

	// 
	// comboBoxCambiaStatoTreno
	// 
	this->comboBoxCambiaStatoTreno->FormattingEnabled = true;
	this->comboBoxCambiaStatoTreno->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"Pronto", L"Non Pronto"});
	this->comboBoxCambiaStatoTreno->Location = System::Drawing::Point(370, 62);
	this->comboBoxCambiaStatoTreno->Name = L"comboBoxCambiaStatoTreno";
	this->comboBoxCambiaStatoTreno->Size = System::Drawing::Size(121, 21);
	this->comboBoxCambiaStatoTreno->TabIndex = 10;

	this->comboBoxCambiaStatoTreno->SelectionChangeCommitted += gcnew System::EventHandler(this, &SingleTrainInfoForm::comboBoxCambiaStatoTreno_SelectionChangeCommitted);

	//this->tableLayoutPanelItinerari->Controls->Add(this->label0, 0, 0);

	//this->tableLayoutPanelItinerari->SetColumnSpan(this->label0, 2);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->ClientSize = System::Drawing::Size(600, 542);
	array<System::Windows::Forms::Control^>^temp0 = {comboBoxCambiaStatoTreno,LabelStateTrain,richTextBox1,label5,Labeltrn,Labelip,LabelEngineNumber,LabelPriorita,textboxPriorita,bclose,bapply,tableLayoutPanelItinerari};
	this->Controls->AddRange( temp0 );
	//this->ControlBox=false;
	this->AutoSize = true;
	this->Icon =Icongreen;
	//this->Click += gcnew System::EventHandler(this, &SingleTrainInfoForm::Click);

	//this->ClientSize = System::Drawing::Size(112, 366);
	//Size = System::Drawing::Size( 150, 150 );
	//this->ForeColor=System::Drawing::Color::Yellow;
	this->ResumeLayout(false);
	this->PerformLayout();
	this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &SingleTrainInfoForm::SingleTrainInfoForm_FormClosing);		
	this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);


		KeyValuePair<int, int> ^itistazione = train->getStazioneItinerario();
	if(itistazione){
	StateTrain statet = train->getStatoTreno();

	int itinUscita = itistazione->Value;
	int idstazione = itistazione->Key;
	richTextBox1->AppendText(forwardItinerario(train->getindex(),train->getListaFermate()));

	this->LabelStateTrain->Text =fromStateTreno(train->getStatoTreno());
	aggiornaiconstate(train->getStatoTreno());
	if(train->getStatoTreno()<3){
		comboBoxCambiaStatoTreno->SelectedIndex=0;
	}else{
		comboBoxCambiaStatoTreno->SelectedIndex=1;
	}
	}else{
			Console::WriteLine("Errore Cambio Stato");
	}



}


void SingleTrainInfoForm::set(){
	this->Name =  train->getPhysicalTrain()->getEngineNumber().ToString();
	this->Text =  train->getPhysicalTrain()->getEngineNumber().ToString();
	//this->form->Name =  train->getPhysicalTrain()->getEngineNumber().ToString();
	//this->form->Text =  train->getPhysicalTrain()->getEngineNumber().ToString();
	this->Labeltrn->Text = L"Train Running Number: ";
	this->Labeltrn->Text += train->getTRN().ToString();
	this->LabelEngineNumber->Text = L"Engine Number: ";
	this->LabelEngineNumber->Text += train->getPhysicalTrain()->getEngineNumber().ToString();
	this->Labelip->Text = L"IP: ";
	this->Labelip->Text +=train->getPhysicalTrain()->getIpAddress();
	this->textboxPriorita->Text = train->getPriorita().ToString();
	setitinerary();



}

void SingleTrainInfoForm::aggiornaiconstate(StateTrain t){
	if(t==StateTrain::NONPRONTO){
		LabelStateTrain->Image =Imagered ;
		this->Icon =Iconred;
	}else{
		LabelStateTrain->Image =Imagegreen ;
		this->Icon =Icongreen;

	}
}
String ^SingleTrainInfoForm::forwardItinerario(int index, List<Fermata^> ^Listafermate){
	String ^result = gcnew String("");
	for (int i = 0; i<=index; i++)
	{
		if(i==0){
			int itinUscita = Listafermate[i]->getIditinerarioUscita();
			int idstazione = Listafermate[i]->getIdStazione();

			result+= KeyValuePair<int, int>(idstazione, itinUscita);
		}else{
			int itinUscita = Listafermate[i]->getIditinerarioUscita();
			int idstazione = Listafermate[i]->getIdStazione();

			result+= KeyValuePair<int, int>(idstazione, itinUscita);
			if(i!=index & StateTrain::ENTRATASTAZIONE!=train->getStatoTreno()){
			int initEntrata = Listafermate[i]->getIditinerarioEntrata();
			idstazione = Listafermate[i]->getIdStazione();
			result+=   KeyValuePair<int, int>(idstazione, initEntrata);
			}
		}
	}

	return result;
	/*void  Train::goNextItinerario(){

	if(Statodeltreno==StateTrain::ENTRATASTAZIONE){
	Statodeltreno=StateTrain::USCITASTAZIONE;

	}else{
	if(Statodeltreno==StateTrain::USCITASTAZIONE){
	Statodeltreno=StateTrain::ENTRATASTAZIONE;
	indicelistaitinerari++;
	}
	}
	}*/
}

String ^SingleTrainInfoForm::fromStateTreno(StateTrain t){
	String ^statotreno = gcnew String("");
	switch (t)
	{
	case PRONTO: statotreno = "PRONTO";
		break;
	case USCITASTAZIONE:  statotreno = "USCITASTAZIONE";
		break;
	case ENTRATASTAZIONE:  statotreno = "ENTRATASTAZIONE";
		break;
	case NONPRONTO:  statotreno = "NONPRONTO";
		break;
	case TERMINATO:  statotreno = "TERMINATO";
		break;
	default:  statotreno = "ND";
		break;
	}
	return statotreno;
}
void SingleTrainInfoForm::setitinerary(){
	/*int riga=0;
	int colonna=0;*/
	this->tableLayoutPanelItinerari->Controls->Clear();
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
	//init();
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


void SingleTrainInfoForm::setinfoTrain(Train ^t){
	if(train==t){
	if(t->getStatoTreno()!=3){
		KeyValuePair<int, int> ^itistazione = t->getStazioneItinerario();
		int itinUscita = itistazione->Value;
		int idstazione = itistazione->Key;
		richTextBox1->AppendText(" "+itistazione);
	}	
	this->LabelStateTrain->Text =fromStateTreno(t->getStatoTreno());
	aggiornaiconstate(t->getStatoTreno());

	}

}

System::Void SingleTrainInfoForm::comboBoxCambiaStatoTreno_SelectionChangeCommitted(System::Object^  sender, System::EventArgs^  e) {

	
	//train->setStatoTreno(StateTrain::NONPRONTO);
	Object ^bb = comboBoxCambiaStatoTreno->SelectedItem;
	String ^vv = bb->ToString();
	Console::WriteLine(" Cambio Stato {0}",vv);
	if(vv=="Non Pronto"){
		tempStateTrain = train->getStatoTreno();
		model->changeState(train,StateTrain::NONPRONTO );
	}else{
		if(vv=="Pronto"){
			if(tempStateTrain){
				model->changeState(train,tempStateTrain );
			}
		}
	}
}

System::Void SingleTrainInfoForm::SingleTrainInfoForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e){

	 e->Cancel = true;
     Visible=false;

}

	