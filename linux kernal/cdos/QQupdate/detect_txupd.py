#coding=utf-8
import os
import re
import time
def dect_txupd():
    content=os.popen("ps -ef |grep txupd.exe").read()
    res=re.search("[0-9]+?",content)
    if(res):
        pid=res.group(1)
        os.popen("kill "+pid)
    return

time.sleep(0.5)
