#pragma once

public enum class QStateItineraio  {itinerarioStatoNonInAtto = 0, itinerarioStatoInAtto = 1};

/*
Rappresenta le informazioni dello stato dell'itinerario del pacchetto stato itinerario rivevuto dall'IXL
*/
using namespace System::Diagnostics::CodeAnalysis;

[ExcludeFromCodeCoverage]
public ref class StateItinerario
{
	int NID_ITIN;
	int Q_STATOITIN ;
	
public:
	StateItinerario(void);
	StateItinerario(int N, int Q){NID_ITIN=N;Q_STATOITIN =Q;};
	void setNID_ITIN( int N){NID_ITIN=N;};
	int getNID_ITIN(){return NID_ITIN;};
	void setQ_STATOITIN( QStateItineraio Q){
					Q_STATOITIN=(int)Q;
		
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

