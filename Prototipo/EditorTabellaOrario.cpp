#include "EditorTabellaOrario.h"

void Prototipo::EditorTabellaOrario::setitinerary(){
	/*int riga=0;
	int colonna=0;*/
	this->tableLayoutPanelItinerari->Controls->Clear();
	Dictionary<int,stazione^ > ^dictabStaz = tabStazioni->getMap();
	int i = 0;
	for each (stazione ^var in dictabStaz->Values)
	{
		try{

			ItineraryBox ^itbox = gcnew ItineraryBox(var,i);
			//itbox->CambioItineraioUscita += gcnew System::EventHandler(this, &SingleTrainInfoForm::ItBox_ItChangedU);
			//itbox->CambioItineraioEntrata += gcnew System::EventHandler(this, &SingleTrainInfoForm::ItBox_ItChangedE);
			this->tableLayoutPanelItinerari->Controls->Add(itbox);
			i++;
		}catch(Exception ^e){
			Console::WriteLine("Errore ",e->Message);
		}

	}
}


