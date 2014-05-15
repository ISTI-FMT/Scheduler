#include "Train.h"




Train::Train(int p, int trn, physicalTrain ^pt){
	TrainRunningNumber=trn;
	PhysicalTrain=pt;
	Listafermate= gcnew List<Fermata^>();
	setStatoTreno(StateTrain::NONPRONTO);
	indicelistafermata=0;
	setPriorita(p);
	PhysicalTrainNumber=pt->getEngineNumber();
}

Train::Train(int p, physicalTrain ^pt){
	TrainRunningNumber=0;
	PhysicalTrain=pt;
	Listafermate= gcnew List<Fermata^>();
	setStatoTreno(StateTrain::NONPRONTO);
	indicelistafermata=0;
	setPriorita(p);
	PhysicalTrainNumber=pt->getEngineNumber();

}

Train::Train(int p, int trn,physicalTrain ^pt, List<Fermata^> ^listf){

	TrainRunningNumber=trn;
	PhysicalTrain=pt;
	setListaFermate(listf);
	setStatoTreno(StateTrain::PRONTO);
	indicelistafermata=0;
	setPriorita(p);
	PhysicalTrainNumber=pt->getEngineNumber();
	setTimeStampNextEvent(listf[0]->getOrarioPartenza());

}


Train::Train(int p, int trn,physicalTrain ^pt, List<Fermata^> ^listf, double time){

	TrainRunningNumber=trn;
	PhysicalTrain=pt;
	setListaFermate(listf);
	setStatoTreno(StateTrain::PRONTO);
	indicelistafermata=0;
	setPriorita(p);
	PhysicalTrainNumber=pt->getEngineNumber();
	setTimeStampNextEvent(time);

}


Train::Train(int p, int trn, physicalTrain ^pt, List<Fermata^> ^listf, StateTrain st){

	TrainRunningNumber=trn;
	PhysicalTrain=pt;
	setListaFermate(listf);
	setStatoTreno(st);
	indicelistafermata=0;
	setPriorita(p);
	PhysicalTrainNumber=pt->getEngineNumber();
	setTimeStampNextEvent(getOrarioPartenza());
}

Double Train::getOrarioPartenza(){
	if(Listafermate->Count>indicelistafermata){
		return Listafermate[indicelistafermata]->getOrarioPartenza();
	}
	return 0;
}

void  Train::goNextItinerario(){

	if(Statodeltreno==StateTrain::ENTRATASTAZIONE){
		Statodeltreno=StateTrain::USCITASTAZIONE;

	}else{
		if(Statodeltreno==StateTrain::USCITASTAZIONE){
			Statodeltreno=StateTrain::ENTRATASTAZIONE;

			if(indicelistafermata<Listafermate->Count-1){
				indicelistafermata++;
			}else{
				Statodeltreno=StateTrain::TERMINATO;
			}
		}
	}
}

KeyValuePair<int, int> ^Train::getStazioneItinerario(){
	
		switch (Statodeltreno)
		{
		case StateTrain::PRONTO:{

			return gcnew  KeyValuePair<int, int>();
			break;

								}
		case StateTrain::USCITASTAZIONE:{
			int itinUscita = Listafermate[indicelistafermata]->getIditinerarioUscita();
			int idstazione = Listafermate[indicelistafermata]->getIdStazione();
			return gcnew  KeyValuePair<int, int>(idstazione, itinUscita);
			break;}
		case StateTrain::ENTRATASTAZIONE:{
			int initEntrata = Listafermate[indicelistafermata]->getIditinerarioEntrata();
			int idstazione = Listafermate[indicelistafermata]->getIdStazione();
			return gcnew  KeyValuePair<int, int>(idstazione, initEntrata);
			break;}
		case StateTrain::NONPRONTO:
			break;
		case StateTrain::TERMINATO:{
			int initEntrata = Listafermate[indicelistafermata]->getIditinerarioEntrata();
			int idstazione = Listafermate[indicelistafermata]->getIdStazione();
			return gcnew  KeyValuePair<int, int>(idstazione, initEntrata);
			break;}
		default:
			break;
		}
	
	return nullptr;
}

System::String ^Train::ToString(){

	String ^time = "null";
	if(getTimeNextEvent()!=nullptr){
		time = getTimeNextEvent()->ToString();
	}
	String ^out=  String::Format("Priorità: {0} TRN: {1} PT: {2} TimeNextEvent: {3}",getPriorita(),getTRN(),getPTN(),time);

	return out;
}

void Train::setTimeStampNextEvent(double time){
	Double times = time*30;
	TimeSpan sinceMidnight = TimeSpan::FromSeconds(times);
	DateTime orarioSupporto = DateTime::ParseExact("00:00:00", "HH:mm:ss", CultureInfo::InvariantCulture);
	setTimeStampNextEvent(orarioSupporto+sinceMidnight);

}


Int32 Train::CompareTo(Train^otherKey){

	if (otherKey == nullptr) return 1;


	if(getPriorita() ==otherKey->getPriorita()){

		if((getTimeNextEvent()!=nullptr)&(otherKey->getTimeNextEvent()!=nullptr)){
			DateTime ^time = getTimeNextEvent();
			DateTime ^timeNext = otherKey->getTimeNextEvent();
			if(time->CompareTo(timeNext)!=0){
				return time->CompareTo(timeNext);		
			}else{
				return getTRN().CompareTo(otherKey->getTRN());

			}


		}else{
			return 0;
		}
	}
	if(getPriorita() >otherKey->getPriorita()){
		return 1;
	}
	if(getPriorita() <otherKey->getPriorita()){
		return -1;
	}
	return 0;
}

void Train::changeOrari( List<Fermata^> ^nuoviorari){
	Listafermate->Clear();
	Listafermate =nuoviorari;
	Console::WriteLine("AGGIORNATI ORARI NEL MODELLO");
	/*for each (Fermata ^var in Listafermate)
	{
	int idstazione = var->getIdStazione();
	if(nuoviorari->Contains(idstazione)){
	DateTime arrivo = nuoviorari[idstazione].Key;
	DateTime partenza = nuoviorari[idstazione].Value;
	DateTime orarioSupporto3 = DateTime::ParseExact("00:00:00", "HH:mm:ss", CultureInfo::InvariantCulture);

	TimeSpan sinceMidnighta = arrivo - orarioSupporto3;
	TimeSpan sinceMidnightp = partenza - orarioSupporto3;
	double	darrivo = sinceMidnighta.TotalSeconds/30;
	double	dpartenza = sinceMidnightp.TotalSeconds/30;
	if(var->getOrarioArrivo()!=darrivo){
	var->setOrarioArrivo(darrivo);
	}
	if(var->getOrarioPartenza()!=dpartenza){
	var->setOrarioPartenza(dpartenza);
	}
	}
	}*/


}