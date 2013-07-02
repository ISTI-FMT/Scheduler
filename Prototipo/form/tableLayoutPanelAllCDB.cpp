#include "tableLayoutPanelAllCDB.h"

tableLayoutPanelAllCDB::tableLayoutPanelAllCDB(	Dictionary<int,Button^> ^lbCDB)
{
	lbuttonCDB =lbCDB;
	init();
	read("..\\FileConfigurazione\\CDB.csv");
}


void tableLayoutPanelAllCDB::init(){
	this-> components = gcnew System::ComponentModel::Container;
	this->errorProvider = gcnew System::Windows::Forms::ErrorProvider;
	this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
	this->label0 = (gcnew System::Windows::Forms::Label());
	// 
	// tableLayoutPanel1
	// 
	this->tableLayoutPanel1->AutoSize = true;
	this->tableLayoutPanel1->ColumnCount = 23;
	this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));

	this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));

	this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));

	this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));

	this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));


	this->tableLayoutPanel1->Cursor = System::Windows::Forms::Cursors::Hand;
	this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
	this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
	this->tableLayoutPanel1->RowCount = 18;
	
	this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 19)));
	
	this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 19)));
	
	this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 19)));
	
	this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));

	this->tableLayoutPanel1->Size = System::Drawing::Size(200, 150);
	this->tableLayoutPanel1->TabIndex = 12;


	// 
	// label0
	// 
	this->label0->Anchor = System::Windows::Forms::AnchorStyles::Top;
	this->label0->AutoSize = true;
	this->label0->Font = (gcnew System::Drawing::Font(L"Gill Sans Ultra Bold", 10.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->label0->ForeColor = System::Drawing::Color::Blue;
	this->label0->Location = System::Drawing::Point(0, -2);
	this->label0->Name = L"1";
	this->label0->Size = System::Drawing::Size(15, 119);
	this->label0->TabIndex = 1;
	this->label0->Text = L"name";


	//this->tableLayoutPanel1->Controls->Add(this->label0, 0, 0);

	//this->tableLayoutPanel1->SetColumnSpan(this->label0, 2);

	//array<System::Windows::Forms::Control^>^temp0 = {label0,label1,label2,label3,label4};
	this->Controls->Add( tableLayoutPanel1 );
	this->AutoSize = true;
	//this->ClientSize = System::Drawing::Size(112, 366);
	//Size = System::Drawing::Size( 150, 150 );
	//this->ForeColor=System::Drawing::Color::Yellow;
	this->ResumeLayout(false);
	this->PerformLayout();

}

Button^ tableLayoutPanelAllCDB::getButton(String ^textbutton){
	// 
	// button
	// 
	System::Windows::Forms::Button ^button = (gcnew System::Windows::Forms::Button());
	button->AccessibleRole = System::Windows::Forms::AccessibleRole::Grip;
	button->Anchor = System::Windows::Forms::AnchorStyles::Top;

	button->BackColor = System::Drawing::Color::Fuchsia;
	button->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.25F));
	//button->Location = System::Drawing::Point(91, 3);
	button->Name = textbutton;
	button->Size = System::Drawing::Size(45,20);
	button->TabIndex = 0;
	button->Text = textbutton;
	button->UseVisualStyleBackColor = true;
//	button->Click += gcnew System::EventHandler(this, &tableLayoutPanelAllCDB::button_Click);



	return button;

}


/*System::Void tableLayoutPanelAllCDB::button_Click(System::Object^  sender, System::EventArgs^  e) {

	Button ^button =(Button^) sender ;
	if(button->BackColor==System::Drawing::Color::Yellow){
		button->BackColor= System::Drawing::Color::Red;
		return;
	}
	if(button->BackColor== System::Drawing::Color::Red){
		button->BackColor= System::Drawing::Color::Green;
		return;
	}
	if(button->BackColor== System::Drawing::Color::Green){
		button->BackColor= System::Drawing::Color::Yellow;
		return;
	}

}*/

void tableLayoutPanelAllCDB::addbutton(String ^namebutton, int riga, int colonna){

	Button ^but = getButton(namebutton);
	lbuttonCDB->Add(int::Parse(namebutton),but);
	this->tableLayoutPanel1->Controls->Add(but, colonna, riga);
	//	rigae++;

}



void tableLayoutPanelAllCDB::read(String ^file){
	int riga=0;
	
	if (File::Exists(file))
	{
		// Create a file to write to.

		array<String^> ^righe =	File::ReadAllLines(file);
		for each (String ^var in righe)
		{
			int colonna=0;
			array<String^> ^elementi =  var->Split(';');//,StringSplitOptions::None);
			for each (String ^elemento in elementi)
			{
				if(elemento->Length>0){
					addbutton(elemento,riga,colonna);
				}
				colonna++;
			}
			riga++;


		}

	}

}