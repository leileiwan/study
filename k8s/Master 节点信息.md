# 一、Master 简介

Master 节点可以自定义安装，比如配置自定义网络（比如可以设置是否运行在可信网络或者非可信网络中）

# 二、Cluster to Master

Master 节点交流通过apiservice 暴露Master节点（没有其他途径），典型的部署是 apiservice 通过监听https（443端口）的客户端连接来认证客户端连接是否合法。apiserver应该支持多种连接形式（如anonymous requests， service account tokens）。

Node 节点需要提供共有root 证书去连接spiservice。

Pod节点通过service account注入到public root 证书来连接apiservice。k8s service支持虚拟IP通过https协议和apiservice交互。


# 三、Master to Cluster 

Master 有两种方式和Cluster交互，一种是apiservice到运行在每一个Node节点上的kubelet process，而是通过apiservice通过apiservice proxy functionality 到任何Node，pod，service

## apiservice to kubelet

使用apiservice连接kubelet主要有三个作用

第一：获取pods日志

第二：附加到正在运行pods

第三：提供kubelet‘s port-forwarding 功能

默认情况apiservice不验证kubelet证书，因此容易受到man-in-the-middle攻击，运行在不可信的网络中。使用--kubelet-certificate-authority标签去验证kubelet的root证书。

## apiservice to pods，service，node

默认的apiservice使用http去 连接pods，services，nodes，即不认证和也不加密。

也可以使用https协议去连接，但是他不会对https两端节点去验证，只是提供传输中加密协议，因此这种方式不能保证节点时诚实节点，如果运行在非安全网络，这种方式是不安全的。


# 三、SSH tunnel（隧道）

k8s支持 ssh隧道保护Master -> Cluster通道，这保证双方的交互不被暴露在外部网络中。

但是SSH tunnel不被建议使用，除非个人非常清楚网络工作方式。



