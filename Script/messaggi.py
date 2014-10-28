'''
Created on 11/mar/2014

@author: isiu
'''
def enum(**enums):
    return type('Enum', (object,), enums)

MessATC=enum   (StatoLineaATC = 11,  FaultReportingATC = 12 );
MessIXL =enum  ( StatoLineaIXL = 1,  FaultReportingIXL = 211 , ComandoItinerari = 10, ComandoBlocco=231);
MessATO = enum( MissionPlan = 200,  FaultReportingATO = 213, UnconditionCommand=201, Acknol=210,Presentation=215 )


def deserializzaStatoLineaIXL(buf):
	dictcdb = {}
	
	NID_MESSAGE= pop(buf, 8, 0);
	L_MESSAGE=pop(buf,11, 8);
	T_TIME=pop(buf, 32, 19);
	NID_PACKET=pop(buf,  8, 51);
	L_PACKET=pop(buf, 13, 59);
	offset=59+13
	tNID_CDB =pop(buf, 32, offset);
	offset += 32;
	tQ_STATOCDB =pop(buf, 2, offset);
	offset += 2;
	tQ_DEVIATOIO =pop(buf, 2, offset);
	offset += 2;
	cdb = [tNID_CDB,tQ_STATOCDB,tQ_DEVIATOIO]
	dictcdb[tNID_CDB] = cdb
	N_ITER = pop(buf, 16, offset)
	offset += 16;
	for i in range(0,N_ITER):
		NID_CDB=pop(buf, 32, offset);
		offset += 32;
		Q_STATOCDB=pop(buf, 2, offset);
		offset += 2;
		Q_DEVIATOIO=pop(buf, 2, offset);
		offset += 2;
		cdb = [NID_CDB,Q_STATOCDB,Q_DEVIATOIO]
		dictcdb[NID_CDB] = cdb
	return dictcdb
    

def deserializzaStatoLineaIXL2(buf):
    dictcdb = []
    NID_MESSAGE= pop(buf, 8, 0);
    L_MESSAGE=pop(buf,11, 8);
    T_TIME=pop(buf, 32, 19);
    NID_PACKET=pop(buf,  8, 51);
    L_PACKET=pop(buf, 13, 59);
    offset=59+13
    tNID_CDB =pop(buf, 32, offset);
    offset += 32;
    tQ_STATOCDB =pop(buf, 2, offset);
    offset += 2;
    tQ_DEVIATOIO =pop(buf, 2, offset);
    offset += 2;
    cdb = [tNID_CDB,tQ_STATOCDB,tQ_DEVIATOIO]
    dictcdb.append(cdb)
    N_ITER = pop(buf, 16, offset)
    offset += 16;
    for i in range(0,N_ITER):
        NID_CDB=pop(buf, 32, offset);
        offset += 32;
        Q_STATOCDB=pop(buf, 2, offset);
        offset += 2;
        Q_DEVIATOIO=pop(buf, 2, offset);
        offset += 2;
        cdb = [NID_CDB,Q_STATOCDB,Q_DEVIATOIO]
        dictcdb.append(cdb)
    return dictcdb    
    

def deserializzaMissionDATA(buf):
    NID_MESSAGE= pop(buf, 8, 0);
    L_MESSAGE=pop(buf,11, 8);
    T_TIME=pop(buf, 32, 19);
    NID_PACKET=pop(buf,  8, 51);
    L_PACKET=pop(buf, 13, 59);
    Q_SCALE=pop(buf, 2, 72);
    tD_MISSION =pop(buf, 15, 74);
    tV_MISSION =pop(buf, 7, 89);
    N_ITER1 = pop(buf, 5, 96);
    offset = 101;
    mS1_vect =[]
    for i in range(0, N_ITER1):
        D_MISSION=pop(buf, 15, offset);
        offset += 15;
        V_MISSION=pop(buf, 7, offset);
        offset += 7;
        mS1_vect.append([D_MISSION,V_MISSION])
    tT_START_TIME=pop(buf, 12, offset);
    offset += 12;
    tD_LRGB=pop(buf, 15, offset);
    offset += 15;
    tNID_LRGB=pop(buf, 24, offset);
    offset += 24;
    tD_STOP=pop(buf, 15, offset);
    offset += 15;
    tQ_DOORS=pop(buf, 4, offset);
    offset += 4;
    tT_DOORS_TIME=pop(buf, 12, offset);
    mS2_vect=[]
    mS2_vect.append([tT_START_TIME,tD_LRGB,tNID_LRGB,tD_STOP,tQ_DOORS,tT_DOORS_TIME]);
    offset += 12;
    N_ITER2 =pop(buf, 5, offset);
    offset += 5;
    for i in range(0,N_ITER2-1):
        T_START_TIME=pop(buf, 12, offset);
        offset += 12;
        tD_LRGB=pop(buf, 15, offset);
        offset += 15;
        NID_LRGB=pop(buf, 24, offset);
        offset += 24;
        D_STOP=pop(buf, 15, offset);
        offset += 15;
        Q_DOORS=pop(buf, 4, offset);
        offset += 4;
        T_DOORS_TIME=pop(buf, 12, offset);
        offset += 12;
        mS2_vect.append([T_START_TIME,tD_LRGB,NID_LRGB,D_STOP,Q_DOORS,T_DOORS_TIME])
    return mS2_vect

def messPres(NID_ENGINE,M_PORT):
    sendBytesP = bytearray([0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0])
    push(sendBytesP, MessATO.Presentation, 8, 0); #//nid_msg
    push(sendBytesP, 16, 11, 8); #//L_msg
    push(sendBytesP, 5555, 32, 19); #//T_msg
    push(sendBytesP, 25, 8, 75);
    push(sendBytesP, NID_ENGINE, 24, 51); #//nid_op
    push(sendBytesP, 56, 13, 83);
    push(sendBytesP, M_PORT, 24, 96);
    return sendBytesP
    

def creamovimento(cdb,NID_ENGINE):
    sendBytes = bytearray([0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0])
    push(sendBytes, 10, 8, 0); #//nid_msg
    push(sendBytes, 12, 10, 8); #//L_msg
    push(sendBytes, 5555, 32, 18); #//T_msg
    push(sendBytes, NID_ENGINE, 32, 50); #//nid_op
    NID_CDB =  int(cdb,10)
    push(sendBytes,NID_CDB, 32, 82);#//nid_cdb
    print "Sono sul CDB: ",cdb
    return sendBytes


def deserializzaCommandDATA(buff):
    NID_MESSAGE= pop(buff, 8, 0);
    L_MESSAGE=pop(buff,11, 8);
    T_TIME=pop(buff, 32, 19);
    NID_PACKET=pop(buff,  8, 51);
    L_PACKET=pop(buff, 13, 59);
    Q_COMMAND_TYPE=pop(buff,3, 72);
    if(Q_COMMAND_TYPE==3):
        M_GOA_LEVEL=pop(buff, 2, 75);
    NID_OPERATIONAL=0
    if(Q_COMMAND_TYPE==4):
        NID_OPERATIONAL=pop(buff, 32, 75);
        print "received data: "+"NID_MESSAGE: "+str(NID_MESSAGE)+" NID_PACKET: "+str(NID_PACKET)+" Q_COMMAND_TYPE: "+str(Q_COMMAND_TYPE)+" NID_OPERATIONAL: "+str(NID_OPERATIONAL)
    return NID_OPERATIONAL
    

    
def messageRBC(NID_ENGINE,NID_OPERATIONAL,NID_CDB):
    buff = bytearray([0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0])
    push(buff, MessATC.StatoLineaATC, 8, 0); #//nid_msg
    push(buff, 17, 11, 8); #//L_msg
    push(buff, 32, 32, 19); #//T_msg
    push(buff, 141, 8, 51);
    push(buff, 11, 13, 59);
    push(buff,  NID_ENGINE, 32, 72);
    push(buff, NID_OPERATIONAL, 32, 104);
    push(buff, NID_CDB, 32, 136);
    push(buff, 0, 16, 168); #N_ITER
    return buff
    
def messageRBC_new(NID_ENGINE,NID_OPERATIONAL,NID_CDB):
    buff = bytearray([0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0])
    push(buff,  NID_ENGINE, 32, 0);
    push(buff, NID_OPERATIONAL, 32, 32);
    push(buff, NID_CDB, 32, 64);
    return buff
    

    
def des_messageRBC_new(buff):
    NID_ENGINE =pop(buff,   32, 0);
    NID_OPERATIONAL=pop(buff , 32, 32);
    NID_CDB=pop(buff, 32, 64);
    print str(NID_ENGINE)+" "+str(NID_OPERATIONAL)+" "+str(NID_CDB)
    return [NID_ENGINE,NID_OPERATIONAL,NID_CDB]

def messageRBC1(list):
    buff = bytearray([0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0])
    push(buff, MessATC.StatoLineaATC, 8, 0); #//nid_msg
    push(buff, 17, 11, 8); #//L_msg
    push(buff, 32, 32, 19); #//T_msg
    push(buff, 141, 8, 51);
    push(buff, 11, 13, 59);
    push(buff,  list[0][0], 32, 72);
    push(buff, list[0][1], 32, 104);
    push(buff, list[0][2], 32, 136);
    niter=len(list)-1
    push(buff,niter , 16, 168); #N_ITER
    offset = 184;
    for i in range(1,niter+1):
        push(buff,  list[i][0], 32, offset);
        offset+=32
        push(buff, list[i][1], 32, offset);
        offset+=32
        push(buff, list[i][2], 32, offset);
        offset+=32
    return buff    

    
def sendACk(NID_ENGINE):
    #110;17;32;65280;162;54;12;1 ACK
    buffer = bytearray([0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0])
    push(buffer, MessATO.Acknol, 8, 0); #//nid_msg
    push(buffer, 17, 11, 8); #//L_msg
    push(buffer, 32, 32, 19); #//T_msg
    push(buffer, NID_ENGINE, 24, 51); #//NID_ENGINE
    push(buffer,162 , 8, 75);#NID_PACKET
    push(buffer, 54, 13, 83);#L_PACKET
    push(buffer, 12, 32, 96);#T_TRAIN
    Q_MISSION_RESPONSE=1
    push(buffer, Q_MISSION_RESPONSE, 1, 128);
    return buffer

def push (buf,  data, leng,  off):
    work=data;
    for i in xrange(0, leng):
        if (work%2==1):
            setbit(buf, off+leng-1-i);
        work=work/2;

def getbit(buf, offset):
    Byteoffset = offset/8;
    bitoffset = offset%8;
    workByte= buf[Byteoffset];
    masks = [128,64,32,16,8,4,2,1]; 
    res = (workByte & masks[bitoffset]) != 0;
    return res;


def setbit(buf, offset):
    Byteoffset = offset/8;
    bitoffset = offset%8;
    workByte= buf[Byteoffset];
    masks = [128,64,32,16,8,4,2,1]; 
    workByte = workByte | masks[bitoffset];
    buf[Byteoffset]=workByte;


def pop (buf, leng, off):
    work=getbit(buf,off);
    for i in xrange(1, leng):
        work = work*2 +getbit(buf,off+i);
    return work;