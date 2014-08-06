@echo on
Title FinestraTReno
START  python simulaRBC.py 
ping 127.0.0.1 -n 5 > nul 
START  python simulaTrenoTabellaOrario.py 5321 7327 7327 0
//ping 127.0.0.1 -n 5 > nul
//START  python simulaTrenoTabellaOrario.py 5312 7237 7237 0
ping 127.0.0.1 -n 5 > nul
START  python simulaTrenoTabellaOrario.py 5132 7723 7723 0
ping 127.0.0.1 -n 5 > nul
START  python simulaTrenoTabellaOrario.py 5123 7732 7732 0