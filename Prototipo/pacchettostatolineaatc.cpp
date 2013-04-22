#include "pacchettostatolineaatc.h"
#include "pacchettoAcknowledgement.h"
#include "utility.h"

pacchettostatolineaatc::pacchettostatolineaatc(void)
{
	data.head.NID_MESSAGE = 0;
	data.head.L_MESSAGE = 0;
	data.head.T_TRAIN = 0;
	
	data.pkg.NID_PACKET = 0;
	data.pkg.L_PACKET = 0;
	data.pkg.NID_OPERATIONAL = 0;
	data.pkg.pstato.NID_CDB = 0;
	data.pkg.pstato.Q_STATOCDB = 0;
	data.pkg.pstato.Q_DEVIATIOIO = 0;
	data.pkg.pstato1 = NULL;
}
