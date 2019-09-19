#coding=utf-8
import os
import re
import time
def dect_txupd():
content=os.popen("ps -ef |grep txupd.exe").read()
res=re.search("Tencent.*QQ.*txupd.exe",content)
if(res):
pid=res.group(1)
os.popen("kill "+pid)
exit(0)

while(True):
time.sleep(1)
dect_txupd()

