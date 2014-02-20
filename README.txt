

Requisiti di sistema:
 Il prototipo per essere eseguito necessita delle librerie:
  - Visual C++ Redistributable 2012 https://www.dropbox.com/s/3yw0bdy3ss1xeqa/Visual%20C%2B%2B%20Redistributable%202012.exe
  - dotnetfx45_full_x86_x64 https://www.dropbox.com/s/ykhl1o7pdfwksvn/dotnetfx45_full_x86_x64.exe
 Per simulare l'ATO si usano degli script scritti in python quindi bisogna installare sul sistema
 python  2.7
  -http://legacy.python.org/ftp//python/2.7.6/python-2.7.6.msi


FileConfigurazione
|-->MapTreni.xml							Indica posizione iniziale treni, dove cioè l'ATS si aspetta di trovare il treno
|-->TabellaOrario.xml						Contiene la tabella orario dei treni
Script
|-->Treno65280percorso1152.txt				File di configurazione per simulare la presentazione di un ATO: il file contiene il NID_ENGINE treno, porta su cui dialogare, cdb di partenza. 
|-->ecc.
PrototipoATS.exe							Schedulatore ATS
PrototipoATS.exe.config
LanciaTreni.bat								Permette di lanciare la simulazione della Presentazione del ATO all'ATS