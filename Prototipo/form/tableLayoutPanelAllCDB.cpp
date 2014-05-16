#include "tableLayoutPanelAllCDB.h"

tableLayoutPanelAllCDB::tableLayoutPanelAllCDB(	Dictionary<int,Button^> ^lbCDB)
{
	lbuttonCDB =lbCDB;
	init();
	read();
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
	this->tableLayoutPanel1->ColumnCount = 24;
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
	this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));

	this->tableLayoutPanel1->Size = System::Drawing::Size(220, 250);
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
	button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif",7.25F));
	//button->Location = System::Drawing::Point(91, 3);
	button->Name = textbutton;
	button->Size = System::Drawing::Size(55,20);
	button->TabIndex = 0;
	button->Text = textbutton;
	button->UseVisualStyleBackColor = true;
	//	button->Click += gcnew System::EventHandler(this, &tableLayoutPanelAllCDB::button_Click);



	return button;

}

Label^ tableLayoutPanelAllCDB::getLabel(String ^textLabel){
	Label ^label = gcnew Label();
	label->Anchor = System::Windows::Forms::AnchorStyles::Top;
	label->AutoSize = true;
	label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.25F));
	label->ForeColor = System::Drawing::Color::Blue;
	//label->Location = System::Drawing::Point(0, -2);
	label->Name = L"1";
	//label->Size = System::Drawing::Size(15, 119);
	label->TabIndex = 1;
	label->Text = textLabel;
	return label;
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

void tableLayoutPanelAllCDB::addlabel(String ^namelabel, int riga, int colonna){

	Label ^lab = getLabel(namelabel);
	
	this->tableLayoutPanel1->Controls->Add(lab, colonna, riga);
	//	rigae++;

}

void tableLayoutPanelAllCDB::read(){
	int riga=0;
	//"CDB.csv"
	String^ tmpFilename = System::IO::Path::GetTempFileName();
	Stream^ readStream = System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream("CDBv.csv");
	FileStream^ writeStream = gcnew FileStream(tmpFilename, FileMode::Create);
	readStream->CopyTo(writeStream);
	readStream->Close();
	writeStream->Close();
	//if (File::Exists(file))
	//{
	// Create a file to write to.

	array<String^> ^righe =	File::ReadAllLines(tmpFilename);
	for each (String ^var in righe)
	{
		int colonna=0;
		array<String^> ^elementi =  var->Split(';');//,StringSplitOptions::None);
		for each (String ^elemento in elementi)
		{
			if(elemento->Length>0){
				int cdb = 0;
				bool result = Int32::TryParse(elemento, cdb);
				if(result){
					addbutton(elemento,riga,colonna);
				}else{

					addlabel(elemento,riga,colonna);
				}
			}
			colonna++;
		}
		riga++;


	}

	//}

}