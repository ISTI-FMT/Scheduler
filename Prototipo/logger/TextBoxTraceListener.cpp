#include "TextBoxTraceListener.h"
#using <system.drawing.dll>

using namespace  System::Diagnostics;
using namespace  System::Windows::Forms;
using namespace  System;

/*TextBoxTraceListener::TextBoxTraceListener(void)
{
}*/



void TextBoxTraceListener::init(void){
	textBox=  (gcnew System::Windows::Forms::TextBox());
	textBox->Location =  System::Drawing::Point(15, 53);
	textBox->Multiline = true;
	textBox->Name = L"textBox";
	textBox->Size = System::Drawing::Size(687, 338);
	textBox->TabIndex = 4;
	//textBox->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox2_TextChanged);
	textBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
	form = gcnew Form();
	form->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
	form->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	form->ClientSize = System::Drawing::Size(730, 415);
	form->Controls->Add(textBox);
	form->Name = L"Message Log Monitor";
	form->Text = L"Message Log Monitor";
	form->ResumeLayout(false);
	form->PerformLayout();
	form->SuspendLayout();

	myDelegate = gcnew SetTextCallback( this, &TextBoxTraceListener::SetText );

	//form->ShowDialog();
	//Application::Run(form);
	form->Visible=true;


};

void TextBoxTraceListener::WriteLine(String ^h){
	TextWriterTraceListener::WriteLine(h+"\r\n");
	Write(h+"\r\n");
};
void TextBoxTraceListener::WriteLine(Object ^h){
	WriteLine(h->ToString()+"\r\n");
};
void TextBoxTraceListener::Write(String ^h){

	if (textBox==nullptr){
		init();
	}
	form->Invoke( myDelegate, h );
};
void TextBoxTraceListener::Write(Object ^h){
	Write(h->ToString());
};

void TextBoxTraceListener::SetText(String ^text)
{
	// InvokeRequired required compares the thread ID of the
	// calling thread to the thread ID of the creating thread.
	// If these threads are different, it returns true.

	if (textBox->Lines->Length>100){
		String ^old = textBox->Text;
		int start = old->Length/2;
		String ^newstr = old->Substring(start);
		textBox->Text=newstr;
	}

	//04/05/2013 13:05:08;Info;Presentazione;19652;215;ATS;146.48.84.52;D7-20-00-00-00-20-40-00-8C-A3-20-F0-00-00-0E-1A;9
	//TimeStamp;typeTrace;module;pid;nid_msg;dest;mitt;message;size =9
	if(text->Contains(";")){

		array<String^> ^arraystr=text->Split(';');
		if(arraystr->Length==7){
			String ^result = String::Format("{0} Module:{1} NID_MSG:{2} Message:{3} Mitt:{4}->Dest:{5} Size:{6}",arraystr[0],arraystr[2],
				arraystr[4],arraystr[7],arraystr[6],arraystr[5],arraystr[8]);
			textBox->Text += result;
		}else{
			textBox->Text += text;
		}
	}else{
		textBox->Text += text;
	}
	textBox->SelectionStart = textBox->Text->Length;
	textBox->ScrollToCaret();
}