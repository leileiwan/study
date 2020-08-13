# 一、k8s作用

k8s主要用在什么地方

1、a container platform（容器平台，需要和PaaS区分开）

2、a microservices platform（微服务平台，体现在k8s最小管理单元是pod）

3、a portable cloud platform and a lot more.（便携式云平台）

# 二、k8s 组件概念
k8s架构图如下

![title](../.local/static/2019/3/2/1554196404362.1554196404452.png)

## Master 节点
Master k8s集群的控制平台。

### kube-apiserver（api server）
提供空时k8s集群接口。

通过创建多个instance来实现水平扩展。

## etcd

提供k8s集群k-v存储。整个集群的数据都是存储在etcd部件中的。

## kube-scheduler
当创建pod时，在k8s集群中寻找空闲Node去运行它。

## kube-controller-manager
将不同请求分配给不同的进程去处理。

（1）Node Controller：当Node节点down时，发现Node节点异常并且做出响应。

（2）Replication Controller: 负责对系统中每一个Replication Controller维持正确的pod个数。

（3）Endpoints Controller: 移植端点对象（pod，service）

（4）Service Account & Token Controllers:对新的namespace，创建默认Account账号和API token 访问途径。

## cloud-controller-manager
cloud-controller-manager 主要是与底层云（第三方）交互。

cloud-controller-manager仅运行特定于云提供程序的控制器循环。 您必须在kube-controller-manager中禁用这些控制器循环。 您可以通过在启动kube-controller-manager时将--cloud-provider标志设置为external来禁用控制器循环。

早先k8s代码依赖云供应商提供代码，但未来云供应商代码和k8s代码独立演化更新。

The following controllers have cloud provider dependencies:

Node Controller: For checking the cloud provider to determine if a node has been deleted in the cloud after it stops responding

Route Controller: For setting up routes in the underlying cloud infrastructure

Service Controller: For creating, updating and deleting cloud provider load balancers

Volume Controller: For creating, attaching, and mounting volumes, and interacting with the cloud provider to orchestrate volumes





## Node 节点
node components运行在每一个node节点上，维持pod的运行并提供k8s运行环境。

### kubelet
运行在每一个node节点上。确保容器运行在pod中。

kubelet采用通过各种机制提供的一组PodSpecs，并确保那些PodSpecs中描述的容器运行且健康。 kubelet不管理不是由Kubernetes创建的容器。

### kube-proxy
通过维持主机上的网络规则并执行连接转发，k8s支持服务抽象。

### Container Runtime
提供容器运行的环境。容器支持docker、containerd等。

## Addons（插件）
插件是实现集群功能的pod和服务。

pod被Deployments和ReplicationControllers管理。namespace addon对象创建在kube-system namespace。

![title](../.local/static/2019/3/4/1554354843923.1554354843929.png)

从图中我们可以理解第三方的pod和service。

### DNS

cluster DNS 本质上是一个DNS server，不同本地DNS，k8s 的DNS是对服务做映射。


### Web UI (Dashboard)
Dashboard is a general purpose, web-based UI for Kubernetes clusters. It allows users to manage and troubleshoot applications running in the cluster, as well as the cluster itself.

### Container Resource Monitoring
Container Resource Monitoring records generic time-series metrics about containers in a central database, and provides a UI for browsing that data.

### Cluster-level Logging
A Cluster-level logging mechanism is responsible for saving container logs to a central log store with search/browsing interface.


# 三、k8s应用管理模型

  ![title](../.local/static/2019/3/3/1554286234033.1554286234037.png)

## pod 
是k8s最小调度资源单位。Pod中会包含一组容器，它们一起工作，并且对外提供一个（或者一组）功能。对于这组容器而言它们共享相同的网络和存储资源，因此它们之间可以直接通过本地网络（127.0.0.1）进行访问。当Pod被创建时，调度器（kube-schedule）会从集群中找到满足条件的节点运行它。

## Controller

如果部署应用程序时，需要启动多个实例（副本），则需要使用到控制器（Controller）。用户可以在Controller定义Pod的调度规则、运行的副本数量以及升级策略等等信息，当某些Pod发生故障之后，Controller会尝试自动修复，直到Pod的运行状态满足Controller中定义的预期状态为止。Kubernetes中提供了多种Controller的实现，包括：Deployment（无状态应用）、StatefulSet（有状态应用）、Daemonset（守护模式）等，以支持不同类型应用的部署和调度模式。

## service（集群内的应用如何通信）
Service在Kubernetes集群内扮演了服务发现和负载均衡的作用。在Kubernetes下部署的Pod实例都会包含一组描述自身信息的Lable，而创建Service，可以声明一个Selector（标签选择器）。Service通过Selector，找到匹配标签规则的Pod实例，并将对Service的请求转发到代理的Pod中。Service创建完成后，集群内的应用就可以通过使用Service的名称作为DNS域名进行相互访问。

## Ingress（外部的用户如何访问部署在集群内的应用）

Kubernetes中定义了单独的资源Ingress（入口）。Ingress是一个工作在7层的负载均衡器，其负责代理外部进入集群内的请求，并将流量转发到对应的服务中。

## Namespace（命名空间）

对于同一个Kubernetes集群其可能被多个组织使用，为了隔离这些不同组织创建的应用程序，Kubernetes定义了Namespace（命名空间）对资源进行隔离。









