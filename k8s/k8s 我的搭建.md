# 安装各种包

## 测试一
之前使用的是默认版本，但是教程版本支持的是11，后面出现问题
yum install -y kubelet-1.14.1-0.x86_64 kubeadm-1.14.1-0.x86_64 kubectl-1.14.1-0.x86_64 docker-ce-17.03.2.ce-1.el7.centos

yum install -y keepalived


## 使用教程版本

1、直接使用下面的命令会出现版本依赖问题，因为现在默认版本已经是14了
```
yum install -y kubelet-1.11.1-0.x86_64 kubeadm-1.11.1-0.x86_64 kubectl-1.11.1-0.x86_64 docker-ce-17.03.2.ce-1.el7.centos
```

2、安装版本11解决办法
(1)设置镜像源

```
$ cat /etc/yum.repos.d/kubernetes.repo
[kubernetes]
name=Kubernetes
baseurl=http://mirrors.aliyun.com/kubernetes/yum/repos/kubernetes-el7-x86_64
enabled=1
gpgcheck=0
repo_gpgcheck=0
gpgkey=http://mirrors.aliyun.com/kubernetes/yum/doc/yum-key.gpg
        http://mirrors.aliyun.com/kubernetes/yum/doc/rpm-package-key.gpg
```

(2) 安装k8s 工具

注意多了一个 kubernetes-cni-0.6.*，这是我们依赖的旧版本
```
yum install -y kubelet-1.11.6* kubeadm-1.11.6* kubectl-1.11.6* kubernetes-cni-0.6.*
```



```
scp -r config/$HOST1/kubeadm-config.yaml $HOST1:/root/
scp -r config/$HOST2/kubeadm-config.yaml $HOST2:/root/
scp -r config/$HOST3/kubeadm-config.yaml $HOST3:/root/
```





# 三台master机器免密登录

ssh-keygen
ssh-copy-id 10.5.9.184
ssh-copy-id 10.5.9.192
ssh-copy-id 10.5.9.199
