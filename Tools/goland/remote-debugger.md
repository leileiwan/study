# goland 远程调试工具设置
* 参考: https://www.jetbrains.com/help/go/attach-to-running-go-processes-with-debugger.html

# 1. 核心步骤
## 1. 远程编译程序
```
go build main.go
```

## 2. 远程段启动服务
```
https://github.com/go-delve/delve/blob/master/Documentation/installation/linux/install.md

dlv --listen=:8999 --headless=true --api-version=2 exec ./main
```
* https://github.com/go-delve/delve/blob/master/Documentation/installation/linux/install.md
* 确保端口是可以访问成功的


结果如下
```
root@k8s-wanlei:~/go/src/documentation-code-examples# dlv --listen=:8999 --headless=true --api-version=2 exec ./main
API server listening at: [::]:8999
```

## 3. 本地goland 配置run config

菜单中点击 "Run"-->"Edit Configurations"-->"左侧+号"

添加配置事注意ip和端口

## 4. 运行
选择debugger 运行


# 2 特点
* 每次运行都必须在远程启动dlv 服务



