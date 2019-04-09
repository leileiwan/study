# 常用服务命令

## 关闭selinux
临时关闭 selinux：setenforce 0    

修改配置：/etc/selinux/config，将SELINUX=enforcing改为SELINUX=disabled，重启机器即可

## 关闭防火墙
systemctl stop firewalld.service

systemctl disable firewalld.service

## 关闭NetworkManager 
systemctl stop NetworkManager

systemctl disable NetworkManager 



