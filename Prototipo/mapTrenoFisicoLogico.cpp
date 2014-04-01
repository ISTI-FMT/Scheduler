#include "mapTrenoFisicoLogico.h"
#using <System.Xml.dll>
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Xml;
using namespace System::Xml::Schema;



mapTrenoFisicoLogico::mapTrenoFisicoLogico(void)
{
	map = gcnew Dictionary<int, TrenoFisicoLogico^>();
	inizializza();
}



void mapTrenoFisicoLogico::inizializza(){
	try{

		System::IO::Stream^ readStreamschemaxsd = System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream("MapTreni.xsd");
		// Create the XmlSchemaSet class.
		XmlSchemaSet^ sc = gcnew XmlSchemaSet;

		// Add the schema to the collection.
		sc->Add( "urn:conftrenofisicoTreni-schema",  gcnew XmlTextReader (readStreamschemaxsd) );
		XmlReaderSettings^ settings = gcnew XmlReaderSettings;
		settings->ValidationType = System::Xml::ValidationType::Schema;
		settings->Schemas = sc;

		System::IO::Stream^ readStreamXML = System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream("MapTreni.xml");
		System::Xml::XmlReader ^reader = System::Xml::XmlReader::Create(readStreamXML,settings);
		reader->ReadToFollowing("bind");
		while (reader->ReadToFollowing("trenofisico")){
			int engineTreno = int::Parse(reader->GetAttribute("engine_nbr"));
			reader->ReadToFollowing("trenilogici");
			System::Xml::XmlReader ^inner = reader->ReadSubtree();
			List<int> ^trns = gcnew List<int>();
			while (inner->ReadToFollowing("idtrenologico")){


				int logico  = System::Int32::Parse( inner->ReadString());
				trns->Add(logico);
			}
			reader->ReadToFollowing("cdblastpos");
			int cdbpos  = System::Int32::Parse( reader->ReadString());


			if (!map->ContainsKey(engineTreno)){
				map->Add(engineTreno,gcnew TrenoFisicoLogico(engineTreno,trns,cdbpos));
			}

			System::Console::WriteLine("Letti idlogico: {0} idfisico: {1} in Pos: {2}",engineTreno,trns[0], cdbpos);

			//std::string stdString = msclr::interop::marshal_as< std::string >( trn);
			//std::cout<<stdString;

		}
	}catch(Exception ^e){
#ifdef TRACE
		Logger::Exception(e,"mapTrenoFisicoLogico");  
#endif // TRACE
		Console::WriteLine(e->Message);
	}
}




void mapTrenoFisicoLogico::saveXml(System::IO::Stream ^stream){
	try{
		System::Xml::XmlWriterSettings ^settings = gcnew System::Xml::XmlWriterSettings();
		settings->Indent = true;
		System::Xml::XmlWriter ^writer =System::Xml::XmlWriter::Create(stream,settings);

		writer->WriteStartDocument();
		writer->WriteStartElement("bind");
		for each( KeyValuePair<int , TrenoFisicoLogico^> ^kvp in map )
		{
			writer->WriteStartElement("trenofisico");
			writer->WriteAttributeString("engine_nbr",kvp->Key.ToString());

			TrenoFisicoLogico ^dvar =kvp->Value;
			writer->WriteStartElement("trenilogici");
			for each (int var in dvar->getIdTrenoListTreniLogici())
			{
				writer->WriteElementString("idtrenologico", var.ToString());
			}
			writer->WriteElementString("cdblastpos", dvar->getCDBLastPosition().ToString());
			writer->WriteEndElement();
		}
		writer->WriteEndElement();
		writer->WriteEndDocument();
		writer->Close();
	}catch(Exception ^e){
#ifdef TRACE
		Logger::Exception(e,"mapTrenoFisicoLogico");  
#endif // TRACE
		Console::WriteLine(e->Message);
	}
}