@echo on
Title FinestraTReno

START  python simulaTreno.py Treno65315percorso1153.txt 0
ping 127.0.0.1 -n 5 > nul
START  python simulaTreno.py Treno65280percorso1152.txt 0

