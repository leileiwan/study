# kubectl 命令类型

![title](../.local/static/2019/3/3/1554300384325.1554300384329.png)

## 命令式（Imperative commands）
eg:
```
kubectl create deployment nginx --image nginx
```

优点：简单，易学
缺点:不保证结果状态，不方便审计

## 配置文件命令式

通过配置文件增删该Object
```
kubectl create -f nginx.yaml
kubectl delete -f nginx.yaml -f redis.yaml
kubectl replace -f nginx.yaml
```

优点：配置文件可以存储，方便再一次 复现和审计。
缺点:需要连接Object模式，并且写yml文件

## 声明型对象配置

配置文件存储的是Object的目标状态，不存储具体操作，操作有kubectl通过对比不同状态自动执行。
配置文件可以存放在目录中。
```
kubectl diff -f configs/
kubectl apply -f configs/
```

优点：配置文件写状态，不谢具体操作
缺点:很难debug




# 命令式

## 创建对象
### run
创建一个Deployment object去运行在一个或多个pod节点。

### expose
创建一个Service object去做pod的负载均衡

### autoscale
创建一个Object可以自动水平扩展。

### create
```
create <objecttype> [<subtype>] <instancename>
```

## update 对象

### scale
通过修改controller的replica，水平扩展或删除controller的pod

### annotate
删除和添加Object的annotate

### label
添加或删除Object的label

### set <field>
设置Object field

### edit
 Directly edit the raw configuration of a live object by opening its configuration in an editor.
### patch
Directly modify specific fields of a live object by using a patch string. For more details on patch strings, see the patch section in API Conventions.


## delete 对象

```
delete <type>/<name>
```
删除对象从集群。

eg：
```
kubectl delete deployment/nginx
```

## view 对象

### get
输出Object 基本信息

### describe
输出Object汇总信息

### logs
打印pod中容器的标准输出和出错信息


## 创建Object前 set 和 --edit修改对象
在创建Object时，有些field并没有flag。可以通过set在对象创建前设定Object filed的value值。

### set before create Object
```
kubectl create service clusterip my-svc --clusterip="None" -o yaml --dry-run | kubectl set selector --local -f - 'environment=qa' -o yaml | kubectl create -f -
```
```
kubectl create service -o yaml --dry-run
```
创建service 配置文件，并将结果输出在yaml文件中，而不是返回给Kubernetes API server 中

```
kubectl set selector --local -f - -o yaml
```
command 从stdin读取配置文件，并且写和更新配置文件输出到yaml文件

```
kubectl create -f - 
```
通过stdin信息创建Object对象


### --edit before create Object

在Object创建之前，可以使用 --edit强制修改Object filed信息
```
kubectl create service clusterip my-svc --clusterip="None" -o yaml --dry-run > /tmp/srv.yaml
kubectl create --edit -f /tmp/srv.yaml
```

```
kubectl create service
```
创建service配置信息，并且保存在yml文件中

```
kubectl create --edit
```
在创建对象之前首先打开配置文件。



#  配置文件命令式

## create
```
kubectl create -f <filename|url>
```

## update
通过 配置文件更新对象，会删除配置文件之外所有的属性字段，一定要注意。
```
kubectl replace -f <filename|url>
```

## delete

```
kubectl delete -f <filename|url>
```

## view
查看配置文件中指定的Object属性信息

当 update Object时，配置文件并不会更新。











# kubectl

1、查看所有节点状态
```
kubectl get pod --all-namespaces
```



2、查看某个节点状态
```
kubectl describe pod calico-node-9fxnm -n kube-system
```

3、查看集群信息
```
kubectl cluster-info
```

4、查看集群更 详细信息
```
kubectl cluster-info dump 
```

5、查看 rc，namespace
```
kubectl get rc,namespace 
```

6、查看pod和svc(和service一样)
```
kubectl get pods,svc 
```

7、创建文件内定义的resource
```
kubectl create -f filename 
```

8、用于对已有资源进行更新、替换
```
kubectl replace -f filename 
```

