#include "ConfigurazioneVelocita.h"
#using <System.Xml.dll>
#include "..\\logger\\Logger.h"

using namespace System;
using namespace System::Globalization;
using namespace System::Xml;
using namespace System::Xml::Schema;

#define TRACE
//#define VALIDATEXML

ConfigurazioneVelocita::ConfigurazioneVelocita(void)
{
	mapidtrenologicopvel= gcnew Dictionary<int,List<ProfiloVelocita^>^>() ;
	schemaxsd="..\\FileConfigurazione\\ConfigurazioneProfiliVelocita.xsd";
	
}

ConfigurazioneVelocita::ConfigurazioneVelocita(String ^nomefile)
{
	mapidtrenologicopvel= gcnew Dictionary<int,List<ProfiloVelocita^>^>() ;
	schemaxsd="..\\FileConfigurazione\\ConfigurazioneProfiliVelocita.xsd";
	 leggifileConfigurazioneVelocita(nomefile);
}

// questa funzione legge il file di configurazione 
void ConfigurazioneVelocita::leggifileConfigurazioneVelocita(String ^nomeFile)
{

	try{

#ifdef VALIDATEXML
		// Create the XmlSchemaSet class.
		XmlSchemaSet^ sc = gcnew XmlSchemaSet;

		// Add the schema to the collection.
		sc->Add("urn:configurazioneprofilivelocita-schema", schemaxsd );
		XmlReaderSettings^ settings = gcnew XmlReaderSettings;
		settings->ValidationType = System::Xml::ValidationType::Schema;
		settings->Schemas = sc;


		System::Xml::XmlReader ^reader = System::Xml::XmlReader::Create(nomeFile, settings);

	/*	XmlDocument ^document = gcnew XmlDocument();
		document->Load(readers);  */

#endif // VALIDATEXML

		System::Xml::XmlReader ^reader = System::Xml::XmlReader::Create(nomeFile);

		// 
		while (reader->ReadToFollowing("profilovelocita")){
			System::Xml::XmlReader ^inner = reader->ReadSubtree();
			
			System::String ^StrIdTrenoLogico = reader->GetAttribute("trenoid");
			
			// converto l'id della stazione da System::String a int
			int IdTrenoLogico = int::Parse(StrIdTrenoLogico);

			if(!mapidtrenologicopvel->ContainsKey(IdTrenoLogico)){

				List<ProfiloVelocita^> ^lprogkm = gcnew List<ProfiloVelocita^>();
				mapidtrenologicopvel->Add(IdTrenoLogico,lprogkm);
				while (inner->ReadToFollowing("progressivakm")){

					
					int pkm = int::Parse(inner->GetAttribute("km"));
					System::Xml::XmlReader ^inner3 = inner->ReadSubtree();
					inner3->ReadToFollowing("velocita");
					int limite = int::Parse( inner3->GetAttribute("limite"));
					ProfiloVelocita ^progkm = gcnew ProfiloVelocita(pkm,limite);
					lprogkm->Add(progkm);
					
				}

				

			}

		}	
	}catch(System::Xml::Schema::XmlSchemaValidationException ^e){

#ifdef TRACE
		Logger::Exception(e,"ConfigurazioneVelocita");  
#endif // TRACE
		Console::WriteLine( L"Validation Error: {0}", e->Message );
	}	
}



System::String^ ConfigurazioneVelocita::ToString() {
	String ^out="Profili Velocità\n\r";
	for each( KeyValuePair<int  ,List< ProfiloVelocita^>^> kvp in mapidtrenologicopvel )
	{

		out+=" IdTreno: "+ kvp.Key+"\n\r";
		for each (ProfiloVelocita ^var in kvp.Value)
		{
			out+=" "+var->ToString()+"\n\r";
		}
		


	}
	return out;
}
