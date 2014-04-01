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
import messaggi

receive_UDP_IP = "127.0.0.1"  #ASCOLTO TRENI
UDP_PORT = 1111
	
def date_key(row):
    return datetime.strptime(row[2].strip(), "%d-%m-%Y %H:%M")

   
def sendUDP(message, UDP_PORT):
	UDP_IP = "192.168.1.213" #send IP ATS
	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
	sock.sendto( message, (UDP_IP, UDP_PORT))

def sendTCP(MESSAGE):
	TCP_IP = "127.0.0.1"
	TCP_PORT = 13000
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # UDP
	sock.connect((TCP_IP, TCP_PORT))
	sock.send(MESSAGE)
	sock.close()



sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
sock.bind((receive_UDP_IP, UDP_PORT))
sock.setblocking(0)
lista={0:[0,0,0],1:[0,0,0],2:[0,0,0],3:[0,0,0],4:[0,0,0],5:[0,0,0]}
while 1:
	try:
		data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
		buff = map(ord,data)
		result = messaggi.des_messageRBC_new(buff)
		if (result[0]==65280) or (result[0]==7732):
			lista[0]=result
		if (result[0]==65615) or (result[0]==7723):
			lista[1]=result
		if (result[0]==65315) or (result[0]==7237):
			lista[2]=result
		if (result[0]==65316) or (result[0]==7327):
			lista[3]=result
		if result[0]==65282:
			lista[4]=result
		if result[0]==65551:
			lista[5]=result
		print "received message:", data
		
	except socket.error as msg:
        #sock.close() 
		print "nessun messaggio ricevuto"
	print "list ", lista 
	buff = messaggi.messageRBC1(lista)
	sendUDP(buff,4010)
	time.sleep(2)
	#raw_input("-->> PRESS ENTER <<<--- ")

	
exit(0)





