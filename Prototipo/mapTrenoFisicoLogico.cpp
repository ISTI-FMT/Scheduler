#include "mapTrenoFisicoLogico.h"
#using <System.Xml.dll>
using namespace System;
using namespace System::Collections::Generic;




mapTrenoFisicoLogico::mapTrenoFisicoLogico(void)
{
	map = gcnew Dictionary<int, TrenoFisicoLogico^>();
	inizializza();
}



void mapTrenoFisicoLogico::inizializza(){
	try{
		System::IO::Stream^ readStreamXML = System::Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream("MapTreni.xml");
	
		System::Xml::XmlReader ^reader = System::Xml::XmlReader::Create(readStreamXML);
		while (reader->ReadToFollowing("map")){
			System::Xml::XmlReader ^inner = reader->ReadSubtree();

			while (inner->ReadToFollowing("map")){

				inner->ReadToFollowing("idtrenologico");
				int logico  = System::Int32::Parse( inner->ReadString());
				inner->ReadToFollowing("idtrenofisico");
				int fisico  = System::Int32::Parse( inner->ReadString());
				inner->ReadToFollowing("cdbpos");
				int cdbpos  = System::Int32::Parse( inner->ReadString());


				if (!map->ContainsKey(fisico)){
					map->Add(fisico,gcnew TrenoFisicoLogico(fisico,logico,cdbpos));
				}

				System::Console::WriteLine("Letti idlogico: {0} idfisico: {1} in Pos: {2}",logico, fisico, cdbpos);

				//std::string stdString = msclr::interop::marshal_as< std::string >( trn);
				//std::cout<<stdString;
			}
		}
	}catch(Exception ^e){
#ifdef TRACE
		Logger::Exception(e,"mapTrenoFisicoLogico");  
#endif // TRACE
		Console::WriteLine(e->Message);
	}
}

 