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


## 1.3 winecfg--配置wine运行环境
### 1.3.1 开启隔离环境
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

### 1.3.2 关闭创建的隔离环境
Ctrl+C 可以停掉容器，如果想杀死容器中的所有进程，可以使用以下命令
```
WINEPREFIX=~/Desktop/win_RUN/ wineserver -k
```

## 1.3.3 winecfg添加程序库文件

在使用wine安装文件时，可能会缺少XX.dll类似的系统文件，这时候可以使用winecfg去添加dll。一般选择“原装先与内建”
![2019-08-09-19-23-24.png](./images/2019-08-09-19-23-24.png)


## 1.4 winetricks 钻床
* 如果说winecfg是一把螺丝刀那么winetricks就是钻床，它们各有所长，但是winetricks是一个更强大工具。

* winecfg 可以改变wine本身设置，而winetricks可以让你改造实际的Windows层，他可以让你装Windows重要的系统组件，比如.dll文件和系统字体，还允许你修改Windows注册表信息。还有任务管理器、卸载工具、文件浏览器。

### 1.4.1 安装winetricks
winetricks和winecfg不同，winecfg是集成在wine中的，而winetricks实际上是一个脚本工具，我们可以使用专门的工作目录去存放所有的工具。

由于winetricks是一个脚本，我们直接下载就好
```
wget https://raw.githubusercontent.com/Winetricks/winetricks/master/src/winetricks

chmod +x winetricks
```
### 1.4.2 安装dll
* 我们使用winetricks最多的任然是安装dll和Windows组件。
* 不带参数启动winetricks程序后就会有一系列图形界面帮组你去安装，比较傻瓜。
![2019-08-09-19-49-32.png](./images/2019-08-09-19-49-32.png)



