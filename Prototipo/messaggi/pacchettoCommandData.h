#pragma once
#include "utility.h"
#include "pacchettoBase.h"

/*
Rappresenta le informazioni contenute nel pacchetto Command Data che l'ATS invia dal ATO nel messaggio di Unconditional Command
*/
public enum class QCmdData{ WAKE_UP = 0, Door = 2,  CHANGE_GOA_LEVEL = 3,TRN=4,SLEEP=7 };
public enum class GOA_LEVEL{ Level_1 = 0, Level_2 = 1,  Level_3 =2,Level_4=3 };
public ref class pacchettoCommandData : pacchettoBase
{
	int L_PACKET;
	int Q_COMMAND_TYPE;
	int M_GOA_LEVEL;
	int NID_OPERATIONAL ;
	int PADDING;

public:
	pacchettoCommandData(void);

	virtual int getSize() override
	{
		//header 51 mess +24 fissi o+2 o +32
		if(getQ_COMMAND_TYPE()==(int)QCmdData::CHANGE_GOA_LEVEL){
			return 26;
		}
		if(getQ_COMMAND_TYPE()==(int)QCmdData::TRN){
			return 56;
		}
		if(getQ_COMMAND_TYPE()==(int)QCmdData::Door){
			return 28;
		}
		return 24;
	};
	
	void setL_PACKET(int L){L_PACKET = L;};
	int getL_PACKET(){return L_PACKET;};

	void setQ_COMMAND_TYPE(QCmdData Q){Q_COMMAND_TYPE = (int)Q;};
	int getQ_COMMAND_TYPE(){return Q_COMMAND_TYPE;};

	void setM_GOA_LEVEL(GOA_LEVEL M){M_GOA_LEVEL =(int) M;};
	int getM_GOA_LEVEL(){return M_GOA_LEVEL;};

	void setNID_OPERATIONAL(int NID){NID_OPERATIONAL = NID;};
	int getNID_OPERATIONAL(){return NID_OPERATIONAL;};

	virtual void serialize(array<Byte>^buffer, int offset) override;
	virtual void deserialize(array<Byte>^buff, int offset) override;
	
	virtual System::String ^ToString() override;

	
};

