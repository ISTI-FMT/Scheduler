#pragma once
#using <System.dll>
#include "Itinerario.h"
#include "binario.h"
using namespace System;
using namespace System::Collections::Generic;

/*utilizzo questa classe per rappresentare le informazioni delle stazioni parsate dal file xml ConfigurazioneItinerari.xml*/


//questa classe rappresenta una stazione
//contiene oltre id numerico e il nome della stazione
//due dizionari per trovare gli itinerari uno la cui chieave è prevcdb
//l'altro la cui chiave è id dell'itinerario
public ref class stazione
{
	String ^nomeStazione;
	int idStazione;
	//la chiave è prevcdb
	Dictionary<int,List<Itinerario^>^ > ^itinerari;
	List<binario^>^binari;
	//lachiave è id dell'itinerario
	Dictionary<int,Itinerario^ > ^itinerariid;

public:
	stazione(void);
	void setNomeStazione(String ^n){nomeStazione = n;}
	void set_SetIDStazione(int n){idStazione = n;}
	void addBinario(binario ^b){binari->Add(b);};
	Dictionary<int,List<Itinerario^>^ > ^ getItinerari(){return itinerari;};
	Dictionary<int,Itinerario^ > ^ getItinerariid(){return itinerariid;};
	String ^get_NomeStazione(){return nomeStazione;};
	List<binario^>^getBinari(){return binari;};
	int get_idStazione(){return idStazione;};
	virtual System::String^ ToString() override;
	//fornendo id dell'itinerario restiuisce una lista di 2 valori interi che rappresentano rispettivamente
	//nid_lrgb e D_stop per quell'itinerario 
	lrbg ^get_infobalise(int id){

		if(itinerariid->ContainsKey(id)){


			return itinerariid[id]->getLrgb();
		}
		return nullptr;

	}
	///indica la direzione in cui va il treno true dx da accademia -> vittoria, false viceversa
	bool get_Direzione_itinerario(int iditini){
		if(itinerariid->ContainsKey(iditini)){

			if( itinerariid[iditini]->getDirezione()=="dx"){
				return true;
			}else{
				return false;
			}

		}
		return false;

	}

	


	lrbg ^get_infobalise_fromBinario(int bina, bool dir){
		String ^dire = "dx";
		if(!dir){
			dire="sx";
		}
		for each (binario ^bin in binari)
		{
			if((bin->getBin()==bina) &(bin->getDirezione()==dire)  ){
				return	bin->get_info_lrgb();
			}
		}
		return gcnew lrbg();
	}

};