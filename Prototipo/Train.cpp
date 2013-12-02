#include "Train.h"




Train::Train( int trn, physicalTrain ^pt){
	TrainRunningNumber=trn;
	PhysicalTrain=pt;
	Listafermate= gcnew List<Fermata^>();
	Statodeltreno=StateTrain::NONPRONTO;
	indicelistaitinerari=0;

}

Train::Train( physicalTrain ^pt){
	TrainRunningNumber=0;
	PhysicalTrain=pt;
	Listafermate= gcnew List<Fermata^>();
	Statodeltreno=StateTrain::NONPRONTO;
	indicelistaitinerari=0;

}


Train::Train( int trn,physicalTrain ^pt, List<Fermata^> ^listf){

	TrainRunningNumber=trn;
	PhysicalTrain=pt;
	Listafermate=listf;
	Statodeltreno=StateTrain::USCITASTAZIONE;
	indicelistaitinerari=0;
}

Train::Train( int trn, physicalTrain ^pt, List<Fermata^> ^listf, StateTrain st){

	TrainRunningNumber=trn;
	PhysicalTrain=pt;
	Listafermate=listf;
	Statodeltreno=st;
	indicelistaitinerari=0;
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

	return "";
}