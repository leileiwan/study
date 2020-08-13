<!-- TOC -->

- [1. 什么是Argoproj](#1-什么是argoproj)
- [2. 优点](#2-优点)

<!-- /TOC -->

REF: 
* https://github.com/argoproj/argo
* https://zhuanlan.zhihu.com/p/40301198
# 1. 什么是Argoproj
Argoproj is a collection of tools for getting work done with Kubernetes.

Argo Workflows is an open source container-native workflow engine for orchestrating parallel jobs on Kubernetes. Argo Workflows is implemented as a Kubernetes CRD (Custom Resource Definition).


* Define workflows where each step in the workflow is a container.
* Model multi-step workflows as a sequence of tasks or capture the dependencies between tasks using a graph (DAG).
* Easily run compute intensive jobs for machine learning or data processing in a fraction of the time using Argo Workflows on Kubernetes.
* Run CI/CD pipelines natively on Kubernetes without configuring complex software development products.

# 2. 优点

* Designed from the ground up for containers without the overhead and limitations of legacy VM and server-based environments.
* Cloud agnostic and can run on any Kubernetes cluster.
* Easily orchestrate highly parallel jobs on Kubernetes.
* Argo Workflows puts a cloud-scale supercomputer at your fingertips!

