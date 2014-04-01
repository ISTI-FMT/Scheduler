#include "stazione.h"

stazione::stazione(void)
{
	nomeStazione = gcnew String("");
	idStazione = 0;
	itinerari= gcnew Dictionary<int,List<Itinerario^>^ >;
	itinerariid= gcnew Dictionary<int,Itinerario^ >;
	binari = gcnew List<binario^>();

}

System::String^ stazione::ToString() {
	String ^out="Station Name:"+get_NomeStazione()+"Station id:"+get_idStazione();
	for each( KeyValuePair<int , List<Itinerario^>^> kvp in itinerari )
	{

		out+=" "+ kvp.Key+"\n\r";

		for each (Itinerario ^dvar in kvp.Value)
		{
			out+= dvar->ToString();
		}


	}
	for each (KeyValuePair<int,Itinerario^ > ^kvp in itinerariid)
	{
		out+=" "+ kvp->Key+"\n\r";

		out+=" "+ kvp->Value+"\n\r";


	}
	for each (binario ^var in binari)
	{
		out+=" "+ var->ToString()+"\n\r";
	}




	return out;
}