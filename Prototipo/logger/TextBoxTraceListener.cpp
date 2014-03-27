#include "TextBoxTraceListener.h"
#using <system.drawing.dll>
#include "..//SchedulerForm.h"

using namespace  System::Diagnostics;
using namespace  System::Windows::Forms;
using namespace  System;

/*TextBoxTraceListener::TextBoxTraceListener(void)
{
}*/



void TextBoxTraceListener::init(void){
	textBox=  (gcnew System::Windows::Forms::TextBox());
	textBox->Location =  System::Drawing::Point(5, 5);
	textBox->Multiline = true;
	textBox->Name = L"textBox";
	textBox->Size = System::Drawing::Size(1225, 410);
	textBox->TabIndex = 4;
	//textBox->BackColor = System::Drawing::Color::Black;
	textBox->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
	//textBox->Font = (gcnew System::Drawing::Font(L"Courier New", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
	//			static_cast<System::Byte>(0)));
//	textBox->ForeColor = System::Drawing::Color::White;
	//textBox->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox2_TextChanged);
	textBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
	form = gcnew Form();
	form->StartPosition =  System::Windows::Forms::FormStartPosition::Manual;
	form->Location = System::Drawing::Point(1, 750);
	form->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
	form->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	form->ClientSize = System::Drawing::Size(1230, 415);
	//form->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
	form->ControlBox=false;
	form->Controls->Add(textBox);
	form->Name = L"Message Log Monitor";
	form->Text = L"Message Log Monitor";
	form->ResumeLayout(true);
	form->PerformLayout();
	form->SuspendLayout();

	myDelegate = gcnew SetTextCallback( this, &TextBoxTraceListener::SetText );
	form->Resize += gcnew System::EventHandler(this, &TextBoxTraceListener::Form_Resize);
	form->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &TextBoxTraceListener::TextBoxTraceListener_FormClosing);
	form->Icon =  gcnew Icon(System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream("app.ico"));
	//form->ShowDialog();
	//Application::Run(form);
	form->Visible=true;


};

 System::Void TextBoxTraceListener::TextBoxTraceListener_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e){
	
	if(e->CloseReason==System::Windows::Forms::CloseReason::UserClosing){
	e->Cancel=true;
	 }else{
		 e->Cancel=false;
	 }
 }
void TextBoxTraceListener::WriteLine(String ^h){
	TextWriterTraceListener::WriteLine(h+"\r\n");
	Write(h+"\r\n");
};
void TextBoxTraceListener::WriteLine(Object ^h){
	WriteLine(h->ToString()+"\r\n");
};
void TextBoxTraceListener::Write(String ^h){
	try{
		if (textBox==nullptr){
			init();
		}
		form->Invoke( myDelegate, h );//try
	}catch(Exception ^e){
		//init();
		//form->Invoke( myDelegate, h );
		Console::WriteLine("Avevi chiuso la finetra del log!!! ",e->Message);
#ifdef TRACE
	//	Logger::Exception(e,"TextBoxTraceListener");  
#endif // TRACE
	}
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
		if(arraystr->Length>=7){
			//String ^result = String::Format("{0} Module:{1} NID_MSG:{2} Message:{3} {4} Send in/out:{5} Size:{6}",arraystr[0],arraystr[2],
			//	arraystr[4],arraystr[7],arraystr[6],arraystr[5],arraystr[8]);
			String ^result = String::Format("{4} {0} Module:{1} NID_MSG:{2} Message:{3}\r\n",arraystr[0],arraystr[2],
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

void TextBoxTraceListener::Form_Resize(System::Object^  sender, System::EventArgs^  e) {

	textBox->Size= System::Drawing::Size(form->Width-30,form->Height-50);
}

