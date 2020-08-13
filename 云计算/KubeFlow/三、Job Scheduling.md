<!-- TOC -->

- [1. 背景](#1-背景)
- [2. Running jobs with gang-scheduling](#2-running-jobs-with-gang-scheduling)
- [3. 注意事项](#3-注意事项)

<!-- /TOC -->
# 1. 背景
https://www.kubeflow.org/docs/use-cases/job-scheduling/

* This guide describes how to use volcano scheduler to support gang-scheduling in Kubeflow, to allow jobs to run multiple pods at the same time.

# 2. Running jobs with gang-scheduling
* Follow the instructions in the volcano repository to install Volcano.
* Take tf-operator for example, enable gang-scheduling in tf-operator by setting true to --enable-gang-scheduling flag.

Note: Volcano scheduler and operator in Kubeflow achieve gang-scheduling by using PodGroup. operator will create the PodGroup of the job automatically.

```
apiVersion: "kubeflow.org/v1beta1"
kind: "TFJob"
metadata:
  name: "tfjob-gang-scheduling"
spec:
  tfReplicaSpecs:
    Worker:
      replicas: 1
      template:
        spec:
          containers:
          - args:
            - python
            - tf_cnn_benchmarks.py
            - --batch_size=32
            - --model=resnet50
            - --variable_update=parameter_server
            - --flush_stdout=true
            - --num_gpus=1
            - --local_parameter_device=cpu
            - --device=gpu
            - --data_format=NHWC
            image: gcr.io/kubeflow/tf-benchmarks-gpu:v20171202-bdab599-dirty-284af3
            name: tensorflow
            resources:
              limits:
                nvidia.com/gpu: 1
            workingDir: /opt/tf-benchmarks/scripts/tf_cnn_benchmarks
          restartPolicy: OnFailure
    PS:
      replicas: 1
      template:
        spec:
          containers:
          - args:
            - python
            - tf_cnn_benchmarks.py
            - --batch_size=32
            - --model=resnet50
            - --variable_update=parameter_server
            - --flush_stdout=true
            - --num_gpus=1
            - --local_parameter_device=cpu
            - --device=cpu
            - --data_format=NHWC
            image: gcr.io/kubeflow/tf-benchmarks-cpu:v20171202-bdab599-dirty-284af3
            name: tensorflow
            resources:
              limits:
                cpu: '1'
            workingDir: /opt/tf-benchmarks/scripts/tf_cnn_benchmarks
          restartPolicy: OnFailure
```

# 3. 注意事项
* 创建PodGroup时，一定要求资源是充足的，如果资源充足，所有的Pod都处于Pending状态。（这个比我们的Controller分配Pod好，因为上面是所有Pod都是Pending）

* 可能造成死锁：
    * when in a high workload, if a pod of the job dies when the job is still running, it might give other pods chance to occupied the resources and cause deadlock.

* Troubleshooting 
If you keep getting problems related to RBAC in your volcano scheduler.

You can try to add the following rules into your clusterrole of scheduler used by volcano scheduler.
```
- apiGroups:
  - '*'
  resources:
  - '*'
  verbs:
  - '*'
```