#include "stazione.h"

stazione::stazione(void)
{
	nomeStazione = gcnew String("");
	idStazione = 0;
	itinerari= gcnew Dictionary<String^,List<Itinerario^>^ >;

}

System::String^ stazione::ToString() {
	String ^out="";
	for each( KeyValuePair<String ^ , List<Itinerario^>^> kvp in itinerari )
	{

		out+=" "+ kvp.Key+"\n\r";

		for each (Itinerario ^dvar in kvp.Value)
		{
			out+= dvar->ToString();
		}


	}
	return out;
}