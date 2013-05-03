#pragma once
#using <System.dll>
#using <System.Windows.Forms.dll>

using namespace  System::Diagnostics;
using namespace  System::Windows::Forms;
using namespace  System;

ref class TextBoxTraceListener :TextWriterTraceListener
{
    System::Windows::Forms::TextBox^  textBox;
	System::Windows::Forms::Form ^  form;

public:
	TextBoxTraceListener(void): TextWriterTraceListener(){init();};

	TextBoxTraceListener( System::Windows::Forms::TextBox^  tb): TextWriterTraceListener(){textBox=tb;};
	TextBoxTraceListener(String ^h): TextWriterTraceListener(h){};
	void  init(void);
	virtual void WriteLine(String ^h) override;
	virtual void WriteLine(Object ^h)override;
	virtual void Write(String ^h)override;
	virtual void Write(Object ^h)override;
	delegate void SetTextCallback(String ^text);
	SetTextCallback^ myDelegate;
	void SetText(String ^text);
};

