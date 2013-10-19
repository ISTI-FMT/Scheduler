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

if len(sys.argv) < 2:
    print "script.py <namefile>"
    exit(1)
	
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
  masks = [-128,64,32,16,8,4,2,1]; 
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
	print Q_COMMAND_TYPE
	if(Q_COMMAND_TYPE==3):
		M_GOA_LEVEL=pop(buff, 2, 75);
	NID_OPERATIONAL=0
	if(Q_COMMAND_TYPE==4):
		NID_OPERATIONAL=pop(buff, 32, 75);
		print "received data: "+"NID_MESSAGE: "+str(NID_MESSAGE)+" NID_PACKET: "+str(NID_PACKET)+" Q_COMMAND_TYPE: "+str(Q_COMMAND_TYPE)+" NID_OPERATIONAL: "+str(NID_OPERATIONAL)
	return NID_OPERATIONAL
	
def hextranslate(s):
        res = ""
        for i in range(len(s)/2):
                realIdx = i*2
                res = res + chr(int(s[realIdx:realIdx+2],16))
        return res


#input = sys.argv[1]
input = "01-4B-1F-FF-FF-FF-E0-14-65-00-00-01-90-10-08-F0-00-00-19-11-00-00-01-92-10"

if (input.find("-")!=-1):
	input= input.replace("-", "");
	
result = hextranslate(input)
buff = map(ord,result)
print buff
NID_MESSAGE= pop(buff, 8, 0);
L_MESSAGE=pop(buff,11, 8);
T_TIME=pop(buff, 32, 19);
NID_PACKET=pop(buff,  8, 51);
L_PACKET=pop(buff, 13, 59);
tNID_CDB =pop(buff, 32, 72);
tQ_STATOCDB =pop(buff, 2, 104);
tQ_DEVIATOIO =pop(buff, 2, 106);
tN_ITER =pop(buff, 16, 108);

print "data: "+"NID_MESSAGE: "+str(NID_MESSAGE)+" NID_PACKET: "+str(NID_PACKET)
print "data: "+"L_MESSAGE: "+str(L_MESSAGE)+" L_PACKET: "+str(L_PACKET)
print "data: "+"T_TIME: "+str(T_TIME)+" tNID_CDB: "+str(tNID_CDB)
exit(0)
sendBytes = raw_input("Enter something: ")

 










