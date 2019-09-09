# 1. 背景
* pytorch 分布式训练模型
* nccl 网络模型替换mpi
* 使用Kubeflow 训练
* 需求
    * 过程接近mpi-controller
    * 指定调度主机
    * 训练结束后，释放pod占用资源

# 2. 实现过程
## 2.1 参考Kubeflow 官网pytorch_mnist example
* 项目比较新，关键文档没有完善。URL job_mnist_DDP_GPU.yaml not found，重要参考文件不存在，因此quit。(后讨论可以在git旧版本中找到)
* 参考链接：https://github.com/kubeflow/examples/tree/master/pytorch_mnist

## 2.2 查阅 pytorch-operator
参考文档：https://github.com/kubeflow/pytorch-operator

### 2.2.1 核心过程
* 创建镜像：build 镜像的时候主要明明规则kubeflow/****(kubeflow 是可以创建的)
* 注意build镜像cuda驱动和GPU驱动对应（出现过不匹配现象）
* 样例中，docker 守护进程是通过build镜像完成的。这样的问题是通用性差，一个训练任务build一个镜像。可以尝试在Container字段中添加command作为守护进程
* 一个pod必须 一张卡，因为world_size


# 3. 运行自身的nccl训练模型
```
spec:
  containers:
  - name: mpirun
    image: mpirun
    imagePullPolicy: IfNotPresent

    command: ["/root/controller-mpirun/controller-mpirun"]
    args: ["-kubeconfig=/root/.kube/config", "-master=https://10.5.8.31:6443"]
```

apiVersion: "kubeflow.org/v1"
kind: "PyTorchJob"
metadata:
  name: "pytorch-dist-mnist-nccl"
spec:
  pytorchReplicaSpecs:
    Master:
      replicas: 1
      restartPolicy: OnFailure
      template:
        spec:
          containers:
            - name: cuda1
              image: registry.sensetime.com/share/platform/pytorch/pytorch:latest
              command: ["/opt/miniconda3/bin/python"]
              args: ["-u", "main_allreduce.py","-a", "resnet50","-j", "32","-b", "512","--epochs=1","--iter=500","--bucket=200","--world-size=16"]
              securityContext:
                capabilities:
                  add: ["IPC_LOCK"]
              env:
                - name: NVIDIA_DRIVER_CAPABILITIES
                  value: "compute,utility"
                - name: NVIDIA_REQUIRE_CUDA
                  value: "cuda>=9.0"
                - name: NVIDIA_VISIBLE_DEVICES
                  value: all
                - name: CUDA_HOME
                  value: "/usr/local/cuda"
                - name: NCCL_DEBUG
                  value: "INFO"
                - name: LD_PRELOAD
                  value: "/opt/nccl-2.4.8-1/lib/libnccl.so"
              resources: 
                limits:
                  rdma/hca: 1
              volumeMounts:
                - mountPath: /dev/shm
                  name: shm
                - mountPath: /tmp
                  name: tmp
                - mountPath: /sys
                  name: sys
                - mountPath: /mnt/lustrenew/share
                  name: share
                - mountPath: /mnt/lustre/share/images
                  name: imagenet
          volumes:
            - name: shm
              hostPath:
                path: /dev/shm
                type: Directory
            - name: tmp
              hostPath:
                path: /tmp
                type: Directory
            - name: sys
              hostPath:
                path: /sys
                type: Directory
            - name: share
              hostPath:
                path: /mnt/lustrenew/share
                type: Directory
            - name: imagenet
              hostPath:
                path: /mnt/lustre/share/images
                type: Directory
    Worker:
      replicas: 15
      restartPolicy: OnFailure
      template:
        spec:
          containers:
            - name: cuda1
              image: registry.sensetime.com/share/platform/pytorch/pytorch:latest
              command: ["/opt/miniconda3/bin/python"]
              args: ["-u", "main_allreduce.py","-a", "resnet50","-j", "32","-b", "512","--epochs=1","--iter=500","--bucket=200","--world-size=16"]
              securityContext:
                capabilities:
                  add: ["IPC_LOCK"]
              env:
                - name: NVIDIA_DRIVER_CAPABILITIES
                  value: "compute,utility"
                - name: NVIDIA_REQUIRE_CUDA
                  value: "cuda>=9.0"
                - name: NVIDIA_VISIBLE_DEVICES
                  value: all
                - name: CUDA_HOME
                  value: "/usr/local/cuda"
              resources: 
                limits:
                  rdma/hca: 1
              volumeMounts:
                - mountPath: /dev/shm
                  name: shm
                - mountPath: /tmp
                  name: tmp
                - mountPath: /sys
                  name: sys
                - mountPath: /mnt/lustrenew/share
                  name: share
                - mountPath: /mnt/lustre/share/images
                  name: imagenet
                - name: NCCL_DEBUG
                  value: "INFO"
                - name: LD_PRELOAD
                  value: "/opt/nccl-2.4.8-1/lib/libnccl.so"
                
          volumes:
            - name: shm
              hostPath:
                path: /dev/shm
                type: Directory
            - name: tmp
              hostPath:
                path: /tmp
                type: Directory
            - name: sys
              hostPath:
                path: /sys
                type: Directory
            - name: share
              hostPath:
                path: /mnt/lustrenew/share
                type: Directory
            - name: imagenet
              hostPath:
                path: /mnt/lustre/share/images
                type: Directory
~                

*  --world-size=16 这个参数没有使用，无关参数不要在args参数中使用，否则会报错
* rank 如何设置.环境变量




#4. 出现的问题
由于网络模型限制，我们必须要分配pod在那些机器上，以及调度pod顺序。
调度pod顺序非常难，可以从模型这边改进，我们可以做的是分配，比如16GPU，可以评分到指定的两个节点上。但是最好是自动平分到两个节点上。

## 4.1 手动指定节点
可以指定所有pod节点，但是谁也无法保证平分
```
 containers:
  - name: nginx
    image: nginx
    imagePullPolicy: IfNotPresent
  nodeSelector:
    disktype: ssd
```
* [确认]  pytorch-operator :通过源码发现，pytorch可以制定pod调度在什么节点上
```
   Worker:
      replicas: 15
      restartPolicy: OnFailure
      template:
        spec:
          affinity:
            nodeAffinity:
              requiredDuringSchedulingIgnoredDuringExecution:
                nodeSelectorTerms:
                - matchExpressions:
                  - key: kubernetes.io/hostname
                    operator: In
                    values:
                    - bj-idc1-10-10-31-25
                    - bj-idc1-10-10-31-26
          containers:
            - name: pytorch
              image: xiaoluwwwxiaolu/pytorch-dist-mnist-test:1.0
              args: ["--backend", "nccl"]
              resources:
                limits:
                  nvidia.com/gpu: 1
```

[待确认]：有调度在什么机器上的需求吗？