from Tkinter import *
import subprocess
import time
DETACHED_PROCESS = 0x00000008

class Treno:
	trn = ''
	cdbs = []
	
def getMissions():
	process = subprocess.Popen(
		[ "GeneraPercorsoTreni.exe", "..\FileConfigurazione"] , stdout=subprocess.PIPE, stderr=subprocess.PIPE
	)

	treni = []
	missions = ''
	while True:
		out = process.stdout.read(1)
		if out == '' and process.poll() != None:
			break
		if out != '':
			missions += out
			
	for line in missions.splitlines():
		line = line.strip()
		if not line:continue
		linetokens = line.split("=")
		
		trn = linetokens[0].strip()
		cdbs = linetokens[1].strip().split(';')
		
		treno = Treno()
		treno.trn = trn
		treno.cdbs = cdbs
		
		treni.append(treno)
	
	return treni
	


def lanciaTreno():
	port = 61000
	for treno in treni:
	
		subprocess.Popen(["python simulaTrenoTabellaOrario.py " + str(treno[0]) + " " + str(treno[1]) + " "+ str(port) + " 0"],
                       creationflags=DETACHED_PROCESS, shell=True)
		time.sleep(2)
		port = port + 1
#ENGINE_NUMBER, TRN
treni = [
		[5132, 7723],
		[5321, 7327],
		[5123, 7732]
		]

subprocess.Popen(["python simulaRBC.py "], creationflags=DETACHED_PROCESS, shell=True)



class Application(Frame):
	def say_hi(self):
		print "hi there, everyone!"
	
	def printo(self, trn):
		print trn

	def createWidgets(self):
		treni = getMissions()
		
		for treno in treni:
			button = Button(self)
			button["text"] = treno.trn
			
			button["command"] = lambda trn = treno.trn: self.printo(trn)
			button.pack({"side": "top"})
			
	def __init__(self, master=None):
		Frame.__init__(self, master)
		self.pack()
		self.createWidgets()

root = Tk()
app = Application(master=root)
app.mainloop()
root.destroy()