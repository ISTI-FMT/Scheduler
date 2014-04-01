#include "lrbg.h"


lrbg::lrbg(int nid, int ds)
{
	nid_lrgb=nid;
	d_stop=ds;
	pkmetricaVsStation = gcnew Dictionary<int,int>();
}
lrbg::lrbg(void)
{
	nid_lrgb=0;
	d_stop=0;
	pkmetricaVsStation = gcnew Dictionary<int,int>();
}

void lrbg::add_progressivakm(int km, int offstation){

	pkmetricaVsStation->Add(offstation,km);
}


int lrbg::get_progressivakm(int offsetStation){
	if(pkmetricaVsStation->ContainsKey(offsetStation)){
		return pkmetricaVsStation[offsetStation];
	}else{

		return -1;
	}
}

System::String^ lrbg::ToString(){
	String ^out="";
	out+=" nid_lrgb: "+nid_lrgb;
	out+=" d_stop: "+d_stop;
	for each (int var in get_progressivakmD()->Keys)
	{
		out+=" km_lrgb:  "+get_progressivakmD()[var]+" from: "+var;
	}
	return out;
}

