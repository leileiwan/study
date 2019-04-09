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
```
ansible-playbook -i ansible/hosts.server  ansible/playbook_server.yml
``` 

4、检查主机文件是否存在

5、修改配置文件并启动服务
在10.5.9.184执行
(1)prometheus

解压
```
cd /root
tar -zxvf prometheus-2.8.1.linux-amd64.tar.gz -C /usr/local/
cd /usr/local
mv prometheus-2.8.1.linux-amd64/ prometheus
cd prometheus
```

修改prometheus.yml 配置文件
```
# My global config/
global:
  scrape_interval:     10s # By default, scrape targets every 30 seconds.
  evaluation_interval: 10s
  external_labels:
    monitor: 'platformon-monitor'
# Alertmanager configuration
alerting:
  alertmanagers:
    - static_configs:
      - targets: ["10.5.9.184:9093"]
#Alert rule
rule_files:
  - /usr/local/prometheus/rules.yml
#Prometheus scrape_configs
scrape_configs:
  - job_name: 'prometheus'
    scrape_interval: 30s
    static_configs:
      - targets: ['10.5.9.184:9090']
        labels:
          instance: prometheus

```

修改rules.yml
```
空
```


启动服务
```
systemctl enable prometheus.service 
sudo systemctl stop prometheus.service 
sudo systemctl start prometheus.service 
```



(2)alertmanager

解压缩
```
cd /root
tar -xzvf alertmanager-0.16.2.linux-amd64.tar.gz -C /usr/local/
cd /usr/local
mv alertmanager-0.16.2.linux-amd64/ alertmanager
vim alertmanager.yml

```

修改配置文件alertmanager.yml
```
global:
  resolve_timeout: 5m
  
  smtp_from: "wanlei19@163.com"
  smtp_smarthost: "smtp.163.com:25"
  smtp_auth_username: "wanlei19@163.com"
  smtp_auth_password: "root123"
  smtp_require_tls: false

route:
  group_by: ['lustre_client']
  group_wait: 10s
  group_interval: 10s
  repeat_interval: 6h
  receiver: '163_email'

receivers:
  - name: '163_email'
    email_configs:
      - to: 'xiaoluwwwxiaolu@163.com'
      - to: 'zhanghequan@sensetime.com'
```

重启服务
```
systemctl enable alertmanager.service
sudo systemctl stop alertmanager.service
sudo systemctl start alertmanager.service
```
(3)grafana
```
cd /root
sudo yum localinstall grafana-5.0.4-1.x86_64.rpm(所有y)
systemctl enable grafana-server.service
systemctl stop grafana-server.service
systemctl start grafana-server.service
```

6、Grafana 同步数据源并添加画布展示
http://confluence.sensetime.com/pages/viewpage.action?pageId=50055555



三、部署Exporter

1、设置免密，参照上面

2、编写host.client文件
```

```









