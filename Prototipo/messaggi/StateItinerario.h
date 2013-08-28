#pragma once
enum typeStateItineraio  {itinerarioStatoNonInAtto = 0, itinerarioStatoInAtto = 1};

/*Utilizzo questa classe per serializzare le informazioni dello stato dell'itinerario del pacchetto stato itinerario
rivevuto dall'IXL*/


//questa classe rappresenta lo stato di un itinerario
ref class StateItinerario
{
	unsigned int NID_ITIN;
	int Q_STATOITIN ;
	
public:
	StateItinerario(void);
	StateItinerario(int N, int Q){NID_ITIN=N;setQ_STATOITIN(Q);};
	void setNID_ITIN( int N){NID_ITIN=N;};
	int getNID_ITIN(){return NID_ITIN;};
	void setQ_STATOITIN( int Q){
		if((Q>=0) & (Q<2)){
			Q_STATOITIN=Q;
		}else{
			Q_STATOITIN=typeStateItineraio::itinerarioStatoInAtto;
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

	StateItinerario ^Clone(){return gcnew StateItinerario(NID_ITIN,Q_STATOITIN);};

	virtual System::String ^ToString() override;
};

