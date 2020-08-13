# 1. deleting namespace stuck at "Terminating" state
## 1.1 问题描述
* delete namespce 一直处于Terminating
* 添加force无效

## 1.2 解决
* https://github.com/kubernetes/kubernetes/issues/60807

* 最终脚本：https://github.com/thyarles/knsk

## 1.3 问题
这样是比较危险的，因为发现删掉namespace之后，namespace资源并没有被删除