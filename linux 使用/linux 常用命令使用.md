
[toc]
# 1.常用服务命令

## 1.1关闭selinux
临时关闭 selinux：setenforce 0    

修改配置：/etc/selinux/config，将SELINUX=enforcing改为SELINUX=disabled，重启机器即可

## 1.2关闭防火墙
systemctl stop firewalld.service

systemctl disable firewalld.service

## 1.3关闭NetworkManager 
systemctl stop NetworkManager

systemctl disable NetworkManager 


## 1.4 diff
* diff 表示两个文件中的内容差异

https://www.runoob.com/linux/linux-comm-diff.html

## 1.5 patch

* 有些项目是闭源，如果想修复其中的漏洞和bug，可以使用patch方式（不修改源码）
* patch 优点是能通过diff比较的两个文件不同，快速的更新就的文件到新文件。如果跟新错误，也能快速回退到旧文件。

### 1.5.1 应用场景--快速打补丁

* 创建两不同文件作为新旧文件
```
root@dev:/home/dev/wanlei# echo aa > test1
root@dev:/home/dev/wanlei# echo bb > test2
```

* diff 两个文件并输出到补丁文件
```
root@dev:/home/dev/wanlei# diff -urN test1 test2 > test.patch
root@dev:/home/dev/wanlei# cat test.patch 
--- test1	2019-08-07 18:44:44.707909343 +0800
+++ test2	2019-08-07 18:44:47.451909249 +0800
@@ -1 +1 @@
-aa
+bb
```
* 更具补丁快速更新旧版本文件到新版本（这样不用修改源文件了）
```
root@dev:/home/dev/wanlei# patch test1 < test.patch 
patching file test1
root@dev:/home/dev/wanlei# cat test1 
bb
```

* 同时若想回退到旧版本
```
root@dev:/home/dev/wanlei# patch -RE test1 < test.patch 
patching file test1
root@dev:/home/dev/wanlei# cat test1
aa
```

### 1.5.2
 重点参数
* patch -RE < 01_test.patch 取消patch对源文件的修改

* p表示跳过几级目录，0标识不去掉为全路径，1标识去掉第一层路径
patch -p1 < patch1.diff
注意：patch -p后面是不能带负数 的。不使用p参数的时候，patch命令会 忽略 任何目录，直接使用文件。



## 1.6 ps
* ps -ef | grep processName
    查看和processname有关所有进程
* ps -aux | grep processname
    查看在内存中和processname有关所有进程
* ps -f
    查看和当前会话有关进程
* ps -u root
    

## 1.7 kill
* kill -9 process 杀死指定进程（-9 可能出现问题）
* killall -9 process 杀死指定进程的全部进程

# 2. 运行符号

* & 让程序在后台执行
    ```
    ./Exe_name &
    ```
* Ctrl+z 暂停当前程序，并转为后台挂起
* bg n 将后台被暂停的n号程序唤醒，并在后台继续执行
* fg n 将后台程序n调度在前台执行
* jobs 查看被挂起的工作序号