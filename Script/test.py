import subprocess
import sys

print sys.argv[1]
print sys.argv[2]

class Treno:
	trn = ''
	cdbs = []

def getMission(missiontrn):
	process = subprocess.Popen(
		[ sys.argv[1], sys.argv[2]] , stdout=subprocess.PIPE, stderr=subprocess.PIPE
	)

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
		cdbs = linetokens[1].strip()
		
		print trn
		print ''
		print cdbs
		
		if (trn != missiontrn):
			continue;
		
		treno = Treno()
		treno.trn = trn
		treno.cdbs = cdbs
		
		return treno
	
	return None


treno = getMission("1151")
if (treno == None):
	print 'errore: treno non trovato!'
	exit()


print treno.trn
print '' 
print treno.cdbs