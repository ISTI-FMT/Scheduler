#include "ConfigurazioneVelocita.h"
#using <System.Xml.dll>
#include "..\\logger\\Logger.h"

using namespace System;
using namespace System::Globalization;
using namespace System::Xml;
using namespace System::Xml::Schema;

#define TRACE
#define VALIDATEXML

ConfigurazioneVelocita::ConfigurazioneVelocita(void)
{
	mapidtrenologicopvel= gcnew Dictionary<int,List<ProfiloVelocita^>^>() ;
	schemaxsd="ConfigurazioneProfiliVelocita.xsd";
	leggifileConfigurazioneVelocita();
	
}



// questa funzione legge il file di configurazione 
void ConfigurazioneVelocita::leggifileConfigurazioneVelocita()
{

	try{

#ifdef VALIDATEXML
		// Create the XmlSchemaSet class.
		XmlSchemaSet^ sc = gcnew XmlSchemaSet;
		System::IO::Stream^ readStreamschemaxsd = System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream(schemaxsd);
		// Add the schema to the collection.
		sc->Add("urn:configurazioneprofilivelocita-schema",   gcnew XmlTextReader (readStreamschemaxsd)  );
		XmlReaderSettings^ settings = gcnew XmlReaderSettings;
		settings->ValidationType = System::Xml::ValidationType::Schema;
		settings->Schemas = sc;
		System::IO::Stream^ readStreamXML = System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream("ConfigurazioneProfiliVelocita.xml");

		System::Xml::XmlReader ^reader = System::Xml::XmlReader::Create(readStreamXML, settings);

	/*	XmlDocument ^document = gcnew XmlDocument();
		document->Load(readers);  */

#endif // VALIDATEXML
		//System::IO::Stream^ readStreamXML = System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream("ConfigurazioneProfiliVelocita.xml");

		//System::Xml::XmlReader ^reader = System::Xml::XmlReader::Create(readStreamXML);

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
