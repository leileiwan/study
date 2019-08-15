[toc]
# 1. ldd 查看程序依赖
```
ldd exe
```
```
root@wanlei:~/C_workspace# ldd calc
	linux-vdso.so.1 =>  (0x00007ffe271df000)
	libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007fc603f0f000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fc603b45000)
	libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007fc60383c000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fc604291000)
	libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007fc603626000)

```
* libstdc++.so.6程序依赖的库
* /lib/x86_64-linux-gnu/libc.so.6 系统提供程序库
* 0x00007ffe271df000 加入库的开始地址
