# 1. 在现有k8s环境中安装Kubeflow
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
* note:一定要注意Kubernetes集群版本 1.12以及以上和1.12以下安装有区别
    * 旧版本安装https://kiddie92.github.io/2019/01/05/CentOS-%E4%B8%8B%E5%9F%BA%E4%BA%8Ekubernetes%E5%AE%89%E8%A3%85%E9%83%A8%E7%BD%B2kubeflow/
https://www.kubeflow.org/docs/started/k8s/kfctl-k8s-istio/