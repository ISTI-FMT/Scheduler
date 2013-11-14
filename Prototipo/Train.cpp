#include "Train.h"




Train::Train( int trn, int tpn){
	TrainRunningNumber=trn;
	 TrainPhisicalNumber=tpn;
	 Listaitinerari= gcnew List<Fermata^>();
	 Statodeltreno=StateTrain::NONPRONTO;
	 indicelistaitinerari=0;

}

Train::Train( int tpn){
	TrainRunningNumber=0;
	 TrainPhisicalNumber=tpn;
	 Listaitinerari= gcnew List<Fermata^>();
	 Statodeltreno=StateTrain::NONPRONTO;
	 indicelistaitinerari=0;

}


Train::Train( int trn, int tpn, List<Fermata^> ^listit){

	 TrainRunningNumber=trn;
	 TrainPhisicalNumber=tpn;
	 Listaitinerari=listit;
	  Statodeltreno=StateTrain::NONPRONTO;
	  indicelistaitinerari=0;
}

Train::Train( int trn, int tpn, List<Fermata^> ^listit, StateTrain st){

	 TrainRunningNumber=trn;
	 TrainPhisicalNumber=tpn;
	 Listaitinerari=listit;
	 Statodeltreno=st;
	 indicelistaitinerari=0;
}

KeyValuePair<int, int> ^Train::getStazioneItinerario(){
	switch (Statodeltreno)
	{
	case PRONTO:
		break;
	case USCITASTAZIONE:{
		int itinUscita = Listaitinerari[indicelistaitinerari]->getIditinerarioUscita();
		int idstazione = Listaitinerari[indicelistaitinerari]->getIdStazione();
		return gcnew  KeyValuePair<int, int>(idstazione, itinUscita);
		break;}
	case ENTRATASTAZIONE:{
		int initEntrata = Listaitinerari[indicelistaitinerari]->getIditinerarioEntrata();
		int idstazione = Listaitinerari[indicelistaitinerari]->getIdStazione();
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