#include "TabellaOrario.h"
#using <System.Xml.dll>
#include <iostream>
#include <msclr\marshal_cppstd.h>


TabellaOrario::TabellaOrario(void)
{
}

// funzione che converte una System::String in un intero
int TabellaOrario::convertiString2int(System::String ^StringValue)
{
	// converto da System::String a std::string
	std::string stdString = msclr::interop::marshal_as< std::string >(StringValue);
	// converto da std::string a int
	int intValue = atoi(stdString.c_str());
	return intValue;
}

// funzione che converte una System::String in un std::string
string TabellaOrario::convertiString2string(System::String ^StringValue)
{
	// converto da System::String a std::string
	std::string stdString = msclr::interop::marshal_as< std::string >(StringValue);
	return stdString;
}

// questa funzione legge il file di configurazione contenente la descrizione della tabella orario
void TabellaOrario::leggiTabellaOrario(string nomeFile)
{
	System::String^ nome = gcnew System::String(nomeFile.c_str());
	System::Xml::XmlReader ^reader = System::Xml::XmlReader::Create(nome);
	// per ogni treno presente nel file di configurazione della tabella orario...
	while (reader->ReadToFollowing("treno")){
		System::Xml::XmlReader ^inner = reader->ReadSubtree();
		// ...leggo l'id del treno
		System::String ^SystemStringIdTreno = reader->GetAttribute("id");
		// converto l'id del treno da System::String a int
		int idTreno = convertiString2int(SystemStringIdTreno);
		// creo un nuovo treno
		TrenoFermate *treno = new TrenoFermate(idTreno);

		// per ogni stazione in cui il treno in question deve fermarsi
		while (inner->ReadToFollowing("stazione")){
			// creo una nuova fermata
			Fermata *stop = new Fermata;
			// leggo l'id della stazione
			System::String ^SystemStringIdStazione = inner->GetAttribute("id");
			// converto l'id della stazione da System::String a int
			string idStazione = convertiString2string(SystemStringIdStazione);
			// configuro l'id della stazione
			stop->setIdStazione(idStazione);

			// leggo l'orario di arrivo
			inner->ReadToFollowing("arrivo");
			System::String ^SystemStringOrarioArrivo = inner->ReadString();
			// converto da System::String a std::string
			string stringOrarioArrivo = convertiString2string(SystemStringOrarioArrivo);
			// estraggo ora, minuto e secondo
			string stringOraArrivo = stringOrarioArrivo.substr(0,2);
			string stringMinutoArrivo = stringOrarioArrivo.substr(3,2);
			string stringSecondoArrivo = stringOrarioArrivo.substr(5,2);
			// converto da string a int
			int oraArrivo = atoi(stringOraArrivo.c_str());
			int minutoArrivo = atoi(stringMinutoArrivo.c_str());
			int secondoArrivo = atoi(stringSecondoArrivo.c_str());
			// configuro l'orario di arrivo della farmata
			stop->setOrarioArrivo_Ora(oraArrivo);
			stop->setOrarioArrivo_Minuto(minutoArrivo);
			stop->setOrarioArrivo_Secondo(secondoArrivo);

			// leggo l'orario di partenza
			inner->ReadToFollowing("partenza");
			System::String ^SystemStringOrarioPartenza = inner->ReadString();
			// converto da System::String a std::string
			string stringOrarioPartenza = convertiString2string(SystemStringOrarioPartenza);
			// estraggo ora, minuto e secondo
			string stringOraPartenza = stringOrarioPartenza.substr(0,2);
			string stringMinutoPartenza = stringOrarioPartenza.substr(3,2);
			string stringSecondoPartenza = stringOrarioPartenza.substr(5,2);
			// converto da string a int
			int oraPartenza = atoi(stringOraPartenza.c_str());
			int minutoPartenza = atoi(stringMinutoPartenza.c_str());
			int secondoPartenza = atoi(stringSecondoPartenza.c_str());
			// configuro l'orario di arrivo della farmata
			stop->setOrarioPartenza_Ora(oraPartenza);
			stop->setOrarioPartenza_Minuto(minutoPartenza);
			stop->setOrarioPartenza_Secondo(secondoPartenza);

			// leggo il binario programmato
			inner->ReadToFollowing("binarioprogrammato");
			System::String ^SystemStringBinarioProgrammato = inner->ReadString();
			// converto il binario programmato da System::String a int
			int binarioProgrammato = convertiString2int(SystemStringBinarioProgrammato);
			// configuro il binario programmato
			stop->setBinarioProgrammato(binarioProgrammato);

			// leggo il lato di apertura porte programmato
			inner->ReadToFollowing("latoaperturaporteprogrammato");
			System::String ^SystemStringLatoProgrammato = inner->ReadString();	
			// converto da System::String a std::string
			string stringLatoAperturaPorte = convertiString2string(SystemStringLatoProgrammato);
			aperturaPorte latoParturaPorte;
			if(stringLatoAperturaPorte == "dx")
				latoParturaPorte = destra;
			else if(stringLatoAperturaPorte == "sx")
				latoParturaPorte = sinistra;
			else if(stringLatoAperturaPorte == "sd")
				latoParturaPorte = destraSinistra;
			else
				latoParturaPorte = noApertura;
			// configuro il lato apertura porte programmato programmato
			stop->setLatoAperturaPorte(latoParturaPorte);

			// a questo punto posso aggiungere la fermata alla lista delle fermate del treno in questione
			treno->aggiungiFermata(*stop);

			//System::Console::WriteLine(idTreno+idSTazione+orarioArrivo+orarioPartenza+binarioProgrammato+latoProgrammato);
			System::Console::WriteLine();
		}
		// a questo punto aggiungo il treno alla tabella orario
		aggiungiTreno(*treno);
	}	
}

void TabellaOrario::aggiungiTreno(TrenoFermate &treno)
{
	tabella.push_front(treno);
}

ostream& operator<<(ostream &out, TabellaOrario &tabella)
{
	for (std::list<TrenoFermate>::iterator it=tabella.tabella.begin(); it != tabella.tabella.end(); ++it)
		out << (*it) << endl;
	return out;
}

TabellaOrario::~TabellaOrario()
{
	

	// scorro tutta la lista...
	//for (std::list<TrenoFermate>::iterator it=tabella.end(); it != tabella.begin(); it--){
		// ...e cancelo tutti gli elementi uno alla volta
	//	std::cout <<it;

	//	tabella.erase(it);
	//}
		
}
