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


def creamovimento(cdb,NID_ENGINE,idmesg):
    sendBytes = bytearray([0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0])
    messaggi.push(sendBytes, idmesg, 8, 0); #//nid_msg
    messaggi.push(sendBytes, 12, 10, 8); #//L_msg
    messaggi.push(sendBytes, 5555, 32, 18); #//T_msg
    messaggi.push(sendBytes, NID_ENGINE, 32, 50); #//nid_op
    NID_CDB =  int(cdb,10)
    messaggi.push(sendBytes,NID_CDB, 32, 82);#//nid_cdb
    print "Sono sul CDB: ",cdb
    return sendBytes

def sendUDPR(message, UDP_PORT, IP):
	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
	sock.sendto( message, (IP, UDP_PORT))


NID_CDB =  "13302"
NID_ENGINE= int("52550",10)

sendBytes =  creamovimento(NID_CDB,NID_ENGINE,10)
print "Sono sul CDB1: ",NID_CDB
###SEND NETWORK
sendUDPR(sendBytes,302,"192.168.1.116")
print "inviato "
time.sleep(2)
