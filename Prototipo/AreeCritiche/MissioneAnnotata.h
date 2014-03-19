#pragma once

using namespace System;
using namespace System::Collections::Generic;

public ref class MissioneAnnotata
{
public:
	List<int>^ ListaCdb;
	List<array<int>^>^ AzioniCdb;
	String^ Trn;
	MissioneAnnotata(void)
	{
		ListaCdb = gcnew List<int>();
		AzioniCdb = gcnew List<array<int>^>();
	}
};