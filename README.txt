IP_ATS : 1.213
IP_IXL : 1.116

PrototipoATS.exe Versione integrale 
PrototipoATS_Lite.exe Versione senza presentazione ATO

Requisiti di sistema:
 Il prototipo per essere eseguito necessita delle librerie:
  - Visual C++ Redistributable 2012 https://www.dropbox.com/s/3yw0bdy3ss1xeqa/Visual%20C%2B%2B%20Redistributable%202012.exe
  - dotnetfx45_full_x86_x64 https://www.dropbox.com/s/ykhl1o7pdfwksvn/dotnetfx45_full_x86_x64.exe
 Per simulare l'ATO si usano degli script scritti in python quindi bisogna installare sul sistema
 python  2.7 (solo per la versione integrale dell'ATS)
  -http://legacy.python.org/ftp//python/2.7.6/python-2.7.6.msi


FileConfigurazione
|-->MapTreni.xml							Indica posizione iniziale treni, dove cioè l'ATS si aspetta di trovare il treno.
|-->TabellaOrario.xml						Contiene la tabella orario dei treni
Script
|-->Treno65280percorso1152.txt				File di configurazione per simulare la presentazione di un ATO: il file contiene il NID_ENGINE treno, porta su cui dialogare, cdb di partenza. 
|-->ecc.
PrototipoATS.exe							Schedulatore ATS
PrototipoATS_Lite.exe						Schedulatore ATS senza la presentazione degli ATO
PrensentaTreni.bat							Permette di simulare la Presentazione del ATO all'ATS

Per lanciale la versione completa avviare:
	1) PrototipoATS.exe
	2) PrensentaTreni.bat

Per la versione Lite avviare solo PrototipoATS_Lite.exe


La versione Lite del prototipo elimina la necessità di presentare gli ATO, i treni vengo inseriti in lista pronti prendendo le informazioni
dell'ATC.