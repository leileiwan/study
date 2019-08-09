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
WINEDEBUG=fixme-shell
```
* 打开trace:shell日志
```
WINEDEBUG=trace+shell
```