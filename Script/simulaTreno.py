#!/usr/bin/python
import random
import time
import os
import sys
import csv
from datetime import datetime
import fileinput
import socket
import re
from array import array
import thread

SendUDP_IP = "127.0.0.1"
ReceiveTCP_IP = "127.0.0.1"
SendTCP_IP = "127.0.0.1"
def enum(**enums):
    return type('Enum', (object,), enums)

MessATC=enum   (StatoLineaATC = 11,  FaultReportingATC = 12 );
MessIXL =enum  ( StatoLineaIXL = 1,  FaultReportingIXL = 211 , ComandoItinerari = 10, ComandoBlocco=231);
MessATO = enum( MissionPlan = 200,  FaultReportingATO = 213, UnconditionCommand=201, Acknol=210,Presentation=215 )


if len(sys.argv) < 2:
    print "script.py <namefile>"
    exit(1)
	
	
def serverTCP(host, port,ACK):
	while 1:
		s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		s.bind((host, port))
		s.listen(1)
		conn, addr = s.accept()
		print "##########################CAMBIO MISSION###############################"
		print 'CAMBIO MISSION Connection address:', addr
		data = conn.recv(86)
		if not data: break
		#print "received data:", data
		buffer3 = map(ord,data)
		print "CAMBIO MISSION received data:", deserializzaMissionDATA(buffer3)
		conn.send(ACK)
		#conn.close()
		#s.close()
		print "##########################END MISSION###############################"		# echo
		#conn.close()



def date_key(row):
        return datetime.strptime(row[2].strip(), "%d-%m-%Y %H:%M")
		
def setbit(buf, offset):
  Byteoffset = offset/8;
  bitoffset = offset%8;
  workByte= buf[Byteoffset];
  masks = [128,64,32,16,8,4,2,1]; 
  workByte = workByte | masks[bitoffset];
  buf[Byteoffset]=workByte;



def push (buf,  data, len,  off):
   work=data;
   for i in xrange(0, len):
     if (work%2==1):
       setbit(buf, off+len-1-i);
     work=work/2;

def getbit(buf, offset):
  Byteoffset = offset/8;
  bitoffset = offset%8;
  workByte= buf[Byteoffset];
  masks = [128,64,32,16,8,4,2,1]; 
  res = (workByte & masks[bitoffset]) != 0;
  return res;



def pop (buf, len, off):
   work=getbit(buf,off);
   for i in xrange(1, len):
       work = work*2 +getbit(buf,off+i);
   return work;

   
def sendUDP(message, UDP_PORT):
	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
	sock.sendto( message, (SendUDP_IP, UDP_PORT))

def sendTCP(MESSAGE):
	TCP_PORT = 13000
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # UDP
	sock.connect((SendTCP_IP, TCP_PORT))
	sock.send(MESSAGE)
	sock.close()

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
	tNID_LRGB=pop(buf, 24, offset);
	offset += 24;
	tD_STOP=pop(buf, 15, offset);
	offset += 15;
	tQ_DOORS=pop(buf, 4, offset);
	offset += 4;
	tT_DOORS_TIME=pop(buf, 12, offset);
	mS2_vect=[]
	mS2_vect.append([tT_START_TIME,tNID_LRGB,tD_STOP,tQ_DOORS,tT_DOORS_TIME]);
	offset += 12;
	N_ITER2 =pop(buf, 5, offset);
	offset += 5;
	for i in range(0,N_ITER2-1):
		T_START_TIME=pop(buf, 12, offset);
		offset += 12;
		NID_LRGB=pop(buf, 24, offset);
		offset += 24;
		D_STOP=pop(buf, 15, offset);
		offset += 15;
		Q_DOORS=pop(buf, 4, offset);
		offset += 4;
		T_DOORS_TIME=pop(buf, 12, offset);
		offset += 12;
		mS2_vect.append([T_START_TIME,NID_LRGB,D_STOP,Q_DOORS,T_DOORS_TIME])
	return mS2_vect

	
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
	

def ReceiveTCP(TCP_PORT, ACK):
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # UDP
	sock.bind((ReceiveTCP_IP, TCP_PORT))
	sock.listen(3)
	conn, addr = sock.accept()
	print 'Connection address:', addr
	MESSAGE1 = conn.recv(10)
	print 'Prima ricezione: ',MESSAGE1
	MESSAGE2 = conn.recv(14)
	print 'Seconda ricezione: ',MESSAGE2
	MESSAGE3 = conn.recv(2048)
	print 'Terza ricezione: ',MESSAGE3
	print len(ACK)
	conn.send(ACK)  # echo
	conn.close()
	sock.close()
	buffer1 = map(ord,MESSAGE1)
	deserializzaCommandDATA(buffer1)
	buffer2 = map(ord,MESSAGE2)
	print "lenb",len(buffer2)
	NID_OPERATIONAL = deserializzaCommandDATA(buffer2)
	buffer3 = map(ord,MESSAGE3)
	print "received data:", deserializzaMissionDATA(buffer3)
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
'''
my_array = array('I',[int('0B',16),int('04',16),int('80',16),int('00',16),int('00',16),int('0E',16),int('61',16),int('00',16),int('E5',16),int('00',16),int('00',16),int('04',16),int('80',16),int('00',16),int('00',16),int('1A',16),int('C6',16),int('00',16),int('00',16),int('33',16),int('F5',16),int('00',16),int('01',16),int('00',16),int('00',16),int('04',16),int('81',16),int('00',16),int('00',16),int('1B',16),int('28',16),int('00',16),int('00',16),int('2C',16),int('25',16),int('00',16)])


NID_MESSAGE= pop(my_array, 8, 0);
L_MESSAGE=pop(my_array,11, 8);
T_TIME=pop(my_array, 32, 19);
NID_PACKET=pop(my_array,  8, 51);
L_PACKET=pop(my_array, 13, 59);
tNID_ENGINE =pop(my_array, 32, 72);
tNID_OPERATIONAL =pop(my_array, 32, 104);
tNID_CDB =pop(my_array, 32, 136);

print NID_MESSAGE
print L_MESSAGE
print T_TIME
print NID_PACKET
print L_PACKET
print tNID_ENGINE
print tNID_OPERATIONAL
print tNID_CDB
'''

spamReader = list(csv.reader(open(sys.argv[1],'U'), delimiter=';'))
NID_ENGINE = int(spamReader[0][0],10)
M_PORT = int(spamReader[0][1],10)
del spamReader[0][0]
del spamReader[0][0]

print "Sono il TRENO: ", NID_ENGINE
#13301;13012;13011;13010;501;14020;14021;14022;14301;14012;14011;14010;502;15020;15021;15022;15301;15012;15011;503;12010;12011;12012;12301;12026;12025;12024;400;402;404;406;408;410;412;414;416;418;420;422;424;426;428;16020;16021;16022;16023;16302;16016;16015;16014;16013;440;442;444;446;448;17010;17011;17012;17013;17014;17302;17016;17018;17020
NID_OPERATIONAL=0
bandiera=True
if(sys.argv[2]=='1'):
	bandiera=False
	op = sys.argv[1][18:22]
	NID_OPERATIONAL=int(op)
	

########## MOVIMENTO VS RBC inizializzazione ######

sendBytes = bytearray([0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0])
push(sendBytes, 18, 8, 0); #//nid_msg
push(sendBytes, 12, 10, 8); #//L_msg
push(sendBytes, 5555, 32, 18); #//T_msg
push(sendBytes, NID_ENGINE, 32, 50); #//nid_op
NID_CDB =  int(spamReader[0][0],10)
push(sendBytes,NID_CDB, 32, 82);#//nid_cdb
print "Sono sul CDB1: ",spamReader[0][0]
sendUDP(sendBytes,302)
buff = messageRBC_new(NID_ENGINE,NID_OPERATIONAL,NID_CDB)
#for i in range(0,70):
sendUDP(buff,1111)
sendUDP(buff,1111)
sendUDP(buff,1111)


#####PRESENTAZIONE VS ATS #########
#115;16;258;65280;25;53;3610 Presentazione


if bandiera==True:
	try:
		sendBytesP = bytearray([0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0])
		push(sendBytesP, MessATO.Presentation, 8, 0); #//nid_msg
		push(sendBytesP, 16, 11, 8); #//L_msg
		push(sendBytesP, 5555, 32, 19); #//T_msg
		push(sendBytesP, 25, 8, 75);
		push(sendBytesP, NID_ENGINE, 24, 51); #//nid_op
		push(sendBytesP, 56, 13, 83);
		push(sendBytesP, M_PORT, 24, 96);
		print "Invio Presentazione"
		sendTCP(sendBytesP)
		print "Ricevo Wake-up TRN MISSION"
		
		NID_OPERATIONAL = ReceiveTCP(M_PORT,sendACk(NID_ENGINE))
		print NID_OPERATIONAL
		####ASCOLTO TCP
		thread.start_new_thread(serverTCP, (ReceiveTCP_IP, M_PORT,sendACk(NID_ENGINE)))
	except socket.error as msg:
        #sock.close() 
		print "Nessuna Presentazione Eseguita, Avvia lo Scheduler",msg


#exit(0)

####### MOVIMENTO VS RBC NEXT MOV######
for line in spamReader:
	for element in line:
		sendBytes = bytearray([0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0])
		push(sendBytes, 18, 8, 0); #//nid_msg
		push(sendBytes, 12, 10, 8); #//L_msg
		push(sendBytes, 5555, 32, 18); #//T_msg
		push(sendBytes, NID_ENGINE, 32, 50); #//nid_op
		NID_CDB =  int(element,10)
		push(sendBytes,NID_CDB, 32, 82);#//nid_cdb
		print "Sono sul CDB: ",element
		sendUDP(sendBytes,302)
		buff = messageRBC_new(NID_ENGINE,NID_OPERATIONAL,NID_CDB)
		#for i in range(0,70):
		sendUDP(buff,1111)
			#time.sleep(0.1)
		raw_input("-->> PRESS ENTER <<<--- ")
		

exit(0)
sendBytes = raw_input("Enter something: ")

 





