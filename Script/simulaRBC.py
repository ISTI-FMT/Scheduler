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

def enum(**enums):
    return type('Enum', (object,), enums)

MessATC=enum   (StatoLineaATC = 11,  FaultReportingATC = 12 );
MessIXL =enum  ( StatoLineaIXL = 1,  FaultReportingIXL = 211 , ComandoItinerari = 10, ComandoBlocco=231);
MessATO = enum( MissionPlan = 200,  FaultReportingATO = 213, UnconditionCommand=201, Acknol=210,Presentation=215 )

	
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
	UDP_IP = "127.0.0.1"
	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
	sock.sendto( message, (UDP_IP, UDP_PORT))

def sendTCP(MESSAGE):
	TCP_IP = "127.0.0.1"
	TCP_PORT = 13000
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # UDP
	sock.connect((TCP_IP, TCP_PORT))
	sock.send(MESSAGE)
	sock.close()


	
def deserializzaCommandDATA(buff):
	NID_MESSAGE= pop(buff, 8, 0);
	L_MESSAGE=pop(buff,11, 8);
	T_TIME=pop(buff, 32, 19);
	NID_PACKET=pop(buff,  8, 51);
	L_PACKET=pop(buff, 13, 59);
	Q_COMMAND_TYPE=pop(buff,3, 72);
	print Q_COMMAND_TYPE
	if(Q_COMMAND_TYPE==3):
		M_GOA_LEVEL=pop(buff, 2, 75);
	NID_OPERATIONAL=0
	if(Q_COMMAND_TYPE==4):
		NID_OPERATIONAL=pop(buff, 32, 75);
		print "received data: "+"NID_MESSAGE: "+str(NID_MESSAGE)+" NID_PACKET: "+str(NID_PACKET)+" Q_COMMAND_TYPE: "+str(Q_COMMAND_TYPE)+" NID_OPERATIONAL: "+str(NID_OPERATIONAL)
	return NID_OPERATIONAL
	


	
	
def messageRBC(NID_ENGINE,NID_OPERATIONAL,NID_CDB):
	buff = bytearray([0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0])
	push(buff, 11, 8, 0); #//nid_msg
	push(buff, 17, 11, 8); #//L_msg
	push(buff, 32, 32, 19); #//T_msg
	push(buff, 141, 8, 51);
	push(buff, 11, 13, 59);
	push(buff,  NID_ENGINE, 32, 72);
	push(buff, NID_OPERATIONAL, 32, 104);
	push(buff, NID_CDB, 32, 136);
	push(buff, 0, 16, 168); #N_ITER
	return buff
	
def des_messageRBC_new(buff):
	NID_ENGINE =pop(buff,   32, 0);
	NID_OPERATIONAL=pop(buff , 32, 32);
	NID_CDB=pop(buff, 32, 64);
	print str(NID_ENGINE)+" "+str(NID_OPERATIONAL)+" "+str(NID_CDB)
	return [NID_ENGINE,NID_OPERATIONAL,NID_CDB]

'''
def messageRBC_ST(buff,buff1):
	buff = bytearray([0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0])
	push(buff,  MessATC.StatoLineaATC, 8, 0); #//nid_msg
	push(buff, 17, 11, 8); #//L_msg
	push(buff, 32, 32, 19); #//T_msg
	push(buff, 141, 8, 51);
	push(buff, 11, 13, 59);
	NID_ENGINE =pop(buff,   32, 0);
	NID_OPERATIONAL=pop(buff , 32, 32);
	NID_CDB=pop(buff, 32, 64);
	push(buff,NID_ENGINE  , 32, 72);
	push(buff, NID_OPERATIONAL, 32, 104);
	push(buff, NID_CDB, 32, 136);
	niter=1
	push(buff,niter , 16, 168); #N_ITER
	NID_ENGINE =pop(buff1,   32, 0);
	NID_OPERATIONAL=pop(buff1 , 32, 32);
	NID_CDB=pop(buff1, 32, 64);
	offset = 184;
	push(buff,  list[i][0], 32, offset);
	offset+=32
	push(buff, list[i][1], 32, offset);
	offset+=32
	push(buff, list[i][2], 32, offset);
	offset+=32
	return buff
'''	
	
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
	




UDP_IP = "127.0.0.1"
UDP_PORT = 1111

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))
sock.setblocking(0)
list={0:[0,0,0],1:[0,0,0],2:[0,0,0],3:[0,0,0],4:[0,0,0],5:[0,0,0]}
while 1:
	try:
		data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
		buff = map(ord,data)
		result = des_messageRBC_new(buff)
		if result[0]==65280:
			list[0]=result
		if result[0]==65615:
			list[1]=result
		if result[0]==65315:
			list[2]=result
		if result[0]==65316:
			list[3]=result
		if result[0]==65282:
			list[4]=result
		if result[0]==65551:
			list[5]=result
		print "received message:", data
		
	except socket.error as msg:
        #sock.close() 
		print "nessun messaggio ricevuto"
	print "list ", list 
	buff = messageRBC1(list)
	sendUDP(buff,4010)
	time.sleep(2)
	#raw_input("-->> PRESS ENTER <<<--- ")

	
exit(0)


 





