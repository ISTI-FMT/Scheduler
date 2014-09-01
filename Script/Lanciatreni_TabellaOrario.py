import subprocess
import time

DETACHED_PROCESS = 0x00000008

#ENGINE_NUMBER, TRN
treni = [
		[5132, 7723],
		[5321, 7327],
		[5123, 7732],
		[5312, 7237]
		]

subprocess.Popen(["python simulaRBC.py "], creationflags=DETACHED_PROCESS, shell=True)

port = 61000
for treno in treni:
	
	subprocess.Popen(["python simulaTrenoTabellaOrario.py " + str(treno[0]) + " " + str(treno[1]) + " "+ str(port) + " 0"],
                       creationflags=DETACHED_PROCESS, shell=True)
	time.sleep(2)
	port = port + 1

