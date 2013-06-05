#include "FormVisualizzeConfItine.h"


FormVisualizzeConfItine::FormVisualizzeConfItine(tabellaItinerari ^tab )
{
	tabella=tab;
	Inizialize();
}


void FormVisualizzeConfItine::Inizialize(){


	dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
	(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(dataGridView1))->BeginInit();
	dataGridView1->AccessibleName = L"datagridit";
	dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;
	dataGridView1->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
	dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
	dataGridView1->Location = System::Drawing::Point(12, 12);
	dataGridView1->Name = L"dataGridViewit";
	dataGridView1->Size = System::Drawing::Size(810, 360);
	dataGridView1->TabIndex = 18;


	this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->ClientSize = System::Drawing::Size(830, 415);
	this->Controls->Add(dataGridView1);
	this->Name = L"Tabella Configurazione Itinerari";
	this->Text = L"Tabella Configurazione Itinerari";
	this->Resize += gcnew System::EventHandler(this, &FormVisualizzeConfItine::Form_Resize);
	this->ResumeLayout(false);
	this->PerformLayout();
	this->SuspendLayout();

	dataGridView1->ColumnCount = 12;
	dataGridView1->RowCount = 410;
	int colonna=0;
	int riga=0;
	dataGridView1->Columns[ 0 ]->Name = "offset";
	// dataGridView1->Columns[ 1 ]->Name = "offset";
	dataGridView1->Columns[ 1 ]->Name = "Nome Stazione";
	dataGridView1->Columns[ 2 ]->Name = "prevCDB";
	dataGridView1->Columns[ 3 ]->Name = "Id It";
	dataGridView1->Columns[ 4 ]->Name = "Nome It";
	dataGridView1->Columns[ 5 ]->Name = "LRGB";
	dataGridView1->Columns[ 6 ]->Name = "DSTOP";
	dataGridView1->Columns[ 7 ]->Name = "Dir";
	dataGridView1->Columns[ 8 ]->Name = "nextCDB";
	//  dataGridView1->Columns[ 10 ]->Name = "prevCDB";
	dataGridView1->Columns[ 9]->Name = "PB";
	dataGridView1->Columns[ 10]->Name = "NS";
	dataGridView1->Columns[ 11 ]->Name = "L_CDB";

	for each( KeyValuePair<int , stazione^> kvp in tabella->getMap() )
	{

		String ^po=kvp.Key+"\n\r";
		dataGridView1->Rows[riga]->Cells[0]->Value=po;

		stazione ^station =kvp.Value;
		// dataGridView1->Rows[riga]->Cells[1]->Value= station->get_idStazione();
		dataGridView1->Rows[riga]->Cells[1]->Value= station->get_NomeStazione();

		for each (KeyValuePair<String^,List<Itinerario^>^> ^ikvp in station->getItinerari())
		{

			dataGridView1->Rows[riga]->Cells[2]->Value=ikvp->Key;
			List<Itinerario^>^listitn = ikvp->Value;
			for each (Itinerario ^itvar in listitn)
			{
				dataGridView1->Rows[riga]->Cells[3]->Value=itvar->getId();
				dataGridView1->Rows[riga]->Cells[4]->Value=itvar->getName();
				dataGridView1->Rows[riga]->Cells[5]->Value=itvar->getLrgb();
				dataGridView1->Rows[riga]->Cells[6]->Value=itvar->getDStop();
				dataGridView1->Rows[riga]->Cells[7]->Value=itvar->getLatoBanchina();
				dataGridView1->Rows[riga]->Cells[8]->Value=itvar->getNextCDB();
				//	 dataGridView1->Rows[riga]->Cells[10]->Value=itvar->getPrevCDB();
				dataGridView1->Rows[riga]->Cells[9]->Value=itvar->getPorteBanchina();
				dataGridView1->Rows[riga]->Cells[10]->Value=itvar->get_nextstation();
				List<int> ^cdb = itvar->getLCDB();
				for each (int cdbvar in cdb)
				{
					if(cdbvar){
						dataGridView1->Rows[riga]->Cells[11]->Value=cdbvar;
					}
					riga++;
				}


			}


		}

	}



}

void FormVisualizzeConfItine::Form_Resize(System::Object^  sender, System::EventArgs^  e) {

	dataGridView1->Size= System::Drawing::Size(this->Width-30,this->Height-50);
}
