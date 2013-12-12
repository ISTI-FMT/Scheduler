#include "Train.h"




Train::Train(int p, int trn, physicalTrain ^pt){
	TrainRunningNumber=trn;
	PhysicalTrain=pt;
	Listafermate= gcnew List<Fermata^>();
	Statodeltreno=StateTrain::NONPRONTO;
	indicelistaitinerari=0;
	Priorita=p;
	PhysicalTrainNumber=pt->getEngineNumber();
}

Train::Train(int p, physicalTrain ^pt){
	TrainRunningNumber=0;
	PhysicalTrain=pt;
	Listafermate= gcnew List<Fermata^>();
	Statodeltreno=StateTrain::NONPRONTO;
	indicelistaitinerari=0;
	Priorita=p;
	PhysicalTrainNumber=pt->getEngineNumber();

}

Train::Train(int p, int trn,physicalTrain ^pt, List<Fermata^> ^listf){

	TrainRunningNumber=trn;
	PhysicalTrain=pt;
	Listafermate=listf;
	Statodeltreno=StateTrain::USCITASTAZIONE;
	indicelistaitinerari=0;
	Priorita=p;
	PhysicalTrainNumber=pt->getEngineNumber();
	setTimeStampNextEvent(listf[0]->getOrarioPartenza());

}


Train::Train(int p, int trn,physicalTrain ^pt, List<Fermata^> ^listf, double time){

	TrainRunningNumber=trn;
	PhysicalTrain=pt;
	Listafermate=listf;
	Statodeltreno=StateTrain::USCITASTAZIONE;
	indicelistaitinerari=0;
	Priorita=p;
	PhysicalTrainNumber=pt->getEngineNumber();
	setTimeStampNextEvent(time);

}


Train::Train(int p, int trn, physicalTrain ^pt, List<Fermata^> ^listf, StateTrain st){

	TrainRunningNumber=trn;
	PhysicalTrain=pt;
	Listafermate=listf;
	Statodeltreno=st;
	indicelistaitinerari=0;
	Priorita=p;
	PhysicalTrainNumber=pt->getEngineNumber();
	setTimeStampNextEvent(getOrarioPartenza());
}

Double Train::getOrarioPartenza(){

	return Listafermate[indicelistaitinerari]->getOrarioPartenza();
}

void  Train::goNextItinerario(){

	if(Statodeltreno==StateTrain::ENTRATASTAZIONE){
		Statodeltreno=StateTrain::USCITASTAZIONE;

	}else{
		if(Statodeltreno==StateTrain::USCITASTAZIONE){
			Statodeltreno=StateTrain::ENTRATASTAZIONE;
			indicelistaitinerari++;
		}
	}
}

KeyValuePair<int, int> ^Train::getStazioneItinerario(){
	switch (Statodeltreno)
	{
	case PRONTO:
		break;
	case USCITASTAZIONE:{
		int itinUscita = Listafermate[indicelistaitinerari]->getIditinerarioUscita();
		int idstazione = Listafermate[indicelistaitinerari]->getIdStazione();
		return gcnew  KeyValuePair<int, int>(idstazione, itinUscita);
		break;}
	case ENTRATASTAZIONE:{
		int initEntrata = Listafermate[indicelistaitinerari]->getIditinerarioEntrata();
		int idstazione = Listafermate[indicelistaitinerari]->getIdStazione();
		return gcnew  KeyValuePair<int, int>(idstazione, initEntrata);
		break;}
	case NONPRONTO:
		break;
	case TERMINATO:
		break;
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

		if(getTimeNextEvent()!=nullptr & otherKey->getTimeNextEvent()!=nullptr ){
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

void Train::changeOrari(Dictionary<int,KeyValuePair<DateTime, DateTime>> ^nuoviorari){
	for each (Fermata ^var in Listafermate)
	{
		int idstazione = var->getIdStazione();
		if(nuoviorari->ContainsKey(idstazione)){
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
	}


}