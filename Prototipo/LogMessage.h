#pragma once
#using <System.dll>
using namespace System;

ref class LogMessage
{
	int NID_MSG;
	DateTime ^time;
	String ^msg;
	String ^mit;
	String ^dest;

public:
	LogMessage(void);
	LogMessage(int n, DateTime ^d, String ^ms, String ^mi, String ^de);

	int getNID_MSG(){return NID_MSG;};
	void setNID_MSG(int N){NID_MSG=N;};

	DateTime ^getTimeStamp(){return time;};
	void setTimeStamp(DateTime ^t){time=t;};

	String ^getMSG(){return msg;};
	void setMSG(String ^str){msg=str;};

	String ^getMit(){return mit;};
	void setMit(String ^str){mit=str;};

	String ^getDest(){return dest;};
	void setDest(String ^str){dest=str;};

	virtual String ^ToString() override{
		String ^out;
		out = out+NID_MSG+";"; 
		out = out+getTimeStamp()+";";
		out = out+getMSG()+";";
		out = out+getMit()+";"+getDest()+";\n\r";
		return out;
	}
	 String ^ToPrint() {
		String ^out;
		out = out+"NID_MSG : "+NID_MSG; 
		out = out+" TimeStamp: "+getTimeStamp();
		out = out+" Messaggio: "+getMSG();
		out = out+" Mitt: "+getMit()+" --> Dest: "+getDest()+"\n\r";
		return out;
	}
};

