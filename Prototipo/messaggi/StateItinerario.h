#pragma once

enum QStateItineraio  {itinerarioStatoNonInAtto = 0, itinerarioStatoInAtto = 1};

/*
Rappresenta le informazioni dello stato dell'itinerario del pacchetto stato itinerario rivevuto dall'IXL
*/
public ref class StateItinerario
{
	int NID_ITIN;
	int Q_STATOITIN ;
	
public:
	StateItinerario(void);
	StateItinerario(int N, QStateItineraio Q){NID_ITIN=N;setQ_STATOITIN(Q);};
	void setNID_ITIN( int N){NID_ITIN=N;};
	int getNID_ITIN(){return NID_ITIN;};
	void setQ_STATOITIN( QStateItineraio Q){
		if((Q>=0) & (Q<2)){
			Q_STATOITIN=Q;
		}else{
			Q_STATOITIN=QStateItineraio::itinerarioStatoInAtto;
		}
	};
	int getQ_STATOITIN(){return Q_STATOITIN;};
	int Size(){return 34;}
	bool Update(StateItinerario ^newitin){
		bool ret=false;
		if(newitin->getNID_ITIN()==NID_ITIN){
			if(newitin->getQ_STATOITIN()!=Q_STATOITIN){
				Q_STATOITIN=newitin->getQ_STATOITIN();
				ret=true;
			}
		}
		return ret;
	};

	StateItinerario ^Clone(){return gcnew StateItinerario(NID_ITIN,(QStateItineraio)Q_STATOITIN);};

	virtual System::String ^ToString() override;
};

