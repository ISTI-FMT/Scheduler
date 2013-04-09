#include "TabellaOrario.h"
#include <iostream>
using namespace std;

int main()
{
	TabellaOrario tabella;
	tabella.leggiTabellaOrario("prova");
	cout << tabella;
	system("Pause");
}