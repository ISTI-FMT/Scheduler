#include "FormVisualizzeMapTreni.h"


FormVisualizzeMapTreni::FormVisualizzeMapTreni(mapTrenoFisicoLogico ^m )
{
	mapFisicoLogico=m;
	Inizialize();
	
}


void FormVisualizzeMapTreni::Inizialize(){


	dataGridView1 = gcnew System::Windows::Forms::DataGridView();
	(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(dataGridView1))->BeginInit();
	dataGridView1->AccessibleName = L"datagrid";
	dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;
	dataGridView1->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
	dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
	dataGridView1->Location = System::Drawing::Point(12, 12);
	dataGridView1->Name = L"dataGridView1";
	dataGridView1->Size = System::Drawing::Size(430, 344);
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
	this->NewTrain->Click += gcnew System::EventHandler(this, &FormVisualizzeMapTreni::NewTrain_Click);

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
	this->SaveXml->Click += gcnew System::EventHandler(this, &FormVisualizzeMapTreni::SaveXml_Click);

	//form = gcnew Form();
	this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->ClientSize = System::Drawing::Size(460, 415);
	this->Icon =  gcnew System::Drawing::Icon(System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream("app.ico"));
	this->Controls->Add(dataGridView1);
	this->Controls->Add(NewTrain);
	this->Controls->Add(SaveXml);
	this->Name = L"Tabella Orario";
	this->Text = L"Tabella Orario";
	//form->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
	this->Resize += gcnew System::EventHandler(this, &FormVisualizzeMapTreni::Form_Resize);
	//form->MaximizeBox = false;    
	this->ResumeLayout(false);
	this->PerformLayout();
	this->SuspendLayout();

	dataGridView1->ColumnCount = 5;
	dataGridView1->RowCount =  mapFisicoLogico->get_Map()->Count*3;
	int colonna=0;
	int riga=0;
	dataGridView1->Columns[ 0 ]->Name = "Id_Engine_Treno";
	dataGridView1->Columns[ 1 ]->Name = "";
	dataGridView1->Columns[ 2 ]->Name = "TRN treno";
	dataGridView1->Columns[ 3 ]->Name = " ";
	dataGridView1->Columns[ 4 ]->Name = "Last Position";
	

	for each( KeyValuePair<int , TrenoFisicoLogico^> ^kvp in mapFisicoLogico->get_Map() )
	{

		String ^po=kvp->Key+"\n\r";
		dataGridView1->Rows[riga]->Cells[0]->Value=po;
		TrenoFisicoLogico^ trenof = kvp->Value;

		for each (int dvar in trenof->getIdTrenoListTreniLogici())
		{ 
			
			dataGridView1->Rows[riga]->Cells[2]->Value=dvar;
			dataGridView1->Rows[riga]->Cells[4]->Value=trenof->getCDBLastPosition();
			riga++;
		}
		

	}





}

void FormVisualizzeMapTreni::Form_Resize(System::Object^  sender, System::EventArgs^  e) {

	/*dataGridView1->Size= System::Drawing::Size(this->Width-30,this->Height-50);*/
}

void FormVisualizzeMapTreni::NewTrain_Click(System::Object^  sender, System::EventArgs^  e){

	/*Prototipo::EditorTabellaOrario ^editor = gcnew Prototipo::EditorTabellaOrario(Tabellastazioni);
	editor->Visible=true;
	editor->Nuovotreno += gcnew System::EventHandler(this,&FormVisualizzeTabOrario::Addtreno);*/

}

void FormVisualizzeMapTreni::SaveXml_Click(System::Object^  sender, System::EventArgs^  e){
	 System::IO::Stream ^ myStream;
      SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog;
      saveFileDialog1->Filter = "xml files (*.xml)|*.xml|All files (*.*)|*.*";
      saveFileDialog1->FilterIndex = 1;
      saveFileDialog1->RestoreDirectory = true;
      if ( saveFileDialog1->ShowDialog() == ::DialogResult::OK )
      {
        if ( (myStream = saveFileDialog1->OpenFile()) != nullptr )
         {
			 mapFisicoLogico->saveXml(myStream);
            // Code to write the stream goes here.
            myStream->Close();
         }
      }
	 
}


void FormVisualizzeMapTreni::Addtreno(System::Object^  sender, System::EventArgs^  e){
	/*KeyValuePair<int,  List<Fermata^>^>^nuovotreno=( KeyValuePair<int,  List<Fermata^>^> )sender;

	int TRN = nuovotreno->Key;

	if( !tabella->get_TabellaOrario()->ContainsKey(TRN)){
		tabella->get_TabellaOrario()->Add(TRN,nuovotreno->Value);
		Aggiorna();
	}else{
		Console::WriteLine("treno gia esistente in tabella orario");
	}*/

}



void FormVisualizzeMapTreni::Aggiorna(){

	


}