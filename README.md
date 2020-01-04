<!-- TOC -->

- [1. 背景](#1-背景)
- [2. Tools](#2-tools)
- [3. 技术栈](#3-技术栈)
    - [3.1 Prometheus、Kubernetes](#31-prometheuskubernetes)
    - [3.2 linxu kernel](#32-linxu-kernel)
    - [3.3 虚拟化](#33-虚拟化)
    - [3.4 分布式](#34-分布式)

<!-- /TOC -->
# 1. 背景
一直在找记录个人博客地方，印象笔记和有道云笔记都试过了，但是用着一直不爽。要么是同步经常出问题，要么是支持markdown功能并不是非常好，要么是查阅笔记不是很方便。

感谢海伟教我将笔记自动同步在git仓库中，真的达到我心中记录笔记的要求。现在本人已经重度依赖git 笔记，技术上面的问题都记录在上面。

现在我主要活动在云计算这一块，从最开始Prometheus、Kubernetes、到现在虚拟化，不过还是积累阶段，特别是虚拟化种类比较多技术较复杂。希望借着对Linux Kernel相对熟悉在虚拟化方向扎根下来。


# 2. Tools
* 环境配置：现在办公笔记本开始越来越多，拿到一台新电脑重现配置环境也是非常必要的。Tools目录记录这本人常用的工具和配置，能方便快速配置个人环境。
    * 参见Tools 目录
* processon 在线画图
* trello: todolist在线工具



# 3. 技术栈
## 3.1 Prometheus、Kubernetes
最开始接触云计算是从Prometheus、Kubernetes较上层应用开始的。由于实验室研究方向和个人希望从事底层技术。
* Prometheus
    * prometheus 各个组成结构和原理文档阅读完毕，参见Prometheus官网
    * prometheus client_python写采集器
    * ansible 自动化不熟采集器和Prometheus，实现一键部署（部署环境估计2000台计算节点）
    * prometheus keepalive实现主备节点
* Kubernetes
    * Kubernetes简单使用手册基本阅读完毕，参见Kubernetes指南
    * 针对人工智能容器训练定制CRD和Controller，容器云训练的核心节点，稳定新还不错（写过脚本验证，0.5s内频繁create delete 不会出现问题）。并发处理性能有待验证（没有大规模资源验证）。
    * client-go源码初略阅读
        * scheme 使用，不是源码分析
        * wrokqueue 源码分析
        * informer 源码分析
* Prometheus-Operator
    * Prometheus Operator 源码阅读完毕。
* kubeflow
    * gitops 理解
    * jupyter doc 阅读
    * pipelines doc 阅读
    * Fairing doc 阅读
    * kubeflow 部署
    * Pytorch opeartor
        * Pytorch-Opeartor 复现训练过程
        * 手动编译Pytorch-Opeartor 源码，执行训练过程
        * [进行中]Pytorch-Operator源码阅读
* kubebatch
    * kube-batch doc 简介和不熟
    * kube-batch doc 概念和原理
    * kube-batch doc 调度过程
    * kube-batch doc Reclaim 过程

## 3.2 linxu kernel
* Linux内核设计艺术
    * 一章：计算机加电到第一次执行Cmain函数
    * 二章：创建0号进程(怠速进程)
    * 三章：创建1号进程(init进程)
    * 四章：创建2号进程（shell进程）
    * 五章：文件基本操作
    * 六章：用户进程与内存管理
    * 七章：缓冲区和多进程操作文件
    * 八章：进程之间通信
    * 九章：操作系统设计的指导思想


## 3.3 虚拟化
* 系统虚拟化(source haiwei)
    * 1. 系统虚拟化简介
    * 2. x86操作系统架构
    * 3. 系统虚拟化方案
* 其它blog
    * 【经典】虚拟机在线迁移技术实现
    * 主流虚拟化技术种类和却别

## 3.4 分布式
* 分布式系统 MIT 6.824
    * MapReduce 
    * GFS




PodGroup controller，
queue controller，（queue状态转化、webhook,ladp接进来，一个用户组定义）
三级部门控制.

workflow
pytroch-operator 优先级、抢占
