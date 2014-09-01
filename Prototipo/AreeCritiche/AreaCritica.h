#using <System.dll>

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

/*
* Questa classe descrive una area critica e contiene metodi per aggiungere/rimuovere treni dall'area e controllare se 
* ha già raggiunto la capienza massima
*/

enum AreaCriticaDirezione {Sinistra, Destra};

#pragma once
public ref class AreaCritica abstract
{
public:
	System::String ^nome;
	/* Ritorna TRUE se l'area contiene già il numero massimo di treni */
	virtual bool entrataPermessa(int idTreno, int cdb, int tipoEntrata) abstract;
	virtual void entrata(int idTreno, int cdb, int tipoEntrata) abstract;
	virtual bool isInside(int trn) abstract;
};

