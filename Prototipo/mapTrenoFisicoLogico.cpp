#include "mapTrenoFisicoLogico.h"
#using <System.Xml.dll>
using namespace System;
using namespace System::Collections::Generic;




mapTrenoFisicoLogico::mapTrenoFisicoLogico(void)
{
	map = gcnew Dictionary<int, int>();
}

mapTrenoFisicoLogico::mapTrenoFisicoLogico(System::String^ s)
{
	map = gcnew Dictionary<int, int>();
	inizializza(s);
}


void mapTrenoFisicoLogico::inizializza(System::String^ s){
	try{
		System::Xml::XmlReader ^reader = System::Xml::XmlReader::Create(s);
		while (reader->ReadToFollowing("map")){
			System::Xml::XmlReader ^inner = reader->ReadSubtree();

			while (inner->ReadToFollowing("map")){

				inner->ReadToFollowing("idtrenologico");
				int logico  = System::Int32::Parse( inner->ReadString());
				inner->ReadToFollowing("idtrenofisico");
				int fisico  = System::Int32::Parse( inner->ReadString());
				inner->ReadToFollowing("cdbpos");
				int cdbpos  = System::Int32::Parse( inner->ReadString());


				if (!map->ContainsKey(logico)){
					map->Add(fisico,logico);
				}

				System::Console::WriteLine("Letti idlogico: {0} idfisico: {1}",logico, fisico);

				//std::string stdString = msclr::interop::marshal_as< std::string >( trn);
				//std::cout<<stdString;
			}
		}
	}catch(Exception ^e){
		Console::WriteLine(e->Message);
	}
}

 