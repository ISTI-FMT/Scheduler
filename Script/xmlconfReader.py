'''
Created on 11/mar/2014

@author: isiu

'''
from xml.dom.minidom import parseString
#all these imports are standard on most modern python implementations
 

def readXml(filename):
	#open the xml file for reading:
	file = open(filename,'r')
	#convert to string:
	data = file.read()
	file.close()
	#parse the xml you got from the file
	dom = parseString(data)
	#retrieve the first xml tag (<tag>data</tag>) that the parser finds with name tagName:
	xmlTagP = dom.getElementsByTagName('partenza')
	xmlTagP += dom.getElementsByTagName('ingresso')
	dict = {}
	for partenza in xmlTagP:
		prevcdb = partenza.getAttribute('prevcdb')
		name =  partenza.getAttribute('name')
		#print name
		#print prevcdb
		xmlTagPCDB = partenza.getElementsByTagName('cdb')
		listcdb = []
		for cdb in xmlTagPCDB:
			value = cdb.firstChild.data
			qdev =  cdb.getAttribute('q_dev')
			listcdb.append((value,qdev))
			#print value
		if not prevcdb in dict:
			dict[prevcdb] = [listcdb]
		else:
			lis = dict[prevcdb]
			lis.append(listcdb)
	#print dict
	return dict
