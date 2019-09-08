<!-- TOC -->

- [1. docker 支持NVIDIA（我司Kubernetes集群支持，可以忽略）](#1-docker-支持nvidia我司kubernetes集群支持可以忽略)
    - [1.1 docker 升级成19.03](#11-docker-升级成1903)
- [2. 安装Kubeflow](#2-安装kubeflow)
- [3. 创建PV](#3-创建pv)

<!-- /TOC -->
# 1. docker 支持NVIDIA（我司Kubernetes集群支持，可以忽略）
## 1.1 docker 升级成19.03

* yum list docker-ce --showduplicates | sort -r
* yum install docker-ce-19.03.1-3.el7
* distribution=$(. /etc/os-release;echo $ID$VERSION_ID)
* zypper ar https://nvidia.github.io/nvidia-docker$distribution/nvidia-docker.repo

* sudo zypper install -y nvidia-docker2  # accept the overwrite of /etc/docker/daemon.json
* yum install nvidia-container-runtime
* sudo systemctl restart docker
* sudo systemctl enable docker
* docker run --gpus all nvidia/cuda:9.0-base nvidia-smi

```
{
    "default-runtime": "nvidia",
    "runtimes": {
        "nvidia": {
            "path": "/usr/bin/nvidia-container-runtime",
            "runtimeArgs": []
        }
    }
}
```
* https://github.com/NVIDIA/nvidia-docker
* https://github.com/NVIDIA/k8s-device-plugin
* https://github.com/kubeflow/examples/tree/master/pytorch_mnist
* https://www.kubeflow.org/docs/examples/kubeflow-samples/



# 2. 安装Kubeflow
* note:一定要注意Kubernetes集群版本 1.12以及以上不能使用下面旧版本安装
    * 旧版本安装https://kiddie92.github.io/2019/01/05/CentOS-%E4%B8%8B%E5%9F%BA%E4%BA%8Ekubernetes%E5%AE%89%E8%A3%85%E9%83%A8%E7%BD%B2kubeflow/

* 安装过程如下
    * 安装过程没有包含PV创建，参照下面过程
https://www.kubeflow.org/docs/started/k8s/kfctl-k8s-istio/

* 安装过程中使用各种工具解释：
  * https://www.kubeflow.org/docs/other-guides/kustomize/


# 3. 创建PV
* 类型是hostPath PV
```
kind: PersistentVolume
apiVersion: v1
metadata:
  name: katib-mysql-pv
  namespace: kubeflow
  labels:
    pv: katib-mysql-pv
spec:
  capacity:
    storage: 10Gi
  accessModes:
    - ReadWriteOnce
  hostPath:
    path: "/mnt/lustrenew/wanlei/kubeflow/katib-mysql"
```

