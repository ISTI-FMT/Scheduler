#include "FormStatoLineaATC.h"

void Prototipo::FormStatoLineaATC::genera(){


	tableLayoutPanelAllCDB ^tableCDB = gcnew tableLayoutPanelAllCDB(listbuttonCDB);
	tableCDB->Location =  System::Drawing::Point(1, 1);
	tableCDB->Name = "statoCDB";
	//tablel->Size =  System::Drawing::Size(75, 16);
	tableCDB->TabIndex = 1;
	tableCDB->Text = "Stato CDB IXL";

	Controls->Add(tableCDB);

}

void Prototipo::FormStatoLineaATC::aggiorna(){

	while(true){
		//Thread::Sleep(50);
		if(eventiATC!=nullptr){
			Event ^even = eventiATC->getEvent();
			if(even!=nullptr){
			StateCDB ^stCDB =	even->getEventStateCDB();
			if(stCDB!=nullptr){
				int id =	stCDB->getNID_CDB();
				int stato =	stCDB->getQ_STATOCDB();

				findandsetCDB(id,stato);

			}
			}

		}




	}

}

void  Prototipo::FormStatoLineaATC::findandsetCDB(int id, int stato){
	if(listbuttonCDB->ContainsKey(id)){
		if(stato==typeStateCDB::cdbOccupato){
			listbuttonCDB[id]->BackColor= System::Drawing::Color::Red;
		}
		if(stato==typeStateCDB::cdbLibero){
			listbuttonCDB[id]->BackColor= System::Drawing::Color::Green;
		}
		if(stato==typeStateCDB::cdbImpegnato){
			listbuttonCDB[id]->BackColor= System::Drawing::Color::Yellow;
		}

	}

}