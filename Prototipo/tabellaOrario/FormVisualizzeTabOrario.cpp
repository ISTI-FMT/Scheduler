#include "FormVisualizzeTabOrario.h"


FormVisualizzeTabOrario::FormVisualizzeTabOrario(TabellaOrario ^tab, TabellaStazioni ^t )
{
	tabella=tab;
	Inizialize();
	Tabellastazioni=t;
}


void FormVisualizzeTabOrario::Inizialize(){


	dataGridView1 = gcnew System::Windows::Forms::DataGridView();
	(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(dataGridView1))->BeginInit();
	dataGridView1->AccessibleName = L"datagrid";
	dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;
	dataGridView1->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
	dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
	dataGridView1->Location = System::Drawing::Point(12, 12);
	dataGridView1->Name = L"dataGridView1";
	dataGridView1->Size = System::Drawing::Size(890, 344);
	dataGridView1->TabIndex = 8;


	//NewTrain
	// 
	this->NewTrain = gcnew Button();
	this->NewTrain->Location = System::Drawing::Point(12, 370);
	this->NewTrain->Name = L"NewTrain";
	this->NewTrain->Size = System::Drawing::Size(146, 23);
	this->NewTrain->TabIndex = 2;
	this->NewTrain->Text = L"NewTrain";
	this->NewTrain->UseVisualStyleBackColor = true;
	this->NewTrain->Click += gcnew System::EventHandler(this, &FormVisualizzeTabOrario::NewTrain_Click);

	//SaveXml
	// 
	this->SaveXml = gcnew Button();
	int x  =12+146+25;
	this->SaveXml->Location = System::Drawing::Point(x,370);
	this->SaveXml->Name = L"SaveXml";
	this->SaveXml->Size = System::Drawing::Size(146, 23);
	this->SaveXml->TabIndex = 2;
	this->SaveXml->Text = L"Save Xml";
	this->SaveXml->UseVisualStyleBackColor = true;
	this->SaveXml->Click += gcnew System::EventHandler(this, &FormVisualizzeTabOrario::SaveXml_Click);

	//Button ^DeleteTrain;
	//DeleteTrain
	// 
	this->DeleteTrain = gcnew Button();
	x  =12+146+25+146+25;
	this->DeleteTrain->Location = System::Drawing::Point(x,370);
	this->DeleteTrain->Name = L"NewTrain";
	this->DeleteTrain->Size = System::Drawing::Size(146, 23);
	this->DeleteTrain->TabIndex = 2;
	this->DeleteTrain->Text = L"Delete Train";
	this->DeleteTrain->UseVisualStyleBackColor = true;
	this->DeleteTrain->Click += gcnew System::EventHandler(this, &FormVisualizzeTabOrario::DeleteTrain_Click);

	//form = gcnew Form();
	this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->ClientSize = System::Drawing::Size(915, 415);
	this->Icon =  gcnew System::Drawing::Icon(System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream("app.ico"));
	this->Controls->Add(dataGridView1);
	this->Controls->Add(NewTrain);
	this->Controls->Add(SaveXml);
	this->Controls->Add(DeleteTrain);
	this->Name = L"Tabella Orario";
	this->Text = L"Tabella Orario";
	//form->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
	this->Resize += gcnew System::EventHandler(this, &FormVisualizzeTabOrario::Form_Resize);
	//form->MaximizeBox = false;    
	this->ResumeLayout(false);
	this->PerformLayout();
	this->SuspendLayout();

	

	Aggiorna();





}

void FormVisualizzeTabOrario::Form_Resize(System::Object^  sender, System::EventArgs^  e) {

	/*dataGridView1->Size= System::Drawing::Size(this->Width-30,this->Height-150);
	this->NewTrain->Location = System::Drawing::Point(12, 370);
		int x  =12+146+25;
	this->SaveXml->Location = System::Drawing::Point(x,370);*/
}

void FormVisualizzeTabOrario::NewTrain_Click(System::Object^  sender, System::EventArgs^  e){

	Prototipo::EditorTabellaOrario ^editor = gcnew Prototipo::EditorTabellaOrario(Tabellastazioni);
	editor->Visible=true;
	editor->Nuovotreno += gcnew System::EventHandler(this,&FormVisualizzeTabOrario::Addtreno);

}

void FormVisualizzeTabOrario::SaveXml_Click(System::Object^  sender, System::EventArgs^  e){
	 System::IO::Stream ^ myStream;
      SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog;
      saveFileDialog1->Filter = "xml files (*.xml)|*.xml|All files (*.*)|*.*";
      saveFileDialog1->FilterIndex = 1;
      saveFileDialog1->RestoreDirectory = true;
      if ( saveFileDialog1->ShowDialog() == ::DialogResult::OK )
      {
        if ( (myStream = saveFileDialog1->OpenFile()) != nullptr )
         {
			 tabella->ScriviTabellaOrario(myStream);
            // Code to write the stream goes here.
            myStream->Close();
         }
      }
	 
}


void FormVisualizzeTabOrario::Addtreno(System::Object^  sender, System::EventArgs^  e){
	KeyValuePair<int,  List<Fermata^>^>^nuovotreno=( KeyValuePair<int,  List<Fermata^>^> )sender;

	int TRN = nuovotreno->Key;

	if( !tabella->get_TabellaOrario()->ContainsKey(TRN)){
		tabella->get_TabellaOrario()->Add(TRN,nuovotreno->Value);
		Aggiorna();
	}else{
		Console::WriteLine("treno gia esistente in tabella orario");
	}

}



void FormVisualizzeTabOrario::Aggiorna(){

	dataGridView1->ColumnCount = 10;
	dataGridView1->RowCount = 1;
	
	dataGridView1->Columns[ 0 ]->Name = "Id_Treno";
	dataGridView1->Columns[ 1 ]->Name = "Nome Stazione";
	dataGridView1->Columns[ 2 ]->Name = "id Stazione";
	dataGridView1->Columns[ 3 ]->Name = "Orario Arrivo";
	dataGridView1->Columns[ 4 ]->Name = "Orario Partenza";
	dataGridView1->Columns[ 5 ]->Name = "BinProg";
	dataGridView1->Columns[ 6 ]->Name = "TempoMAPorte";
	dataGridView1->Columns[ 7 ]->Name = "LatoAPorte";
	dataGridView1->Columns[ 8 ]->Name = "It Entrata";
	dataGridView1->Columns[ 9 ]->Name = "It Uscita";
	int colonna=0;
	int riga=0;
	
	for each( KeyValuePair<int , List<Fermata^>^> kvp in tabella->get_TabellaOrario() )
	{

		dataGridView1->RowCount +=  kvp.Value->Count;
		String ^po=kvp.Key+"\n\r";
		dataGridView1->Rows[riga]->Cells[0]->Value=po;


		for each (Fermata ^dvar in kvp.Value)
		{ 
			dataGridView1->Rows[riga]->Cells[1]->Value=dvar->getnameStazione();
			dataGridView1->Rows[riga]->Cells[2]->Value=dvar->getIdStazione();
			TimeSpan Arrivo = TimeSpan::FromSeconds(dvar->getOrarioArrivo()*30);
			dataGridView1->Rows[riga]->Cells[3]->Value= Arrivo.ToString();
			TimeSpan Partenza = TimeSpan::FromSeconds(dvar->getOrarioPartenza()*30);
			dataGridView1->Rows[riga]->Cells[4]->Value=Partenza.ToString();
			dataGridView1->Rows[riga]->Cells[5]->Value=dvar->getBinarioProgrammato();
			dataGridView1->Rows[riga]->Cells[6]->Value=dvar->gettempoMinimoAperturaPorte();
			dataGridView1->Rows[riga]->Cells[7]->Value=(int) dvar->getLatoAperturaPorte();
			dataGridView1->Rows[riga]->Cells[8]->Value=dvar->getnameitinerarioEntrata();
			dataGridView1->Rows[riga]->Cells[9]->Value=dvar->getnameitinerarioUscita();
			riga++;
		}

	}


}


void FormVisualizzeTabOrario::DeleteTrain_Click(System::Object^  sender, System::EventArgs^  e){
	Prototipo::FormDeleteElement ^formdelete = gcnew Prototipo::FormDeleteElement(tabella);
	formdelete->DeleteTreno +=gcnew System::EventHandler(this, &FormVisualizzeTabOrario::DelTrain);
	formdelete->Visible=true;
}

void FormVisualizzeTabOrario::DelTrain(System::Object^  sender, System::EventArgs^  e){
	try{
		int elementodaeliminare = (int)sender;
		if(tabella->get_TabellaOrario()->ContainsKey(elementodaeliminare)){
			tabella->get_TabellaOrario()->Remove(elementodaeliminare);
		Aggiorna();
	}else{
		Console::WriteLine("treno non esistente in tabella orario");
	}


	}catch(Exception ^e){
		Console::WriteLine("treno non eliminato {0}",e->Message);
	}
}

