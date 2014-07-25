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
from os import system
import messaggi


SendUDP_IP = "127.0.0.1" #send fake Rbc
ReceiveTCP_IP = ""  #receive any ip
SendTCP_IP = "192.168.1.213" #send presentazione ATS




if len(sys.argv) < 2:
	print "script.py <namefile> 0 or 1 se fare o meno la presentazione"
	exit(1)
	
	
def serverTCP(host, port,ACK):
	while 1:
		s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
		s.bind((host, port))
		s.listen(1)
		conn, addr = s.accept()
		
		print 'CAMBIO Connection address:', addr
		data = conn.recv(1024)
		if not data: break
		#print "received data:", data
		buffer1 = map(ord,data)
		if not (buffer1[1]==6):
			print "##########################CAMBIO TRN###############################"
			MESSAGE2 = conn.recv(14)
			buffer2 = map(ord,MESSAGE2)
			MESSAGE3 = conn.recv(2048)
			buffer3 = map(ord,MESSAGE3)
			messaggi.deserializzaCommandDATA(buffer1)
			NID_OPERATIONAL = messaggi.deserializzaCommandDATA(buffer2)
			print "NID_OPERATIONAL ",NID_OPERATIONAL
			print "received data:", messaggi.deserializzaMissionDATA(buffer3)
			conn.send(ACK)
			print "##########################END CAMBIO TRN###############################"
		else:
			print "##########################CAMBIO MISSION###############################"
			print "CAMBIO MISSION received data:", messaggi.deserializzaMissionDATA(buffer1)
			conn.send(ACK)
			#conn.close()
			#s.close()
			print "##########################END MISSION###############################"		# echo
			#conn.close()



def date_key(row):
	return datetime.strptime(row[2].strip(), "%d-%m-%Y %H:%M")
		

def sendUDP(message, UDP_PORT):
	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
	sock.sendto( message, (SendUDP_IP, UDP_PORT))
	
	
def sendUDPR(message, UDP_PORT):
	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
	sock.sendto( message, ("192.168.1.116", UDP_PORT))

def sendTCP(MESSAGE):
	TCP_PORT = 13000
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # UDP
	sock.connect((SendTCP_IP, TCP_PORT))
	sock.send(MESSAGE)
	sock.close()


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
	messaggi.deserializzaCommandDATA(buffer1)
	buffer2 = map(ord,MESSAGE2)
	print "lenb",len(buffer2)
	NID_OPERATIONAL = messaggi.deserializzaCommandDATA(buffer2)
	buffer3 = map(ord,MESSAGE3)
	print "received data:", messaggi.deserializzaMissionDATA(buffer3)
	return NID_OPERATIONAL
	

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
	op = sys.argv[3]#[18:22]
	NID_OPERATIONAL=int(op)
	

########## MOVIMENTO VS RBC inizializzazione ######


NID_CDB =  int(spamReader[0][0],10)
sendBytes =  messaggi.creamovimento(spamReader[0][0],NID_ENGINE)
print "Sono sul CDB1: ",NID_CDB
###SEND NETWORK
sendUDPR(sendBytes,302)
buff = messaggi.messageRBC_new(NID_ENGINE,NID_OPERATIONAL,NID_CDB)
#for i in range(0,70):
sendUDP(buff,1111)
sendUDP(buff,1111)
sendUDP(buff,1111)

#Imposto il nome della console
if os.name=='posix':
	sys.stdout.write("\x1b]2; Treno: " + str(NID_ENGINE) + " (CDB " + str(NID_CDB) + ") \x07")
else:
	system("TITLE "+"Treno: " + str(NID_ENGINE) + " (CDB " + str(NID_CDB) + ")")

#####PRESENTAZIONE VS ATS #########
#115;16;258;65280;25;53;3610 Presentazione


if bandiera==True:
	try:
		sendBytesP = messaggi.messPres(NID_ENGINE,M_PORT)
		print "Invio Presentazione"
		sendTCP(sendBytesP)
		print "Ricevo Wake-up TRN MISSION"
		
		NID_OPERATIONAL = ReceiveTCP(M_PORT,messaggi.sendACk(NID_ENGINE))
		print "nid_op", NID_OPERATIONAL
		####ASCOLTO TCP
		thread.start_new_thread(serverTCP, (ReceiveTCP_IP, M_PORT,messaggi.sendACk(NID_ENGINE)))
	except socket.error as msg:
		#sock.close() 
		print "Nessuna Presentazione Eseguita, Avvia lo Scheduler",msg


    

#exit(0)
data = []
scatti = []

####### MOVIMENTO VS RBC NEXT MOV######
for line in spamReader:
	i = 0
	
	while i<len(line):	
		###SEND NETWORK
		sendBytes = messaggi.creamovimento(line[i],NID_ENGINE)
		sendUDPR(sendBytes,302)
		###SEND FAKE RBC
		NID_CDB = int(line[i],10)
		if os.name=='posix':
			sys.stdout.write("\x1b]2; Treno: " + str(NID_ENGINE) + " (CDB " + str(NID_CDB) + ") \x07")
		else:
			system("TITLE "+"Treno " + str(NID_ENGINE) + " (CDB " + str(NID_CDB) + ")")
		buff = messaggi.messageRBC_new(NID_ENGINE,NID_OPERATIONAL,NID_CDB)
		sendUDP(buff,1111)
		sockfarbc = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
		sockfarbc.bind(("127.0.0.1", NID_ENGINE))
		#sockfarbc.setblocking(0)
		print i
		print len(line)
		print data
		if not data and len(scatti)==0:
			print "cccc"
			data, addr = sockfarbc.recvfrom(1024)
			list = data.replace('[','').replace("]","").replace('u','').replace('\'','').replace(" ","")
			scatti = list.split(',')
			print "lista", list
			data = []
		if len(scatti)>0:
			if scatti[0]==line[i+1]:
				print "Scatto", scatti[0]
				del scatti[0]
				print "scatti", scatti
				i+=1
			else:
				scatti=[]
		print "live"
		time.sleep(2)
		#inputt = raw_input("-->> PRESS ENTER <<<--- ")
		#if(inputt.upper()=="RETURN" or inputt.upper()=="R"):
		#	i-=1
		#else:
		#	i+=1
		

exit(0)
