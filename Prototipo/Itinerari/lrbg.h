#pragma once
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;
ref class lrbg
{
	/*<lrgb nid="105" dstop="150" >
          <pkm km="150" idoffstaz="13000"/>
      </lrgb>*/
	int nid;
	int dstop;
	Dictionary<int,int> ^pkmetricaVsStation;
public:
	lrbg(int nid,int ds);
	property int nid_lrgb 
	{
		int get()
		{
			return nid;
		}
		void set(int val){
			nid=val;
		}
	}
	property int d_stop
	{
		int get()
		{
			return dstop;
		}
		void set(int val){
			dstop=val;
		}
	}

	void add_progressivakm(int km, int offstation);
	int get_progressivakm(int offsetStation);

};

