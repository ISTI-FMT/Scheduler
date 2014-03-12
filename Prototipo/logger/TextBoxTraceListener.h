#pragma once
#using <System.dll>
#using <System.Windows.Forms.dll>

using namespace  System::Diagnostics;
using namespace  System::Windows::Forms;
using namespace  System;

/*Utilizzo questa classe per visualizzare graficamente in un area di testo in cui stampare i messaggi di log 
intercettati dal TraceListener */

//questa classe listener estende TextWriterTraceListener e  permette di visualizzare le informazioni di logging in una text box.
ref class TextBoxTraceListener :TextWriterTraceListener
{
	System::Windows::Forms::TextBox^  textBox;
	System::Windows::Forms::Form ^  form;
	void Form_Resize(System::Object^  sender, System::EventArgs^  e);
public:
	TextBoxTraceListener(void): TextWriterTraceListener(){init();};

	//TextBoxTraceListener( System::Windows::Forms::TextBox^  tb): TextWriterTraceListener(){textBox=tb;};
	TextBoxTraceListener(String ^h): TextWriterTraceListener(h){init();};
	void  init(void);
	virtual void WriteLine(String ^h) override;
	virtual void WriteLine(Object ^h)override;
	virtual void Write(String ^h)override;
	virtual void Write(Object ^h)override;
	delegate void SetTextCallback(String ^text);
	SetTextCallback^ myDelegate;
	void SetText(String ^text);
	 System::Void TextBoxTraceListener_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
};

