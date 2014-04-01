#include "FormVisualizzeConfFermate.h"


FormVisualizzeConfFermate::FormVisualizzeConfFermate(TabellaStazioni ^tab )
{
	tabella=tab;
	Inizialize();
}


void FormVisualizzeConfFermate::Inizialize(){

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
	this->Name = L"Tabella Configurazione Fermata";
	this->Text = L"Tabella Configurazione Fermata";
	this->Resize += gcnew System::EventHandler(this, &FormVisualizzeConfFermate::Form_Resize);
	this->ResumeLayout(false);
	this->PerformLayout();
	this->SuspendLayout();

	dataGridView1->ColumnCount = 11;
	dataGridView1->RowCount = 1;
	int colonna=0;
	int riga=0;

	dataGridView1->Columns[ 0 ]->Name = "Nome Fermata";				
	dataGridView1->Columns[ 1 ]->Name = "Nome Binario";
	dataGridView1->Columns[ 2 ]->Name = "Binario";
	dataGridView1->Columns[ 3 ]->Name = "Direzione";
	dataGridView1->Columns[ 4 ]->Name = "NID_LRGB";
	dataGridView1->Columns[ 5 ]->Name = "DSTOP";
	dataGridView1->Columns[ 6 ]->Name = "PB";
	dataGridView1->Columns[ 7 ]->Name = "LB";
	dataGridView1->Columns[ 8 ]->Name = "nextCDB";

	dataGridView1->Columns[ 9]->Name = "prevCDB";
	dataGridView1->Columns[ 10]->Name = "CDB";


	for each( KeyValuePair<int ,  stazione ^> ^kvp in tabella->getMap() )
	{
		if(kvp->Value->get_idStazione()<999){
			dataGridView1->RowCount += kvp->Value->getBinari()->Count;
			String ^po=kvp->Value->get_NomeStazione()+"\n\r";
			dataGridView1->Rows[riga]->Cells[0]->Value=po;


			List<binario^> ^binari =kvp->Value->getBinari();

			for each (binario^ ikvp in binari)
			{	
				dataGridView1->Rows[riga]->Cells[1]->Value= ikvp->getNameBin();
				dataGridView1->Rows[riga]->Cells[2]->Value=ikvp->getBin();
				dataGridView1->Rows[riga]->Cells[3]->Value=ikvp->getDirezione();
				dataGridView1->Rows[riga]->Cells[4]->Value=ikvp->get_info_lrgb();
				dataGridView1->Rows[riga]->Cells[5]->Value=ikvp->getD_stop();
				dataGridView1->Rows[riga]->Cells[6]->Value=ikvp->getPorteBanchina();
				dataGridView1->Rows[riga]->Cells[7]->Value=ikvp->getLatoBanchina();
				dataGridView1->Rows[riga]->Cells[8]->Value=ikvp->getNextCDB();
				//	 dataGridView1->Rows[riga]->Cells[10]->Value=itvar->getPrevCDB();
				dataGridView1->Rows[riga]->Cells[9]->Value=ikvp->getPrevCDB();
				dataGridView1->Rows[riga]->Cells[10]->Value=ikvp->getCDB ();


				riga++;

			}
		}

	}






}

void FormVisualizzeConfFermate::Form_Resize(System::Object^  sender, System::EventArgs^  e) {

	dataGridView1->Size= System::Drawing::Size(this->Width-30,this->Height-50);
}
