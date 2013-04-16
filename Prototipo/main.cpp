#include "TabellaOrario.h"
#include "pacchettoMissionPlan.h"
#include "pacchettoCommandData1.h"
#include <iostream>
using namespace std;

void stampaBuffer(byte *buff, int nBit)
{
	cout << nBit << endl;

	for(int j = 0; j < (nBit / 8); ++j)
	{
		for(int k = 7; k >= 0; --k)
		{
			byte mask = 1 << k;
			byte aux = buff[j] & mask;
			char supp = aux?'1':'0';
			cout << supp;
		}
		cout << endl;
	}
	for(int k = (nBit % 8) - 1; k >= 0; --k)
	{
		byte mask = 1 << k;
		byte aux = buff[(nBit / 8) + 1] & mask;
		char supp = aux?'1':'0';
		cout << supp;
	}
	cout << endl;
}

void provaSerializePacchettoCommandData1(pacchettoCommandData1 &pkt)
{
	int NID_MESSAGE, L_MESSAGE, T_TRAIN, NID_PACKET, L_PACKET, Q_COMMAND_TYPE;
	cout << "Insert NID_MESSAGE" << endl;
	cin >> NID_MESSAGE;
	pkt.setNID_MESSAGE(NID_MESSAGE);
	cout << "Insert L_MESSAGE" << endl;
	cin >> L_MESSAGE;
	pkt.setL_MESSAGE(L_MESSAGE);
	cout << "Insert T_TRAIN" << endl;
	cin >> T_TRAIN;
	pkt.setT_TRAIN(T_TRAIN);
	cout << "Insert NID_PACKET" << endl;
	cin >> NID_PACKET;
	pkt.setNID_PACKET(NID_PACKET);
	cout << "Insert L_PACKET" << endl;
	cin >> L_PACKET;
	pkt.setL_PACKET(L_PACKET);
	cout << "Insert Q_COMMAND_TYPE" << endl;
	cin >> Q_COMMAND_TYPE;
	pkt.setQ_COMMAND_TYPE(Q_COMMAND_TYPE);
	byte buff[100];
	for(int i = 0; i < 100; ++i)
		buff[i] = 0;
	int len = 0;
	pkt.serializepacchettoCommandData(buff);
	stampaBuffer(buff, 80);
}

int main()
{
	TabellaOrario tabella;
	tabella.leggiTabellaOrario("..\\..\\FileConfigurazione\\TabellaOrario.xml");
	cout << tabella;

	byte buff[100];
	for(int i = 0; i < 100; ++i)
		buff[i] = 0;

	/*
	// Prova di serializzazione di pacchetto missione plan
	pacchettoMissionPlan p;
	int x;
	cin >> x;
	p.setNID_MESSAGE(x);
	cin >> x;
	p.setL_MESSAGE(x);
	cin >> x;
	p.setT_TRAIN(x);

	int i = 0;
	p.serializeStructuredHeader(buff, i);

	stampaBuffer(buff,i);
	*/

	pacchettoCommandData1 pkt1;
	cout << sizeof(pkt1) << endl;
	provaSerializePacchettoCommandData1(pkt1);

	system("Pause");

}