#!/bin/sh



osascript -e 'tell application "Terminal" to do script "/Users/isiu/github/Scheduler/Script/simulaRBC2.py"'


osascript -e 'tell application "Terminal" to do script "/Users/isiu/github/Scheduler/Script/simulaTreno2.py /Users/isiu/github/Scheduler/Script/Treno65315percorso5151.txt 0"'
/Users/isiu
osascript -e 'tell application "Terminal" to do script "/Users/isiu/github/Scheduler/Script/simulaTreno2.py /Users/isiu/github/Scheduler/Script/Treno65281percorso1153.txt 0"'

osascript -e 'tell application "Terminal" to do script "/Users/isiu/github/Scheduler/Script/simulaTreno2.py /Users/isiu/github/Scheduler/Script/Treno65000percorso1152.txt 0"'

osascript -e 'tell application "Terminal" to do script "/Users/isiu/github/Scheduler/Script/simulaTreno2.py /Users/isiu/github/Scheduler/Script/Treno65280percorso1177.txt 0"'

osascript -e 'tell application "Terminal" to do script "/Users/isiu/github/Scheduler/Script/simulaTreno2.py /Users/isiu/github/Scheduler/Script/Treno55666percorso1154.txt 0"'


#open -n -a Terminal.app --args /Users/isiu/github/Scheduler/Script/simulaRBC2.py
#open -n -a Terminal.app --args '/Users/isiu/github/Scheduler/Script/simulaTreno2.py /Users/isiu/github/Scheduler/Script/Treno7327percorso5321.txt 0'