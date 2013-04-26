#include "proveSerializzazione.h"
#include <iostream>
using namespace std;
proveSerializzazione::proveSerializzazione(void)
{
}

void proveSerializzazione::provaSerializePacchettostatolineaatc(pacchettostatolineaatc &pkt, int index)
{
/*	int NID_MESSAGE, L_MESSAGE, T_TRAIN, NID_PACKET, L_PACKET, NID_OPERATIONAL, NID_CDB,N_ITER,Q_DEVIATIOIO,Q_STATOCDB;
	cout << "Insert NID_MESSAGE" << endl;
	cin >> NID_MESSAGE;
	pkt.setNID_MESSAGE(NID_MESSAGE);
	cout << "Insert L_MESSAGE" << endl;
	cin >> L_MESSAGE;
	pkt.setL_MESSAGE(L_MESSAGE);
	cout << "Insert T_TRAIN" << endl;
	cin >> T_TRAIN;
	pkt.setT_TRAIN(T_TRAIN);
	cout << "Insert NID_PACKET" << endl;
	cin >> NID_PACKET;
	pkt.setNID_PACKET(NID_PACKET);
	cout << "Insert L_PACKET" << endl;
	cin >> L_PACKET;
	pkt.setL_PACKET(L_PACKET);

	cout << "Insert NID_OPERATIONAL" << endl;
	cin >> NID_OPERATIONAL;
	pkt.setNID_OPERATIONAL(NID_OPERATIONAL);

	cout << "Insert N_ITER" << endl;
	cin >> N_ITER;
	pkt.setN_ITER(N_ITER);

	cout << "Insert NID_CDB" << endl;
	cin >> NID_CDB;
	pkt.setNID_CDB(index, NID_CDB);
	cout << "Insert Q_STATOCDB" << endl;
	cin >> Q_STATOCDB;
	pkt.setQ_STATOCDB(index,Q_STATOCDB);
	cout << "Insert Q_DEVIATIOIO" << endl;
	cin >> Q_DEVIATIOIO;
	pkt.setQ_DEVIATIOIO(index, Q_DEVIATIOIO);

	

	
	*/
}



void  proveSerializzazione::provaSerializePacchettoPresentazione(pacchettopresentazione &pkt)
{
	/*int NID_MESSAGE, L_MESSAGE, T_TRAIN, NID_PACKET, L_PACKET, N_PORT,NID_ENGINE;
	cout << "Insert NID_MESSAGE" << endl;
	cin >> NID_MESSAGE;
	pkt.setNID_MESSAGE(NID_MESSAGE);
	cout << "Insert L_MESSAGE" << endl;
	cin >> L_MESSAGE;
	pkt.setL_MESSAGE(L_MESSAGE);
	cout << "Insert T_TRAIN" << endl;
	cin >> T_TRAIN;
	pkt.setT_TRAIN(T_TRAIN);

	cout << "Insert NID_ENGINE" << endl;
	cin >> NID_ENGINE;
	pkt.setNID_ENGINE(NID_ENGINE);


	cout << "Insert NID_PACKET" << endl;
	cin >> NID_PACKET;
	pkt.setNID_PACKET(NID_PACKET);
	cout << "Insert L_PACKET" << endl;
	cin >> L_PACKET;
	pkt.setL_PACKET(L_PACKET);
	cout << "Insert M_PORT" << endl;
	cin >> N_PORT;
	pkt.setM_PORT(N_PORT);*/
	
}

void  proveSerializzazione::provaSerializePacchettoack(pacchettoAcknowledgement &pkt)
{
	/*int NID_MESSAGE, L_MESSAGE, T_TRAIN, NID_PACKET, L_PACKET, Q_MISSION;
	cout << "Insert NID_MESSAGE" << endl;
	cin >> NID_MESSAGE;
	pkt.setNID_MESSAGE(NID_MESSAGE);
	cout << "Insert L_MESSAGE" << endl;
	cin >> L_MESSAGE;
	pkt.setL_MESSAGE(L_MESSAGE);
	cout << "Insert T_TRAIN" << endl;
	cin >> T_TRAIN;
	pkt.setT_TRAIN(T_TRAIN);
	cout << "Insert NID_PACKET" << endl;
	cin >> NID_PACKET;
	pkt.setNID_PACKET(NID_PACKET);
	cout << "Insert L_PACKET" << endl;
	cin >> L_PACKET;
	pkt.setL_PACKET(L_PACKET);
	cout << "InsertQMission" << endl;
	cin >> Q_MISSION;
	pkt.setQ_MISSION_RESPONSE(Q_MISSION);*/
	
}
void  proveSerializzazione::provaSerializePacchettoCommandData1(pacchettoCommandData &pkt)
{
	/*int NID_MESSAGE, L_MESSAGE, T_TRAIN, NID_PACKET, L_PACKET, Q_COMMAND_TYPE;
	cout << "Insert NID_MESSAGE" << endl;
	cin >> NID_MESSAGE;
	pkt.setNID_MESSAGE(NID_MESSAGE);
	cout << "Insert L_MESSAGE" << endl;
	cin >> L_MESSAGE;
	pkt.setL_MESSAGE(L_MESSAGE);
	cout << "Insert T_TRAIN" << endl;
	cin >> T_TRAIN;
	pkt.setT_TRAIN(T_TRAIN);
	cout << "Insert NID_PACKET" << endl;
	cin >> NID_PACKET;
	pkt.setNID_PACKET(NID_PACKET);
	cout << "Insert L_PACKET" << endl;
	cin >> L_PACKET;
	pkt.setL_PACKET(L_PACKET);
	cout << "Insert Q_COMMAND_TYPE" << endl;
	cin >> Q_COMMAND_TYPE;
	pkt.setQ_COMMAND_TYPE(Q_COMMAND_TYPE);*/
	//byte buff[100];
	//for(int i = 0; i < 100; ++i)
	//	buff[i] = 0;
	//int len = 0;
	//pkt.serializepacchettoCommandData(buff);
	//stampaBuffer(buff, 80);
}
