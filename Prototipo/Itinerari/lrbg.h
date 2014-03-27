#pragma once
#using <System.dll>
using namespace System;
using namespace System::Collections::Generic;

/*Questa classe contiene le informazioni sulle last relevant balise group. Contiene l'identificativo,
la distanza dalla fermata e una mappa di riferimenti kilometrici riferiti ad una stazione di riferimento*/
public ref class lrbg
{
	/*<lrgb nid="105" dstop="150" >
          <pkm km="150" idoffstaz="13000"/>
      </lrgb>*/
	int nid;
	int dstop;

	Dictionary<int,int> ^pkmetricaVsStation;
public:
	lrbg(void);
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
	Dictionary<int,int>^ get_progressivakmD(){return pkmetricaVsStation;};
	virtual System::String^ ToString() override;
};

