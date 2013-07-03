#include "FormStatoItinerari.h"

void Prototipo::FormStatoItinerari::genera(){

	Dictionary<int,stazione^ >::ValueCollection ^valueColl =
		tabItinerari->getMap()->Values;
	for each (stazione ^station in valueColl)
	{
		tableLayoutPanelSingleItin ^tablel = gcnew tableLayoutPanelSingleItin(station,listbutton);
		tablel->Location =  System::Drawing::Point(1, 1);
		tablel->Name = "statoItinerari";
		//tablel->Size =  System::Drawing::Size(75, 16);
		tablel->TabIndex = 1;
		tablel->Text = "Stato Itinerari IXL";

		tableLayoutPanel1->Controls->Add(tablel);
		//return;
	}
	tableLayoutPanelAllCDB ^tableCDB = gcnew tableLayoutPanelAllCDB(listbuttonCDB);
	tableCDB->Location =  System::Drawing::Point(1, 475);
	tableCDB->Name = "statoCDB";
	//tablel->Size =  System::Drawing::Size(75, 16);
	tableCDB->TabIndex = 1;
	tableCDB->Text = "Stato CDB IXL";

	Controls->Add(tableCDB);

}

void Prototipo::FormStatoItinerari::aggiorna(){

	while(true){
		//Thread::Sleep(50);
		if(eventiItinerario!=nullptr){
			Event ^even = eventiItinerario->getEvent();
			if(even!=nullptr){
				StateItinerario ^st =	even->getEventStateItinerario();
				if(st!=nullptr){
					int id =	st->getNID_ITIN();
					int stato =	st->getQ_STATOITIN();

					findandset(id,stato);
				}else{
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

}

void Prototipo::FormStatoItinerari::findandset(int id, int stato){
	if(listbutton->ContainsKey(id)){
		if(stato==typeStateItineraio::itinerarioStatoInAtto){
			listbutton[id]->BackColor= System::Drawing::Color::Red;
		}
		if(stato==typeStateItineraio::itinerarioStatoNonInAtto){
			listbutton[id]->BackColor= System::Drawing::Color::Gray;
		}


	}


}

void  Prototipo::FormStatoItinerari::findandsetCDB(int id, int stato){
	if(listbuttonCDB->ContainsKey(id)){
		if(stato==typeStateCDB::cdbOccupato){
			listbuttonCDB[id]->BackColor= System::Drawing::Color::Red;
		}
		if(stato==typeStateCDB::cdbLibero){
			listbuttonCDB[id]->BackColor= System::Drawing::Color::Gray;
		}
		if(stato==typeStateCDB::cdbImpegnato){
			listbuttonCDB[id]->BackColor= System::Drawing::Color::White;
		}

	}

}




void Prototipo::FormStatoItinerari::setCdBItin(List<StateCDB^> ^listCdB, int stato){
	for each (StateCDB ^cdb in listCdB)
	{
		cdb->setQ_STATOCDB(stato);
	}


}