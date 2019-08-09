[toc]

# 1. WINEDEBUG初步

## 1.1 Wine运行日志理解

```
fixme:shell:IShellBrowser_fnOnViewWindowActive stub, 0x15b4a0 (0x175f68)
err:shell:ICommDlgBrowser3_fnOnDefaultCommand Failed to get IDataObject.
fixme:shell:IShellBrowser_fnOnViewWindowActive stub, 0x15b4a0 (0x175f68)
fixme:shell:IShellBrowser_fnOnViewWindowActive stub, 0x15b4a0 (0x175f68)
fixme:shell:ShellView_OnNotify LVN_KEYDOWN key=0x00000090
fixme:shell:ShellView_OnNotify LVN_KEYDOWN key=0x00000011
```

* 上述例子中fixme成为class，shell成为channel
* class 分为err warn fixme trace四种
* channels有400多宗

## 1.2 运行程序的命令格式
```
WINEDEBUG=[class][+/-]channel[,[class2][+/-][channel2]]
```

### 1.2.1 例子
* 关闭fixme:shell日志
```
WINEDEBUG=fixme-shell wine explorer
```
* 打开trace:shell日志
```
WINEDEBUG=trace+shell wine explorer
```
* 打开所有ddl警告和heap信息
```
WINEDEBUG=warn+shell,+heap wine explorer
```


## 1.3 配置wine运行环境
主要是创建运行容器隔离环境。通过WINEPREFIX与winecfg命令，可以使用独立C盘和注册表配置
* 创建文件夹
    ```
    mkdir -p ~/Desktop/win_RUN/
    ```
* 搭建容器环境
    ```
    WINEPREFIX=~/Desktop/win_RUN/ winecfg
    ```
* 在隔离环境中运行程序
    ```
    WINEPREFIX=~/Desktop/win_RUN/ wine SourceInsight_V3.5.83.0_Setup.exe 
    ```
* 安装玩软件后，发现软件属性任然需要wine来启动（env WINEPREFIX="/home/wanlei/Desktop/win_RUN" wine C:\\Program\ Files\ \(x86\)\\Source\ Insight\ 3\\Insight3.exe ）

## 1.4 关闭创建的隔离环境
Ctrl+C 可以停掉容器，如果想杀死容器中的所有进程，可以使用以下命令
```
WINEPREFIX=~/Desktop/win_RUN/ wineserver -k
```