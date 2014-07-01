@echo on
Title FinestraTReno
START  python simulaRBC.py 
ping 127.0.0.1 -n 5 > nul 
START  python simulaTreno.py Treno7732percorso5123.txt 0 5123
ping 127.0.0.1 -n 5 > nul
START  python simulaTreno.py Treno7237percorso5312.txt 0 5312
ping 127.0.0.1 -n 5 > nul
START  python simulaTreno.py Treno7723percorso5132.txt 0 5132
ping 127.0.0.1 -n 5 > nul
START  python simulaTreno.py Treno7327percorso5321.txt 0 5321

