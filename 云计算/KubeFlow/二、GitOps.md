<!-- TOC -->

- [1. Introduction](#1-introduction)
- [2. GitOps For KubeFlow Using Argo CD](#2-gitops-for-kubeflow-using-argo-cd)
- [3. Argo CD and GitOps](#3-argo-cd-and-gitops)
    - [3.1 安装](#31-安装)

<!-- /TOC -->
# 1. Introduction
Guides to  specific ways using kubeflow.
# 2. GitOps For KubeFlow Using Argo CD
This guide describes how to setup Kubeflow using a GitOps methodology by using Argo-CD.

* GitOps is a Continuous Delivery methodology centered around using Git as a single source of truth for declarative infrastructure and application code. 

* The Git repo defines the desired state of an application using declarative specifications, and a GitOps tool like Argo CD will reconcile the differences between the manifest defined by the git repo and the live system. As a result, GitOps enforces an operating model where all changes are observable and verifiable through git commits. 

* The declarative specifications streamline deployments as developers do not need to write scripts to build and deploy their application. Once the application is deployed, debugging is simplified as developers have a clear set of change logs through their Git commits history. 

* Even if the live system has drifted away from the source repo’s desired state, the GitOps methodology provides the tools to converge the real system with the desired state through the declarative specs. 

* Finally, once the breaking commit is found, rollback becomes as simple as syncing a previously good git commit. 

All these benefits reduce the amount of work developers have to spend on managing deployments to allow them to focus on other features.

# 3. Argo CD and GitOps
* Argo CD is a Kubernetes-native Declarative Continuous Delivery tool that follows the GitOps methodology. Along with all the benefits of using GitOps, Argo CD offers:
* Integrations with templating tools like Ksonnet, Helm, and Kustomize in addition to plain yaml files to define the desired state of an application
Automated or manual syncing of applications to its desired state
* Intuitive UI to provide observability into the state of applications
* Extensive CLI to integrate Argo CD with any CI system
* Enterprise-ready features like auditability, compliance, security, RBAC, and SSO

## 3.1 安装
https://www.kubeflow.org/docs/use-cases/gitops-for-kubeflow/

