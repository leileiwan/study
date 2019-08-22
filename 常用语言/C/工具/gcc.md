[toc]

# 1. 背景
* 原来gcc是用来编译C，g++是用来编译C++的。但后来gcc集成了很多其它编译器，所以现在gcc是一组编译器集合，不限于c。
* 一般我们编译C程序任然使用gcc

```
gcc hello.c -o hello
```
# 2. gdb

## 2.1 调试使用的基本命令

* debug 编译程序
```
gcc -g hello.c -o hello
```

* gdb启动程序
```
gdb ./hello
```
* 设置断点
```
(gdb) break main
Breakpoint 1 at 0x40052e: file hello.c, line 3.
```
* 运行程序
```
(gdb) break main
Breakpoint 1 at 0x40052e: file hello.c, line 3.

```
* 停止程序运行
```
q
```

## 2.2 gdb 常用的调试命令

* c (continue) 继续执行，到下一个断电
* n (next) 单步跟踪，不会进入函数体
* s (step) 单步调试，会进入到函数体

* until 用于跳出循环体
* until row 跳到第row 行

* clear row 清楚掉第row行代码
* delete breakpoints 清除掉所有断点

* print var 打印变量内容
* info b 查看断点设置情况（所有设置断点）
* info locals 显示当前堆栈页的所有变量

* finish 运行完毕当前函数，并打印函数返回时的堆栈地址和返回值及参数值等

* bt 当前堆栈列表

* whatis 查看变量或者函数类型
* layout src 显示源码，可是化调试


# 2.3 gcc常用的5个参数

* -a 重命名可执行文件
* -g 添加调试信息
* -c 值编译文件，不做链接
```
root@wanlei:~/C_workspace# gcc -c hello.c 
root@wanlei:~/C_workspace# ls
hello.c  hello.o
```
* -S 生成汇编代码
```
root@wanlei:~/C_workspace# gcc -S hello.c
root@wanlei:~/C_workspace# ls
hello.c  hello.o  hello.s
```
* -E 对编译源码进行预处理
    比如讲#include包含起来，讲define替换掉




# 3 Makefile 基本模式

## 3.1 安装make
```
apt-get install make
```

## 3.2 最简单的make规则
```
root@wanlei:~/C_workspace# cat makefile 
hello: hello.c
	gcc hello.c -o hello
```
* hello 使我们最终生成的文件，hello.c是我们依赖文件
* gcc 这行叫做make规则，make规则前面必须是tab，不能是空格
* 文件必须被命名为makefile或者Makefile
* 在makefile当前目录下运行make，就能生成对应文件

## 3.3 复杂一点的makefile

```
root@wanlei:~/C_workspace# cat calc.h
#ifndef __MAKEFILE_CALC_H__
#define __MAKEFILE_CALC_H__

class Calc{
	public: int add(int a,int b);
};
#endif
```

```
root@wanlei:~/C_workspace# cat calc.cpp 
#include "calc.h"

int Calc::add(int a,int b){
	return a+b;
}
```

```
root@wanlei:~/C_workspace# cat main.cpp 
#include "iostream"
#include "calc.h"
using namespace std;

int main(){
	Calc c;
	cout << c.add(1,2);

	return 0;
}
```

* makefile1
```
root@wanlei:~/C_workspace# cat makefile 
calc: main.o calc.o
	g++ -o calc main.o calc.o
main.o:main.cpp calc.h
	g++ -c main.cpp
calc.o:calc.cpp calc.h
	g++ -c calc.cpp

```
* makefile2
```
root@wanlei:~/C_workspace# cat makefile 
calc: main.o calc.o
	g++ -o calc main.o calc.o
main.o:calc.h
calc.o:calc.h
```

* 如果在大型系统中，文件依赖是意见非常麻烦事情。如下命令可以查看依赖关系
    ```
    g++ -MM main.cpp 
    ```
    其它编译器可能使用参数-M


## 3.4 不复杂的makefile
* make有一定的自动推到能力，这样可以简化我们的makefile。
* 但是makefile默认是使用gcc编译器,因此我们需要指定我们的编译器
    在头文件指定CC=g++
* 有时候需要使用一定的清楚工作
    ```
    clean:
        rm *.o
    ```
    或者
    ```
    .PHONY: clean
    clean:
        -rm *.o
    ```



最终代码如下。执行清楚工作，还是需要单独的执行make clean命令
```
root@wanlei:~/C_workspace# cat makefile 
CC=g++
calc: main.o calc.o
main.o calc.o: calc.h

.PHONY: clean
clean:
	-rm *.o
```
* 推荐使用下面一种清楚命令（.POHONY方式）。
    * .PHONY是makefile关键字，标识clean是一个伪目标。
    * rm 前面"-"表示在rm出现问题时先不要管
    * clean 并不是我们要执行的文件，为目标不是文件，更像是一个label


## 3.5 makefile自动生成
    makefile 可使用cmake自动生成。参考<<cmake入门实战>>



执行过程如下
```
root@wanlei:~/C_workspace# make
g++    -c -o calc.o calc.cpp
g++    -c -o main.o main.cpp
g++   calc.o main.o   -o calc
root@wanlei:~/C_workspace# ls
calc  calc.cpp  calc.h  calc.o  main.cpp  main.o  makefile
root@wanlei:~/C_workspace# make clean
rm *.o
root@wanlei:~/C_workspace# ls
calc  calc.cpp  calc.h  main.cpp  makefile
```