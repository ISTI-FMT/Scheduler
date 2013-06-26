#include "tableLayoutPanelSingleItin.h"


tableLayoutPanelSingleItin::tableLayoutPanelSingleItin(stazione ^station,Dictionary<int,Button^> ^listb)
{
	rigae =1;
	rigau =1;
	listbutton=listb;
	init(station->get_NomeStazione(), station->get_idStazione());
	paint(station);
}

void tableLayoutPanelSingleItin::init(String ^name, int id){
	this-> components = gcnew System::ComponentModel::Container;
	this->errorProvider = gcnew System::Windows::Forms::ErrorProvider;
	this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
	this->label0 = (gcnew System::Windows::Forms::Label());
	// 
	// tableLayoutPanel1
	// 
	this->tableLayoutPanel1->AutoSize = true;
	this->tableLayoutPanel1->ColumnCount = 2;
	this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
		50)));
	this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
		50)));

	this->tableLayoutPanel1->Cursor = System::Windows::Forms::Cursors::Hand;
	this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
	this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
	this->tableLayoutPanel1->RowCount = 8;
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
	this->label0->Name = id.ToString();
	this->label0->Size = System::Drawing::Size(15, 19);
	this->label0->TabIndex = 1;
	this->label0->Text = name;


	this->tableLayoutPanel1->Controls->Add(this->label0, 0, 0);

	this->tableLayoutPanel1->SetColumnSpan(this->label0, 2);

	//array<System::Windows::Forms::Control^>^temp0 = {label0,label1,label2,label3,label4};
	this->Controls->Add( tableLayoutPanel1 );
	this->AutoSize = true;
	//this->ClientSize = System::Drawing::Size(112, 366);
	//Size = System::Drawing::Size( 150, 150 );
	//this->ForeColor=System::Drawing::Color::Yellow;
	this->ResumeLayout(false);
	this->PerformLayout();

}

Button^ tableLayoutPanelSingleItin::getButton(String ^textbutton, int id){
	// 
	// button
	// 
	System::Windows::Forms::Button ^button = (gcnew System::Windows::Forms::Button());
	button->AccessibleRole = System::Windows::Forms::AccessibleRole::Grip;
	button->Anchor = System::Windows::Forms::AnchorStyles::Top;

	button->BackColor = System::Drawing::Color::Silver;
	button->FlatStyle = System::Windows::Forms::FlatStyle::Flat;

	//button->Location = System::Drawing::Point(91, 3);
	button->Name = id.ToString();
	button->Font = (gcnew System::Drawing::Font(L"Times New Roman", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
	button->Size = System::Drawing::Size(70, 18);
	button->TabIndex = 0;
	button->Text = textbutton;
	button->UseVisualStyleBackColor = true;
	//button->Click += gcnew System::EventHandler(this, &tableLayoutPanelSingleItin::button_Click);



	return button;

}


System::Void tableLayoutPanelSingleItin::button_Click(System::Object^  sender, System::EventArgs^  e) {

	Button ^button =(Button^) sender ;
	if(button->BackColor==System::Drawing::Color::Silver){
		button->BackColor= System::Drawing::Color::Red;
		return;
	}
	if(button->BackColor== System::Drawing::Color::Red){
		button->BackColor= System::Drawing::Color::Green;
		return;
	}
	if(button->BackColor== System::Drawing::Color::Green){
		button->BackColor= System::Drawing::Color::Silver;
		return;
	}

}

void tableLayoutPanelSingleItin::addbuttonEntrata(String ^namebutton, int id){
	Button ^but = getButton(namebutton, id);
	listbutton->Add(id,but);
	this->tableLayoutPanel1->Controls->Add(but, 0, rigae);
	rigae++;

}
void tableLayoutPanelSingleItin::addbuttonUscita(String ^namebutton, int id){
	Button ^but = getButton(namebutton, id);
	listbutton->Add(id,but);
	this->tableLayoutPanel1->Controls->Add(but, 1, rigau);
	rigau++;

}

void tableLayoutPanelSingleItin::paint(stazione ^station){

Dictionary<int,Itinerario^ >::ValueCollection ^valuecollitini = station->getItinerariid()->Values;
		for each (Itinerario^ var in valuecollitini)
		{

			if(var->getDStop()>0){

				this->addbuttonEntrata(var->getName(),var->getId()+station->get_idStazione());
			}else{
				this->addbuttonUscita(var->getName(),var->getId()+station->get_idStazione());

			}
		}

}