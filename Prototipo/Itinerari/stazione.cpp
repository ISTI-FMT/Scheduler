#include "stazione.h"

stazione::stazione(void)
{
	nomeStazione = gcnew String("");
	idStazione = 0;
	itinerari= gcnew Dictionary<int,List<Itinerario^>^ >;
	itinerariid= gcnew Dictionary<int,Itinerario^ >;

}

System::String^ stazione::ToString() {
	String ^out="";
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




	return out;
}