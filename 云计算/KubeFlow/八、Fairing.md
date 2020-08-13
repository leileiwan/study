<!-- TOC -->

- [1. 背景](#1-背景)
- [2. Getting started](#2-getting-started)
    - [2.1 installing Kubeflow Fairing](#21-installing-kubeflow-fairing)
        - [2.1.1 Using Kubeflow Fairing with Kubeflow notebooks](#211-using-kubeflow-fairing-with-kubeflow-notebooks)
        - [2.1.2 Set up Kubeflow Fairing in a hosted Jupyter notebook](#212-set-up-kubeflow-fairing-in-a-hosted-jupyter-notebook)
            - [2.1.2.1 Prerequisites](#2121-prerequisites)
            - [2.1.2.2 Install Kubeflow Fairing](#2122-install-kubeflow-fairing)
            - [2.1.2.3 Configure Kubeflow Fairing](#2123-configure-kubeflow-fairing)
    - [2.2  configuring your development environment with access to Kubeflow.](#22--configuring-your-development-environment-with-access-to-kubeflow)
    - [2.3 fairing tutorials](#23-fairing-tutorials)

<!-- /TOC -->

# 1. 背景
关键字：packages、deploy、hybrid cloud environment

* Kubeflow Fairing streamlines the process of building, training, and deploying machine learning (ML) training jobs in a hybrid cloud environment.（混合云）
* Kubeflow Fairing packages your Jupyter notebook, Python function, or Python file as a Docker image, then deploys and runs the training job on Kubeflow or AI Platform. After your training job is complete, you can use Kubeflow Fairing to deploy your trained model as a prediction endpoint on Kubeflow.（Fairing可以包含Jupyter使用）

Fairing通过Python code or a Jupyter notebook来执行，并且支持训练之后部署训练模型。并且Fairing针对混合云，Provide a high-level API for training ML models to make it easy to run training jobs in the cloud, without needing to understand the underlying infrastructure.

# 2. Getting started
## 2.1 installing Kubeflow Fairing
https://www.kubeflow.org/docs/fairing/install-fairing/
Fairing 通过python 和Jupyter notebook执行，下面我们只关注Jupyter notebook方式。
### 2.1.1 Using Kubeflow Fairing with Kubeflow notebooks 
Kubeflow notebook servers that are built from one of the standard Jupyter Docker images include Kubeflow Fairing and come preconfigured for using Kubeflow Fairing to run training jobs on your Kubeflow cluster.

### 2.1.2 Set up Kubeflow Fairing in a hosted Jupyter notebook
If you are using a Kubeflow notebook server that was built from one of the standard Jupyter Docker images, your notebooks environment has been preconfigured for training and deploying ML models with Kubeflow Fairing and no additional installation steps are required.

#### 2.1.2.1 Prerequisites
Check the following prerequisites to verify that Kubeflow Fairing is compatible with your hosted notebook environment.
* In the Jupyter notebooks user interface, click File > New > Terminal in the menu to start a new terminal session in your notebook environment.
* You need Python 3.6 or later to use Kubeflow Fairing. To check if you have Python 3.6 or later installed, run the following command in your terminal session:
    * python3 -V
* Kubeflow Fairing uses Docker to package your code. Run the following command in your terminal session to verify if Docker is installed and running in your notebook environment
    * docker ps
#### 2.1.2.2 Install Kubeflow Fairing 
* In the Jupyter notebooks user interface, click File > New > Terminal in the menu to start a new terminal session in your notebook environment.

* Run the following command to install Kubeflow Fairing.
    * pip3 install fairing

* After successful installation, the fairing python package should be available. Run the following command to verify that Kubeflow Fairing is installed:
    * pip3 show fairing

#### 2.1.2.3 Configure Kubeflow Fairing 
This guide describes how to configure Kubeflow Fairing to run training jobs on Kubeflow.
官方Kubeflow notebook images已经对Fairing进行配置，不需要其他配置，如果是自定义镜像，需要如下配置。

* Configure Docker with access to your container image registry（https://docs.docker.com/engine/reference/commandline/login/）
* Configure access to your Kubeflow cluster
Use the following instructions to configure kubeconfig with access to your Kubeflow cluster.
    * kubectl installed
    * Follow the guide to configuring access to Kubernetes clusters(https://kubernetes.io/docs/reference/access-authn-authz/authentication/)

https://www.kubeflow.org/docs/fairing/gcp/tutorials/gcp-kubeflow-notebook/

## 2.2  configuring your development environment with access to Kubeflow.
https://www.kubeflow.org/docs/fairing/configure-fairing/
## 2.3 fairing tutorials
https://www.kubeflow.org/docs/fairing/tutorials/other-tutorials/







