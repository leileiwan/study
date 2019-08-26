<!-- TOC -->

- [1. 背景](#1-背景)
- [2. Tools](#2-tools)
- [3. 技术栈](#3-技术栈)
    - [3.1 Prometheus、Kubernetes](#31-prometheuskubernetes)
    - [3.2 研究生期间重点工作内容](#32-研究生期间重点工作内容)

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
最开始接触云计算是从Prometheus、Kubernetes较上层应用开始的。由于实验室研究方向和个人希望从事底层技术，以后对这方面只是保持了解状态，不会继续深究。
* Prometheus
    * prometheus 各个组成结构和原理文档阅读完毕，参见Prometheus官网
    * prometheus client_python写采集器
    * ansible 自动化不熟采集器和Prometheus，实现一键部署（部署环境估计2000台计算节点）
    * prometheus keepalive实现主备节点
* Kubernetes
    * Kubernetes简单使用手册基本阅读完毕，参见Kubernetes指南
    * 针对人工智能容器训练定制CRD和Controller，容器云训练的核心节点，稳定新还不错（写过脚本验证，0.5s内频繁create delete 不会出现问题）。并发处理性能有待验证（没有大规模资源验证）。
    * client-go源码初略阅读完毕。
* Prometheus-Operator
    * Prometheus Operator 源码阅读完毕。
## 3.2 研究生期间重点工作内容
* Linux内核设计艺术【2019.08.10-至今】
    * 计算机加电到第一次执行Cmain函数
    * 创建0号进程(怠速进程)
    * 创建1号进程(init进程)
    * 创建2号进程（shell进程）
    * 文件基本操作

* C++ template [2019.08.22-至今]
    * 函数template
    * class template

* Wine 兼容内核[2019.08.22-至今]
    （刚开是不是很喜欢做wine，觉得这玩意做出来东西没什么用，但是wine本身设计思路是很有意思的，有个能为虚拟化呢提供一种设计思路，所以打算读下去）
    * 漫谈wine概述

* Linux kernel 0.11 源码阅读和编译修改【跟进中】
