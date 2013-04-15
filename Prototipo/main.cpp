#include "TabellaOrario.h"
#include "pacchettoMissionPlan.h"
#include <iostream>
using namespace std;

int main()
{
	TabellaOrario tabella;
	tabella.leggiTabellaOrario("..\\..\\FileConfigurazione\\TabellaOrario.xml");
	cout << tabella;

	pacchettoMissionPlan p;
	int x;
	cin >> x;
	p.setNID_MESSAGE(x);
	cin >> x;
	p.setL_MESSAGE(x);
	cin >> x;
	p.setT_TRAIN(x);
	byte buff[100];
	for(int i = 0; i < 100; ++i)
		buff[i] = 0;

	int i = 0;
	p.serializeStructuredHeader(buff, i);

	cout << i << endl;

	for(int j = 0; j < (i / 8); ++j)
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
	for(int k = (i % 8) - 1; k >= 0; --k)
	{
		byte mask = 1 << k;
		byte aux = buff[(i / 8) + 1] & mask;
		char supp = aux?'1':'0';
		cout << supp;
	}
	cout << endl;

	system("Pause");

}