#include "lrbg.h"


lrbg::lrbg(int nid, int ds)
{
	nid_lrgb=nid;
	d_stop=ds;
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


