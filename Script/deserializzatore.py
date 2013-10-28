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
#input = "01-4B-1F-FF-FF-FF-E0-14-65-00-00-01-90-10-08-F0-00-00-19-11-00-00-01-92-10"
#input="01-4B-1F-FF-FF-FF-E0-14-65-00-00-01-90-10-08-F0-00-00-19-11-00-00-01-92-10-00-00-19-31-00-00-01-94-10-00-00-19-51-00-00-01-96-10-00-00-19-71-00-00-01-98-10-00-00-19-91-00-00-01-9A-10-00-00"
input = "01-4B-1F-FF-FF-FF-E0-14-65-00-00-01-90-10-08-F0-00-00-19-11-00-00-01-92-10-00-00-19-31-00-00-01-94-10-00-00-19-51-00-00-01-96-10-00-00-19-71-00-00-01-98-10-00-00-19-91-00-00-01-9A-10-00-00-19-B1-00-00-01-9C-10-00-00-19-D1-00-00-01-9E-10-00-00-19-F1-00-00-01-A0-10-00-00-1A-11-00-00-01-A2-10-00-00-1A-31-00-00-01-A4-10-00-00-1A-51-00-00-01-A6-10-00-00-1A-71-00-00-01-A8-10-00-00-1A-91-00-00-01-AA-10-00-00-1A-B1-00-00-01-AC-10-00-00-1A-D1-00-00-01-B8-10-00-00-1B-91-00-00-01-BA-10-00-00-1B-B1-00-00-01-BC-10-00-00-1B-D1-00-00-01-BE-10-00-00-1B-F1-00-00-01-C0-10-00-00-1C-18-00-00-01-F5-80-00-00-1F-61-00-00-01-F7-80-00-00-1F-84-00-00-01-F9-10-00-02-71-A0-00-00-27-1B-00-00-02-71-C1-00-00-27-1D-10-00-02-83-D1-00-00-28-3E-10-00-02-B0-21-00-00-2B-03-10-00-02-B0-41-00-00-2B-05-10-00-02-B0-C1-00-00-2B-0D-10-00-02-B0-E1-00-00-2B-0F-10-00-02-C2-51-00-00-2C-26-10-00-02-EE-A8-00-00-2E-EB-80-00-02-EE-CA-00-00-2E-ED-10-00-02-EE-E1-00-00-2E-EF-A0-00-02-EF-0A-00-00-2E-F4-10-00-02-EF-51-00-00-2E-F6-10-00-02-EF-71-00-00-2E-F8-10-00-02-EF-91-00-00-2E-FA-10-00-03-00-D1-00-00-30-0E-10-00-03-00-F5-00-00-32-D2-80-00-03-2D-38-00-00-32-D4-90-00-03-3F-55-00-00-33-F6-10-00-03-6B-A1-00-00-36-BB-10-00-03-6B-C1-00-00-36-C4-10-00-03-6C-51-00-00-36-C6-10-00-03-7D-D1-00-00-37-DE-10-00-03-AA-21-00-00-3A-A3-10-00-03-AA-41-00-00-3A-AC-10-00-03-AA-D1-00-00-3A-AE-10-00-03-BC-51-00-00-3B-C6-10-00-03-E8-A1-00-00-3E-8B-10-00-03-E8-C1-00-00-3E-8D-10-00-03-E8-E1-00-00-3E-8F-10-00-03-E9-01-00-00-3E-91-10-00-03-E9-41-00-00-3E-9B-10-00-03-E9-61-00-00-3E-97-10-00-03-E9-81-00-00-3E-95-10-00-03-E9-91-00-00-3E-9A-10-00-03-FA-D1-00-00-3F-AE-10-00-03-FA-F1-00-00-42-72-10-00-04-27-31-00-00-42-74-10-00-04-27-51-00-00-42-76-10-00-04-27-71-00-00-42-78-10-00-04-27-91-00-00-42-7A-10-00-04-27-B1-00-00-42-7C-10-00-04-28-68-00-00-42-87-80-00-04-28-89-00-00-42-89-90-00-04-28-A9-00-00-42-8B-10-00-04-28-C1-00-00-42-8D-10-00-04-28-E1-00-00-42-8F-10-00-04-29-01-00-00-43-95-10-00-04-39-61-00-00-43-97-50-00-04-39-81-04-4F-C8-00-01-3B-A1-00-10-C0-00-09-DD-42-00-00-4E-EC-20-00-02-77-70-80-00-15-AE-08-00-00-AD-74-20-00-05-6B-C1-00-00-2B-5F-08-00-01-5B-00-40-00-0A-D8-44-00-00-56-C4-10-00-02-B6-30-80-00-17-A2-08-00-00-BD-14-20-00-05-E8-C1-00-00-2F-47-08-00-01-7A-40-40-00-0B-D2-44-00-00-5E-94-20-00-02-F4-B0-80-00-17-A6-04-00-00-BD-34-20-00-05-E9-C1-00-00-2F-4F-10-00-01-7A-81-00-00-0B-D4-42-00-00-66-58-40-00-03-32-D0-80-00-19-97-08-00-00-CC-BC-20-00-06-E2-82-00-00-37-15-08-00-01-B8-B0-40-00-0D-C5-C2-00-00-6E-30-10-00-03-71-91-00-00-1B-8D-04-00-00-DC-6C-20-00-07-5F-82-00-00-3A-FD-08-00-01-D7-F0-40-00-0E-BF-C2-00-00-76-00-10-00-03-B0-11-00-00-1D-81-04-00-00-EC-0C-20-00-07-DC-81-00-00-3E-E5-08-00-01-F7-30-80-00-0F-B9-C2-00-00-7D-D0-10-00-03-EE-90-80-00-1F-75-04-00-00-FB-AC-40-00-07-DD-82-00-00-3E-ED-08-00-01-F7-70-40-00-0F-BB-C2-00-00-7D-E0-10-00-03-EF-11-00-00-21-66-04-00-01-0B-34-40-00-08-59-C1-00-00-42-CF-08-00-02-16-80-80-00-10-B4-42-00-00-85-A4-40-00-04-2D-30-82-8A-24-00-00-D4-91-00-11-00-00-39-0B-40-00-0E-43-10-00-02-96-C4-00-00-F3-CD-00-00-3C-F4-40-00-0B-55-50-00-02-D5-64-00-00-C4-F5-00-00-31-3E-40-00-0C-4F-D0-00-03-14-04-00-01-03-79-00-00-40-DF-40-00-10-38-10-00-04-0E-14-00-01-13-19-00-00-44-C7-41-90-6C-00-00-54-63-00-0E-80-00-0A-91-50-00-01-52-30-00-00-2A-47-00-00-05-49-00-00-00-B8-64-00-00-17-0D-00-00-02-E2-30-00-00-5C-48-00-00-0B-8B-40-00-01-71-70-00-00-35-E9-80-00-06-BD-40-00-00-D7-F5-00-00-1A-FF-00-00-03-5F-F0-00-00-6C-00-00-00-0C-80-60-00-01-90-10-00-00-32-03-00-00-06-40-80-00-00-C8-2C-00-00-19-06-00-00-03-20-D0-00-00-64-2A-00-00-0C-85-80-00-01-90-BA-00-00-39-D1-00-00-07-3A-40-00-00-E7-6C-00-00-1C-EE-00-00-03-9E-50-00-00-73-CC-00-00-0F-6E-40-00-01-ED-D0-00-00-3D-C3-00-00-07-B8-80-00-00-F7-34-00-00-1E-E7-00-00-04-1A-10-00-00-83-44-00-00-10-68-C0-00-02-0D-20-00-00-41-AB-00-00-08-35-80-00-01-06-B4-00-00-20-DA-80-00-04-1B-60-00-00-83-6E-00-00-11-62-40-00-02-2C-5C-00-00-45-9D-00-00-08-B3-C0-00-01-16-7D-00-00-22-D0-00-00-04-5A-10-00-00-8B-44-00-00-11-68-C0-00-02-2D-20-FF-FF"
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
print "data: "+"tN_ITER: "+str(tN_ITER)+" len: "+str(len(buff)*8)
exit(0)
sendBytes = raw_input("Enter something: ")

 










