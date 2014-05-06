@echo on
Title FinestraTReno
START  python simulaRBC.py 
ping 127.0.0.1 -n 5 > nul 
START  python simulaTreno.py Treno7732percorso5123.txt 1 5123

