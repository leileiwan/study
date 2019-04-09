一、版本

OS:centos7.4
Prometheus：prometheus-2.8.1.linux-amd64
AlertManager：alertmanager-0.16.2.linux-amd64
Grafana：grafana-5.0.4-1.x86_64

GO：go1.11.4-linux-amd64
Python：2.7.5
python库：prometheus_client,Flask
	pip install prometheus_client
	pip install  Flask




二、部署服务端
条件：保证网络正常（关闭本地防火墙，OpenStack安全组等）
ip：10.5.9.184
文件：Prometheus，AlertManager，Grafana

1、免密 ssh登录
管理节点执行
	ssh-keygen
	ssh-copy-id root@IP
	输入密码
2、编写配置文件
（1）host.server
prometheus主机ip
path：prometheus_deployment/ansible/hosts.server 
```
[server]
10.5.9.184
```

(2) playbook_server.yml
copy部署文件，本地文件路径需要正确
path:prometheus_deployment/ansible/playbook_server.yml
```
#copy file to client
- hosts: server
  remote_user: root
  tasks:
  - name: copy prometheus file to server
    copy: src=/root/prometheus_deployment/pkg/prometheus-2.8.1.linux-amd64.tar.gz  dest=/root
  - name: copy grafana  file to server
    copy: src=/root/prometheus_deployment/pkg/grafana-5.0.4-1.x86_64.rpm dest=/root
  - name: copy alertmanager  file to server
    copy: src=/root/prometheus_deployment/pkg/alertmanager-0.16.2.linux-amd64.tar.gz  dest=/root
```

3、执行部署脚本
ansible-playbook -i ansible/hosts.server  ansible/playbook_server.yml 

4、检查主机文件是否存在

5、启动服务
(1)prometheus

(当前路径 /root)
tar -zxvf prometheus-2.8.1.linux-amd64.tar.gz -C /usr/local/
cd /usr/local
mv prometheus-2.8.1.linux-amd64/ prometheus
sudo systemctl stop prometheus.service 
sudo systemctl start prometheus.service 

(2)alertmanager

(当前路径 /root)
tar -xzvf alertmanager-0.16.2.linux-amd64.tar.gz -C /usr/local/
cd /usr/local







