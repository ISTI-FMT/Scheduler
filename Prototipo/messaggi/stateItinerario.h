#pragma once
ref class stateItinerario
{
	unsigned int NID_ITIN;
	unsigned int Q_STATOITIN ;
	enum typeStateItineraio {itinerarioStatoIgnoto = -1, itinerarioStatoNonInAtto = 0, itinerarioStatoInAtto = 1,};
public:
	stateItinerario(void);
	stateItinerario(int N, int Q){NID_ITIN=N;setQ_STATOITIN(Q);};
	void setNID_ITIN( int N){NID_ITIN=N;};
	int getNID_ITIN(){return NID_ITIN;};
	void setQ_STATOITIN( int Q){
		if(Q>-2 & Q<2){
			Q_STATOITIN=Q;
		}else{
			Q_STATOITIN=typeStateItineraio::itinerarioStatoIgnoto;
		}
	};
	int getQ_STATOITIN(){return Q_STATOITIN;};
	int Size(){return 34;}
	bool Update(stateItinerario ^newitin){
		bool ret=false;
		if(newitin->getNID_ITIN()==NID_ITIN){
			if(newitin->getQ_STATOITIN()!=Q_STATOITIN){
				Q_STATOITIN=newitin->getQ_STATOITIN();
				ret=true;
			}



		}
		return ret;
	};
	virtual System::String ^ToString() override;
};

