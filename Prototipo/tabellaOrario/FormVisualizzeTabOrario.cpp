#include "FormVisualizzeTabOrario.h"


FormVisualizzeTabOrario::FormVisualizzeTabOrario(TabellaOrario ^tab )
{
	tabella=tab;
	Inizialize();
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

	//form = gcnew Form();
	this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->ClientSize = System::Drawing::Size(915, 415);
	this->Controls->Add(dataGridView1);
	this->Name = L"Tabella Orario";
	this->Text = L"Tabella Orario";
	//form->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
	this->Resize += gcnew System::EventHandler(this, &FormVisualizzeTabOrario::Form_Resize);
	//form->MaximizeBox = false;    
	this->ResumeLayout(false);
	this->PerformLayout();
	this->SuspendLayout();

	dataGridView1->ColumnCount = 10;
	dataGridView1->RowCount = tabella->get_TabellaOrario()->Count*8;
	int colonna=0;
	int riga=0;
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

	for each( KeyValuePair<int , List<Fermata^>^> kvp in tabella->get_TabellaOrario() )
	{

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
			dataGridView1->Rows[riga]->Cells[7]->Value=dvar->getLatoAperturaPorte();
			dataGridView1->Rows[riga]->Cells[8]->Value=dvar->getnameitinerarioEntrata();
			dataGridView1->Rows[riga]->Cells[9]->Value=dvar->getnameitinerarioUscita();
			riga++;
		}

	}


	


}

void FormVisualizzeTabOrario::Form_Resize(System::Object^  sender, System::EventArgs^  e) {

	dataGridView1->Size= System::Drawing::Size(this->Width-30,this->Height-50);
}
