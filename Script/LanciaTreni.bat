@echo on
Title FinestraTReno
START  python simulaRBC.py 
#ping 127.0.0.1 -n 5 > nul 
START  python simulaTreno.py Treno65615percorso1173.txt 1
#ping 127.0.0.1 -n 5 > nul
START  python simulaTreno.py Treno65316percorso1154.txt 1
#ping 127.0.0.1 -n 5 > nul
START  python simulaTreno.py Treno65315percorso1153.txt 1
#ping 127.0.0.1 -n 5 > nul
START  python simulaTreno.py Treno65280percorso1152.txt 1
#ping 127.0.0.1 -n 5 > nul
#START  python simulaTreno.py Treno65282percorso1151.txt 1
#ping 127.0.0.1 -n 5 > nul
#START  python simulaTreno.py Treno65551percorso1166.txt 1
START  python simulaTreno.py  Treno65666percorso1166.txt 1 